#include <cstdlib>

#include "src/include/Board.hpp"
#include "src/include/BoardTextDisplay.hpp"

int main() {
  auto board_ref = std::make_shared<Board>(Board(10, 10, DEBUG));
  std::cout << "\n MINE COUNT: " << board_ref->get_mine_count() << '\n';
  std::cout << "\n COUNT MINES AT (1,1): " << board_ref->count_mines(1, 1)
            << '\n';

  BoardTextView view(board_ref);
  view.draw();

  return 0;
}
