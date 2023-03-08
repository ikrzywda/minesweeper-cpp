#include <cstdlib>

#include "src/include/Board.hpp"


Board board_fixture() {
  int width = 10, height = 10;
  Board fixture(width, height);

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      fixture.set_field(i, j, Field(std::rand() > RAND_MAX / 2,std::rand() > RAND_MAX / 2,std::rand() > RAND_MAX / 2
      ));
    }
  }

  return fixture;
}


int main() {
  Board board = board_fixture();
  board.debug_display();
  return 0;
}
