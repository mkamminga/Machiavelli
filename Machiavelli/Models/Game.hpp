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
    void addToLaidout(std::shared_ptr<BaseCard> card) {
        laidoutCards.push_back(card);
    }
    
    std::shared_ptr<BaseCard> takeCard () {
        if (availibleCards.size() > 0) {
            auto back = availibleCards.back();
            availibleCards.pop_back();
            
            return back;
        }
        
        return nullptr;
    }
    
    std::vector<std::shared_ptr<BaseCard>> takeCards (int number) {
        std::vector<std::shared_ptr<BaseCard>> cards;
        
        if (number > 0) {
            for (int i = 0; i<number; i++) {
                auto card = takeCard();
                cards.push_back(card);
            }
        }
        
        return cards;
    }
    
private:
    std::vector<std::shared_ptr<BaseCard>> availibleCards;
    std::vector<std::shared_ptr<BaseCard>> laidoutCards;
};

#endif /* Game_hpp */
