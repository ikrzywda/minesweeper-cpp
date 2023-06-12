#include "include/Board.hpp"

unsigned long Board::compute_field_index(int row, int col) const {
  return row * this->width + col;
}

int Board::get_adjacent_field_indices(
    unsigned long field_index,
    std::vector<unsigned long> &adjacent_indices) const {
  unsigned long current_row = field_index / this->width;
  if (field_index < 0 || field_index > this->board.size()) {
    return 0;
  }

  adjacent_indices.clear();
  if ((field_index - 1) / this->width == current_row) {
    adjacent_indices.push_back(field_index - 1);
    adjacent_indices.push_back(field_index + this->width - 1);
    adjacent_indices.push_back(field_index - this->width - 1);
  }

  if ((field_index + 1) / this->width == current_row) {
    adjacent_indices.push_back(field_index + 1);
    adjacent_indices.push_back(field_index + this->width + 1);
    adjacent_indices.push_back(field_index - this->width + 1);
  }

  adjacent_indices.push_back(field_index + this->width);
  adjacent_indices.push_back(field_index - this->width);

  return 1;
}

void Board::populate_board_debug() {
  for (int i = 0; i < height; ++i) {
    this->set_field(i, 0, Field(true, false, false));
    this->set_field(i, i, Field(true, false, false));
    this->mine_count += 2;
  }
}

void Board::populate_board(int mine_count) {
  int field_index;
  if (mine_count > this->board.size()) {
    mine_count = this->board.size();
  }
  // mine_count = this->board.size() / mine_count;

  for (int i = 0; i < mine_count;) {
    field_index = rand() % this->board.size();
    if (this->board.at(field_index).has_mine) {
      continue;
    }
    this->board.at(field_index).has_mine = true;
    this->mine_count++;
    i++;
  }
}

void Board::eager_compute_mine_count() {
  for (int i = 0; i < this->board.size(); i++) {
    if (!this->board.at(i).has_mine) {
      this->board.at(i).mine_count = this->count_mines(i);
    }
  }
}

Board::Board(int width, int height, int mine_count, int flag_count) {
  this->width = width;
  this->height = height;
  this->board = std::vector<Field>(width * height, Field());
  this->mine_count = 0;
  this->flag_count = flag_count;

  this->populate_board(mine_count);
  this->eager_compute_mine_count();
}

Board::Board(int width, int height) {
  this->width = width;
  this->height = height;
  this->board = std::vector<Field>(width * height, Field());
  this->mine_count = 0;
  this->flag_count = 2137;

  this->populate_board_debug();
  this->eager_compute_mine_count();
}

void Board::subscribe_to_board_updated(std::function<void()> callback) {
  this->board_updated_callbacks.push_back(callback);
}

void Board::subscribe_to_game_lost(std::function<void()> callback) {
  this->on_game_lost_callbacks.push_back(callback);
}

void Board::subscribe_to_game_won(std::function<void()> callback) {
  this->on_game_won_callbacks.push_back(callback);
}

void Board::run_callbacks_board_updated() {
  for (auto callback : this->board_updated_callbacks) {
    callback();
  }
}

void Board::run_callbacks_game_won() {
  for (auto callback : this->on_game_won_callbacks) {
    callback();
  }
}

void Board::run_callbacks_game_lost() {
  for (auto callback : this->on_game_lost_callbacks) {
    callback();
  }
}

void Board::debug_display() const {
  int row = 0, col = 0;
  std::string current_field_str;

  std::cout << "    ";

  for (int i = 0; i < this->width; i++) {
    std::cout << i << std::setw(5);
  }

  for (auto field : this->board) {
    current_field_str = field.get_debug_str();

    if (!(col % this->width)) {
      std::cout << '\n';
      std::cout << row++ << std::setw(6);
    }
    std::cout << current_field_str;
    col++;
  }
}

int Board::set_field(int x, int y, Field value) {
  unsigned long index = x + this->width * y;
  if (this->board.size() < index) {
    return 0;
  }

  this->board.at(index) = value;
  return 1;
}

int Board::get_width() const { return this->width; }
int Board::get_height() const { return this->height; }

int Board::count_mines(unsigned long field_index) const {
  std::vector<unsigned long> adjacent_indices(8);

  if (!this->get_adjacent_field_indices(field_index, adjacent_indices)) {
    return -1;
  }
  return std::accumulate(std::begin(adjacent_indices),
                         std::end(adjacent_indices), 0, [&](auto sum, auto i) {
                           if (i < 0 || i >= this->board.size()) {
                             return sum;
                           }

                           if (this->board.at(i).has_mine) {
                             return sum + 1;
                           }

                           return sum;
                         });
}

void Board::evaluate_score() {
  int uncovered_field_count =
      this->board.size() - std::accumulate(std::begin(this->board),
                                           std::end(this->board), 0,
                                           [&](auto sum, auto field) {
                                             if (field.is_revealed) {
                                               return sum + 1;
                                             }
                                             return sum;
                                           });
  if (uncovered_field_count < this->mine_count) {
    std::cout << "You won!" << std::endl;
    this->run_callbacks_game_won();
  }
}

bool Board::has_flag(unsigned long field_index) const {
  if (field_index < 0 || field_index > this->board.size()) {
    return false;
  }

  return this->board.at(field_index).has_flag;
}

void Board::toggle_flag(unsigned long field_index) {
  if (field_index < 0 || field_index > this->board.size()) {
    return;
  }

  this->board.at(field_index).has_flag = !this->board.at(field_index).has_flag;
  this->flag_count--;
  this->run_callbacks_board_updated();
}

void Board::reveal_field(unsigned long field_index) {
  Field field;

  if (field_index < 0 || field_index > this->board.size()) {
    return;
  }

  field = this->board.at(field_index);

  if (field.is_revealed) {
    return;
  }
  if (field.has_mine) {
    this->run_callbacks_game_lost();
    return;
  }
  field.is_revealed = true;
  this->board.at(field_index) = field;
  this->reveal_adjacent_fields(field_index);
  this->run_callbacks_board_updated();
  this->evaluate_score();
}

int Board::reveal_adjacent_fields(unsigned long field_index) {
  std::function<bool(Field &)> mutating_predicate = [](Field &field) {
    if (field.is_revealed || field.has_mine) {
      return false;
    }
    if (field.mine_count > 0) {
      field = Field(false, false, true, field.mine_count);
      return false;
    }
    field.is_revealed = true;
    return true;
  };

  flood_fill(this->board, this->width, this->height, mutating_predicate,
             field_index);
  return 1;
}

const std::vector<Field> &Board::get_board() const { return board; }
