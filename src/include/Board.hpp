#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

#include "Field.hpp"
#include "flood_fill.hpp"
class Board {
  int width;
  int height;
  int mine_count;
  int flag_count;
  std::vector<Field> board;

  int get_adjacent_field_indices(
      unsigned long field_index,
      std::vector<unsigned long> &adjacent_indices) const;
  void evaluate_score();
  void populate_board_debug();
  void populate_board(int mine_count);
  void eager_compute_mine_count();
  int reveal_adjacent_fields(unsigned long field_index);

  std::vector<std::function<void()>> board_updated_callbacks;
  std::vector<std::function<void()>> on_game_lost_callbacks;
  std::vector<std::function<void()>> on_game_won_callbacks;

  void run_callbacks_game_lost();
  void run_callbacks_game_won();
  void run_callbacks_board_updated();

 public:
  explicit Board(int width, int height, int mine_count, int flag_count);
  Board(int width, int height);
  unsigned long compute_field_index(int row, int col) const;

  void subscribe_to_board_updated(std::function<void()> callback);
  void subscribe_to_game_lost(std::function<void()> callback);
  void subscribe_to_game_won(std::function<void()> callback);

  void debug_display() const;
  int set_field(int x, int y, Field value);

  int get_width() const;
  int get_height() const;

  int count_mines(unsigned long field_index) const;
  bool has_flag(unsigned long field_index) const;
  void toggle_flag(unsigned long field_index);
  void reveal_field(unsigned long field_index);

  const std::vector<Field> &get_board() const;
};

#endif
