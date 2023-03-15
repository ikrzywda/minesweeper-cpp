#include <cstdlib>

#include "src/include/Board.hpp"

int main() {
  Board board(10, 10, DEBUG);
  board.debug_display();
  std::cout << "\n MINE COUNT: " << board.get_mine_count() << '\n';
  std::cout << "\n COUNT MINES AT (1,1): " << board.count_mines(1, 1) << '\n';

  return 0;
}
