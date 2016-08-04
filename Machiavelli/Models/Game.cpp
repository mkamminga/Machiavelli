//
//  Game.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "Game.hpp"

void Game::addCard(std::shared_ptr<BaseCard> card){
    availibleCards.push_back(card);
}