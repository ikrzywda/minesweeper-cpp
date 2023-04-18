#include "include/TextButtonView.hpp"

TextButtonView::TextButtonView(sf::Vector2f position, sf::Vector2f size,
                               std::string text) {
  this->setPosition(position);
  this->setSize(size);
  this->setFillColor(sf::Color::White);
  this->setOutlineColor(sf::Color::Black);
  this->setOutlineThickness(1);
  this->text.setString(text);
  this->text.setFont(Assets::font_regular);
  this->text.setCharacterSize(20);
  this->text.setFillColor(sf::Color::Black);
  this->text.setPosition(sf::Vector2f(
      position.x + size.x / 2 - this->text.getLocalBounds().width / 2,
      position.y + size.y / 2 - this->text.getLocalBounds().height / 2));
}
