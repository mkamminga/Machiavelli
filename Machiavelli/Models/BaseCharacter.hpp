//
//  BaseCharacter.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef BaseCharacter_hpp
#define BaseCharacter_hpp

#include <stdio.h>
#include <string>

class Player;

enum Characters {
    MURDERER,
    THIEF,
    WIZZARD,
    PREACHER,
    MERCHANT,
    MASTER_BUILER,
    CONDOTTIERI
};

class BaseCharacter {
public:
    BaseCharacter(int type, const std::string& name): type(type), name(name) {};
    const std::string getname () { return name; }
    const int getType () { return type; }
    void setPlayer(std::shared_ptr<Player> player);
    std::shared_ptr<Player> getPlayer () {
        return player;
    }
    
    
private:
    int type;
    std::string name;
    std::shared_ptr<Player> player = nullptr;
};

#endif /* BaseCharacter_hpp */
