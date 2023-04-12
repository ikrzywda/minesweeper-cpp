#include "include/GUIViewController.hpp"

void GUIViewController::reveal_field(unsigned long field_index) {
  board.reveal_field(field_index);
}

void GUIViewController::flag_field(int row, int col) {
  unsigned long field_index = board.compute_field_index(row, col);
  board.toggle_flag(field_index);
}

void GUIViewController::start_game() { board.start_game(); }

void GUIViewController::run() {
  board.start_game();
  unsigned long mouse_field_index;
  sf::Event event;
  while (1) {
    sf::Event event;

    // board.set_mouse_position(sf::Mouse::getPosition(this->window));
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      this->board.set_mouse_position(sf::Mouse::getPosition(this->window));
    }
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
  }
}
