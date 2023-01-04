#include "WordSearchSolver.hpp"

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle):
    puzzle_(puzzle) {
  if (puzzle_.empty()) {
    puzzle_height_ = 0;
    puzzle_width_ = 0;
  } else {
    puzzle_height_ = puzzle_.size();
    puzzle_width_ = puzzle.at(0).size();
  }
}
WordLocation WordSearchSolver::Horizontal(const std::string& word) {
  CharPositions character{};
  std::vector<CharPositions> char_positions;
  WordLocation word_found;
  int word_index = 0;
  unsigned long equal_count = 0;
  for (size_t i = 0; i < puzzle_height_; i++) {
    char_positions.clear();
    for (size_t j = 0; j < puzzle_width_; j++) {
      if (puzzle_.at(i).at(j) == word.at(word_index)) {
        character.character = word.at(word_index);
        character.row = i;
        character.col = j;
        // character ={word.at(word_index),i,j};
        char_positions.push_back(character);
        word_index++;
        equal_count++;
        if (equal_count == word.size()) {
          word_found.word = word;
          word_found.char_positions = char_positions;
          return word_found;
        }
      } else if (puzzle_.at(i).at(j) == word.at(0)) {
        char_positions.clear();
        character.character = word.at(0);
        character.row = i;
        character.col = j;
        char_positions.push_back(character);
        word_index = 1;
        equal_count = 1;
      } else {
        char_positions.clear();
        word_index = 0;
        equal_count = 0;
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::Vertical(const std::string& word) {
  CharPositions character{};
  std::vector<CharPositions> char_positions;
  WordLocation word_found;
  int word_index = 0;
  unsigned long equal_count = 0;
  for (size_t j = 0; j < puzzle_width_; j++) {
    char_positions.clear();
    for (size_t i = 0; i < puzzle_height_; i++) {
      if (puzzle_[i][j] == word.at(word_index)) {
        character = {word.at(word_index), i, j};
        char_positions.push_back(character);
        word_index++;
        equal_count++;
        if (equal_count == word.size()) {
          word_found = {word, char_positions};
          return word_found;
        }
      } else if (puzzle_[i][j] == word.at(0)) {
        char_positions.clear();
        word_index = 1;
        equal_count = 1;
        character = {word.at(0), i, j};
        char_positions.push_back(character);
      } else {
        char_positions.clear();
        word_index = 0;
        equal_count = 0;
      }
    }
  }
  return WordLocation{};
}
WordLocation WordSearchSolver::RightDiag(const std::string& word) {
  CharPositions character{};
  std::vector<CharPositions> char_positions;
  WordLocation word_found;
  for (size_t i = 0; i < puzzle_height_; i++) {
    char_positions.clear();
    size_t row = i;
    for (size_t j = 0; j < puzzle_width_; j++) {
      char_positions.clear();
      int word_index = 0;
      unsigned long equal_count = 0;
      row = i;
      if (puzzle_[i][j] == word[0]) {
        size_t col = j;
        for (unsigned long k = 0; k < word.size(); k++) {
          if (puzzle_[row][col] == word.at(word_index)) {
            character = {word.at(word_index), row, col};
            char_positions.push_back(character);
            word_index++;
            equal_count++;
            row++;
            col++;
            if (equal_count == word.size())
              return WordLocation{word, char_positions};
            if (row == puzzle_height_ || col == puzzle_width_) {
              break;
            }
          } else {
            break;
          }
        }
      }
    }
  }
  return WordLocation{};
}
WordLocation WordSearchSolver::LeftDiag(const std::string& word) {
  CharPositions character{};
  std::vector<CharPositions> char_positions;
  WordLocation word_found;
  for (size_t i = 0; i < puzzle_height_; i++) {
    char_positions.clear();
    size_t row = i;
    for (size_t j = 0; j < puzzle_width_; j++) {
      char_positions.clear();
      int word_index = 0;
      unsigned long equal_count = 0;
      row = i;
      if (puzzle_[i][j] == word[0]) {
        size_t col = j;
        for (unsigned long k = 0; k < word.size(); k++) {
          if (puzzle_[row][col] == word.at(word_index)) {
            character = {word.at(word_index), row, col};
            char_positions.push_back(character);
            word_index++;
            equal_count++;
            if (equal_count == word.size())
              return WordLocation{word, char_positions};
            if (row == puzzle_height_ - 1) {
              break;
            }
            row++;
            col--;
          } else {
            break;
          }
        }
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  if (direction == CheckDirection::kHorizontal) {
    return Horizontal(word);
  }
  if (direction == CheckDirection::kVertical) {
    return Vertical(word);
  }
  if (direction == CheckDirection::kRightDiag) {
    return RightDiag(word);
  }
  if (direction == CheckDirection::kLeftDiag) {
    return LeftDiag(word);
  }
  return WordLocation{};
}
WordLocation WordSearchSolver::FindWord(const std::string& word) {
  WordLocation word_found;
  word_found = FindWord(word, CheckDirection::kHorizontal);
  if (word_found.word == word) {
    return word_found;
  }
  word_found = FindWord(word, CheckDirection::kVertical);
  if (word_found.word == word) {
    return word_found;
  }
  word_found = FindWord(word, CheckDirection::kRightDiag);
  if (word_found.word == word) {
    return word_found;
  }
  word_found = FindWord(word, CheckDirection::kLeftDiag);
  if (word_found.word == word) {
    return word_found;
  }
  return word_found;
}

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}