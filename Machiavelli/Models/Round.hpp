//
//  Round.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef Round_hpp
#define Round_hpp

#include <stdio.h>

#include "BaseCharacter.hpp"
#include "Game.hpp"

class Round {
public:
    Round(std::shared_ptr<Game> game) : game(game) {
        characters[0] = MURDERER;
        characters[1] = THIEF;
        characters[2] = WIZZARD;
        characters[3] = PREACHER;
        characters[4] = MERCHANT;
        characters[5] = MASTER_BUILER;
        characters[7] = CONDOTTIERI;
        
    };
private:
    std::shared_ptr<Game> game;
    int characters[7];
};

#endif /* Round_hpp */
