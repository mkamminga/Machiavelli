//
//  main.cpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 22-08-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#include "main.hpp"

std::vector<std::string> readFile (std::string textfile) {
    std::ifstream input_file{textfile};
    
    if (!input_file.is_open()) {
        throw std::runtime_error("Could not open file: "+ textfile);
    }
    std::string line;
    std::vector<std::string> list;
    
    while (getline(input_file, line)) {
        list.push_back(line);
    }
    
    input_file.close();
    
    return list;
}

std::vector<std::string> devideString (const std::string& input, char divider) {
    std::vector<std::string> divided;
    
    std::stringstream ss(input);
    std::string item;
    while (std::getline(ss, item, divider)) {
        divided.push_back(item);
    }
    
    return divided;
};

std::vector<std::vector<std::string>> devideSet (const std::vector<std::string>& set, char divider) {
    std::vector<std::vector<std::string>> devidedSet;
    
    for (auto it = set.begin(); it != set.end(); it++) {
        devidedSet.push_back(devideString(it.operator*(), divider));
    }
    
    return devidedSet;
}