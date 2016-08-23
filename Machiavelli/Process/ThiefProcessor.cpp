//
//  ThiefProcessor.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "ThiefProcessor.hpp"

void ThiefProcessor::setupBinds(std::string &message){
    MainProcessor::setupBinds(message);
    binds["use special"] = [this, &message]() {
        handleSpecialFeature(message);
    };
    
    options["use special"] = "** with this option you can steal from any character (even murdered characters)..";
}

void ThiefProcessor::handleSpecialFeature(std::string& broadcastMessage) {
    
    client->write("Who would you like to steal from?\n");
    
    int chosenItem = roundView.displayCharactersAndAskCharacter(client, round->getCharacters(), 2);
    
    auto character = round->getCharacterByType(chosenItem);
    
    round->addCallback(chosenItem, [this, character]() {
        int currentAmount = player->getCoins();
        character->giveCoinsToPlayer(player);
        
        client->write("You have stolen " + std::to_string(player->getCoins() - currentAmount) + " coins from characater " + character->getname() + ".\n");
        client->write("Your total is: "+ std::to_string(player->getCoins()) +"\n\n");
    });
    
    broadcastMessage = "\n** thief will steal from "+ character->getname() + " **\n";
    options.erase("use special");
}