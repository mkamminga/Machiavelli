//
//  MerchantProcessor.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "MerchantProcessor.hpp"

void MerchantProcessor::setupBinds(std::string &message){
    MainProcessor::setupBinds(message);
    binds["use special"] = [this, &message]() {
        handleSpecialFeature(message);
    };
}

void MerchantProcessor::askMainQuestion(std::string& message) {
    int num = round->getGame()->takeCoins(1);
    player->putCoins(num);
    client->write("You have recived coins" + std::to_string(num)+ "\n");
    roundView.broadcastToPlayers(players, "Player "+ player->get_name() + " has received "+ std::to_string(num) + " coins.\n" );
    MainProcessor::askMainQuestion(message);
}

void MerchantProcessor::handleSpecialFeature(std::string &broadcastMessage) {
    int numberRecived = handlePointsForCardColours(GREEN);
    
    if (numberRecived > 0) {
        client->write("You have recieved "+ std::to_string(numberRecived) +" coins..");
    } else {
        client->write("No cards of the colour green were found!");
    }
    
    options.erase("use special");
}