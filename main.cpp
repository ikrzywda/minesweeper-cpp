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

  controller.run();
  return 0;
}
