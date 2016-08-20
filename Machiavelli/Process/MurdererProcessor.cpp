//
//  MurdererProcessor.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "MurdererProcessor.hpp"
#include <string>


void MurdererProcessor::handleSpecialFeature(std::shared_ptr<Round> round, std::shared_ptr<Player> player, std::shared_ptr<ConsoleView> client, std::string& broadcastMessage) {
    
    client->write("Who would you like to murder?\n");

    int chosenItem = roundView.displayCharactersAndAskCharacter(client, round->getCharacters(), 1);
    
    auto character = round->getCharacterByType(chosenItem);
    
    if (character->getPlayer()){
        character->getPlayer()->remove_character(character);
    }
    
    broadcastMessage = "\n** character "+ character->getname() + " has been murdered! **\n";
}