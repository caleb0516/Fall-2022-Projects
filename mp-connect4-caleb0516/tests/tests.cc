
/////////////////////////////////////////////////////////////////////////////////////////////asdsadsadsadsadasdasdasdsadasdasdasdsadas
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

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
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}
void CopyBoard(DiskType solution[6][7], Board& b) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      b.board[i][j] = solution[i][j];
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
//lang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}
TEST_CASE("Board initialization not", "[board_init_not]") {
  // SECTION("Can use sections") {}
  //clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE_FALSE(AreEqual(solution, student.board));
}
TEST_CASE("If column is > kBoardWidth or less than 0 throw run_time_error ",
          "[Stop, Dropping out of bounds]") {
  Board b;
  InitBoard(b);
  REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer1, kBoardWidth));
  REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer1, -1));
  REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer2, kBoardWidth));
  REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer2, -1));
}
TEST_CASE("If column is full throw run_time_error",
          "[Stop Drop To Full Column]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  Board b;
  InitBoard(b);
  CopyBoard(solution, b);
  REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer1, 0));
  REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer2, 0));
}
TEST_CASE("If column is completely full throw run_time_error",
          "[Stop Drop To Full Column]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1},
                                                  {DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1}};
  Board b;
  InitBoard(b);
  CopyBoard(solution, b);
  REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer1, 0));
  REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer2, 0));
}
TEST_CASE("If column is not full drop disk to desired location and return b",
          "[DropDiskToBoard]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  REQUIRE(AreEqual(solution, b.board));
}

TEST_CASE("If row >= kBoardHeight || row <0 return false",
          "Row out of bounds") {
  REQUIRE_FALSE(BoardLocationInBounds(-1, 0));
  REQUIRE_FALSE(BoardLocationInBounds(8, 0));
  REQUIRE_FALSE(BoardLocationInBounds(8, 10));
}

TEST_CASE("If column >= kBoardHeight || column <0 return false",
          "column out of bounds") {
  REQUIRE_FALSE(BoardLocationInBounds(0, 9));
  REQUIRE_FALSE(BoardLocationInBounds(0, -1));
  REQUIRE_FALSE(BoardLocationInBounds(8, 10));
}

TEST_CASE("If column and row in bounds return true ", "BoardLocationInBounds") {
  REQUIRE(BoardLocationInBounds(1, 4));
  REQUIRE(BoardLocationInBounds(5, 3));
}

TEST_CASE("If player 1 has four in a row return true", "Check Player1]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  Board b;
  InitBoard(b);
  CopyBoard(solution, b);
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  // REQUIRE(CheckForWinner(b,DiskType::kEmpty));
}

TEST_CASE("If player 2 has four in a row return true", "[check Player2]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  Board b;
  InitBoard(b);
  CopyBoard(solution, b);
  REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  // REQUIRE(CheckForWinner(b,DiskType::kEmpty));
}

TEST_CASE("If nobody has four in a row return false", "[Check No Winner]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  Board b;
  InitBoard(b);
  CopyBoard(solution, b);
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  // REQUIRE(CheckForWinner(b,DiskType::kEmpty));
}

TEST_CASE(
    "If player 1 has a horizontal win, return true for kplayer1 and "
    "khorizontal",
    "[Search for Player 1 horizontal Win]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  Board b;
  InitBoard(b);
  CopyBoard(solution, b);
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
}

TEST_CASE(
    "If Player2 has a horizontal win, return true for kPlayer2 and khorizontal",
    "[Search for Player 2 horizontal Win]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  Board b;
  InitBoard(b);
  CopyBoard(solution, b);
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
}

TEST_CASE(
    "If Player1 has a vertical win, return true for kplayer1 and khorizontal",
    "[Search for Player1 vertical Win]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  Board b;
  InitBoard(b);
  CopyBoard(solution, b);
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
}

TEST_CASE(
    "If Player1 has a Right Diagonal win, return true for kplayer1 and "
    "kRightDiagonal",
    "[Search for Player1 Right Diagonal Win]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  Board b;
  InitBoard(b);
  CopyBoard(solution, b);
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
}

TEST_CASE(
    "If Player1 has a Left Diagonal win, return true for kplayer1 and "
    "khorizontal",
    "[Search for Player1 Left Diagonal Win]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  Board b;
  InitBoard(b);
  CopyBoard(solution, b);
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
}

TEST_CASE(
    "If Player2 has a vertical win, return true for kPlayer2 and khorizontal",
    "[Search for Player2 vertical Win]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  Board b;
  InitBoard(b);
  CopyBoard(solution, b);
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
}

TEST_CASE(
    "If Player2 has a Right Diagonal win, return true for kPlayer2 and "
    "khorizontal",
    "[Search for Player2 Right Diagonal Win]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  Board b;
  InitBoard(b);
  CopyBoard(solution, b);
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
}

TEST_CASE(
    "If Player2 has a Left Diagonal win, return true for kPlayer2 and "
    "khorizontal",
    "[Search for Player2 Left Diagonal Win]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kPlayer1,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer1,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kPlayer2,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  Board b;
  InitBoard(b);
  CopyBoard(solution, b);
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
}

TEST_CASE("If there is no four in a row return false", "[Search When No WIN]") {
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  Board b;
  InitBoard(b);
  CopyBoard(solution, b);
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
}