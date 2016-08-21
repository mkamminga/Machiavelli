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
    options["receive coins"] = "** receive 2 coins by command: receive coins";
    options["receive cards"] = "** receive 2 cards with command: receive cards";
    options["use special"]   = "** use special feature with command: use special";
    options["build"]         = "** build by using command: build";
    options["pass"]          = "** pass with command: pass";
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
        client->write("\nWould you like to do?\n\n");
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
    auto cards = player->getCards();
    bool hasBuilt = false;
    
    while (!hasBuilt) {
        int chosenCard = roundView.displayCardsAndAskCard(client, cards);
        auto card = cards.at(chosenCard);
            
        if (card->getPoints() <= player->getCoins()) {
            player->build(card);
            round->getGame()->addToLaidout(card);
        
            broadcastMessage = "Card "+ card->getName() + " with "+ std::to_string(card->getPoints()) + " laid out\n";
            hasBuilt = true;
            options.erase("build");
        } else {
            client->write("Cannot do so...\n\n");
            break;
        }
    }
}