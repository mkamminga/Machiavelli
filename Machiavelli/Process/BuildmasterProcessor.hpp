//
//  BuildmasterProcessor.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef BuildmasterProcessor_hpp
#define BuildmasterProcessor_hpp

#include <stdio.h>

#include "MainProcessor.hpp"

class BuildmasterProcessor : public MainProcessor {
protected:
    virtual void setupBinds(std::string& message);
    virtual void handleBuildPhase(std::string& broadcastMessage);
    virtual void handleSpecialFeature(std::string& broadcastMessage);
    virtual void handlePickCardPhase(std::string& broadcastMessage);
};

#endif /* BuildmasterProcessor_hpp */
