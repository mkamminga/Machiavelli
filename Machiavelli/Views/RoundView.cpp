//
//  RoundView.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 19-08-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//
#include <regex>
#include "RoundView.hpp"

void RoundView::displayCharacaters(std::shared_ptr<ConsoleView> consoleView, std::vector<std::shared_ptr<BaseCharacter>> characters) {
    
}

void RoundView::displayCards(std::shared_ptr<ConsoleView> consoleView, std::vector<std::shared_ptr<BaseCard>> cards) {
    int i = 0;
    for (auto card : cards) {
        consoleView->write("["+ std::to_string(i) +"] = "+ card->getName() +  " has " + std::to_string(card->getPoints()) + " points\n");
        i++;
    }
}

int RoundView::displayCardsAndAskCard(std::shared_ptr<ConsoleView> consoleView, std::vector<std::shared_ptr<BaseCard>> cards) {
    displayCards(consoleView, cards);
    consoleView->write("\nWhich card: \n\n>>");
    std::string::size_type sz;
    std::string cardToAdd;
    bool chosen = false;
    
    std::regex pattern ("^[0-9]+$");
    int chosenCard = 0;
    
    while (!chosen) {
        cardToAdd = consoleView->readline();
        
        if (std::regex_match(cardToAdd, pattern)) {
            chosenCard = std::stoi (cardToAdd,&sz);
            if (chosenCard >= 0 && chosenCard < cards.size()) {
                chosen = true;
            } else {
                consoleView->write("\nInvalid input! Number must be between 0 and "+ std::to_string(cards.size()) +"\n>>");
            }
        } else {
            consoleView->write("\nInvalid input!\n>>");
        }
    }
    
    return chosenCard;
}

void RoundView::broadcastToPlayers(std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>> &players, const std::string& message) {
    for (auto otherPlayerClient : players) {
        otherPlayerClient.second->write(message);
    }
}