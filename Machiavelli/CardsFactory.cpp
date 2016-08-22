//
//  CardsFactory.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 22-08-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include <map>
#include <string>
#include <regex>
#include "CardsFactory.hpp"

std::vector<std::shared_ptr<BaseCard>> CardsFactory::create(const std::vector<std::vector<std::string>>& set) {
    std::vector<std::shared_ptr<BaseCard>> cards;
    
    std::map<std::string, int> types;
    
    types["groen"]  = GREEN;
    types["blauw"]  = BLUE;
    types["rood"]   = RED;
    types["geel"]   = YELLOW;
    types["lila"]   = PURPLE;
    
    std::regex pattern ("^[0-9]+$");
    std::string::size_type sz;
    
    for (auto attributes : set) {
        if (attributes.size() >= 3) {
            std::string name    = attributes.at(0);
            std::string points  = attributes.at(1);
            std::string colour  = attributes.at(2);
            
            if (types.find(colour) != types.end()) {
                if (std::regex_match(points, pattern)) {
                    int numberOfPoints = std::stoi (points,&sz);
                    
                    cards.push_back(std::shared_ptr<BaseCard>( new BaseCard(types[colour], name, numberOfPoints) ));
                }
            }
        }
    }
    
    return cards;
}