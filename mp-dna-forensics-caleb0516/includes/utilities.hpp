#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace utilities {
  std::vector<std::string> GetSubstrs(const std::string& str, char delimiter);
}

#endif