#include "include/MenuView.hpp"

MenuView::MenuView(sf::Vector2f view_position, sf::Vector2f view_dimensions,
                   GameState &game_state)
    : game_state(game_state) {
  sf::Vector2f button_position(view_position.x + view_dimensions.x / 2 - 150,
                               view_position.y + view_dimensions.y / 2);
  sf::Vector2f button_size(100, 50);

  this->new_game_button = std::make_unique<TextButtonView>(
      sf::Vector2f(view_position.x + view_dimensions.x / 2 - 100,
                   view_position.y + view_dimensions.y / 2 - 150),
      sf::Vector2f(200, 50), "Start");

  this->easy_difficulty_button =
      std::make_unique<TextButtonView>(button_position, button_size, "Easy");

  this->normal_difficulty_button = std::make_unique<TextButtonView>(
      sf::Vector2f(button_position.x + 110, button_position.y), button_size,
      "Medium");

  this->hard_difficulty_button = std::make_unique<TextButtonView>(
      sf::Vector2f(button_position.x + 220, button_position.y), button_size,
      "Hard");

  this->exit_game_button = std::make_unique<TextButtonView>(
      sf::Vector2f(view_position.x + view_dimensions.x / 2 - 100,
                   view_position.y + view_dimensions.y / 2 + 200),
      sf::Vector2f(200, 50), "Exit");

  this->set_position(view_position);
  this->set_size(view_dimensions);
  this->background.setFillColor(sf::Color::Black);
  this->background.setOutlineColor(sf::Color::Black);
  this->background.setOutlineThickness(1);
  this->title.setFont(Assets::font_bold);
  this->title.setCharacterSize(50);
  this->title.setFillColor(sf::Color::White);
  this->title.setString("Minesweeper");

  this->title.setPosition(
      sf::Vector2f(view_position.x + view_dimensions.x / 2 -
                       this->title.getLocalBounds().width / 2,
                   view_position.y + 50));

  this->difficulty_title.setFont(Assets::font_bold);
  this->difficulty_title.setCharacterSize(30);
  this->difficulty_title.setFillColor(sf::Color::White);
  this->difficulty_title.setString(
      game_difficulty_names.at(game_state.get_game_difficulty()));
  this->difficulty_title.setPosition(
      sf::Vector2f(view_position.x + view_dimensions.x / 2 -
                       this->difficulty_title.getLocalBounds().width / 2,
                   view_position.y + 150));
}

void MenuView::set_size(sf::Vector2f view_dimensions) {
  this->background.setSize(view_dimensions);
  this->new_game_button->setSize(sf::Vector2f(200, 50));
  this->exit_game_button->setSize(sf::Vector2f(200, 50));
  this->new_game_button->setPosition(
      sf::Vector2f(view_dimensions.x / 2 - 100, 200));
  this->exit_game_button->setPosition(
      sf::Vector2f(view_dimensions.x / 2 - 100, 300));
}

void MenuView::set_position(sf::Vector2f view_position) {
  this->background.setPosition(view_position);
}

void MenuView::run_new_game_click_handlers() {
  for (auto &handler : this->new_game_click_handlers) {
    handler();
  }
}

void MenuView::run_exit_game_click_handlers() {
  for (auto &handler : this->exit_game_click_handlers) {
    handler();
  }
}

void MenuView::run_difficulty_click_handlers(GameDifficulty difficulty) {

  for (auto &handler : this->difficulty_click_handlers) {
    handler(difficulty);
  }
}

void MenuView::run_click_handlers(sf::Vector2i mouse_position) {
  sf::Vector2f mouse_position_f(mouse_position.x, mouse_position.y);
  // make it a map? idk
  if (this->new_game_button->getGlobalBounds().contains(mouse_position_f)) {
    this->run_new_game_click_handlers();
  } else if (this->exit_game_button->getGlobalBounds().contains(
                 mouse_position_f)) {
    this->run_exit_game_click_handlers();
  } else if (this->easy_difficulty_button->getGlobalBounds().contains(
                 mouse_position_f)) {
    this->run_difficulty_click_handlers(GameDifficulty::EASY);
  } else if (this->normal_difficulty_button->getGlobalBounds().contains(
                 mouse_position_f)) {
    this->run_difficulty_click_handlers(GameDifficulty::NORMAL);
  } else if (this->hard_difficulty_button->getGlobalBounds().contains(
                 mouse_position_f)) {
    this->run_difficulty_click_handlers(GameDifficulty::HARD);
  }
}

void MenuView::subscribe_to_new_game_click(std::function<void()> handler) {
  this->new_game_click_handlers.push_back(handler);
}

void MenuView::subscribe_to_exit_game_click(std::function<void()> handler) {
  this->exit_game_click_handlers.push_back(handler);
}

void MenuView::subscribe_to_difficulty_click(
    std::function<void(GameDifficulty)> handler) {
  this->difficulty_click_handlers.push_back(handler);
}

void MenuView::draw(sf::RenderWindow &window) const {
  window.draw(this->background);
  window.draw(this->title);

  // this->new_game_button->draw(window);
  // this->exit_game_button->draw(window);
  this->easy_difficulty_button->draw(window);
  this->normal_difficulty_button->draw(window);
  this->hard_difficulty_button->draw(window);
  for (auto &button : this->difficulty_buttons) {
    window.draw(button);
  }
}
