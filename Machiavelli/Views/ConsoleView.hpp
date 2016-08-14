//
//  ConsoleView.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef ConsoleView_hpp
#define ConsoleView_hpp

#include <stdio.h>
#include <functional>
#include <map>
#include "../Socket.h"

class ConsoleView : public Socket {
public:
    ConsoleView(SOCKET sock, const struct sockaddr& address) : Socket(sock, address) {};
    virtual std::string readline() const;
    void addHandler(const std::string& cmd, std::function<void()> callback);
    void removeHandler(const std::string& cmd);
private:
    std::map<std::string, std::function<void()>> binds;
};

#endif /* ConsoleView_hpp */
