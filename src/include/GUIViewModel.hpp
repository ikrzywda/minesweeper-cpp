#ifndef GUI_VIEW_MODEL_HPP
#define GUI_VIEW_MODEL_HPP

#include "AssetWrappers.hpp"
#include "Board.hpp"

#include <SFML/Graphics.hpp>

class GUIViewModel : public Board {

  std::vector<std::function<void(sf::Vector2i)>> left_mouse_click_callbacks;

  std::vector<std::function<void(sf::Vector2i)>> right_mouse_click_callbacks;

public:
  using Board::Board;
  void dispatch_left_mouse_click(sf::Vector2i mouse_position);
  void dispatch_right_mouse_click(sf::Vector2i mouse_position);
  void
  subscribe_to_left_mouse_click(std::function<void(sf::Vector2i)> callback);
  void
  subscribe_to_right_mouse_click(std::function<void(sf::Vector2i)> callback);
};

#endif
