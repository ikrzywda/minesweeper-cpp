#include "include/TextView.hpp"

std::string TextView::field_to_str(Field field) {
  if (!field.is_revealed) {
    return "#";
  } else if (field.mine_count == 0) {
    return "o";
  } else {
    return std::to_string(field.mine_count);
  }

  if (field.has_mine) {
    return "x";
  }
  if (field.has_flag) {
    return "l";
  }
}

void TextView::draw() {
  std::cout << "GAME MODE: "
            << GameModeDescriptors.at(this->board.get_game_mode()) << '\n';
  std::cout << "GAME MODE: "
            << GameStateDescriptors.at(this->board.get_game_state()) << '\n';

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
}
