//
//  MerchantProcessor.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef MerchantProcessor_hpp
#define MerchantProcessor_hpp

#include <stdio.h>

#include "MainProcessor.hpp"

class MerchantProcessor : public MainProcessor {
protected:
    virtual void setupBinds(std::string& message);
    virtual void handleSpecialFeature(std::string& broadcastMessage);
};

#endif /* MerchantProcessor_hpp */
