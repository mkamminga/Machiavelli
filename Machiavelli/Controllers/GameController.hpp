//
//  GameController.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef GameController_hpp
#define GameController_hpp

#include <stdio.h>
#include <map>
#include <string>
#include "../Process/MainProcessor.hpp"
#include "../Player.hpp"
#include "../Models/Game.hpp"
#include "../Process/MainProcessor.hpp"

class GameController {
public:
    GameController();
    
    void addPlayer(std::shared_ptr<Player> player);
    bool start();
    bool isGameOver();
    bool hasStarted();
    bool canStart();
    void handleCommand (const std::string& cmd);
private:
    void setupCards();
    void setupCharacters();
    void setupProcessors();
    
    std::shared_ptr<Game> game = nullptr;
    std::shared_ptr<Player> firstPlayer = nullptr;
    std::shared_ptr<Player> secondPlayer = nullptr;
    
    std::map<int, std::unique_ptr<MainProcessor>> processors;

    bool gameOver = false;
    bool gameStarted = false;
    
    
};

#endif /* GameController_hpp */
