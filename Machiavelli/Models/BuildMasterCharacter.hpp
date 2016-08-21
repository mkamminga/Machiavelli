//
//  BuildMasterCharacter.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 21-08-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef BuildMasterCharacter_hpp
#define BuildMasterCharacter_hpp

#include <stdio.h>

#include "BaseCharacter.hpp"

class BuildMasterCharacter : public BaseCharacter {
public:
    BuildMasterCharacter(int type, const std::string& name) : BaseCharacter(type, name)  {
        numberOfAllowedCards = 2;
        numberOfAllowedCardsToBuild = 3;
    }
};

#endif /* BuildMasterCharacter_hpp */
