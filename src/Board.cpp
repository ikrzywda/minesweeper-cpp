#include "include/Board.hpp"

unsigned long Board::get_field_index(int row, int col) const {
  return row * this->width + col;
}

Board::Board(int width, int height, GameMode game_mode) {
  this->width = width;
  this->height = height;
  this->game_mode = game_mode;
  this->board = std::vector<Field>(width * height, Field());
  this->game_state = RUNNING;

  int mine_count;
  int field_index;

  if (game_mode == DEBUG) {
    for (int i = 0; i < height; ++i) {
      this->set_field(i, 0, Field(true, false, false));
      this->set_field(i, i, Field(true, false, false));
    }
    return;
  }

  mine_count = this->board.size() / game_mode;

  for (int i = 0; i < mine_count;) {
    field_index = rand() % this->board.size();

    if (this->board.at(field_index).has_mine) {
      continue;
    }

    this->board.at(field_index).has_mine = true;
    i++;
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

    current_field_str = field.get_display_str();

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
int Board::get_mine_count() const {
  int mine_count = 0;

  for (auto field : this->board) {
    if (field.has_mine) {
      mine_count++;
    }
  }
  return mine_count;
}

int Board::count_mines(int row, int col) const {

  unsigned long field_index;

  if ((field_index = get_field_index(row, col)) < 0 ||
      field_index > this->board.size()) {
    return -1;
  }

  unsigned long adjacent_indeces[8] = {
      get_field_index(row + 1, col - 1), get_field_index(row + 1, col),
      get_field_index(row + 1, col + 1), get_field_index(row, col + 1),
      get_field_index(row - 1, col - 1), get_field_index(row - 1, col),
      get_field_index(row - 1, col + 1), get_field_index(row, col - 1),
  };
  int mine_count = 0;

  for (auto i : adjacent_indeces) {

    if (i < 0 || i >= this->board.size()) {
      continue;
    }

    if (this->board.at(i).has_mine) {
      mine_count++;
    }
  }

  return mine_count;
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
  } else if (field.has_mine) {
    this->game_state = FINISHED_LOSS;
  } else {
    field.has_flag = true;
    field.is_revealed = true;
    this->board.at(field_index) = field;
  }
}

GameState Board::get_game_state() const { return this->game_state; }
