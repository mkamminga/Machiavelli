//
//  BaseCharacter.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "BaseCharacter.hpp"
#include "../Player.hpp"

void BaseCharacter::setPlayer(std::shared_ptr<Player> player){
    this->player = player;
};