#ifndef GUI_VIEW_MODEL_HPP
#define GUI_VIEW_MODEL_HPP

#include "AssetWrappers.hpp"
#include "Board.hpp"

#include <SFML/Graphics.hpp>

class GUIViewModel : public Board {

  static std::vector<sf::Texture> textures;
  std::vector<std::function<void(sf::Vector2i)>>
      mouse_position_updated_callbacks;

  void run_callbacks_mouse_position_updated();

public:
  using Board::Board;
  sf::Vector2i mouse_position;
  void subscribe_to_mouse_position_updated(
      std::function<void(sf::Vector2i)> callback);
  void set_mouse_position(sf::Vector2i mouse_position);
};

#endif
