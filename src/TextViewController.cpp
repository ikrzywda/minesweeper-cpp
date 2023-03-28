#include "include/TextViewController.hpp"

void TextViewController::reveal_field(int row, int col) {
  unsigned long field_index = board.compute_field_index(row, col);
  board.reveal_field(field_index);
}

void TextViewController::flag_field(int row, int col) {
  unsigned long field_index = board.compute_field_index(row, col);
  board.toggle_flag(field_index);
}
