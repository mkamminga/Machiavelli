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
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

#include "../Socket.h"
#include "../Sync_queue.h"
#include "../ClientCommand.h"

#include "../Process/MainProcessor.hpp"
#include "../Player.hpp"
#include "../Models/Game.hpp"
#include "../Process/MainProcessor.hpp"
#include "../Models/Round.hpp"


class GameController {
public:
    GameController();
    ~GameController(){
        quit();
    }
    void addPlayer(std::shared_ptr<Player> player, std::shared_ptr<Socket> client);
    bool start();
    bool isGameOver();
    bool hasStarted();
    bool canStart();
    void startRound();
    void callCharcaters();
    void quit();
    
private:
    void setupCards();
    void setupCharacters();
    void setupProcessors();
    std::shared_ptr<BaseCharacter> removeChoseCharacter(const std::string& question, std::shared_ptr<Socket> client, std::vector<std::shared_ptr<BaseCharacter>>& characters);
    
    std::shared_ptr<Game> game = nullptr;
    std::map<int, std::unique_ptr<MainProcessor>> processors;
    std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>>> players;
    std::vector<std::shared_ptr<BaseCharacter>> characters;
    bool gameOver = false;
    bool gameStarted = false;
    
};

#endif /* GameController_hpp */
