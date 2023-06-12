#ifndef BOARD_VIEW_HPP
#define BOARD_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "AssetWrappers.hpp"
#include "GameState.hpp"

class BoardView {
  const sf::Texture *get_field_texture(Field field);
  sf::Vector2f view_position;
  sf::Vector2f view_dimensions;
  sf::Vector2f field_dimensions;
  sf::Text flag_count_text;
  std::vector<sf::RectangleShape> field_rects;

  std::vector<std::function<void(unsigned long)>> field_click_handlers;
  std::vector<std::function<void(unsigned long)>> right_click_handlers;

  GameState &game_state;

 public:
  void update();
  BoardView(GameState &game_state, sf::Vector2f view_position,
            sf::Vector2f view_dimensions);
  void set_size(sf::Vector2f view_dimensions);
  void set_position(sf::Vector2f view_position);
  sf::Vector2f get_size() const;
  sf::Vector2f get_position() const;
  sf::Vector2f get_field_dimensions() const;

  void subscribe_to_field_click(std::function<void(unsigned long)> handler);
  void subscribe_to_right_field_click(
      std::function<void(unsigned long)> handler);
  void run_field_click_handlers(unsigned long field_index,
                                sf::Mouse::Button button);
  void run_click_handlers(sf::Vector2i mouse_position,
                          sf::Mouse::Button button);

  void draw(sf::RenderWindow &window) const;
};

#endif
