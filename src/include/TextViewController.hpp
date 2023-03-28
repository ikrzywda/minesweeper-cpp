#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Board.hpp"
#include "TextView.hpp"

class TextViewController {
  Board &board;
  TextView &view;

public:
  TextViewController(Board &board_ref, TextView &text_view_ref)
      : board(board_ref), view(text_view_ref){};
};

#endif
