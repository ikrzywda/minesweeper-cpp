#ifndef BUTTON_VIEW_HPP
#define BUTTON_VIEW_HPP

#include "AssetWrappers.hpp"

#include <SFML/Graphics.hpp>

class TextButtonView : public sf::RectangleShape {
  sf::Text text;

public:
  TextButtonView(sf::Vector2f position, sf::Vector2f size, std::string text);
};

#endif
