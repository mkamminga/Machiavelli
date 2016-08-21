//
//  CondottieriProcessor.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef CondottieriProcessor_hpp
#define CondottieriProcessor_hpp

#include <stdio.h>

#include "MainProcessor.hpp"

class CondottieriProcessor : public MainProcessor {
protected:
    virtual void setupBinds(std::string& message);
    virtual void handleSpecialFeature(std::string& broadcastMessage);
};

#endif /* CondottieriProcessor_hpp */
