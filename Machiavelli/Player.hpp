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
	
private:
	std::string name;
    std::vector<std::shared_ptr<BaseCard>> cards;
    std::vector<std::shared_ptr<BaseCard>> builtCards;
    std::vector<std::shared_ptr<BaseCharacter>> characters;
    int coins = 0;
};

#endif /* Player_hpp */
