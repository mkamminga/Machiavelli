//
//  MainProcessor.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef MainProcessor_hpp
#define MainProcessor_hpp

#include <stdio.h>

#include "../Models/Round.hpp"
#include "../Socket.h"
#include "Player.hpp"

class MainProcessor {
public:
    MainProcessor () {
        allowedCommands.push_back("r");
        allowedCommands.push_back("s");
        allowedCommands.push_back("b");
    }
    virtual void handle(std::shared_ptr<Round> round, std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>>> &players, std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>>& playerClient);
private:
    
protected:
    virtual void handleSpecialFeature()  = 0;
    void askMainQuestion(std::shared_ptr<Round> round, std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>>> &players, std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>>& playerClient);
    void handleIncomePhase(std::shared_ptr<Round> round, std::shared_ptr<Player> player, std::shared_ptr<Socket> client);
    void handlePickCardPhase(std::shared_ptr<Round> round, std::shared_ptr<Player> player, std::shared_ptr<Socket> client, std::string& broadcastMessage);
    void handleBuildPhase();
    void broadcastToPlayers(std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>>> &players, const std::string& message);
    
    std::vector<std::string> allowedCommands;
};

#endif /* MainProcessor_hpp */
