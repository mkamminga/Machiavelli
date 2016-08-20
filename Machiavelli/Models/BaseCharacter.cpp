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

void BaseCharacter::giveCoinsToPlayer(std::shared_ptr<Player> player) {
    if (this->player) {
        int number = this->player->getCoins();
        if (number > 0) {
            player->putCoins(number);
            this->player->takeCoins(number);
        }
    }
}