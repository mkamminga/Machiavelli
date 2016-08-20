//
//  WizzardProcessor.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef WizzardProcessor_hpp
#define WizzardProcessor_hpp

#include <stdio.h>

#include "MainProcessor.hpp"

class WizzardProcessor : public MainProcessor {
    virtual void handleSpecialFeature(std::shared_ptr<Round> round, std::shared_ptr<Player> player, std::shared_ptr<ConsoleView> client, std::string& broadcastMessage);
};

#endif /* WizzardProcessor_hpp */
