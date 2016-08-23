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

#include "../Views/ConsoleView.hpp"

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
        for (auto clientPlayer : players){
            auto client = clientPlayer.second;
            
            if (client && client->is_open()) {
                client->close();
            }
        }
    }
    void addPlayer(std::shared_ptr<Player> player, std::shared_ptr<ConsoleView> client);
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
    void resetPlayerCharacters();
    void devideCardsToPlayers(std::vector<std::shared_ptr<BaseCharacter>>& characters);
    std::shared_ptr<BaseCharacter> removeAndChoseCharacter(const std::string& question, std::shared_ptr<ConsoleView> client, std::vector<std::shared_ptr<BaseCharacter>>& characters);
    std::shared_ptr<Player> determinWinner ();
    
    std::shared_ptr<Game> game = nullptr;
    std::map<int, std::unique_ptr<MainProcessor>> processors;
    std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>> players;
    std::vector<std::shared_ptr<BaseCharacter>> characters;
    std::shared_ptr<Round> currentRound = nullptr;
    bool gameOver = false;
    bool gameStarted = false;
    RoundView roundView;
    
};

#endif /* GameController_hpp */
