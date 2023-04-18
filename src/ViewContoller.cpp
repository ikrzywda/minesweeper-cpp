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

ViewController::ViewController(sf::RenderWindow &window, GameState &game_state,
                               BoardView &board_view_ref)
    : window(window), board_view(board_view_ref) {
  game_state.subscribe_to_board_updated(
      std::bind(&ViewController::on_board_update, this));
  game_state.subscribe_to_game_won(
      std::bind(&ViewController::on_game_won, this));
  game_state.subscribe_to_game_lost(
      std::bind(&ViewController::on_game_lost, this));
}
