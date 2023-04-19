#include "include/GameOverView.hpp"

GameOverView::GameOverView(sf::Vector2f view_position,
                           sf::Vector2f view_dimensions) {
  this->back_to_menu_button = std::make_unique<TextButtonView>(
      sf::Vector2f(view_position.x + view_dimensions.x / 2 - 100,
                   view_position.y + view_dimensions.y / 2 - 100),
      sf::Vector2f(200, 50), "Back To Menu");

  this->set_position(view_position);
  this->set_size(view_dimensions);
  this->background.setFillColor(sf::Color(0, 0, 0, 200));
  this->background.setOutlineColor(sf::Color::Black);
  this->background.setOutlineThickness(1);
  this->title.setFont(Assets::font_bold);
  this->title.setCharacterSize(50);
  this->title.setFillColor(sf::Color::White);
  this->title.setString("Game Over!");

  this->title.setPosition(
      sf::Vector2f(view_position.x + view_dimensions.x / 2 -
                       this->title.getLocalBounds().width / 2,
                   view_position.y + 50));
}

void GameOverView::run_back_to_menu_click_handlers() {
  for (auto &handler : this->back_to_menu_click_handlers) {
    handler();
  }
}

void GameOverView::set_size(sf::Vector2f view_dimensions) {
  this->background.setSize(view_dimensions);
  this->back_to_menu_button->setSize(sf::Vector2f(200, 50));
  this->back_to_menu_button->setPosition(
      sf::Vector2f(view_dimensions.x / 2 - 100, 200));
}

void GameOverView::set_position(sf::Vector2f view_position) {
  this->background.setPosition(view_position);
}

void GameOverView::subscribe_to_back_to_menu_click(
    std::function<void()> handler) {
  this->back_to_menu_click_handlers.push_back(handler);
}

void GameOverView::draw(sf::RenderWindow &window) const {
  window.draw(this->background);
  window.draw(this->title);
  window.draw(*this->back_to_menu_button);
}

void GameOverView::run_click_handlers(sf::Vector2i mouse_position) {
  if (this->back_to_menu_button->getGlobalBounds().contains(
          sf::Vector2f(mouse_position))) {
    this->run_back_to_menu_click_handlers();
  }
}
