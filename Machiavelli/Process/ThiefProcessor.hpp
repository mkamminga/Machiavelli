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
    virtual void setupBinds(std::string& message);
    virtual void handleSpecialFeature(std::string& broadcastMessage);
};

#endif /* ThiefProcessor_hpp */
