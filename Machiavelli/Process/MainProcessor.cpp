//
//  MainProcessor.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "MainProcessor.hpp"
#include <map>

void MainProcessor::handle(std::shared_ptr<Round> round,std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket> > > &players, std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>>& playerClient){
    //Ask main question, would you like to pick cards or take money
    askMainQuestion(players, playerClient);
}

void MainProcessor::askMainQuestion (std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>>> &players, std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>>& playerClient) {
    //ask, Would you like to receive to coins or two cards?
    for (auto otherPlayerClient : players) {
        otherPlayerClient.second->write("Waiting for player: "+ playerClient.first->get_name() + "!\n");
    }
    
    auto client = playerClient.second;
    client->write("Would you like to do?\nType the letters after the ':'\n\n");
    
    std::map<std::string, std::string> options;
    options["receive coins"] = "recive 2 coins by command: receive coins";
    options["receive cards"] = "recive 2 cards with command: receive cards";
    options["use special"]   = "use special feature with command: use special";
    options["build"]         = "build by using command: build";
    options["pass"]          = "pass with command: pass";
    
    while (options.size() > 0){
        for (auto option: options) {
            client->write(option.second + "\n" );
        }
        
        std::string cmd = "";
        while (true){
            cmd = client->readline();
            if (std::find(allowedCommands.begin(), allowedCommands.end(), cmd) != allowedCommands.end()) {
                break;
            }
        }
        
        if (cmd == "receive coins") {
            
        } else if (cmd == "pass") {
            break;
        }
    }
}