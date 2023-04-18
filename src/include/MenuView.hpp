#ifndef MENU_VIEW_HPP
#define MENU_VIEW_HPP

#include "TextButtonView.hpp"

#include <SFML/Graphics.hpp>

class MenuView {
  sf::RectangleShape background;

  sf::Text title;
  TextButtonView new_game_button;
  TextButtonView exit_game_button;
  std::vector<sf::RectangleShape> difficulty_buttons;

  std::vector<std::function<void()>> new_game_click_handlers;
  std::vector<std::function<void()>> exit_game_click_handlers;
  std::vector<std::function<void(unsigned long)>> difficulty_click_handlers;

  void run_new_game_click_handlers();
  void run_exit_game_click_handlers();
  void run_difficulty_click_handlers(unsigned long difficulty);
  void run_click_handlers(sf::Vector2i mouse_position);
  void draw(sf::RenderWindow &window) const;

public:
  MenuView();
  void set_size(sf::Vector2f view_dimensions);
  void set_position(sf::Vector2f view_position);

  void subscribe_to_new_game_click(std::function<void()> handler);
  void subscribe_to_exit_game_click(std::function<void()> handler);
  void
  subscribe_to_difficulty_click(std::function<void(unsigned long)> handler);

};

#endif
