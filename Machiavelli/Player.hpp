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

class Player {
public:
	Player() {}
	Player(const std::string& name) : name {name} {}
	
	std::string get_name() const { return name; }
	void set_name(const std::string& new_name) { name = new_name; }
    void add_card(std::shared_ptr<BaseCard> card) {
        cards.push_back(card);
    }
	
private:
	std::string name;
    std::vector<std::shared_ptr<BaseCard>> cards;
};

#endif /* Player_hpp */
