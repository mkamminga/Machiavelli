//
//  CharacterFactory.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 22-08-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "CharacterFactory.hpp"

#include <string>
#include <regex>
#include <algorithm>

#include "CardsFactory.hpp"
#include "BuildMasterCharacter.hpp"

std::vector<std::shared_ptr<BaseCharacter>> CharacterFactory::create(const std::vector<std::vector<std::string>>& set) {
    std::vector<std::shared_ptr<BaseCharacter>> characters;
        
    std::regex pattern ("^[0-9]+$");
    std::string::size_type sz;
    
    for (auto attributes : set) {
        if (attributes.size() >= 2) {
            std::string name    = attributes.at(1);
            std::string type    = attributes.at(0);
            
            if (std::regex_match(type, pattern)) {
                int typeNumber = std::stoi (type,&sz);
                std::replace(name.begin(), name.end(), '\r', '.');
                if (typeNumber == 6) {
                    characters.push_back(std::shared_ptr<BaseCharacter>( new BuildMasterCharacter(typeNumber, name)));
                } else {
                    characters.push_back(std::shared_ptr<BaseCharacter>( new BaseCharacter(typeNumber, name)));
                }
            }
        }
    }
    
    return characters;
}