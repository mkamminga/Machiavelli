//
//  main.cpp
//  socketexample
//
//  Created by Bob Polis on 16/09/14.
//  Copyright (c) 2014 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include <thread>
#include <iostream>
#include <exception>
#include <memory>
#include <utility>
#include <vector>

using namespace std;

#include "Socket.h"
#include "Sync_queue.h"
#include "ClientCommand.h"
#include "Player.hpp"
#include "Controllers/GameController.hpp"

namespace machiavelli {
    const int tcp_port {1080};
    const string prompt {"machiavelli> "};
}



void handle_client(shared_ptr<Socket> client, GameController* gameController) // this function runs in a separate thread
{
    try {
        client->write("Welcome to Server 1.0! To quit, type 'quit'.\r\n");
		client->write("What's your name?\r\n");
        client->write(machiavelli::prompt);
		string name {client->readline()};
		shared_ptr<Player> player {new Player {name}};
		*client << "Welcome, " << name << ", have fun playing our game!\r\n" << machiavelli::prompt;
        
        gameController->addPlayer(player, client);
        
        if (gameController->canStart()) {
            client->write("You have been proclaimed king!.\r\n");
            gameController->start();

            while (!gameController->isGameOver()) { // game loop
                try {
                    //Round start, 
                    gameController->startRound();
                    // ->
                    // 2. Character handle
                    // <-
                    gameController->callCharcaters();
                    cerr << '[' << client->get_dotted_ip() << " (" << client->get_socket() << ") " << player->get_name() << "] "  << '\n';
                    
                } catch (const exception& ex) {
                    cerr << "*** exception in client handler thread for player " << player->get_name() << ": " << ex.what() << '\n';
                    if (client->is_open()) {
                        *client << "ERROR: " << ex.what() << "\r\n";
                    }
                } catch (...) {
                    cerr << "*** exception in client handler thread for player " << player->get_name() << '\n';
                    if (client->is_open()) {
                        client->write("ERROR: something went wrong during handling of your request. Sorry!\r\n");
                    }
                }
            }

        } else {
            //wait for all players
            client->write("Waiting for other player to join.\r\n");
        }
	} catch (...) {
        gameController->quit();
        cerr << "handle_client crashed\n";
    }
}

int main(int argc, const char * argv[])
{
    GameController gameController;
    // keep client threads here, so we don't need to detach them
    vector<thread> handlers;
    
	// create a server socket
	ServerSocket server {machiavelli::tcp_port};
    
	while (true) {
		try {
			while (true) {
				// wait for connection from client; will create new socket
				cerr << "server listening" << '\n';
				unique_ptr<Socket> client {server.accept()};
                
                if (!gameController.hasStarted()){
                    // communicate with client over new socket in separate thread
                    thread handler {handle_client, move(client), &gameController};
                    handlers.push_back(move(handler));
                } else if (gameController.isGameOver()) {
                    //exit
                    return 0;
                } else {
                    client->write("I'm so sorry, the maximum amount of players has already been reached!");
                    client->close();
                }
			}
		} catch (const exception& ex) {
			cerr << ex.what() << ", resuming..." << '\n';
        } catch (...) {
            cerr << "problems, problems, but: keep calm and carry on!\n";
        }
        
	}
    
    return 0;
}

