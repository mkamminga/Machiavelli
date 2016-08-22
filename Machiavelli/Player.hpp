//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <string>
#include <vector>
#include <memory>
#include "BaseCard.hpp"
#include "Models/BaseCharacter.hpp"

class Player {
public:
	Player() {}
	Player(const std::string& name) : name {name} {}
	
	std::string get_name() const { return name; }
	void set_name(const std::string& new_name) { name = new_name; }
    void add_card(std::shared_ptr<BaseCard> card) {
        cards.push_back(card);
    }
    
    void add_cards(std::vector<std::shared_ptr<BaseCard>> gameCards) {
        for (auto card : gameCards) {
            cards.push_back(card);
        }
    }
    
    void add_character (std::shared_ptr<BaseCharacter> character ) {
        characters.push_back(character);
    }
    
    void remove_character (std::shared_ptr<BaseCharacter> character) {
        for (auto it = characters.begin(); it != characters.end(); it++ ) {
            auto characterIt = it.operator*();
            if (characterIt == character) {
                characterIt->setPlayer(nullptr);
                
                characters.erase(it);
                break;
            }
        }
    }
    
    void removeCard (std::shared_ptr<BaseCard> card) {
        cards.erase(std::remove_if(
            cards.begin(),
            cards.end(),
            [card] (std::shared_ptr<BaseCard> b){
              return b == card;
            }),
            cards.end()
        );

    }
    
    const std::vector<std::shared_ptr<BaseCharacter>>& get_characters () {
        return characters;
    }
    
    void putCoins (int number) {
        coins+= number;
    }
    
    void takeCoins (int number) {
        if (number > coins) {
            coins = 0;
        } else {
            coins-= number;
        }
    }
    
    int getCoins () {
        return coins;
    }
    
    const std::vector<std::shared_ptr<BaseCard>>& getCards () {
        return cards;
    }
    
    void build (std::shared_ptr<BaseCard> card) {
        auto position = std::find(cards.begin(), cards.end(), card);
        
        if (position != cards.end()) {
            coins-= card->getPoints();
            cards.erase(position);
            builtCards.push_back(card);
        }
    }
    
    void exchangeCardsWith(std::shared_ptr<Player> player){
        auto playerCards = player->cards;
        player->cards = cards;
        this->cards = playerCards;
    }
    
    int getNumberOfCards () {
        return (int)cards.size();
    }
    
    int countCardsOfColour (int type) {
        return (int)std::count_if(builtCards.begin(), builtCards.end(), [type](const std::shared_ptr<BaseCard> b){
            return b->getColour() == type;
        });
    }
    
    const std::vector<std::shared_ptr<BaseCard>>& built () {
        return builtCards;
    }
    
    void setFinnishedFirst () {
        finnishedFirst = true;
    }
    
    bool hasFinnishedFirst () {
        return finnishedFirst;
    }
    
    int calculateTotalPoints () {
        int points = 0;
        if (finnishedFirst) {
            points+= 4;
        } else if (builtCards.size() >= 8) {
            points+= 2;
        }
        //count per type refernce
        int pointsPerType[5]{
            0,0,0,0,0
        };
        
        for (auto card : builtCards) {
            points += card->getPoints();
            
            pointsPerType[card->getColour()] += card->getPoints();
        }
        
        int num = 0;
        //run through the set types
        for (int i = 0; i < 5; i++) {
            if (pointsPerType[i] > 0) {
                num++;
            } else{
                break;
            }
        }

        if (num == 5) {
            points+= 3;
        }
        
        return points;
    }
    
    int getPoints () {
        int total = 0;
        for (auto card : builtCards) {
            total+= card->getPoints();
        }
        
        return total;
    }
    
private:
	std::string name;
    std::vector<std::shared_ptr<BaseCard>> cards;
    std::vector<std::shared_ptr<BaseCard>> builtCards;
    std::vector<std::shared_ptr<BaseCharacter>> characters;
    int coins = 0;
    bool finnishedFirst  = false;
};

#endif /* Player_hpp */
