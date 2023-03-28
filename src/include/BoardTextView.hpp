#ifndef BOARD_DISPLAY_HPP
#define BOARD_DISPLAY_HPP

#include "Board.hpp"

#include <iostream>

class BoardTextView {
  std::shared_ptr<Board> board;
  std::string field_to_str(Field field);

public:
  BoardTextView(std::shared_ptr<Board> board);
  void draw();
};

#endif
