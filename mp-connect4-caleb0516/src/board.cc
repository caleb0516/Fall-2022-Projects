#include "board.hpp"

// you might need additional includes
#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  for (size_t i = 0; i < Board::kBoardHeight; i++) {
    // as to b.kboard... not Board:kboard...
    //  height goes first in array
    for (size_t j = 0; j < Board::kBoardWidth; j++) {
      // std::cout << "i is " << i << "j is " << j << std::endl;
      b.board[i][j] = DiskType::kEmpty;
    }
  }

  // b.board[0][0] = DiskType::kEmpty;
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  // if (disk != DiskType::kEmpty) {
  if (col >= Board::kBoardWidth || col < 0)
    throw std::runtime_error("Out of Bounds");
  if (col < Board::kBoardWidth) {  // don't need if statement
    // std::cout << "inside if?\n";
    for (int row = 0; row < Board::kBoardHeight; row++) {
      // std::cout << "row is: " << row << "column is: " << col << std::endl;
      if (b.board[row][col] == DiskType::kEmpty) {
        b.board[row][col] = disk;
        break;  // break cause only 1 disk at a time
      }
      if (row == Board::kBoardHeight - 1)
        throw std::runtime_error("Column is full");
    }
  }
  //}
}
bool CheckHorizontalWin(Board& b, DiskType disk) {
  bool winner = false;
  for (size_t row = 0; row < Board::kBoardHeight; row++) {
    int four_counter = 0;  // start at 0 for each new row
    // start at row 0 col 0 and see if there is 4 in a row horizontally
    for (size_t column = 0; column < Board::kBoardWidth; column++) {
      if (b.board[row][column] == disk)
        // if the position is taken by the player disk is assigned to add 1 to
        // the 4 counter
        four_counter++;
      else
        four_counter = 0;
      if (four_counter == 4) {
        winner = true;
        return winner;
        break;
      }
    }
  }
  return winner;
}
bool CheckVerticalWin(Board& b, DiskType disk) {
  bool winner = false;
  for (size_t column = 0; column < Board::kBoardWidth; column++) {
    int four_counter = 0;  // start at 0 for each new column
    // start at row 0 col 0 and see if there is 4 in a row horizontally
    for (size_t row = 0; row < Board::kBoardWidth; row++) {
      if (b.board[row][column] == disk)
        // if the position is taken by the player disk is assigned to add 1 to
        // the 4 counter
        four_counter++;
      else
        four_counter = 0;
      if (four_counter == 4) {
        winner = true;
        return winner;
        break;
      }
    }
  }
  return winner;
}

bool CheckRightDiagonalWin(Board& b, DiskType disk) {
  bool winner = false;
  int four_counter = 0;
  for (int column = 1; column < 4; column++) {
    four_counter = 0;
    int column_two = column;
    int row = 0;
    while (column_two < Board::kBoardWidth) {
      if (b.board[row][column_two] == disk)
        four_counter++;
      else
        four_counter = 0;
      if (four_counter == 4) {
        winner = true;
        break;
      }
      column_two++;
      row++;
    }
    if (four_counter == 4) break;
  }
  for (int row = 0; row < Board::kBoardHeight - 3; row++) {
    four_counter = 0;
    int row_two = row;
    int column = 0;
    while (row_two < Board::kBoardHeight) {
      if (b.board[row_two][column] == disk)
        four_counter++;
      else
        four_counter = 0;
      if (four_counter == 4) {
        winner = true;
        break;
      }
      column++;
      row_two++;
    }
    if (four_counter == 4) break;
  }
  return winner;
}

bool CheckLeftDiagonalWin(Board& b, DiskType disk) {
  bool winner = false;
  int four_counter = 0;
  for (int column = Board::kBoardWidth - 2; column > 2; column--) {
    four_counter = 0;
    int column_two = column;
    int row = 0;
    while (column_two >= 0) {
      if (b.board[row][column_two] == disk)
        four_counter++;
      else
        four_counter = 0;
      if (four_counter == 4) {
        winner = true;
        break;
      }
      column_two--;
      row++;
    }
    if (four_counter == 4) break;
  }
  for (size_t row = 0; row < Board::kBoardHeight - 3; row++) {
    four_counter = 0;
    size_t row_two = row;
    int column = Board::kBoardWidth - 1;
    while (row_two < Board::kBoardHeight) {
      if (b.board[row_two][column] == disk)
        four_counter++;
      else
        four_counter = 0;
      if (four_counter == 4) {
        winner = true;
        break;
      }
      column--;
      row_two++;
    }
    if (four_counter == 4) break;
  }
  return winner;
}

bool CheckForWinner(Board& b, DiskType disk) {
  // this checks who is in that four in a row
  return (SearchForWinner(b, disk, WinningDirection::kHorizontal) ||
          SearchForWinner(b, disk, WinningDirection::kVertical) ||
          SearchForWinner(b, disk, WinningDirection::kRightDiag) ||
          SearchForWinner(b, disk, WinningDirection::kLeftDiag));
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  // this jsut checks any four in a row
  bool winner_exists = false;
  // if (disk == DiskType::kEmpty)
  // winner_exists = false;
  // else {
  switch (to_check) {
  case WinningDirection::kHorizontal:
    winner_exists = CheckHorizontalWin(b, disk);
    break;
  case WinningDirection::kVertical:
    winner_exists = CheckVerticalWin(b, disk);
    break;
  case WinningDirection::kRightDiag:  // starting from 0,0
    winner_exists = CheckRightDiagonalWin(b, disk);
    break;
  case WinningDirection::kLeftDiag:  // start point 0,6
    winner_exists = CheckLeftDiagonalWin(b, disk);
    break;
  default:
    winner_exists = false;
    break;
  }
  //}
  return winner_exists;
}
bool BoardLocationInBounds(int row, int col) {
  bool inbounds = true;
  if (row >= Board::kBoardHeight || row < 0) {
    inbounds = false;
  }
  if (col >= Board::kBoardWidth || col < 0) {
    inbounds = false;
  }

  return inbounds;
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}