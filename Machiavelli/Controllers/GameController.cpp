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
#include "../Models/PreacherCharacter.hpp"
#include "../Models/BuildMasterCharacter.cpp"
#include "../Process/MurdererProcessor.hpp"
#include "../Process/ThiefProcessor.hpp"
#include "../Process/WizzardProcessor.hpp"
#include "../Process/PreacherProcessor.hpp"
#include "../Process/MerchantProcessor.hpp"
#include "../Process/BuildmasterProcessor.hpp"
#include "../Process/CondottieriProcessor.hpp"


GameController::GameController() {
    game = std::shared_ptr<Game>(new Game);
    setupCards();
    setupCharacters();
    setupProcessors();
};

void GameController::addPlayer(std::shared_ptr<Player> player, std::shared_ptr<ConsoleView> client){
    if (!hasStarted()){
        players.push_back(make_pair(player, client));
        
    }
}

bool GameController::start(){
    if (!gameStarted){
        
        for (auto playerClient : players) {
            auto player = playerClient.first;
            auto client = playerClient.second;
            
            player->putCoins(game->takeCoins(2));
            player->add_cards(game->takeCards(2));
            
            client->addHandler("show cards", [player, client]() {
                auto cards = player->getCards();
                client->write("Cards: \n");
                for (auto card : cards) {
                    client->write(" > "+ card->getName() + " - "+ std::to_string(card->getPoints()));
                }
                client->write("\n");
            });
            
        }
        
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
    for (int i = 0; i < 3; i++) {
        game->addCard(std::shared_ptr<BaseCard>(new BaseCard(YELLOW, "Geel", 2)));
        game->addCard(std::shared_ptr<BaseCard>(new BaseCard(RED, "Rood", 7)));
        game->addCard(std::shared_ptr<BaseCard>(new BaseCard(BLUE, "Blauw", 2)));
        game->addCard(std::shared_ptr<BaseCard>(new BaseCard(BLUE, "Blauw", 3)));
        game->addCard(std::shared_ptr<BaseCard>(new BaseCard(BLUE, "Blauw", 4)));
        game->addCard(std::shared_ptr<BaseCard>(new BaseCard(BLUE, "Blauw", 8)));
        game->addCard(std::shared_ptr<BaseCard>(new BaseCard(RED, "Rood", 4)));
        game->addCard(std::shared_ptr<BaseCard>(new BaseCard(PURPLE, "Paars", 6)));
        game->addCard(std::shared_ptr<BaseCard>(new BaseCard(YELLOW, "Geel", 2)));
    }
}

void GameController::setupCharacters() {
    //TODO create and distribute characters
    characters.push_back(std::shared_ptr<BaseCharacter>(new BaseCharacter(MURDERER, "Murderer")));
    characters.push_back(std::shared_ptr<BaseCharacter>(new BaseCharacter(THIEF, "Thief")));
    characters.push_back(std::shared_ptr<BaseCharacter>(new BaseCharacter(WIZZARD, "Wizzard")));
    characters.push_back(std::shared_ptr<BaseCharacter>(new PreacherCharacter(PREACHER, "Preacher")));
    characters.push_back(std::shared_ptr<BaseCharacter>(new BaseCharacter(MERCHANT, "Merchant")));
    characters.push_back(std::shared_ptr<BaseCharacter>(new BuildMasterCharacter(MASTER_BUILER, "Master builder")));
    characters.push_back(std::shared_ptr<BaseCharacter>(new BaseCharacter(CONDOTTIERI, "Condottieri")));
}

void GameController::setupProcessors() {
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
    return players.size() == 2;
}

void GameController::startRound(){
    currentRound = std::shared_ptr<Round>(new Round(game, characters));
    //copy characters
    auto roundCharacters = characters;
    std::random_shuffle ( roundCharacters.begin(), roundCharacters.end() );
    //reset charcaters, unbind all connections
    resetPlayerCharacters();
    //present cards of which in two turn both players can choose and throw away one card
    devideCardsToPlayers(roundCharacters);
    //set a new object for the new round
    
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
            
            
            auto character = removeAndChoseCharacter("Which characater would you like to keep?", client, roundCharacters);
            player->add_character(character);
            character->setPlayer(player);
            
            client->write("Character '"+ character->getname() +"' added!\n");
            
            if (roundCharacters.size() < 6 && roundCharacters.size() > 1){
                character = removeAndChoseCharacter("Which charcater would you like to throw away?", client, roundCharacters);
                client->write("Character '"+ character->getname() +"' thrown away!\n\n");
            }
        }
    }
}

std::shared_ptr<BaseCharacter> GameController::removeAndChoseCharacter(const std::string& question, std::shared_ptr<ConsoleView> client, std::vector<std::shared_ptr<BaseCharacter>>& characters) {
    client->write(question + "\n");
    int chosenCard = roundView.displayCharactersAndAskCharacter(client, characters, 0);
    auto character = characters.at(chosenCard);
    characters.erase(characters.begin() + chosenCard);

    return character;
}

void GameController::callCharcaters () {
    int nextCharacter  = currentRound->getNextCharacher();
    //call every character untill all have been called
    while(nextCharacter >= 0){
        
        auto character = currentRound->getCharacterByType(nextCharacter);
        std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>> position;
        roundView.broadcastToPlayers(players, "King is calling character: " + character->getname() + "\n");
        
        auto player = character->getPlayer();
        //if the current charcater has a
        if (player) {
            //find the player client pair connected to the player
            auto playerClient = std::find_if(players.begin(), players.end(), [player] (const std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>>& it) {
                return it.first == player;
            });
            //set the other players poule
            std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>> otherPlayers;
            std::copy_if(players.begin(), players.end(), back_inserter(otherPlayers), [player] (std::pair<std::shared_ptr<Player>, std::shared_ptr<Socket>> it) {
                return it.first != player;
            });
            //process the character by the specialised processor
            processors[nextCharacter]->handle(currentRound, otherPlayers, playerClient.operator*());
        }
        
        nextCharacter = currentRound->getNextCharacher();
    }
    
    if (currentRound->isFinalRound()) {
        gameOver = true;
        gameStarted = false;
    }
}


void GameController::quit () {
    roundView.broadcastToPlayers(players, "Shutting down now");
    for (auto clientPlayer : players){
        auto client = clientPlayer.second;
        if (client->is_open()) client->close();
    }
}

