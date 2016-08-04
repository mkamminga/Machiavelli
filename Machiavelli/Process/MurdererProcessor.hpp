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
public:
    virtual void handleSpecialFeature();
};

#endif /* MurdererProcessor_hpp */
