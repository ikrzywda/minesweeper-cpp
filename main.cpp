#include <cstdlib>

#include "src/include/Board.hpp"

int main() {
  Board board(10, 10, NORMAL);
  board.debug_display();
  std::cout << "\n MINE COUNT: " << board.get_mine_count() << '\n';
  return 0;
}
