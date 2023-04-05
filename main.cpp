#include "src/include/Board.hpp"
#include "src/include/GUIView.hpp"
#include "src/include/GUIViewController.hpp"
#include "src/include/GUIViewModel.hpp"
#include "src/include/TextView.hpp"
#include "src/include/TextViewController.hpp"

#include <SFML/Graphics.hpp>

int main() {

  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(500, 500)), "SFML works!");
  GUIViewModel board(10, 10, DEBUG);
  GUIViewController controller(board, window);
  GUIView view(window, board);

  // controller.run();
  controller.reveal_field(6, 2);
  controller.run();
  // view.game_view();

  // Board board(10, 10, DEBUG);
  // board.debug_display();
  // TextViewController controller(board);
  // TextView view(board, controller);

  // controller.run();
  return 0;
}
