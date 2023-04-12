#include "include/View.hpp"

void ButtonView::handle_click(sf::Vector2f pos) {
  for (auto &button : buttons) {
    if (button.contains(pos)) {
      button.on_click();
      break;
    }
  }
}

void ButtonView::handle_right_click(sf::Vector2f pos) {
  for (auto &button : buttons) {
    if (button.contains(pos)) {
      button.on_right_click();
      break;
    }
  }
}

void ButtonView::draw(sf::RenderWindow &window) {
  window.clear();

  for (auto &button : this->buttons) {
    window.draw(button);
  }

  window.display();
}
