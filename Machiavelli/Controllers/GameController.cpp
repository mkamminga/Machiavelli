//
//  GameController.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 31-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "GameController.hpp"
#include "../Models/BaseCharacter.hpp"
#include "../Process/MurdererProcessor.hpp"
#include "../Process/ThiefProcessor.hpp"
#include "../Process/WizzardProcessor.hpp"
#include "../Process/PreacherProcessor.hpp"
#include "../Process/MerchantProcessor.hpp"
#include "../Process/BuildmasterProcessor.hpp"
#include "../Process/CondottieriProcessor.hpp"

GameController::GameController() {
    game = std::shared_ptr<Game>(new Game);
};

void GameController::addPlayer(std::shared_ptr<Player> player){
    if (!firstPlayer){
        firstPlayer = player;
    } else if (!secondPlayer) {
        secondPlayer = player;
    }
}

bool GameController::start(){
    if (!gameStarted){
        
        setupCards();
        setupCharacters();
        
        gameOver = false;
        gameStarted = true;
        
        return true;
    }
    
    return false;
}

bool GameController::isGameOver() {
    return (gameStarted && gameOver);
}

void GameController::setupCards() {
    //TODO implement import to replace hardcoded setup
    game->addCard(std::shared_ptr<BaseCard>(new BaseCard(YELLOW, 2)));
    game->addCard(std::shared_ptr<BaseCard>(new BaseCard(RED, 7)));
    game->addCard(std::shared_ptr<BaseCard>(new BaseCard(BLUE, 2)));
    game->addCard(std::shared_ptr<BaseCard>(new BaseCard(RED, 4)));
    game->addCard(std::shared_ptr<BaseCard>(new BaseCard(PURPLE, 6)));
    game->addCard(std::shared_ptr<BaseCard>(new BaseCard(YELLOW, 2)));
}

void GameController::setupCharacters() {
    //TODO create and distribute characters
}

void GameController::setupProcessors() {
    //TODO implement import to replace hardcoded setup
    processors[MURDERER]            = std::unique_ptr<MainProcessor>(new MurdererProcessor);
    processors[THIEF]               = std::unique_ptr<MainProcessor>(new ThiefProcessor);
    processors[WIZZARD]             = std::unique_ptr<MainProcessor>(new WizzardProcessor);
    processors[PREACHER]            = std::unique_ptr<MainProcessor>(new PreacherProcessor);
    processors[MERCHANT]            = std::unique_ptr<MainProcessor>(new MerchantProcessor);
    processors[MASTER_BUILER]       = std::unique_ptr<MainProcessor>(new BuildmasterProcessor);
    processors[CONDOTTIERI]         = std::unique_ptr<MainProcessor>(new CondottieriProcessor);
}

bool GameController::hasStarted() {
    return gameStarted;
}

bool GameController::canStart() {
    return firstPlayer && secondPlayer;
}

void GameController::handleCommand (const std::string& cmd) {
    
}


