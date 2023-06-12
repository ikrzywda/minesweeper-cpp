#ifndef BUTTON_VIEW_HPP
#define BUTTON_VIEW_HPP

#include <SFML/Graphics.hpp>

#include "AssetWrappers.hpp"

class TextButtonView : public sf::RectangleShape {
  sf::Text text;

 public:
  TextButtonView(sf::Vector2f position, sf::Vector2f size, std::string text);
  void draw(sf::RenderWindow &window) const;
};

#endif
