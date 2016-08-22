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
    
    if (player->getCoins() > 0) {
        handleDistroyFromPlayer(broadcastMessage);
    } else {
        client->write("You have not enuogh coins to destroy any laidout cards..\n");
    }
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
            
            auto preacher = round->getCharacterByType(PREACHER);
            if (!preacher->isMurdered() && preacher->getPlayer() != otherPlayer) {
                int cardNumber = roundView.displayCardsAndAskCard(client, built);
                auto card = built.at(cardNumber);

                if ((card->getPoints() - 1)  <= player->getCoins()) {
                    otherPlayer->removeCard(card);
                    round->getGame()->addToLaidout(card);
                } else {
                    client->write("No can do. You cannot build card. To few pointd..\n");
                }
            } else {
                client->write("Player is protected by preacher");
            }
            
        } else {
            client->write("No can do. Player has no built cards!\n");
        }
        
        if (!roundView.willContinue(client)) {
            break;
        }
    }
}