//
//  MurdererProcessor.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "MurdererProcessor.hpp"
#include <string>

void MurdererProcessor::setupBinds(std::string &message){
    MainProcessor::setupBinds(message);
    binds["use special"] = [this, &message]() {
        handleSpecialFeature(message);
    };
    
    options["use special"] = "** with this option, you can kill anyone (except yourself).";
}

void MurdererProcessor::handleSpecialFeature(std::string& broadcastMessage) {
    
    client->write("Who would you like to murder?\n");

    int chosenItem = roundView.displayCharactersAndAskCharacter(client, round->getCharacters(), 1);
    
    auto character = round->getCharacterByType(chosenItem);
    character->setMurdered();
    
    broadcastMessage = "\n** character "+ character->getname() + " has been murdered! **\n";
    options.erase("use special");
}