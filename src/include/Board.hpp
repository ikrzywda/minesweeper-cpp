#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include "Field.hpp"

#include <iomanip>
#include <iostream>
#include <vector>

enum GameMode { DEBUG, EASY, NORMAL, HARD };

class Board {
  int width;
  int height;
  GameMode game_mode;
  std::vector<Field> board;

public:
  Board(int width, int height, GameMode game_mode);
  void debug_display() const;
  int set_field(int x, int y, Field value);
};

#endif
