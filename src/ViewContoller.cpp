#include "include/ViewController.hpp"

void ViewController::draw() {
  switch (this->current_view) {
  case Views::BOARD:
    this->board_view.draw(this->window, sf::RenderStates::Default);
    break;
  case Views::GAME_OVER:
    break;
  case Views::MENU:
    break;
  }
}

void ViewController::on_game_lost() {
  this->current_view = Views::GAME_OVER;
  draw();
}

void ViewController::on_game_won() {
  this->current_view = Views::GAME_OVER;
  draw();
}

void ViewController::on_board_update() {
  this->board_view.update();
  draw();
}

void ViewController::on_game_start() {
  this->current_view = Views::BOARD;
  draw();
}

// TODO: move to BoardView
void ViewController::on_click_game_view(sf::Vector2i mouse_position) {
  int row, col;
  if (mouse_position.x < this->board_view.get_position().x ||
      mouse_position.x >
          this->board_view.get_position().x + this->board_view.get_size().x ||
      mouse_position.y < this->board_view.get_position().y ||
      mouse_position.y >
          this->board_view.get_position().y + this->board_view.get_size().y) {
    return;
  }

  row = (mouse_position.y - this->board_view.get_position().y) /
        this->board_view.get_field_dimensions().y;
  col = (mouse_position.x - this->board_view.get_position().x) /
        this->board_view.get_field_dimensions().x;

  this->game_controller.uncover_field(row * col);
}

void ViewController::on_click() {
  sf::Vector2i mouse_position = sf::Mouse::getPosition(this->window);
  switch (this->current_view) {
  case Views::BOARD:
    on_click_game_view(mouse_position);
    break;
  case Views::GAME_OVER:
    on_click_game_over_view(mouse_position);
    break;
  case Views::MENU:
    on_click_menu_view(mouse_position);
    break;
  }
}

ViewController::ViewController(sf::RenderWindow &window, GameState &game_state,
                               BoardView &board_view_ref,
                               GameController &game_controller_ref)
    : window(window), board_view(board_view_ref),
      game_controller(game_controller_ref) {
  game_state.subscribe_to_board_updated(
      std::bind(&ViewController::on_board_update, this));
  game_state.subscribe_to_game_won(
      std::bind(&ViewController::on_game_won, this));
  game_state.subscribe_to_game_lost(
      std::bind(&ViewController::on_game_lost, this));
}
