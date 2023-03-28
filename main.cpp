#include <cstdlib>

#include "src/include/Board.hpp"
#include "src/include/BoardTextView.hpp"
#include "src/include/flood_fill.hpp"

int main() {
  // auto board_ref = std::make_shared<Board>(Board(10, 10, DEBUG));
  // board_ref->reveal_field(6, 2);
  // board_ref->debug_display();
  // std::cout << '\n';
  // board_ref->debug_display();
  // BoardTextView view(board_ref);
  // view.draw();
  std::vector<int> board = {1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 3,
                            2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1};
  const std::vector<int> overridable_values = {2};
  const int overriding_value = 9;
  unsigned long start_index = 7;

  std::cout << "Before flood fill:" << std::endl;
  for (unsigned long i = 0; i < board.size(); i++) {
    std::cout << board[i] << " ";
    if ((i + 1) % 5 == 0) {
      std::cout << std::endl;
    }
  }

  flood_fill(board, 5, 5, overridable_values, overriding_value, start_index);

  std::cout << "After flood fill:" << std::endl;
  for (unsigned long i = 0; i < board.size(); i++) {
    std::cout << board[i] << " ";
    if ((i + 1) % 5 == 0) {
      std::cout << std::endl;
    }
  }
  return 0;
}
