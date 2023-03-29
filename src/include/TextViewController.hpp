#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Board.hpp"

class TextViewController {
  Board &board;

public:
  TextViewController(Board &board_ref) : board(board_ref){};

  void reveal_field(int row, int col);
  void flag_field(int row, int col);
  void run();
};

#endif
