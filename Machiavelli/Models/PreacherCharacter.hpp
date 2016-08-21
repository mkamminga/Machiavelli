//
//  PreacherCharacter.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 21-08-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef PreacherCharacter_hpp
#define PreacherCharacter_hpp

#include <stdio.h>

#include "BaseCharacter.hpp"

class PreacherCharacter : public BaseCharacter {
public:
    PreacherCharacter(int type, const std::string& name) : BaseCharacter(type, name)  {
        protects = true;
    }

};

#endif /* PreacherCharacter_hpp */
