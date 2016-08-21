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
public:
    virtual void setupBinds(std::string& message);
    virtual void handleSpecialFeature(std::string& broadcastMessage);
    void handleExchangeWithPlayer(std::string& broadcastMessage);
    void handleExchangeWithLaidOut(std::string& broadcastMessage);
};

#endif /* WizzardProcessor_hpp */
