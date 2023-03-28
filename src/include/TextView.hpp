#ifndef BOARD_DISPLAY_HPP
#define BOARD_DISPLAY_HPP

#include "Board.hpp"

#include <iostream>

class TextView {
  Board &board;
  std::string field_to_str(Field field);

public:
  TextView(Board &board_ref) : board(board_ref){};
  void draw();
};

#endif
