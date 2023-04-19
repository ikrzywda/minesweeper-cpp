#include "include/ViewController.hpp"

void ViewController::draw() {
  switch (this->current_view) {
  case Views::BOARD:
    this->board_view->draw(this->window);
    break;
  case Views::WON:
    this->game_over_view->draw(this->window, true);
    break;
  case Views::LOST:
    this->game_over_view->draw(this->window, false);
    break;
  case Views::MENU:
    this->menu_view->draw(this->window);
    break;
  }
}

void ViewController::on_game_lost() {
  this->current_view = Views::LOST;
  this->draw();
}

void ViewController::on_game_won() {
  this->current_view = Views::WON;
  this->draw();
}

void ViewController::on_board_update() {
  this->board_view->update();
  this->draw();
}

void ViewController::on_game_start() {
  // this->game_controller.start_game();
  this->current_view = Views::BOARD;
  this->board_view->update();
  this->draw();
}

// Case for inheritance -- to refactor
void ViewController::on_click() {
  sf::Vector2i mouse_position = sf::Mouse::getPosition(this->window);
  switch (this->current_view) {
  case Views::BOARD:
    this->board_view->run_click_handlers(mouse_position);
    break;
  case Views::LOST:
  case Views::WON:
    this->game_over_view->run_click_handlers(mouse_position);
    break;
  case Views::MENU:
    this->menu_view->run_click_handlers(mouse_position);
    break;
  }
}

ViewController::ViewController(sf::RenderWindow &window, GameState &game_state,
                               GameControllerSFML &game_controller_ref)
    : window(window), game_controller(game_controller_ref) {
  this->board_view = std::make_unique<BoardView>(
      game_state, sf::Vector2f(0, 0), sf::Vector2f(window.getSize()));
  this->menu_view = std::make_unique<MenuView>(
      sf::Vector2f(0, 0), sf::Vector2f(window.getSize()), game_state);
  this->game_over_view = std::make_unique<GameOverView>(
      sf::Vector2f(0, 0), sf::Vector2f(window.getSize()));

  this->menu_view->subscribe_to_new_game_click(
      std::bind(&ViewController::on_game_start, this));

  this->board_view->subscribe_to_field_click(
      std::bind(&GameControllerSFML::uncover_field, &game_controller_ref,
                std::placeholders::_1));

  this->game_over_view->subscribe_to_back_to_menu_click(
      [this]() { this->current_view = Views::MENU; });

  this->menu_view->subscribe_to_difficulty_click(
      [this](GameDifficulty difficulty) {
        this->current_view = Views::BOARD;
        this->game_controller.start_game(difficulty);
        board_view->update();
        this->draw();
      });

  game_state.subscribe_to_board_updated(
      std::bind(&ViewController::on_board_update, this));
  game_state.subscribe_to_game_won(
      std::bind(&ViewController::on_game_won, this));
  game_state.subscribe_to_game_lost(
      std::bind(&ViewController::on_game_lost, this));

  this->current_view = Views::MENU;
}
