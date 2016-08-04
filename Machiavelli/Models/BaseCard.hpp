//
//  BaseCard.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 30-07-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef BaseCard_hpp
#define BaseCard_hpp

#include <stdio.h>

enum CardColours {
    GREEN,
    YELLOW,
    RED,
    PURPLE,
    BLUE
};

class BaseCard {
public:
    BaseCard (int cardColour, int points): colour(cardColour),points(points){};
private:
    int colour;
    int points;
};
#endif /* BaseCard_hpp */
