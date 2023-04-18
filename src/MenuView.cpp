#include "include/MenuView.hpp"

MenuView::MenuView(sf::Vector2f view_position, sf::Vector2f view_dimensions)
    : new_game_button(sf::Vector2f(0, 0), sf::Vector2f(0, 0), "New Game"),
      exit_game_button(sf::Vector2f(0, 0), sf::Vector2f(0, 0), "Exit Game") {
  this->set_position(view_position);
  this->set_size(view_dimensions);
  this->background.setFillColor(sf::Color(0, 0, 0, 200));
  this->background.setOutlineColor(sf::Color::Black);
  this->background.setOutlineThickness(1);
  this->title.setFont(Assets::font_regular);
  this->title.setCharacterSize(50);
  this->title.setFillColor(sf::Color::White);
  this->title.setString("Minesweeper");

  this->title.setPosition(
      sf::Vector2f(view_position.x + view_dimensions.x / 2 -
                       this->title.getLocalBounds().width / 2,
                   view_position.y + 50));
}

void MenuView::set_size(sf::Vector2f view_dimensions) {
  this->background.setSize(view_dimensions);
  this->new_game_button.setSize(sf::Vector2f(200, 50));
  this->exit_game_button.setSize(sf::Vector2f(200, 50));
  this->new_game_button.setPosition(
      sf::Vector2f(view_dimensions.x / 2 - 100, 200));
  this->exit_game_button.setPosition(
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

void MenuView::run_difficulty_click_handlers(unsigned long difficulty) {
  for (auto &handler : this->difficulty_click_handlers) {
    handler(difficulty);
  }
}

void MenuView::run_new_game_click_handlers() {
  for (auto &handler : this->new_game_click_handlers) {
    handler();
  }
}

void MenuView::run_click_handlers(sf::Vector2i mouse_position) {
  if (this->new_game_button.getGlobalBounds().contains(
          sf::Vector2f(mouse_position))) {
    this->run_new_game_click_handlers();
  } else if (this->exit_game_button.getGlobalBounds().contains(
                 sf::Vector2f(mouse_position))) {
    this->run_exit_game_click_handlers();
  } else {
    for (int i = 0; i < this->difficulty_buttons.size(); i++) {
      if (this->difficulty_buttons[i].getGlobalBounds().contains(
              sf::Vector2f(mouse_position))) {
        this->run_difficulty_click_handlers(i);
      }
    }
  }
}

void MenuView::subscribe_to_new_game_click(std::function<void()> handler) {
  this->new_game_click_handlers.push_back(handler);
}

void MenuView::subscribe_to_exit_game_click(std::function<void()> handler) {
  this->exit_game_click_handlers.push_back(handler);
}

void MenuView::subscribe_to_new_game_click(std::function<void()> handler) {
  this->new_game_click_handlers.push_back(handler);
}

void MenuView::subscribe_to_exit_game_click(std::function<void()> handler) {
  this->exit_game_click_handlers.push_back(handler);
}

void MenuView::subscribe_to_difficulty_click(
    std::function<void(unsigned long)> handler) {
  this->difficulty_click_handlers.push_back(handler);
}

void MenuView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(this->background);
  target.draw(this->title);
  target.draw(this->new_game_button);
  target.draw(this->exit_game_button);
  for (auto &button : this->difficulty_buttons) {
    target.draw(button);
  }
}
