#ifndef GUI_VIEW_MODEL_HPP
#define GUI_VIEW_MODEL_HPP

#include "Board.hpp"

#include <SFML/Graphics.hpp>

class GUIViewModel : public Board {

  static sf::Vector2u current_field_size, previous_field_size;
  static sf::Image uncovered_field;
  static sf::Image covered_field;
  static sf::Image mine;
  static std::vector<sf::Image> numbers;

  sf::RectangleShape field_shape;
  std::vector<std::function<void(sf::Vector2i)>>
      mouse_position_updated_callbacks;

  void emit_mouse_position_updated();

public:
  using Board::Board;
  sf::Vector2i mouse_position;
  void subscribe_to_mouse_position_updated(
      std::function<void(sf::Vector2i)> callback);
  void set_mouse_position(sf::Vector2i mouse_position);
};

#endif
