#ifndef BUTTON_VIEW_HPP
#define BUTTON_VIEW_HPP

#include "Button.hpp"
#include "GUIViewModel.hpp"

class ButtonView {
protected:
  std::vector<Button> buttons;

public:
  virtual ~ButtonView() = default;
  void handle_click(sf::Vector2f pos);
  virtual void draw(sf::RenderWindow &window);
};

#endif
