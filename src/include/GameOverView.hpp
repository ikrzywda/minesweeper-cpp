#ifndef GAME_OVER_VIEW_HPP
#define GAME_OVER_VIEW_HPP

#include <SFML/Graphics.hpp>

#include "TextButtonView.hpp"

class GameOverView {
  sf::RectangleShape background;

  sf::Text title;
  std::unique_ptr<TextButtonView> back_to_menu_button;

  std::vector<sf::RectangleShape> difficulty_buttons;

  std::vector<std::function<void()>> back_to_menu_click_handlers;
  void run_back_to_menu_click_handlers();

 public:
  GameOverView(sf::Vector2f view_position, sf::Vector2f view_dimensions);
  void set_size(sf::Vector2f view_dimensions);
  void set_position(sf::Vector2f view_position);

  void subscribe_to_back_to_menu_click(std::function<void()> handler);
  void draw(sf::RenderWindow &window, bool has_won);

  void run_click_handlers(sf::Vector2i mouse_position);
};

#endif
