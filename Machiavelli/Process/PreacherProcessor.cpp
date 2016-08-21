//
//  PreacherProcessor.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "PreacherProcessor.hpp"

void PreacherProcessor::setupBinds(std::string &message){
    MainProcessor::setupBinds(message);
    binds["use special"] = [this, &message]() {
        handleSpecialFeature(message);
    };
}

void PreacherProcessor::handleSpecialFeature(std::string &broadcastMessage) {
    int numberRecived = handlePointsForCardColours(BLUE);
    
    if (numberRecived > 0) {
        client->write("You have recieved "+ std::to_string(numberRecived) +" coins..");
    } else {
        client->write("No cards of the colour blue were found!");
    }
    
    options.erase("use special");
}

