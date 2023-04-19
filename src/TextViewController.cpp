// #include "include/TextViewController.hpp"

// void TextViewController::reveal_field(int row, int col) {
//   unsigned long field_index = board.compute_field_index(row, col);
//   board.reveal_field(field_index);
// }

// void TextViewController::flag_field(int row, int col) {
//   unsigned long field_index = board.compute_field_index(row, col);
//   board.toggle_flag(field_index);
// }

// void TextViewController::run() {
//   board.start_game();
//   while (board.get_game_state() == RUNNING) {
//     std::cout << "Enter row and column: ";
//     int row, col;
//     std::cin >> row >> col;
//     std::cout << "Enter f to flag, r to reveal: ";
//     char action;
//     std::cin >> action;
//     if (action == 'f') {
//       flag_field(row, col);
//     } else if (action == 'r') {
//       reveal_field(row, col);
//     }
//   }
// }
