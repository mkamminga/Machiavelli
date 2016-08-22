//
//  MainProcessor.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "MainProcessor.hpp"
#include <map>
#include "../Models/Game.hpp"

using namespace std;

void MainProcessor::handle(std::shared_ptr<Round> round,std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView> > > &players, std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>& playerClient){
    this->players = players;
    this->player = playerClient.first;
    this->client = playerClient.second;
    this->round = round;
    //broadcast
    roundView.broadcastToPlayers(players, "Waiting for player: "+ player->get_name() + "!\n");
    std::string message = "";
    setupBinds(message);
    //Ask main question, would you like to pick cards or take money
    askMainQuestion(message);
}

void MainProcessor::setupBinds(std::string& message) {
    options.clear();
    options["receive coins"] = "** receive 2 coins by command";
    options["receive cards"] = "** receive 2 cards with command";
    options["use special"]   = "** use special feature with command";
    options["build"]         = "** build by using command";
    options["pass"]          = "** pass with command";
    options["view cards"]    = "??view current cards";
    options["view coins"]    = "??view number of coins";
    options["view laid out"] = "??view laid out pile";
    binds.clear();
    binds["receive coins"] = [this, &message]() {
        handleIncomePhase(message);
    };
    
    binds["receive cards"] = [this, &message]() {
        handlePickCardPhase(message);
    };
    
    binds["use special"] = [this, &message]() {
        handleSpecialFeature(message);
    };
    
    binds["build"] = [this, &message]() {
        handleBuildPhase(message);
    };
    
    binds["pass"] = [this, &message]() {
        message = "Player has passed";
        options.clear();
    };
    
    binds["view cards"] = [this, &message]() {
        auto cards = player->getCards();
        roundView.displayCards(client, cards);
    };
    
    binds["view coins"] = [this, &message]() {
        client->write("Number of coins: "+ std::to_string(player->getCoins()));
    };
    
    binds["view laid out"] = [this, &message]() {
        auto cards = round->getGame()->laidOutCards();
        roundView.displayCards(client, cards);
    };
}

void MainProcessor::askMainQuestion (std::string& message) {
    
    while (options.size() > 0 && !(options.size() == 1 && options.find("pass") != options.end())){
        client->write("\nWhat would you like to do?\n\n");
        message = "";
        roundView.displayOptionsAndHandleChoice(client, options, binds);
        if (message.size() > 0){
            roundView.broadcastToPlayers(players, message + "\n");
        }
    }
}

void MainProcessor::handleIncomePhase(std::string &broadcastMessage) {
    broadcastMessage = "\n>> player "+ player->get_name() + " has received two coins!\n";
    int coins = round->getGame()->takeCoins(2);
    
    player->putCoins(coins);
    
    options.erase("receive coins");
    options.erase("receive cards");
}

void MainProcessor::handlePickCardPhase(std::string &broadcastMessage) {
    std::vector<std::shared_ptr<BaseCard>> cards = round->getGame()->takeCards(2);

    
    while (cards.size() > 1) {
        int chosenCard = roundView.displayCardsAndAskCard(client, cards);
        auto card = cards.at(chosenCard);
        cards.erase(cards.begin() + chosenCard);
        
        player->add_card(card);
        round->getGame()->addToLaidout(cards.front());

        broadcastMessage = "Card "+ cards.front()->getName() + " with "+ std::to_string(cards.front()->getPoints()) + " points\n";
    }
    
    options.erase("receive coins");
    options.erase("receive cards");
}

void MainProcessor::handleBuildPhase(std::string &broadcastMessage) {
    
    auto character = round->getCharacterByType(round->getCurrentCharacter());
    int numberCanBuild = character->allowedCardsToBuild();
    
    while (numberCanBuild > 0) {
        auto cards = player->getCards();
        int chosenCard = roundView.displayCardsAndAskCard(client, cards);
        auto card = cards.at(chosenCard);
            
        if (card && card->getPoints() <= player->getCoins() && player->canBuild(card)) {
            player->build(card);
            
            auto built = player->getBuiltCards();
        
            broadcastMessage = "Card "+ card->getName() + " with "+ std::to_string(card->getPoints()) + " laid out\n";
            numberCanBuild--;
            //set player has finnished first, and round.. This will trigger the game is over display setter
            if (built.size() >= GAME_BUILD_MAX && !player->hasFinnishedFirst() && !round->isFinalRound()) {
                broadcastMessage += "\n** Player "+ player->get_name() +" has built "+ std::to_string(GAME_BUILD_MAX) +" cards.. Game wil finnish after this round..\n\n";
                client->write("You have built enough buidings to finnish the game..\n");
                player->setFinnishedFirst();
                round->setFinalRound();
            }
            
        } else {
            client->write("Cannot do so... Not enough coins or similar card has been built..\n\r");
        }
        
        if (numberCanBuild > 0) {
            if (!roundView.willContinue(client)) {
                break;
            }
        }
    }
    
    if (character->allowedCardsToBuild() != numberCanBuild) {
        options.erase("build");
    }
}

int MainProcessor::handlePointsForCardColours(int type){
    int numberOfCards = player->countCardsOfColour(type);
    
    if (numberOfCards > 0) {
        int numberRecived = round->getGame()->takeCoins(numberOfCards);
        player->putCoins(numberRecived);
        
        return numberRecived;
    }
    
    return 0;
}