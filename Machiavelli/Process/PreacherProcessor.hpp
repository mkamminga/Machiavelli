//
//  PreacherProcessor.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef PreacherProcessor_hpp
#define PreacherProcessor_hpp

#include <stdio.h>

#include "MainProcessor.hpp"

class PreacherProcessor : public MainProcessor {
protected:
    virtual void setupBinds(std::string& message);
    virtual void handleSpecialFeature(std::string& broadcastMessage);
};

#endif /* PreacherProcessor_hpp */
