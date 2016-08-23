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

void WizzardProcessor::setupBinds(std::string &message){
    MainProcessor::setupBinds(message);
    binds["use special"] = [this, &message]() {
        handleSpecialFeature(message);
    };
    
    options["use special"] = "** with this option you can either exchange your hand held cards (can be none) with those of any other player, or you can exchange them with game laid out pile (equal number)..";
}

void WizzardProcessor::handleSpecialFeature(std::string& broadcastMessage){
    client->write("Would you like to exchange with a player or with the laid out pile?\n");
    std::map<std::string, std::function<void()>> wizzardBinds;
    std::map<std::string, std::string> wizzardOptions {
        {"exchange with player", "exchange with cards with another player"},
        {"exchange laid out", "exchange a number of cards with the laid out pile"}
    };
    
    wizzardBinds["exchange with player"] = [this, &broadcastMessage](){
        handleExchangeWithPlayer(broadcastMessage);
    };
    
    wizzardBinds["exchange laid out"] = [this,  &broadcastMessage](){
        handleExchangeWithLaidOut(broadcastMessage);
    };
    
    roundView.displayOptionsAndHandleChoice(client, wizzardOptions, wizzardBinds);
}

void WizzardProcessor::handleExchangeWithPlayer(std::string &broadcastMessage){
    int playerNumber = roundView.displayPlayersAndAskPlayer(client, players);
    
    auto otherPlayer = players.at(playerNumber).first;
    
    player->exchangeCardsWith(otherPlayer);
    
    broadcastMessage = "You have exchanged your cards with player: "+ otherPlayer->get_name();
    options.erase("use special");
}

void WizzardProcessor::handleExchangeWithLaidOut(std::string &broadcastMessage){
    
    int numOfLaidout = round->getGame()->numberOfLaidOutCards();
    //does the player have enough cards or are there enough cards laidout
    if (player->getNumberOfCards() > 0 && numOfLaidout > 0){
        
        int num = (player->getNumberOfCards() > numOfLaidout ? numOfLaidout : player->getNumberOfCards());
        client->write("How many cards would you like to exchange? Maximum number: "+ std::to_string(num) +"\n");
        int numberOf = roundView.askInputBetweenRange(client, 1, num);
        
        while (numberOf > 0) {
            client->write("Which card would you like to exchange?\n");
            auto playerCards = player->getCards();
            int cardToExchangeWithNumber = roundView.displayCardsAndAskCard(client, playerCards);
            auto card = playerCards.at(cardToExchangeWithNumber);
            
            client->write("Which laid out card would you like to exchange your card with?\n");
            auto gameCards = round->getGame()->laidOutCards();
            int cardToExchangeForNumber = roundView.displayCardsAndAskCard(client, gameCards);
            auto cardToExchangeFor = gameCards.at(cardToExchangeForNumber);

            round->getGame()->exchangeCardFromLaidOut(card, cardToExchangeFor, player);
            numberOf--;
        }
        
        options.erase("use special");
    } else {
        client->write("Not enough cards or not enough cards laid out..\n");
    }
}