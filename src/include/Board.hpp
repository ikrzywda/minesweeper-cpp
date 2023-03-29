#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include "Field.hpp"
#include "flood_fill.hpp"

#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <vector>

enum GameMode { DEBUG = 2, EASY = 100, NORMAL = 5, HARD = 3 };
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
  int mine_count;
  std::vector<Field> board;
  GameMode game_mode;
  GameState game_state;

  int get_adjacent_field_indices(
      unsigned long field_index,
      std::vector<unsigned long> &adjacent_indices) const;
  void evaluate_score();
  void populate_board_debug();
  void populate_board(int mine_count);
  void eager_compute_mine_count();
  int reveal_adjacent_fields(unsigned long field_index);

  std::vector<std::function<void()>> board_updated_callbacks;
  std::vector<std::function<void(GameState)>> game_state_updated_callbacks;

  void emit_game_state_updated();
  void emit_board_updated();

public:
  Board(int width, int height, GameMode game_mode);
  unsigned long compute_field_index(int row, int col) const;

  void subscribe_to_board_updated(std::function<void()> callback);
  void subscribe_to_game_state_updated(std::function<void(GameState)> callback);

  void debug_display() const;
  int set_field(int x, int y, Field value);

  int get_width() const;
  int get_height() const;

  int count_mines(unsigned long field_index) const;
  bool has_flag(unsigned long field_index) const;
  void toggle_flag(unsigned long field_index);
  void reveal_field(unsigned long field_index);

  const std::vector<Field> &get_board() const;
  GameMode get_game_mode() const;
  GameState get_game_state() const;
};

#endif
