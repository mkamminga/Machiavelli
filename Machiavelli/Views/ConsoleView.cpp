//
//  ConsoleView.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "ConsoleView.hpp"
std::string ConsoleView::readline() const {
    std::string cmd = Socket::readline();
    
    if (binds.find(cmd) != binds.end()) {
        auto callback = binds.find(cmd).operator*().second;
        callback();
    }
    
    return cmd;
}

void ConsoleView::addHandler(const std::string &cmd, std::function<void ()> callback){
    binds[cmd] = callback;
}

void ConsoleView::removeHandler(const std::string &cmd) {
    auto pos = binds.find(cmd);
    if (pos != binds.end()) {
        binds.erase(pos);
    }
}