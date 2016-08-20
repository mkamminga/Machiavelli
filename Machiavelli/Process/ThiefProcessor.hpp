//
//  ThiefProcessor.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef ThiefProcessor_hpp
#define ThiefProcessor_hpp

#include <stdio.h>

#include "MainProcessor.hpp"

class ThiefProcessor : public MainProcessor {
protected:
    virtual void handleSpecialFeature(std::shared_ptr<Round> round, std::shared_ptr<Player> player, std::shared_ptr<ConsoleView> client, std::string& broadcastMessage);
};

#endif /* ThiefProcessor_hpp */
