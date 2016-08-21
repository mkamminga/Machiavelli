//
//  CondottieriProcessor.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "CondottieriProcessor.hpp"

void CondottieriProcessor::setupBinds(std::string &message){
    MainProcessor::setupBinds(message);
    binds["use special"] = [this, &message]() {
        handleSpecialFeature(message);
    };
}

void CondottieriProcessor::handleSpecialFeature(std::string &broadcastMessage) {
    receiveCoins(broadcastMessage);
    handleDistroyFromPlayer(broadcastMessage);
    
    options.erase("use special");
}

void CondottieriProcessor::receiveCoins (std::string &broadcastMessage) {
    int numberRecived = handlePointsForCardColours(RED);
    
    if (numberRecived > 0) {
        client->write("You have recieved "+ std::to_string(numberRecived) +" coins..");
    } else {
        client->write("No cards of the colour red were found!");
    }
}

void CondottieriProcessor::handleDistroyFromPlayer(std::string& broadcastMessage){
    while (true){
        client->write("From which player would you like to destory:\n");
        int playerNumber = roundView.displayPlayersAndAskPlayer(client, players);
        auto otherPlayer = players.at(playerNumber).first;
        auto built = otherPlayer->built();
        if (built.size() > 0){
            
        } else {
            client->write("No can do. Player has no built cards!\n");
        }
        
        if (!roundView.willContinue(client)) {
            break;
        }
    }
}