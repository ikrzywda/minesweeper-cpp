#include "include/GUIViewController.hpp"

void GUIViewController::run() {
  board.start_game();
  while (board.get_game_state() == RUNNING) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
  }
}
