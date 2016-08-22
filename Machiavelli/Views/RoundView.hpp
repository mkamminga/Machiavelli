//
//  RoundView.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 19-08-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef RoundView_hpp
#define RoundView_hpp

#include <stdio.h>
#include <vector>
#include <functional>
#include <map>

#include "ConsoleView.hpp"
#include "../Models/BaseCharacter.hpp"
#include "../Models/BaseCard.hpp"
#include "../Player.hpp"

class RoundView {
public:
    void displayCharacaters(std::shared_ptr<ConsoleView> consoleView, const std::vector<std::shared_ptr<BaseCharacter>>& characters);
    void displayCharacaters(std::shared_ptr<ConsoleView> consoleView, const std::vector<std::shared_ptr<BaseCharacter>>& characters, int starFrom);
    int displayCharactersAndAskCharacter(std::shared_ptr<ConsoleView> consoleView, const std::vector<std::shared_ptr<BaseCharacter>>& characters, int starFrom);
    void displayCards(std::shared_ptr<ConsoleView> consoleView, std::vector<std::shared_ptr<BaseCard>>& cards);
    int displayCardsAndAskCard(std::shared_ptr<ConsoleView> consoleView, std::vector<std::shared_ptr<BaseCard>>& cards);
    void broadcastToPlayers(const std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>> &players, const std::string& message);
    void displayOptionsAndHandleChoice(std::shared_ptr<ConsoleView> consoleView, const std::map<std::string, std::string>& availibleOptions, const std::map<std::string, std::function<void ()>>& binds);
    int displayPlayersAndAskPlayer(std::shared_ptr<ConsoleView> consoleView, const std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>> &players);
    int askInputBetweenRange(std::shared_ptr<ConsoleView> consoleView, int from, int till);
    bool willContinue(std::shared_ptr<ConsoleView> consoleView);
    void displayFinalPoints (const std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>> &players, std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>, std::shared_ptr<Player> winner);
};

#endif /* RoundView_hpp */
