#include "include/TextView.hpp"

std::string TextView::field_to_str(Field field) {
  if (!field.is_revealed) {
    return field.has_flag ? "l" : "#";
  } else if (field.mine_count == 0) {
    return "o";
  } else {
    return std::to_string(field.mine_count);
  }

  if (field.has_mine) {
    return "x";
  }
}

void TextView::game_view() {

  if (this->board.get_game_state() != RUNNING) {
    return;
  }

  int row = 0, col = 0;
  std::string current_field_str;
  std::cout << "    ";

  const std::vector<Field> &game_board = this->board.get_board();

  for (int i = 0; i < this->board.get_width(); i++) {
    std::cout << i << std::setw(5);
  }

  for (auto field : game_board) {

    if (!(col % this->board.get_width())) {
      std::cout << '\n';
      std::cout << row++ << std::setw(4);
    }
    std::cout << this->field_to_str(field) << std::setw(5);
    col++;
  }
  std::cout << "\n\n";
}

void TextView::input_view() {
  int row, col;
  std::string action;

  std::cout << "Enter row: ";
  std::cin >> row;
  std::cout << "Enter col: ";
  std::cin >> col;
  std::cout << "Enter action: ";
  std::cin >> action;

  if (action == "r") {
    this->controller.reveal_field(row, col);
  } else if (action == "f") {
    this->controller.flag_field(row, col);
  }
}

void TextView::conclusion_view(GameState game_state) {
  if (game_state == RUNNING) {
    return;
  }
  std::cout << "Game over!\n";
  std::cout << "You " << (game_state == FINISHED_WIN ? "won" : "lost") << "!\n";
}
