//
//  Game.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <vector>
#include "BaseCard.hpp"

class Game {
public:
    void addCard(std::shared_ptr<BaseCard> card);
    ~Game() {
        
    }
    
private:
    std::vector<std::shared_ptr<BaseCard>> availibleCards;
    std::vector<std::shared_ptr<BaseCard>> laidoutCards;
};

#endif /* Game_hpp */
