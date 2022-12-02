#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace utilities {
  std::vector<std::string> GetSubstrs(const std::string& str, char delimiter);
}

std::vector<std::string> utilities::GetSubstrs(const std::string& str,
                                               char delimiter) {
  size_t last = 0;
  std::vector<std::string> substrs;
  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) == delimiter) {
      std::string substr = str.substr(last, i - last);
      last = i + 1;
      substrs.push_back(substr);
    }
  }
  std::string substr = str.substr(last, str.length() - last);
  substrs.push_back(substr);

  return substrs;
}
std::vector<std::string> StrandNames(std::string input);

std::vector<std::string> StrandNames(std::string input) {
  std::ifstream ifs{input};
  if (!ifs.is_open()) std::cout << "file not open" << std::endl;
  std::string first_line;
  std::getline(
      ifs,
      first_line);  // this should be "name:, AATC , AAT" or whatever strands
  std::vector<std::string> full_line = utilities::GetSubstrs(
      first_line,
      ',');  // this should give me a vector strings of name, AATC , STR, STR
  std::vector<std::string> strand_names;
  for (size_t i = 1; i < full_line.size(); i++) {
    strand_names.push_back(
        full_line[i]);  // this will get me a vector of the strand names
  }
  // for (size_t i = 0; i < strand_names.size(); i++) {
  //   std::cout << strand_names[i] << std::endl;
  // }
  return strand_names;
}

// add strads.size only when we find the strand
std::vector<int> StrandCount(
    std::vector<std::string> strand,
    std::string
        sequence);  // sequence is the vector of the Call by doing
                    // StrandCount(StrandNames(std::string input),sequence)
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
      } else
        counter = 0;
    }
    strand_count.push_back(biggest);
  }
  return strand_count;
}
std::map<std::string, std::vector<int>> MapNameToNumbers(
    std::string input);  // file name
std::map<std::string, std::vector<int>> MapNameToNumbers(std::string input) {
  std::map<std::string, std::vector<int>>
      result;  // result map that maps names with their str frequency
  std::vector<std::string> lines;        // takes all the lines of the file into
                                         // seperate strings into a vector
  std::vector<std::string> line_vector;  //
  std::vector<int>
      line_vector_no_name;  // outputs the numbers only from line_vector

  std::ifstream ifs{input};
  if (!ifs.is_open()) std::cout << "file not open" << std::endl;

  for (std::string line; std::getline(ifs, line); line = "")
    lines.push_back(
        line);  // lines[0] = "names, str ,str ,str" lines[1] == "casey,2,5,8"
                // line[2] == "Amani 3,7,4" //lines has all the lines from the
                // doc lines is a vector with all the lines from the file

  // for (size_t i = 0; i < lines.size(); i++) {
  //  std::cout << lines.at(i) << std::endl;
  //}
  for (size_t j = 1; j < lines.size(); j++)  // line 0 is the strand row
  {
    line_vector = utilities::GetSubstrs(
        lines[j],
        ',');  // this will get us {"casey", "5","2","8"} // then amani 3,7,4
               // make that the case for every elemetn in lines
    // for (size_t i = 0; i < lines.size(); i++) {  //line vector is working as
    // expected std::cout << line_vector.at(i) << std::endl;
    //}
    // std::cout << line_vector.at(0);
    for (size_t i = 1; i < line_vector.size(); i++) {
      line_vector_no_name.push_back(std::stoi(
          line_vector[i]));  // line_vector_no_name[i-1] =  line_vector[i];
                             // //this will give us linvector with no name
                             // //linevector atm is {"casey","2","5","8"}
    }

    // for (size_t i = 1; i < lines.size(); i++) {
    result.insert(std::pair<std::string, std::vector<int>>(
        line_vector[0],
        line_vector_no_name));    // map will have key casey, [5,2,8]
    line_vector_no_name.clear();  // need to do this or it will have everyones
                                  // number at the end
    //}
  }
  // std::vector<int> output = result.at("Casey");
  // for (size_t i = 0; i < output.size(); i++) {
  // std::cout << output.at(i) << std::endl;}

  return result;  // result will now be a map of keys with eveyr name and values
                  // with every combination
}

int main() {
  std::string input_file = "test.dat";
  std::map<std::string, std::vector<int>> result = MapNameToNumbers(
      input_file);          // works as planned //maps a name to its str numbers
  StrandNames(input_file);  // works as planned //returns a vector with each str
                            // as its elements
  std::vector<int> counter =
      StrandCount(StrandNames("test.dat"),
                  "TATTATTATTATAACCCTGCGCGCGCGCGATCCAGCATTAGCTAGCATCAAGATGAGATG"
                  "AGATGGAATTTCGAAATGAATGAATGAATGAATGAATGAATG");
  // testing the values of each vector
  std::cout << "vector for counter is \n";
  for (size_t i = 0; i < counter.size(); i++) {
    std::cout << counter[i] << std::endl;
  }
  std::cout << "vector for counter in name map is \n";
  std::vector<int> name_and_number = result.at("Amani");
  for (size_t i = 0; i < name_and_number.size(); i++) {
    std::cout << name_and_number[i] << std::endl;
  }

  // works as planed counts each str. returns vector of ints
  // key = name value = numbers
  // if counter == result value print the key.
  // swithc key and value

  int count = 0;
  for (auto i = result.begin(); i != result.end(); ++i) {
    if (i->second == counter) {
      std::cout << i->first << std::endl;
      break;
    }
    count++;
    if (count == result.size()) std::cout << "No Match\n";
  }
}