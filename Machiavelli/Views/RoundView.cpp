//
//  RoundView.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 19-08-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//
#include <regex>
#include "RoundView.hpp"

void RoundView::displayCharacaters(std::shared_ptr<ConsoleView> consoleView, const std::vector<std::shared_ptr<BaseCharacter>>& characters) {
    displayCharacaters(consoleView, characters, 0);
}

void RoundView::displayCharacaters(std::shared_ptr<ConsoleView> consoleView, const std::vector<std::shared_ptr<BaseCharacter> > &characters, int startFrom){
    int i = startFrom;
    if (i < characters.size()) {
        auto it = characters.begin() + i;
        for ( ; it != characters.end(); it++){
            auto listCharacter = it.operator*();
            consoleView->write("["+ std::to_string(i) +"] => "+ listCharacter->getname() + ".\n");
            i++;
        }
    }
}

void RoundView::displayCards(std::shared_ptr<ConsoleView> consoleView, std::vector<std::shared_ptr<BaseCard>>& cards) {
    int i = 0;
    for (auto card : cards) {
        consoleView->write("["+ std::to_string(i) +"] = "+ card->getName() +  " has " + std::to_string(card->getPoints()) + " points\n");
        i++;
    }
}

int RoundView::displayCardsAndAskCard(std::shared_ptr<ConsoleView> consoleView, std::vector<std::shared_ptr<BaseCard>>& cards) {
    displayCards(consoleView, cards);
    consoleView->write("\nWhich card: \n\n>>");

    return askInputBetweenRange(consoleView, 0, (int)(cards.size() - 1));
}

int RoundView::displayCharactersAndAskCharacter(std::shared_ptr<ConsoleView> consoleView, const std::vector<std::shared_ptr<BaseCharacter>>& characters, int startFrom) {
    displayCharacaters(consoleView, characters, startFrom);
    consoleView->write("\nWhich character: \n\n>>");
    
    return askInputBetweenRange(consoleView, startFrom, (int)(characters.size() - 1));
}

void RoundView::broadcastToPlayers(std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>> &players, const std::string& message) {
    for (auto otherPlayerClient : players) {
        otherPlayerClient.second->write(message);
    }
}

void displayOptionsAndHandleChoice(std::shared_ptr<ConsoleView> consoleView, const std::map<std::string, std::function<void ()>>& options) {
    
}

int RoundView::askInputBetweenRange (std::shared_ptr<ConsoleView> consoleView, int from, int till) {
    std::regex pattern ("^[0-9]+$");
    std::string::size_type sz;
    std::string input;
    
    bool chosen = false;
    int chosenInput = 0;
    
    while (!chosen) {
        input = consoleView->readline();
        
        if (std::regex_match(input, pattern)) {
            chosenInput = std::stoi (input,&sz);
            if (chosenInput >= from && chosenInput <= till) {
                chosen = true;
            } else {
                consoleView->write("\nInvalid input! Number must be between "+ std::to_string(from) +" and "+ std::to_string(till) +"\n>>");
            }
        } else {
            consoleView->write("\nInvalid input!\n>>");
        }
    }

    return chosenInput;
}