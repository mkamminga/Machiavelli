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

#include "../Views/ConsoleView.hpp"
#include "../Views/RoundView.hpp"

#include "../Models/Round.hpp"
#include "Player.hpp"

class MainProcessor {
public:
    virtual void handle(std::shared_ptr<Round> round, std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>> &players, std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>& playerClient);
private:
    
protected:
    //virtual void handleSpecialFeature()  = 0;
    void askMainQuestion(std::string& message);
    virtual void setupBinds(std::string& message);
    void handleIncomePhase(std::string& broadcastMessage);
    void handlePickCardPhase(std::string& broadcastMessage);
    void handleBuildPhase(std::string& broadcastMessage);
    virtual void handleSpecialFeature(std::string& broadcastMessage) {}
    
    std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>> players;
    RoundView roundView;
    std::map<std::string, std::string> options;
    std::map<std::string, std::function<void()>> binds;
    std::shared_ptr<Round> round = nullptr;
    std::shared_ptr<Player> player = nullptr;
    std::shared_ptr<ConsoleView> client = nullptr;
};

#endif /* MainProcessor_hpp */
