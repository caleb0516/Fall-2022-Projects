#include <iostream>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  // std::cerr << argv[1] << std::endl << argv[2] << std::endl;
  std::string input = argv[1];
  std::map<std::string, std::vector<int>> result =
      MapNameToNumbers(input);  // this will get us the map names and ints
  std::vector<int> counter = StrandCount(
      StrandNames(input), argv[2]);  // this will get us the vector of ints
  size_t count = 0;  // requries the map and vector  //strand coutn gives vector
                     // // mapnametonumbers gives map
  for (auto i = result.begin(); i != result.end(); ++i) {
    if (i->second == counter) {
      std::cout << i->first << std::endl;
      break;
    }
    count++;
    if (count == result.size()) {
      std::cout << "No Match\n";
    }
  }
}
