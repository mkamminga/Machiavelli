//
//  CharacterFactory.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 22-08-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef CharacterFactory_hpp
#define CharacterFactory_hpp

#include <stdio.h>
#include <vector>
#include "BaseCharacter.hpp"

class CharacterFactory {
public:
    std::vector<std::shared_ptr<BaseCharacter>> create(const std::vector<std::vector<std::string>>& set);
};

#endif /* CharacterFactory_hpp */
