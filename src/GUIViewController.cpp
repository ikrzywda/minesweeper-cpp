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
  unsigned long mouse_field_index;
  sf::Event event;
  while (board.get_game_state() == RUNNING) {
    sf::Event event;

    board.set_mouse_position(sf::Mouse::getPosition(this->window));
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      mouse_field_index = this->board.mouse_position.x / 50 +
                          this->board.mouse_position.y / 50 * board.get_width();
      reveal_field(mouse_field_index / board.get_width(),
                   mouse_field_index % board.get_width());
    }
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
  }
}
