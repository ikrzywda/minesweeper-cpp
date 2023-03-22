#ifndef BOARD_DISPLAY_HPP
#define BOARD_DISPLAY_HPP

#include "Board.hpp"

#include <iostream>

class BoardTextView {
  std::shared_ptr<Board> board;

public:
  BoardTextView(std::shared_ptr<Board> board);
  void draw();
};

#endif
