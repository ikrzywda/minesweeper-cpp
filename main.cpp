#include <cstdlib>

#include "src/include/Board.hpp"
#include "src/include/TextView.hpp"
#include "src/include/flood_fill.hpp"

int main() {
  Board board(10, 10, DEBUG);
  board.debug_display();
  board.reveal_field(6, 2);
  std::cout << '\n';
  board.debug_display();
  TextView view(board);
  view.draw();

  return 0;
}
