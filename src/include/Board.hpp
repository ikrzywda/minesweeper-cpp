#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include "Field.hpp"

#include <iomanip>
#include <iostream>
#include <vector>

enum GameMode { DEBUG = 2, EASY = 1, NORMAL = 5, HARD = 3 };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

class Board {
  int width;
  int height;
  GameMode game_mode;
  GameState game_state;
  std::vector<Field> board;

  unsigned long get_field_index(int row, int col) const;

public:
  Board(int width, int height, GameMode game_mode);
  void debug_display() const;
  int set_field(int x, int y, Field value);

  int get_width() const;
  int get_height() const;
  int get_mine_count() const;

  int count_mines(int row, int col) const;
  bool has_flag(int row, int col) const;
  void toggle_flag(int row, int col);
  void reveal_field(int row, int col);

  GameState get_game_state() const;
};

#endif
