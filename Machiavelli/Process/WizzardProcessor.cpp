//
//  WizzardProcessor.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "WizzardProcessor.hpp"
#include "../Models/Game.hpp"
#include <functional>

void WizzardProcessor::handleSpecialFeature(std::shared_ptr<Round> round, std::shared_ptr<Player> player, std::shared_ptr<ConsoleView> client, std::string& broadcastMessage){
    client->write("Would you like to exchange with a player or with the laid out pile?\n");
    std::map<std::string, std::function<void()>> binds;
    std::map<std::string, std::string> options {
        {"exchange with player", "exchange with cards with another player"},
        {"exchange laid out", "exchange a number of cards with the laid out pile"}
    };
    
    binds["exchange with player"] = [this, round, player, client, &broadcastMessage](){
        this->handleExchangeWithPlayer(round, player, client, broadcastMessage);
    };
    
    binds["exchange laid out"] = [this, round, player, client, &broadcastMessage](){
        this->handleExchangeWithLaidOut(round, player, client, broadcastMessage);
    };
    
    roundView.displayOptionsAndHandleChoice(client, options, binds);
}

void WizzardProcessor::handleExchangeWithPlayer(std::shared_ptr<Round> round, std::shared_ptr<Player> player, std::shared_ptr<ConsoleView> client, std::string &broadcastMessage){
    int playerNumber = roundView.displayPlayersAndAskPlayer(client, players);
    
    auto otherPlayer = players.at(playerNumber).first;
    
    player->exchangeCardsWith(otherPlayer);
    
    broadcastMessage = "You have exchanged your cards with player: "+ otherPlayer->get_name();
}

void WizzardProcessor::handleExchangeWithLaidOut(std::shared_ptr<Round> round, std::shared_ptr<Player> player, std::shared_ptr<ConsoleView> client, std::string &broadcastMessage){

    
    int numOfLaidout = round->getGame()->numberOfLaidOutCards();
    if (player->getNumberOfCards() > 0 && numOfLaidout > 0 &&  player->getNumberOfCards() >= numOfLaidout){
        
        int num = (player->getNumberOfCards() > numOfLaidout ? numOfLaidout : player->getNumberOfCards());
        int numberOf = roundView.askInputBetweenRange(client, 1, num);
        client->write("How many cards would you like to exchange? Maximum number: "+ std::to_string(num) +"\n");
        auto playerCards = player->getCards();
        while (numberOf > 0) {
            client->write("Which card would you like to exchange?\n");
            int cardToExchangeWithNumber = roundView.displayCardsAndAskCard(client, playerCards);
            auto card = playerCards.at(cardToExchangeWithNumber);
            
            client->write("Which laid out card would you like to exchange your card with?\n");
            auto gameCards = round->getGame()->laidOutCards();
            int cardToExchangeForNumber = roundView.displayCardsAndAskCard(client, playerCards);
            auto cardToExchangeFor = gameCards.at(cardToExchangeForNumber);

            round->getGame()->exchangeCardFromLaidOut(card, cardToExchangeFor, player);
            numberOf--;
        }
    } else {
        client->write("Not enough cards or not enough cards laid out..\n");
    }
}