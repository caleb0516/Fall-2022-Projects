#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utilities.hpp"

std::vector<std::string> StrandNames(std::string input);
std::vector<int> StrandCount(std::vector<std::string> strand,
                             std::string sequence);
std::map<std::string, std::vector<int>> MapNameToNumbers(std::string input);

#endif