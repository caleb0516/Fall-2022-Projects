// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

WordLocation Horizontal(size_t row, std::string word, size_t col) {
  CharPositions character{};
  std::vector<CharPositions> char_positions;
  WordLocation result{};
  int word_index = 0;
  for (size_t i = col; i < col + word.size(); ++i) {
    character = {word[word_index], row, i};
    char_positions.push_back(character);
    word_index++;
  }
  result = {word, char_positions};
  return result;
}

WordLocation Vertical(size_t row, std::string word, size_t col) {
  CharPositions character{};
  std::vector<CharPositions> char_positions;
  WordLocation result{};
  int word_index = 0;
  for (size_t i = row; i < row + word.size(); ++i) {
    character = {word[word_index], i, col};
    char_positions.push_back(character);
    word_index++;
  }
  result = {word, char_positions};
  return result;
}

WordLocation RightDiag(size_t row, std::string word, size_t col) {
  CharPositions character{};
  std::vector<CharPositions> char_positions;
  WordLocation result{};
  int word_index = 0;

  for (size_t i = row; i < row + word.size(); ++i) {
    character = {word[word_index], i, col};
    char_positions.push_back(character);
    ++word_index;
    ++col;
  }
  result = {word, char_positions};
  return result;
}

WordLocation LeftDiag(size_t row, std::string word, size_t col) {
  CharPositions character{};
  std::vector<CharPositions> char_positions;
  WordLocation result{};
  int word_index = 0;
  for (size_t i = row; i < row + word.size(); ++i) {
    character = {word[word_index], i, col};
    char_positions.push_back(character);
    ++word_index;
    --col;
  }
  result = {word, char_positions};
  return result;
}

bool AreEqual(WordLocation check, WordLocation given) {
  if (check.char_positions.size() != given.char_positions.size()) {
    return false;
  }
  if (check.word != given.word) {
    return false;
  }
  for (size_t index = 0; index < given.char_positions.size(); ++index) {
    if (check.char_positions[index].character !=
            given.char_positions[index].character ||
        check.char_positions[index].row != given.char_positions[index].row ||
        check.char_positions[index].col != given.char_positions[index].col)
      return false;
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Checking horizontal", "[Horizontal]") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'h', 'e', 'l', 'l', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'},
                                        {'a', 'e', 't', 'a', 'u'},
                                        {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver wss(puzzle);
  WordLocation check = wss.FindWord("hello", CheckDirection::kHorizontal);
  WordLocation given = Horizontal(1, "hello", 0);
  REQUIRE(AreEqual(check, given));
  check = wss.FindWord("hello");
  REQUIRE(AreEqual(check, given));

  std::vector<std::vector<char>> puzzle2{{'d', 'e', 'a', 'o', 'u'},
                                         {'h', 'e', 'l', 'l', 'o'},
                                         {'c', 'a', 'l', 'o', 'm'},
                                         {'a', 'e', 't', 'a', 'u'},
                                         {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver wss2(puzzle2);
  check = wss2.FindWord("helloc", CheckDirection::kHorizontal);
  REQUIRE(check.word.empty());
  REQUIRE(check.char_positions.empty());
  check = wss2.FindWord("helloc");
  REQUIRE(check.word.empty());
  REQUIRE(check.char_positions.empty());

  std::vector<std::vector<char>> puzzle3{{'d', 'e', 'a', 'o', 'u'},
                                         {'h', 'e', 'l', 'o', 'n'},
                                         {'c', 't', 'o', 'n', 'g'},
                                         {'a', 'e', 't', 'a', 'u'},
                                         {'t', 'l', 'o', 'n', 'g'}};
  WordSearchSolver wss3(puzzle3);
  check = wss3.FindWord("long", CheckDirection::kHorizontal);
  given = Horizontal(4, "long", 1);
  REQUIRE(AreEqual(check, given));
  check = wss3.FindWord("long");
  REQUIRE(AreEqual(check, given));
}
//   std::vector<std::vector<char>> puzzle4{{'d', 'e', 'a', 'o', 'u'},
//                                          {'h', 'e', 'l', 'l', 'o'},
//                                          {'t', 'c', 'l', 'o', 'm'},
//                                          {'a', 'e', 't', 'a', 'u'},
//                                          {'t', 'e', 't', 'o', 'u'}};
//   WordSearchSolver wss4(puzzle4);
//   check = wss4.FindWord("helloc", CheckDirection::kHorizontal);
//   REQUIRE(check.word.empty());
//   REQUIRE(check.char_positions.empty());
//   check = wss4.FindWord("helloc");
//   REQUIRE(check.word.empty());
//   REQUIRE(check.char_positions.empty());

//   std::vector<std::vector<char>> puzzle5{{'d', 'e', 'a', 'o', 'u'},
//                                          {'h', 'e', 'l', 'l', 'o'},
//                                          {'t', 'c', 'l', 'o', 'm'},
//                                          {'a', 'e', 't', 'a', 'u'},
//                                          {'t', 'e', 't', 'o', 'w'}};
//   WordSearchSolver wss5(puzzle5);
//   check = wss5.FindWord("town", CheckDirection::kHorizontal);
//   REQUIRE(check.word.empty());
//   REQUIRE(check.char_positions.empty());
//   check = wss5.FindWord("town");
//   REQUIRE(check.word.empty());
//   REQUIRE(check.char_positions.empty());

//   std::vector<std::vector<char>> puzzle6{{'d', 'e', 'a', 'o', 'u'},
//                                          {'h', 'h', 'e', 'l', 'l'},
//                                          {'t', 'c', 'l', 'o', 'm'},
//                                          {'a', 'e', 't', 'a', 'u'},
//                                          {'t', 'e', 't', 'o', 'w'}};
//   WordSearchSolver wss6(puzzle6);
//   check = wss6.FindWord("hell", CheckDirection::kHorizontal);
//   given = Horizontal(1, "hell", 1);
//   REQUIRE(AreEqual(check, given));
//   check = wss6.FindWord("hell");
//   REQUIRE(AreEqual(check, given));
// }

// TEST_CASE("Vertical Search", "[Vertical][Search]") {
//   std::vector<std::vector<char>> puzzle{{'t', 'e', 'a', 'o', 'u'},
//                                         {'o', 'e', 'l', 'l', 'o'},
//                                         {'w', 'a', 'l', 'o', 'm'},
//                                         {'n', 'e', 't', 'a', 'u'},
//                                         {'y', 'e', 't', 'o', 'u'}};
//   WordSearchSolver wss(puzzle);
//   WordLocation check = wss.FindWord("towny", CheckDirection::kVertical);
//   WordLocation given = Vertical(0, "towny", 0);
//   REQUIRE(AreEqual(check, given));
//   check = wss.FindWord("towny");
//   REQUIRE(AreEqual(check, given));

//   std::vector<std::vector<char>> puzzle2{{'a', 'y', 'a', 'o', 'u'},
//                                          {'t', 'e', 'l', 'l', 'o'},
//                                          {'o', 'a', 'l', 'o', 'm'},
//                                          {'w', 'e', 't', 'a', 'u'},
//                                          {'n', 'e', 't', 'o', 'u'}};
//   WordSearchSolver wss2(puzzle2);
//   check = wss2.FindWord("towny", CheckDirection::kVertical);
//   REQUIRE(check.word.empty());
//   REQUIRE(check.char_positions.empty());
//   check = wss2.FindWord("towny");
//   REQUIRE(check.word.empty());
//   REQUIRE(check.char_positions.empty());

//   std::vector<std::vector<char>> puzzle3{{'a', 'e', 'a', 'o', 'u'},
//                                          {'d', 'n', 'l', 'l', 'o'},
//                                          {'t', 'a', 'l', 'o', 'm'},
//                                          {'o', 'e', 't', 'a', 'u'},
//                                          {'w', 'e', 't', 'o', 'u'}};
//   WordSearchSolver wss3(puzzle3);
//   check = wss3.FindWord("town", CheckDirection::kVertical);
//   REQUIRE(check.word.empty());
//   REQUIRE(check.char_positions.empty());
//   check = wss3.FindWord("town");
//   REQUIRE(check.word.empty());
//   REQUIRE(check.char_positions.empty());

//   std::vector<std::vector<char>> puzzle4{{'a', 'e', 'a', 'o', 'u'},
//                                          {'d', 'n', 'l', 'l', 't'},
//                                          {'t', 'a', 'l', 'o', 'o'},
//                                          {'o', 'e', 't', 'a', 'w'},
//                                          {'w', 'e', 't', 'o', 'n'}};
//   WordSearchSolver wss4(puzzle4);
//   check = wss4.FindWord("towny", CheckDirection::kVertical);
//   REQUIRE(check.word.empty());
//   REQUIRE(check.char_positions.empty());
//   check = wss4.FindWord("towny");
//   REQUIRE(check.word.empty());
//   REQUIRE(check.char_positions.empty());

//   std::vector<std::vector<char>> puzzle5{{'a', 'e', 'a', 'o', 'u'},
//                                          {'d', 'n', 'l', 'l', 't'},
//                                          {'t', 'a', 'l', 'o', 'o'},
//                                          {'o', 'e', 't', 'a', 'w'},
//                                          {'w', 'e', 't', 'o', 'n'}};
//   WordSearchSolver wss5(puzzle5);
//   check = wss5.FindWord("town", CheckDirection::kVertical);
//   given = Vertical(1, "town", 4);
//   REQUIRE(AreEqual(check, given));
//   check = wss5.FindWord("town");
//   REQUIRE(AreEqual(check, given));

//   std::vector<std::vector<char>> puzzle6{{'a', 'e', 'a', 'o', 'h'},
//                                          {'d', 'n', 'l', 'l', 'e'},
//                                          {'t', 'a', 'l', 'o', 'l'},
//                                          {'o', 'e', 't', 'a', 'l'},
//                                          {'w', 'e', 't', 'o', 'o'}};
//   WordSearchSolver wss6(puzzle6);
//   check = wss6.FindWord("hello", CheckDirection::kVertical);
//   given = Vertical(0, "hello", 4);
//   REQUIRE(AreEqual(check, given));
//   check = wss6.FindWord("hello");
//   REQUIRE(AreEqual(check, given));

//   std::vector<std::vector<char>> puzzle7{{'a', 'e', 'a', 'o', 'h'},
//                                          {'d', 'n', 'l', 'l', 'e'},
//                                          {'t', 'a', 'l', 'o', 'l'},
//                                          {'o', 'e', 'o', 'a', 'l'},
//                                          {'w', 'e', 't', 'o', 'o'}};
//   WordSearchSolver wss7(puzzle7);
//   check = wss7.FindWord("allot", CheckDirection::kVertical);
//   given = Vertical(0, "allot", 2);
//   REQUIRE(AreEqual(check, given));
//   check = wss7.FindWord("allot");
//   REQUIRE(AreEqual(check, given));

//   std::vector<std::vector<char>> puzzle8{{'a', 'e', 'a', 'o', 'h'},
//                                          {'d', 'n', 'l', 'l', 'e'},
//                                          {'t', 'a', 'l', 'o', 'l'},
//                                          {'o', 'e', 'o', 'a', 'l'},
//                                          {'w', 'e', 't', 'o', 'o'}};
//   WordSearchSolver wss8(puzzle8);
//   check = wss8.FindWord("alloto", CheckDirection::kVertical);
//   REQUIRE(check.char_positions.empty());
//   REQUIRE(check.word.empty());
//   check = wss8.FindWord("alloto");
//   REQUIRE(check.char_positions.empty());
//   REQUIRE(check.word.empty());

//   std::vector<std::vector<char>> puzzle9{{'a', 'e', 'a', 'o', 'h'},
//                                          {'d', 'n', 'l', 't', 'e'},
//                                          {'t', 'a', 'l', 'a', 'l'},
//                                          {'o', 'e', 'o', 'm', 'l'},
//                                          {'w', 'e', 't', 'o', 'o'}};
//   WordSearchSolver wss9(puzzle9);
//   check = wss9.FindWord("tam", CheckDirection::kVertical);
//   given = Vertical(1, "tam", 3);
//   REQUIRE(AreEqual(check, given));
//   check = wss9.FindWord("tam");
//   REQUIRE(AreEqual(check, given));

//   std::vector<std::vector<char>> puzzle10{{'a', 'e', 'a', 'o', 'h'},
//                                           {'d', 'n', 'l', 'l', 'e'},
//                                           {'t', 'a', 'l', 'o', 'l'},
//                                           {'o', 'e', 'o', 'a', 'l'},
//                                           {'w', 'e', 't', 'o', 'o'}};
//   WordSearchSolver wss10(puzzle10);
//   check = wss10.FindWord("lot", CheckDirection::kVertical);
//   given = Vertical(2, "lot", 2);
//   REQUIRE(AreEqual(check, given));
//   check = wss10.FindWord("lot");
//   REQUIRE(AreEqual(check, given));
// }

// TEST_CASE("Right Diagonal", "[Right][Diagonal]") {
//   std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
//                                         {'h', 'e', 'l', 'l', 'o'},
//                                         {'c', 'a', 'l', 'o', 'm'},
//                                         {'a', 'e', 't', 'a', 'u'},
//                                         {'t', 'e', 't', 'o', 'u'}};
//   WordSearchSolver wss(puzzle);
//   WordLocation check = wss.FindWord("delau", CheckDirection::kRightDiag);
//   WordLocation given = RightDiag(0, "delau", 0);
//   REQUIRE(AreEqual(check, given));
//   check = wss.FindWord("delau");
//   REQUIRE(AreEqual(check, given));

//   std::vector<std::vector<char>> puzzle2{{'h', 'u', 'a', 'o', 'u'},
//                                          {'h', 'e', 'l', 'l', 'o'},
//                                          {'c', 'a', 'l', 'o', 'm'},
//                                          {'a', 'e', 't', 'l', 'u'},
//                                          {'t', 'e', 't', 'o', 'o'}};
//   WordSearchSolver wss2(puzzle2);
//   check = wss2.FindWord("hellou", CheckDirection::kRightDiag);
//   REQUIRE(check.char_positions.empty());
//   REQUIRE(check.word.empty());
//   check = wss2.FindWord("hellou");
//   REQUIRE(check.char_positions.empty());
//   REQUIRE(check.word.empty());

//   std::vector<std::vector<char>> puzzle3{{'l', 'l', 'l', 'l', 'l'},
//                                          {'h', 'l', 'l', 'l', 'l'},
//                                          {'l', 'e', 'h', 'l', 'm'},
//                                          {'l', 'e', 'l', 'e', 'u'},
//                                          {'l', 'e', 'l', 'o', 'l'}};
//   WordSearchSolver wss3(puzzle3);
//   check = wss3.FindWord("hell", CheckDirection::kRightDiag);
//   REQUIRE(check.char_positions.empty());
//   REQUIRE(check.word.empty());
//   check = wss3.FindWord("hell");
//   REQUIRE(check.char_positions.empty());
//   REQUIRE(check.word.empty());

//   std::vector<std::vector<char>> puzzle4{{'k', 'u', 'a', 'o', 'u'},
//                                          {'h', 'i', 'l', 'l', 'o'},
//                                          {'c', 'a', 't', 'o', 'm'},
//                                          {'a', 'e', 't', 't', 'u'},
//                                          {'t', 'e', 't', 'o', 'y'}};
//   WordSearchSolver wss4(puzzle4);
//   check = wss4.FindWord("kitty", CheckDirection::kRightDiag);
//   given = RightDiag(0, "kitty", 0);
//   REQUIRE(AreEqual(check, given));
//   check = wss4.FindWord("kitty");
//   REQUIRE(AreEqual(check, given));
// }

// TEST_CASE("Left Diagonal", "[Left][Diagonal]") {
//   std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
//                                         {'h', 'e', 'l', 'l', 'o'},
//                                         {'c', 'a', 'l', 'o', 'm'},
//                                         {'a', 'e', 't', 'a', 'u'},
//                                         {'t', 'e', 't', 'o', 'u'}};
//   WordSearchSolver wss(puzzle);
//   WordLocation check = wss.FindWord("mat", CheckDirection::kLeftDiag);
//   WordLocation given = LeftDiag(2, "mat", 4);
//   REQUIRE(AreEqual(check, given));
//   check = wss.FindWord("mat");
//   REQUIRE(AreEqual(check, given));

//   std::vector<std::vector<char>> puzzle2{{'t', 't', 't', 't', 't'},
//                                          {'t', 't', 't', 't', 't'},
//                                          {'t', 't', 't', 't', 'm'},
//                                          {'t', 't', 't', 'a', 't'},
//                                          {'t', 't', 't', 't', 't'}};
//   WordSearchSolver wss2(puzzle2);
//   check = wss2.FindWord("matt", CheckDirection::kLeftDiag);
//   REQUIRE(check.char_positions.empty());
//   REQUIRE(check.word.empty());
//   check = wss2.FindWord("matt");
//   REQUIRE(check.char_positions.empty());
//   REQUIRE(check.word.empty());

//   std::vector<std::vector<char>> puzzle3{{'d', 'e', 'a', 'o', 'h'},
//                                          {'h', 'e', 'l', 'e', 'o'},
//                                          {'c', 'a', 'l', 'o', 'm'},
//                                          {'a', 'l', 't', 'a', 'u'},
//                                          {'o', 'e', 't', 'o', 'u'}};
//   WordSearchSolver wss3(puzzle3);
//   check = wss3.FindWord("hello", CheckDirection::kLeftDiag);
//   given = LeftDiag(0, "hello", 4);
//   REQUIRE(AreEqual(check, given));
//   check = wss3.FindWord("hello");
//   REQUIRE(AreEqual(check, given));
// }

/////////////////////////////////////////////////////////////////////////////////////////////