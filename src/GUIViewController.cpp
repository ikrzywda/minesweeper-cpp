#include "include/GUIViewController.hpp"

void GUIViewController::reveal_field(int row, int col) {
  unsigned long field_index = board.compute_field_index(row, col);
  board.reveal_field(field_index);
}

void GUIViewController::flag_field(int row, int col) {
  unsigned long field_index = board.compute_field_index(row, col);
  board.toggle_flag(field_index);
}

void GUIViewController::run() {
  board.start_game();
  while (board.get_game_state() == RUNNING) {
    sf::Event event;
    board.set_mouse_position(sf::Mouse::getPosition(window));
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
  }
}
