#include "src/include/Board.hpp"
#include "src/include/GUIView.hpp"
#include "src/include/GUIViewController.hpp"
#include "src/include/TextView.hpp"
#include "src/include/TextViewController.hpp"

#include <SFML/Graphics.hpp>

int main() {

  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(500, 500)), "SFML works!");
  Board board(10, 10, DEBUG);
  GUIViewController controller(board, window);
  GUIView view(window, board);

  // controller.run();
  controller.reveal_field(6, 2);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    view.game_view();
  }
  // view.game_view();

  // Board board(10, 10, DEBUG);
  // board.debug_display();
  // TextViewController controller(board);
  // TextView view(board, controller);

  // controller.run();
  return 0;
}
