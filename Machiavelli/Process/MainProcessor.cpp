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
    //ask, Would you like to receive to coins or two cards?
    roundView.broadcastToPlayers(players, "Waiting for player: "+ playerClient.first->get_name() + "!\n");
    //Ask main question, would you like to pick cards or take money
    askMainQuestion(round, playerClient);
}

void MainProcessor::askMainQuestion (std::shared_ptr<Round> round, std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>& playerClient) {
    
    auto client = playerClient.second;
    auto player = playerClient.first;
    
    
    std::map<std::string, std::string> options;
    options["receive coins"] = "receive 2 coins by command: receive coins";
    options["receive cards"] = "receive 2 cards with command: receive cards";
    options["use special"]   = "use special feature with command: use special";
    options["build"]         = "build by using command: build";
    options["pass"]          = "pass with command: pass";
    
    while (options.size() > 0){
        client->write("\nWould you like to do?\n\n");
        for (auto option: options) {
            client->write(" -> "+option.second + "\n" );
        }
        
        client->write("\n >> ");
        std::string cmd = "";
        while (true){
            cmd = client->readline();
            if (options.find(cmd) != options.end()) {
                break;
            }
        }
        
        std::string message = "";
        
        if (cmd == "receive coins") {
            handleIncomePhase(round, player, client, message);
            options.erase("receive coins");
            options.erase("receive cards");
        } else if (cmd == "receive cards") {
            handlePickCardPhase(round, player, client, message);
            options.erase("receive coins");
            options.erase("receive cards");
        } else if (cmd == "build") {
          //Build
            handleBuildPhase(round, player, client, message);
            options.erase("build");
        } else if (cmd == "use special") {
            //Use special feature
            handleSpecialFeature(round, player, client, message);
            options.erase("use special");
        }else if (cmd == "pass") {
            break;
        } else {
            client->write("uhm, not sure what you mean...\n>>");
        }
        
        roundView.broadcastToPlayers(players, message + "\n");
    }
}

void MainProcessor::handleIncomePhase(std::shared_ptr<Round> round, std::shared_ptr<Player> player, std::shared_ptr<ConsoleView> client, std::string &broadcastMessage) {
    broadcastMessage = "\n>> player "+ player->get_name() + " has received two coins!\n";
    int coins = round->getGame()->takeCoins(2);
    
    player->putCoins(coins);
}

void MainProcessor::handlePickCardPhase(std::shared_ptr<Round> round, std::shared_ptr<Player> player, std::shared_ptr<ConsoleView> client, std::string &broadcastMessage) {
    std::vector<std::shared_ptr<BaseCard>> cards = round->getGame()->takeCards(2);
    
    while (cards.size() > 1) {
        int chosenCard = roundView.displayCardsAndAskCard(client, cards);
        auto card = cards.at(chosenCard);
        cards.erase(cards.begin() + chosenCard);
        
        player->add_card(card);
        round->getGame()->addToLaidout(cards.front());

        broadcastMessage = "Card "+ cards.front()->getName() + " with "+ std::to_string(cards.front()->getPoints()) + " points\n";
    }
}

void MainProcessor::handleBuildPhase(std::shared_ptr<Round> round, std::shared_ptr<Player> player, std::shared_ptr<ConsoleView> client, std::string &broadcastMessage) {
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
        } else {
            break;
        }
    }
}