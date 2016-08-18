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
    client->write("[1] => thief\n");
    client->write("[2] => wizzard\n");
    client->write("[3] => preacher\n");
    client->write("[4] => merchant\n");
    client->write("[5] => build master\n");
    client->write("[6] => condottieri\n");
    client->write(">> ");
    
    std::string::size_type sz;
    while (true) {
        std::string cmd = client->readline();
        int chosenItem = std::stoi (cmd,&sz);
    
        if (chosenItem > 0 && chosenItem <= 6) {
            auto character = round->getCharacterByType(chosenItem);
            
            if (character->getPlayer()){
                character->getPlayer()->remove_character(character);
            }
            
            broadcastMessage = "\n** character "+ character->getname() + " has been murdered! **\n";
            break;
        }
    }
}