#include "functions.hpp"

#include "utilities.hpp"
std::vector<std::string> StrandNames(std::string input) {
  std::ifstream ifs{input};
  if (!ifs.is_open()) std::cout << "file not open" << std::endl;
  std::string first_line;
  std::getline(ifs, first_line);
  std::vector<std::string> full_line = utilities::GetSubstrs(first_line, ',');
  std::vector<std::string> strand_names;
  for (size_t i = 1; i < full_line.size(); i++) {
    strand_names.push_back(full_line[i]);
  }

  return strand_names;
}

std::vector<int> StrandCount(std::vector<std::string> strands,
                             std::string sequence) {
  std::vector<int> strand_count;

  for (size_t j = 0; j < strands.size(); j++) {  // check each unique str
    int counter = 0;
    int biggest = 0;
    for (size_t i = 0; i < sequence.size() - strands[j].size() + 1; i++) {
      if (strands[j] == sequence.substr(i, strands[j].size())) {
        counter++;
        i += (strands[j].size() - 1);
        if (counter > biggest) biggest = counter;
      } 
      else
        counter = 0;
    }
    strand_count.push_back(biggest);
  }
  return strand_count;
}

std::map<std::string, std::vector<int>> MapNameToNumbers(std::string input) {
  std::map<std::string, std::vector<int>> result;
  std::vector<std::string> lines;
  std::vector<std::string> line_vector;
  std::vector<int> line_vector_no_name;
  std::ifstream ifs{input};
  if (!ifs.is_open()) std::cout << "file not open" << std::endl;
  for (std::string line; std::getline(ifs, line); line = "")
    lines.push_back(line);
  for (size_t j = 1; j < lines.size(); j++) {
    line_vector = utilities::GetSubstrs(lines[j], ',');
    for (size_t i = 1; i < line_vector.size(); i++) {
      line_vector_no_name.push_back(std::stoi(line_vector[i]));
    }
    result.insert(std::pair<std::string, std::vector<int>>(
        line_vector[0], line_vector_no_name));
    line_vector_no_name.clear();
  }
  return result;
}