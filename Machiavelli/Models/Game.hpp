//
//  Game.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "../GameDefines.h"
#include <algorithm>
#include <stdio.h>
#include <vector>
#include "BaseCard.hpp"
#include "Player.hpp"

class Game {
public:
    void addCards(std::vector<std::shared_ptr<BaseCard>> cards){
        std::random_shuffle ( cards.begin(), cards.end() );
        this->availibleCards = cards;
    }
    
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
    
    int takeCoins (int number) {
        if (number <= numberOfCoins) {
            numberOfCoins-= number;
            
            return number;
        } else if (numberOfCoins > 0) {
            int returnNumber = numberOfCoins;
            numberOfCoins = 0;
            
            return returnNumber;
        }
        
        return -1;
    }
    
    int getCoins () {
        return numberOfCoins;
    }
    
    void putCoins (int number) {
        numberOfCoins+= number;
        
        if (numberOfCoins > 30) {
            numberOfCoins = 30;
        }
    }
    
    int numberOfLaidOutCards () {
        return (int)(laidoutCards.size());
    }
    
    const std::vector<std::shared_ptr<BaseCard>>& laidOutCards (){
        return laidoutCards;
    }
    
    void exchangeCardFromLaidOut (std::shared_ptr<BaseCard> cardFromPlayer, std::shared_ptr<BaseCard> laidOutCard, std::shared_ptr<Player> player) {
        laidoutCards.push_back(cardFromPlayer);
        
        laidoutCards.erase(std::remove_if(
            laidoutCards.begin(),
            laidoutCards.end(),
            [laidOutCard] (std::shared_ptr<BaseCard> b){
                return b == laidOutCard;
            }),
            laidoutCards.end()
        );
        
        player->removeCard(cardFromPlayer);
        player->add_card(laidOutCard);
    }
    
private:
    std::vector<std::shared_ptr<BaseCard>> availibleCards;
    std::vector<std::shared_ptr<BaseCard>> laidoutCards;
    int numberOfCoins = 30;
};

#endif /* Game_hpp */
