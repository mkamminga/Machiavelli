//
//  main.hpp
//  Machiavelli
//
//  Created by Mark Jan Kamminga on 22-08-16.
//  Copyright © 2016 Mark Jan Kamminga. All rights reserved.
//

#ifndef main_hpp
#define main_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

std::vector<std::string> readFile (std::string textfile);

std::vector<std::string> devideString (const std::string& input, char divider);

std::vector<std::vector<std::string>> devideSet (const std::vector<std::string>& set, char divider);

#endif /* main_hpp */
