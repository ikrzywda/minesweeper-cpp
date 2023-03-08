#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include "Field.hpp"

#include <vector>
#include <iostream>
#include <iomanip>

class Board {
  int width;
  int height;
  std::vector<Field> board;

  public:
    Board(int width, int height);
    void debug_display() const;
    int set_field(int x, int y, Field value);
};



#endif
