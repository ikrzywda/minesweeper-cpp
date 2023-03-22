#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include "Field.hpp"

#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

enum GameMode { DEBUG = 2, EASY = 1, NORMAL = 5, HARD = 3 };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

const std::map<int, std::string> GameModeDescriptors = {
    {DEBUG, "debug"}, {EASY, "easy"}, {NORMAL, "normal"}, {HARD, "hard"}};

const std::map<int, std::string> GameStateDescriptors = {
    {RUNNING, "running"},
    {FINISHED_WIN, "finished_win"},
    {FINISHED_LOSS, "finished_loss"}};

class Board {
  int width;
  int height;
  std::vector<Field> board;
  GameMode game_mode;
  GameState game_state;

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

  const std::vector<Field> &get_board() const;
  GameMode get_game_mode() const;
  GameState get_game_state() const;
};

#endif
