//
//  GameController.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 31-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//
#include <algorithm>    // std::copy_if, std::distance
#include "GameController.hpp"
#include "../Models/BaseCharacter.hpp"
#include "../Process/MurdererProcessor.hpp"
#include "../Process/ThiefProcessor.hpp"
#include "../Process/WizzardProcessor.hpp"
#include "../Process/PreacherProcessor.hpp"
#include "../Process/MerchantProcessor.hpp"
#include "../Process/BuildmasterProcessor.hpp"
#include "../Process/CondottieriProcessor.hpp"
#include "../ClientCommand.h"

GameController::GameController() {
    game = std::shared_ptr<Game>(new Game);
    setupCards();
    setupCharacters();
    setupProcessors();
};

void GameController::addPlayer(std::shared_ptr<Player> player, std::shared_ptr<Socket> client){
    if (!hasStarted()){
        players.push_back(make_pair(player, client));
    }
}

bool GameController::start(){
    if (!gameStarted){
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
    characters.push_back(std::shared_ptr<BaseCharacter>(new BaseCharacter(MURDERER, "Murderer")));
    characters.push_back(std::shared_ptr<BaseCharacter>(new BaseCharacter(THIEF, "Thief")));
    characters.push_back(std::shared_ptr<BaseCharacter>(new BaseCharacter(WIZZARD, "Wizzard")));
    characters.push_back(std::shared_ptr<BaseCharacter>(new BaseCharacter(PREACHER, "Preacher")));
    characters.push_back(std::shared_ptr<BaseCharacter>(new BaseCharacter(MERCHANT, "Merchant")));
    characters.push_back(std::shared_ptr<BaseCharacter>(new BaseCharacter(MASTER_BUILER, "Master builder")));
    characters.push_back(std::shared_ptr<BaseCharacter>(new BaseCharacter(CONDOTTIERI, "Condottieri")));
}

void GameController::setupProcessors() {
    processors[MURDERER]            = std::unique_ptr<MainProcessor>(new MurdererProcessor);
    /*processors[THIEF]               = std::unique_ptr<MainProcessor>(new ThiefProcessor);
    processors[WIZZARD]             = std::unique_ptr<MainProcessor>(new WizzardProcessor);
    processors[PREACHER]            = std::unique_ptr<MainProcessor>(new PreacherProcessor);
    processors[MERCHANT]            = std::unique_ptr<MainProcessor>(new MerchantProcessor);
    processors[MASTER_BUILER]       = std::unique_ptr<MainProcessor>(new BuildmasterProcessor);
    processors[CONDOTTIERI]         = std::unique_ptr<MainProcessor>(new CondottieriProcessor);*/
}

bool GameController::hasStarted() {
    return gameStarted;
}

bool GameController::canStart() {
    return players.size() == 2;
}

void GameController::startRound(){
    //copy characters
    auto roundCharacters = characters;
    std::random_shuffle ( roundCharacters.begin(), roundCharacters.end() );
    //reset charcaters, unbind all connections
    resetPlayerCharacters();
    //present cards of which in two turn both players can choose and throw away one card
    devideCardsToPlayers(roundCharacters);
    //set a new object for the new round
    currentRound = std::shared_ptr<Round>(new Round(game));
}

void GameController::resetPlayerCharacters () {
    //reset the connected characters connection, and vc, from the players
    for (auto playerClient : players) {
        auto player = playerClient.first;
        
        const std::vector<std::shared_ptr<BaseCharacter>> playerCharacters = player->get_characters();
        for (auto character : playerCharacters){
            player->remove_character(character);
        }
    }
}

void GameController::devideCardsToPlayers (std::vector<std::shared_ptr<BaseCharacter>>& roundCharacters) {
    while(roundCharacters.size() > 1){
        for (auto playerClient : players) {
            auto player = playerClient.first;
            auto client = playerClient.second;
            int i = 0;
            for (auto listCharacter : roundCharacters){
                client->write("["+ std::to_string(i) +"] => "+ listCharacter->getname() + ".\r\n");
                i++;
            }
            
            auto character = removeAndChoseCharacter("Which characater would you like to keep?\n", client, roundCharacters);
            player->add_character(character);
            character->setPlayer(player);
            
            client->write("Character '"+ character->getname() +"' added!\n");
            
            if (roundCharacters.size() < 6 && roundCharacters.size() > 1){
                character = removeAndChoseCharacter("Which charcater would you like to throw away?", client, roundCharacters);
                client->write("Character '"+ character->getname() +"' thrown away!\n");
            }
        }
    }
}

std::shared_ptr<BaseCharacter> GameController::removeAndChoseCharacter(const std::string& question, std::shared_ptr<Socket> client, std::vector<std::shared_ptr<BaseCharacter>>& characters) {
    std::string::size_type sz;   // alias of size_t
    int chosenCard = -1;
    long size = characters.size();
    //choose card to keep
    while(chosenCard < 0 || chosenCard >= size){
        client->write(question + "\n");
        std::string cardToAdd       = client->readline();
        chosenCard = std::stoi (cardToAdd,&sz);
    }
    
    auto character = characters.at(chosenCard);
    characters.erase(characters.begin() + chosenCard);

    return character;
}

void GameController::callCharcaters () {
    int nextCharacter = 0;
    while(nextCharacter >= 0){
        nextCharacter = currentRound->getNextCharacher();
        auto characterPosition = std::find_if(characters.begin(), characters.end(), [&nextCharacter](const std::shared_ptr<BaseCharacter> c) {
            return c->getType() == nextCharacter;
        });
        
        auto character = characterPosition.operator*();
        
        std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>> position;
        for (auto playerClient : players) {
            auto player = playerClient.first;
            auto client = playerClient.second;
            
            client->write("King is calling character: " + character->getname() + "\n");
        }
        auto player = character->getPlayer();
        if (player) {
            auto playerClient = std::find_if(players.begin(), players.end(), [player] (const std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>>& it) {
                return it.first == player;
            
            });
            
            std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>>> otherPlayers;
            std::copy_if(players.begin(), players.end(), back_inserter(otherPlayers), [player] (std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>> it) {
                return it.first == player;
            });
            
            processors[nextCharacter]->handle(currentRound, players, playerClient.operator*());
        }
    }
}


void GameController::quit () {
    for (auto clientPlayer : players){
        auto client = clientPlayer.second;
        if (client->is_open()) client->close();
    }
}

