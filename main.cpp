#include "src/include/Board.hpp"
#include "src/include/TextView.hpp"
#include "src/include/TextViewController.hpp"

int main() {
  Board board(10, 10, DEBUG);
  board.debug_display();
  TextViewController controller(board);
  TextView view(board, controller);

  controller.run();

  return 0;
}
