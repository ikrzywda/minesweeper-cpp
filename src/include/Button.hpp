#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button : public sf::RectangleShape {
protected:
  std::function<void()> on_click_callback;
  std::function<void()> on_right_click_callback;

public:
  Button(const sf::Vector2f &size, std::function<void()> callback,
         std::function<void()> right_callback)
      : sf::RectangleShape(size), on_click_callback(callback),
        on_right_click_callback(right_callback){};
  ~Button() = default;
  bool contains(sf::Vector2f pos) const {
    return sf::Rect<float>(getPosition(), getSize()).contains(pos);
  }

  void on_click() {
    if (on_click_callback) {
      on_click_callback();
    }
  }

  void on_right_click() {
    if (on_right_click_callback) {
      on_right_click_callback();
    }
  }
};

#endif
