#include "include/Board.hpp"

unsigned long Board::get_field_index(int row, int col) const {
  return row * this->width + col;
}

int Board::get_adjacent_field_indices(
    unsigned long field_index,
    std::vector<unsigned long> &adjacent_indices) const {

  if (field_index < 0 || field_index > this->board.size()) {
    return 0;
  }

  adjacent_indices.clear();
  if (field_index % this->width != 0) {
    adjacent_indices.push_back(field_index - 1);
    adjacent_indices.push_back(field_index + this->width - 1);
    adjacent_indices.push_back(field_index - this->width - 1);
  }

  if (field_index % this->width != 1) {
    adjacent_indices.push_back(field_index + 1);
    adjacent_indices.push_back(field_index + this->width + 1);
    adjacent_indices.push_back(field_index - this->width + 1);
  }

  adjacent_indices.push_back(field_index + this->width);
  adjacent_indices.push_back(field_index - this->width);

  return 1;
}

void Board::populate_board() {
  int mine_count;
  int field_index;

  if (this->game_mode == DEBUG) {
    for (int i = 0; i < height; ++i) {
      this->set_field(i, 0, Field(true, false, false));
      this->set_field(i, i, Field(true, false, false));
    }
    return;
  }

  mine_count = this->board.size() / this->game_mode;

  for (int i = 0; i < mine_count;) {
    field_index = rand() % this->board.size();

    if (this->board.at(field_index).has_mine) {
      continue;
    }

    this->board.at(field_index).has_mine = true;
    i++;
  }
}

void Board::eager_compute_mine_count() {
  for (int row = 0; row < this->height; row++) {
    for (int col = 0; col < this->width; col++) {
      if (!this->board.at(this->get_field_index(row, col)).has_mine) {
        this->board.at(this->get_field_index(row, col)).mine_count =
            this->count_mines(row, col);
      }
    }
  }
}

Board::Board(int width, int height, GameMode game_mode) {
  this->width = width;
  this->height = height;
  this->game_mode = game_mode;
  this->board = std::vector<Field>(width * height, Field());
  this->game_state = RUNNING;

  this->populate_board();
  this->eager_compute_mine_count();
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

int Board::count_mines(int row, int col) const {

  unsigned long field_index = this->get_field_index(row, col);
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

bool Board::has_flag(int row, int col) const {
  unsigned long field_index;

  if ((field_index = get_field_index(row, col)) < 0 ||
      field_index > this->board.size()) {
    return false;
  }

  return this->board.at(field_index).has_flag;
}

void Board::toggle_flag(int row, int col) {
  unsigned long field_index;
  bool flag_value;

  if ((field_index = get_field_index(row, col)) < 0 ||
      field_index > this->board.size()) {
    return;
  }

  flag_value = this->board.at(field_index).has_flag;
  this->board.at(field_index).has_flag = flag_value ? false : flag_value;
}

void Board::reveal_field(int row, int col) {
  unsigned long field_index;
  Field field;

  if ((field_index = get_field_index(row, col)) < 0 ||
      field_index > this->board.size()) {
    return;
  }

  field = this->board.at(field_index);

  if (field.is_revealed) {
    return;
    if (field.has_mine) {
      this->game_state = FINISHED_LOSS;
      return;
    }
  }
  field.is_revealed = true;
  this->board.at(field_index) = field;
  this->reveal_adjacent_fields(field_index);
}

int Board::reveal_adjacent_fields(unsigned long field_index) {
  auto uncover_field_predicate = [](const Field &field) {
    return field.is_revealed == false && field.has_mine == false;
  };

  auto field_mapping = [](const Field &field) {
    return Field(field.has_mine, field.has_flag, true, field.mine_count);
  };

  flood_fill(this->board, this->width, this->height, uncover_field_predicate,
             field_mapping, field_index);

  return 1;
}

const std::vector<Field> &Board::get_board() const { return board; }

GameState Board::get_game_state() const { return this->game_state; }

GameMode Board::get_game_mode() const { return this->game_mode; }
