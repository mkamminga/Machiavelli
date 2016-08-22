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
#include <string>

enum CardColours {
    GREEN,
    YELLOW,
    RED,
    PURPLE,
    BLUE
};

class BaseCard {
public:
    BaseCard (int cardColour, std::string colourName, std::string name, int points): colour(cardColour), colourName(colourName), name(name), points(points){};
    
    int getColour () {
        return colour;
    }
    
    std::string getColourname () {
        return colourName;
    }
    
    int getPoints () {
        return points;
    }
    
    std::string getName () {
        return name;
    }
    
private:
    int colour;
    std::string name;
    std::string colourName;
    int points;
};
#endif /* BaseCard_hpp */
