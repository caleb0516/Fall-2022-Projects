//#include "functions.hpp"

#include <iostream>
#include <string>

std::string Convert(std::string input);
std::string Vowels(std::string input);
std::string VowelsTwo(std::string input);
std::string DoubleVowelsOne(std::string input);
std::string DoubleVowelsTwo(std::string input);
std::string Consonants(std::string input);

std::string Convert(std::string input) {
  std::string output;
  input =
      VowelsTwo(DoubleVowelsTwo(DoubleVowelsOne(Vowels(Consonants(input)))));
  for (unsigned long i = 1; i < input.size(); i++) {
    if (input[i] == '-' && input[i + 1] == ' ')
      i = i + 1 - 1;
    else if (input[i] == '-' && ispunct(input[i + 1]))
      i = i + 0;
    else
      output.push_back(input[i]);
  }
  std::cout << output << std::endl;
  return output;
}
std::string Vowels(std::string input) {
  std::string output;
  std::string lower;
  for (unsigned long i = 0; i < input.size(); i++) {
    lower.push_back(tolower(input[i]));
  }
  for (unsigned long i = 0; i < lower.size(); i++) {
    if (lower[i] == 'a' && lower[i + 1] != 'e' && lower[i + 1] != 'i' &&
        lower[i + 1] != 'o' && lower[i + 1] != 'u')
      output.append("ah-");
    else if (lower[i] == 'e' && lower[i + 1] != 'i' && lower[i + 1] != 'u' &&
             lower.at(i - 1) != 'a')  //&& lower[i-1] != 'a'
      output.append("eh-");
    else if (lower[i] == 'i' && lower[i - 1] != 'e' && lower[i - 1] != 'o' &&
             lower[i - 1] != 'u' && lower[i + 1] != 'u' &&
             lower.at(i - 1) != 'a')
      output.append("ee-");
    else if (lower[i] == 'o' && lower[i + 1] != 'i' && lower[i - 1] != 'u' &&
             lower.at(i - 1) != 'a')
      output.append("oh-");
    else if (lower[i] == 'u' && lower[i - 1] != 'e' && lower[i - 1] != 'i' &&
             lower[i - 1] != 'o' && lower[i + 1] != 'i' &&
             lower.at(i - 1) != 'a')
      output.append("oo-");
    else
      output.push_back(lower[i]);
  }
  if (output[output.size() - 1] == '-') output.pop_back();
  input = output;
  // std::cout<< output<< std::endl;
  return input;
}

std::string DoubleVowelsOne(std::string input) {
  std::string output;
  for (unsigned long i = 0; i < input.size(); i++) {
    if (input[i] == 'a') {
      if (input[i + 1] == 'e' || input[i + 1] == 'i') {
        output.append("eye-");
        i++;
      } else if (input[i + 1] == 'o' || input[i + 1] == 'u') {
        output.append("ow-");
        i++;
      } else
        output.push_back(input[i]);
    } else if (input[i] == 'e') {
      if (input[i + 1] == 'i') {
        output.append("ay-");
        i++;
      } else if (input[i + 1] == 'u') {
        output.append("eh-oo-");
        i++;
      } else
        output.push_back(input[i]);
    } else if (input[i] == 'i') {
      if (input[i + 1] == 'u') {
        output.append("ew-");
        i++;
      } else
        output.push_back(input[i]);
    } else
      output.push_back(input[i]);
  }
  if (output[output.size() - 1] == '-') output.pop_back();
  return output;
}

std::string DoubleVowelsTwo(std::string input) {
  std::string output;
  for (unsigned long i = 0; i < input.size(); i++) {
    if (input[i] == 'o') {
      if (input[i + 1] == 'i' || input[i + 1] == 'I') {
        output.append("oy-");
        i++;
      }
      if (input[i + 1] == 'u' || input[i + 1] == 'U') {
        output.append("ow-");
        i++;
      } else
        output.push_back(input[i]);
    } else if (input[i] == 'u' || input[i] == 'U') {
      if (input[i + 1] == 'i' || input[i + 1] == 'I') {
        output.append("ooey-");
        i++;
      } else
        output.push_back(input[i]);
    } else
      output.push_back(input[i]);
  }
  if (output[output.size() - 1] == '-') output.pop_back();
  return output;
}

std::string Consonants(std::string input) {
  std::string output;
  std::string lower;
  for (unsigned long i = 0; i < input.size(); i++) {
    lower.push_back(tolower(input[i]));
  }
  output.push_back(' ');  // so we can check 0-1 posistion for vowels
  for (unsigned long i = 0; i < lower.size(); i++) {
    if (lower[i] == 'b' || lower[i] == 'c' || lower[i] == 'd' ||
        lower[i] == 'f' || lower[i] == 'g' || lower[i] == 'j' ||
        lower[i] == 'q' || lower[i] == 'r' || lower[i] == 's' ||
        lower[i] == 't' || lower[i] == 'v' || lower[i] == 'x' ||
        lower[i] == 'y' || lower[i] == 'z') {
      std::cout << '[' << input << ']'
                << " contains a character not a part of the Hawaiian language.";
      break;
    } else if (lower[i] == 'w' && lower[i - 1] == 'i')
      output.push_back('v');
    else if (lower[i] == 'w' && lower[i - 1] == 'e')
      output.push_back('v');
    else
      output.push_back(lower[i]);
  }
  return output;
}

std::string VowelsTwo(std::string input) {
  std::string output;
  int j = input.size() - 1;

  for (unsigned long i = 0; i < input.size(); i++) {
    output.push_back(input[i]);
  }

  if (input[j] == 'a' && input[j - 1] == '-') {
    output.pop_back();
    output.append("ah-");
  } else if (input[j] == 'e' && input[j - 1] == '-') {
    output.pop_back();
    output.append("eh-");
  } else if (input[j] == 'i' && input[j - 1] == '-') {
    output.pop_back();
    output.append("ee-");
  } else if (input[j] == 'o' && input[j - 1] == '-') {
    output.pop_back();
    output.append("oh-");
  } else if (input[j] == 'u' && input[j - 1] == '-') {
    output.pop_back();
    output.append("oo-");
  }
  if (output[output.size() - 1] == '-') output.pop_back();
  // std::cout<< output<< std::endl;
  return output;
}

/*for (unsigned long i = 0; i < lower.size(); i++){
    if (lower[i] == 'a' && ispunct(lower[i-1]) !=0) //|| lower[i] == 'a' &&
lower[i-1] == ' ') output.append("ah-"); else if (lower[i] == 'e' && lower[i-1]
== '-')// || lower[i] == 'a' && lower[i-1] == ' ') output.append("eh-"); else if
(lower[i] == 'i' && lower[i-1] == '-') //|| lower[i] == 'a' && lower[i-1] == '
') output.append("ee-"); else if (lower[i] == 'o' && lower[i-1] == '-')// ||
lower[i] == 'a' && lower[i-1] == ' ') output.append("oh-"); else if (lower[i] ==
'u' && lower[i-1] == '-')// || lower[i] == 'a' && lower[i-1] == ' ')
     output.append("oo-");
    else
     output.push_back(lower[i]);
}*/