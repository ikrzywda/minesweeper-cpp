#include "include/Board.hpp"

Board::Board(int width, int height) {
  this->width = width;
  this->height = height;
  this->board = std::vector<Field>(width * height, Field());
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
  int index = x + this->width * y;
  if (this->board.size() < index) {
    return 0;
  }
  
  this->board.at(index) = value;
  return 1;
}
