#ifndef BOARD_VIEW_HPP
#define BOARD_VIEW_HPP

#include "AssetWrappers.hpp"
#include "GameController.hpp"
#include "GameState.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class BoardView : sf::Drawable {
  const sf::Texture *get_field_texture(Field field);
  sf::Vector2f view_position;
  sf::Vector2f view_dimensions;
  sf::Vector2f field_dimensions;
  std::vector<sf::RectangleShape> field_rects;

  int get_field_size();
  GameState &game_state;

public:
  void update();
  BoardView(sf::Vector2f view_position, sf::Vector2f view_dimensions,
            GameState &game_state);
  void set_size(sf::Vector2f view_dimensions);
  void set_position(sf::Vector2f view_position);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif
