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
#include <functional>
#include <map>

#include "BaseCharacter.hpp"
#include "Game.hpp"

class Round {
public:
    Round(std::shared_ptr<Game> game, std::vector<std::shared_ptr<BaseCharacter>> roundCharacters) : game(game), roundCharacters(roundCharacters) {
        characters[0] = MURDERER;
        characters[1] = THIEF;
        characters[2] = WIZZARD;
        characters[3] = PREACHER;
        characters[4] = MERCHANT;
        characters[5] = MASTER_BUILER;
        characters[6] = CONDOTTIERI;
    }
    
    int getCurrentCharacter() {
        return currentCharacter;
    }
    
    int getNextCharacher() {
        if (currentCharacter < 6){
            currentCharacter++;
            
            if (binds.find(currentCharacter) != binds.end()) {
                auto callback = binds[currentCharacter];
                callback();
            }
            
            return currentCharacter;
        }
        
        currentCharacter = -1;
        
        return currentCharacter;
    }
    
    std::shared_ptr<BaseCharacter> getCharacterByType (int num) {
        auto pos = std::find_if(roundCharacters.begin(), roundCharacters.end(), [num] (const std::shared_ptr<BaseCharacter> c) {
            return c->getType() == num;
        });
        
        if (pos != roundCharacters.end()) {
            return pos.operator*();
        }
        
        return nullptr;
    }
    
    std::shared_ptr<Game> getGame () {
        return game;
    }
    
    std::vector<std::shared_ptr<BaseCharacter>> const getCharacters () {
        return roundCharacters;
    }
    
    void addCallback(int type, std::function<void ()> callback){
        binds[type] = callback;
    }
    
    void setFinalRound () {
        finalRound = true;
    }
    
    bool isFinalRound () {
        return finalRound;
    }

private:
    std::shared_ptr<Game> game;
    int characters[7];
    int currentCharacter = -1;
    std::vector<std::shared_ptr<BaseCharacter>> roundCharacters;
    std::map<int, std::function<void()>> binds;
    bool finalRound = false;
    
};

#endif /* Round_hpp */
