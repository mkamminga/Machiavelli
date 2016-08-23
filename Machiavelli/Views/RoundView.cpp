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
            consoleView->write("["+ std::to_string(i) +"] => "+ listCharacter->getname() + ".\n\r");
            i++;
        }
    }
}

void RoundView::displayCards(std::shared_ptr<ConsoleView> consoleView, std::vector<std::shared_ptr<BaseCard>>& cards) {
    int i = 0;
    for (auto card : cards) {
        consoleView->write("["+ std::to_string(i) +"] => "+ card->getName() +  " has " + std::to_string(card->getPoints()) + " points and is coloured:  "+ card->getColourname() +"\n\r");
        i++;
    }
}

int RoundView::displayCardsAndAskCard(std::shared_ptr<ConsoleView> consoleView, std::vector<std::shared_ptr<BaseCard>>& cards) {
    displayCards(consoleView, cards);
    consoleView->write("\nWhich card: \n");

    return askInputBetweenRange(consoleView, 0, (int)(cards.size() - 1));
}

int RoundView::displayCharactersAndAskCharacter(std::shared_ptr<ConsoleView> consoleView, const std::vector<std::shared_ptr<BaseCharacter>>& characters, int startFrom) {
    displayCharacaters(consoleView, characters, startFrom);
    consoleView->write("\nWhich character: \n>> ");
    
    return askInputBetweenRange(consoleView, startFrom, (int)(characters.size() - 1));
}

void RoundView::broadcastToPlayers(const std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>> &players, const std::string& message) {
    for (auto otherPlayerClient : players) {
        otherPlayerClient.second->write(message);
    }
}

void RoundView::displayOptionsAndHandleChoice(std::shared_ptr<ConsoleView> consoleView, const std::map<std::string, std::string>& options, const std::map<std::string, std::function<void ()>>& binds) {
    
    while (true) {
        for (auto option : options) {
            consoleView->write("[" + option.first + "] -> "+ option.second + "\n\r");
        }
        
        consoleView->write("\n>> ");
        std::string const option = consoleView->readline();
        
        if (options.find(option) != options.end()) {
            auto pos = binds.find(option);
            if (pos != binds.end()) {
                auto callback = pos.operator*().second;
                
                callback();
                break;
            }
        } else {
            consoleView->write("uhm, not sure what you mean...\n>> ");
        }
        
        if (!consoleView->is_open()) {
            throw std::runtime_error("connection has closed");
        }
    }
}

int RoundView::displayPlayersAndAskPlayer(std::shared_ptr<ConsoleView> consoleView, const std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>> &players) {
    
    consoleView->write("Players.\n");
    int i = 0;
    for (auto playerClient : players) {
        auto player = playerClient.first;
        consoleView->write("["+ std::to_string(i++) +"] => "+ player->get_name() + "\n\r");
    }
    
    consoleView->write("\n>> ");
    
    return askInputBetweenRange(consoleView, 0, (int)(players.size() - 1));
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
                consoleView->write("\nInvalid input! Number must be between "+ std::to_string(from) +" and "+ std::to_string(till) +"\n\r>> ");
            }
        } else {
            consoleView->write("\nInvalid input!\n\r>> ");
        }
        
        if (!consoleView->is_open()) {
            throw std::runtime_error("connection has closed");
        }
    }

    return chosenInput;
}

bool RoundView::willContinue(std::shared_ptr<ConsoleView> consoleView) {
    consoleView->write("Would you like to continue? (y/n)\n\n>> ");
    while (true) {
        std::string yn = consoleView->readline();
    
        if (yn == "y" || yn == "n") {
            return yn == "y";
        } else {
            if (!consoleView->is_open()) {
                throw std::runtime_error("connection has closed");
            }
            consoleView->write("not quite sure what you mean... Please try again..\n\n>> ");
        }
    }
}

void RoundView::displayFinalPoints (const std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>> &players, std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>> currentPlayerClient, std::shared_ptr<Player> winner){
    if (winner == currentPlayerClient.first) {
        currentPlayerClient.second->write("You have won with "+ std::to_string(winner->calculateTotalPoints()) + " points..\n" );
    } else {
        currentPlayerClient.second->write("You have gathered "+ std::to_string(currentPlayerClient.first->calculateTotalPoints()) + " points..\n" );
    }

    for (auto playerClient : players) {
        auto client = playerClient.second;
        auto player = playerClient.first;
        
        if (winner == player) {
            client->write("Player "+ player->get_name()+  " has won with "+ std::to_string(player->calculateTotalPoints()) + " points..\n" );
        } else {
            client->write("Player "+ player->get_name()+  " has gathered "+ std::to_string(player->calculateTotalPoints()) + " points..\n" );
        }
    }
}