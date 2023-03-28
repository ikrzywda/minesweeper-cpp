#include <cstdlib>

#include "src/include/Board.hpp"
#include "src/include/BoardTextView.hpp"
#include "src/include/flood_fill.hpp"

int main() {
  auto board_ref = std::make_shared<Board>(Board(10, 10, DEBUG));
  board_ref->debug_display();
  board_ref->reveal_field(6, 2);
  std::cout << '\n';
  board_ref->debug_display();
  BoardTextView view(board_ref);

  return 0;
}
