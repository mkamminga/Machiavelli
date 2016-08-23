//
//  BuildmasterProcessor.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "BuildmasterProcessor.hpp"

void BuildmasterProcessor::setupBinds(std::string &message){
    MainProcessor::setupBinds(message);
    binds["use special"] = [this, &message]() {
        handleSpecialFeature(message);
    };
    
    options["use special"]              = "** alias of build: you can build upto 3 buildings";
    options["build"]                    =  "you can build upto 3 buildings";
}

void BuildmasterProcessor::handlePickCardPhase(std::string& broadcastMessage) {
    std::vector<std::shared_ptr<BaseCard>> cards = round->getGame()->takeCards(2);
    
    client->write("Cards added: \n");
    roundView.displayCards(client, cards);
    
    for (auto card : cards){
        player->add_card(card);
    }
    
    broadcastMessage = "** Player "+ player->get_name() + " has taken two cards. **";
    
    options.erase("receive coins");
    options.erase("receive cards");

}

void BuildmasterProcessor::handleBuildPhase(std::string& broadcastMessage) {
    MainProcessor::handleBuildPhase(broadcastMessage);
    
    if (options.find("build") == options.end()) {
        options.erase("use special");
    }
}

void BuildmasterProcessor::handleSpecialFeature(std::string& broadcastMessage) {
    handleBuildPhase(broadcastMessage);
}