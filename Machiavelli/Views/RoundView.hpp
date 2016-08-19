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

#include "ConsoleView.hpp"
#include "../Models/BaseCharacter.hpp"
#include "../Models/BaseCard.hpp"

class RoundView {
public:
    void displayCharacaters(std::shared_ptr<ConsoleView> consoleView, std::vector<std::shared_ptr<BaseCharacter>> characters);
    void displayCards(std::shared_ptr<ConsoleView> consoleView, std::vector<std::shared_ptr<BaseCard>> cards);
    int displayCardsAndAskCard(std::shared_ptr<ConsoleView> consoleView, std::vector<std::shared_ptr<BaseCard>> cards);
    void broadcastToPlayers(std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<ConsoleView>>> &players, const std::string& message);
};

#endif /* RoundView_hpp */
