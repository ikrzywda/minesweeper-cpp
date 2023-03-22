#include "include/BoardTextView.hpp"

BoardTextView::BoardTextView(std::shared_ptr<Board> board) {
  this->board = board;
}

void BoardTextView::draw() {
  std::cout << GameModeDescriptors.at(this->board->get_game_mode()) << '\n';
  std::cout << GameStateDescriptors.at(this->board->get_game_state()) << '\n';

  int row = 0, col = 0;
  std::string current_field_str;

  std::cout << "    ";

  const std::vector<Field> &game_board = this->board->get_board();

  for (int i = 0; i < this->board->get_width(); i++) {
    std::cout << i << std::setw(5);
  }

  for (auto field : game_board) {

    current_field_str = field.get_display_str();

    if (!(col % this->board->get_width())) {
      std::cout << '\n';
      std::cout << row++ << std::setw(6);
    }
    std::cout << current_field_str;
    col++;
  }
}
