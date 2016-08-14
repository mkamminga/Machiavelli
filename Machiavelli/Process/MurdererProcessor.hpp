//
//  MurdererProcessor.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef MurdererProcessor_hpp
#define MurdererProcessor_hpp

#include <stdio.h>
#include "MainProcessor.hpp"

class MurdererProcessor : public MainProcessor {
protected:
    virtual void handleSpecialFeature(std::shared_ptr<Round> round, std::shared_ptr<Player> player, std::shared_ptr<ConsoleView> client, std::string& broadcastMessage);
};

#endif /* MurdererProcessor_hpp */
