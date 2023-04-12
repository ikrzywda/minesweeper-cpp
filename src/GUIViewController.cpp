#include "include/GUIViewController.hpp"

void GUIViewController::reveal_field(unsigned long field_index) {
  board.reveal_field(field_index);
}

void GUIViewController::flag_field(unsigned long field_index) {
  board.toggle_flag(field_index);
}

void GUIViewController::start_game() { board.start_game(); }

void GUIViewController::run() {
  sf::Event event;
  while (1) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      this->board.dispatch_left_mouse_click(
          sf::Mouse::getPosition(this->window));
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
      this->board.dispatch_right_mouse_click(
          sf::Mouse::getPosition(this->window));
    }
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
  }
}
