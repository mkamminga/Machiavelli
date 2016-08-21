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
    int numberRecived = handlePointsForCardColours(RED);
    
    if (numberRecived > 0) {
        client->write("You have recieved "+ std::to_string(numberRecived) +" coins..");
    } else {
        client->write("No cards of the colour red were found!");
    }
    
    options.erase("use special");
}