//
//  CardsFactory.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 22-08-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef CardsFactory_hpp
#define CardsFactory_hpp

#include <stdio.h>
#include <vector>
#include "Models/BaseCard.hpp"

class CardsFactory {
public:
    std::vector<std::shared_ptr<BaseCard>> create(const std::vector<std::vector<std::string>>& set);
};

#endif /* CardsFactory_hpp */
