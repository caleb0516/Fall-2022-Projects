#include <iostream>

#include "board.cc"
#include "board.hpp"

int main() {
  Board b;
  InitBoard(b);

  /* DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);*/
  b.board[0][1] = DiskType::kPlayer1;
  b.board[1][2] = DiskType::kPlayer1;
  b.board[2][3] = DiskType::kPlayer1;
  b.board[3][4] = DiskType::kPlayer1;
  // b.board[4][5] = DiskType::kPlayer1;
  //  b.board[5][6] = DiskType::kPlayer1;
  Board c;
  c.board = b.board;

  if (CheckForWinner(b, DiskType::kPlayer1) == 1)
    std::cout << "there is a winner\n";
  else
    std::cout << "there is no winner\n";
  // std::cout << CheckForWinner(b, DiskType::kPlayer2) << std::endl;
  std::cout << BoardToStr(c);
}
