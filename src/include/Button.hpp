#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button : public sf::RectangleShape {
protected:
  std::function<void()> on_click_callback;

public:
  Button(const sf::Vector2f &size, std::function<void()> callback)
      : sf::RectangleShape(size), on_click_callback(callback){};
  ~Button() = default;
  bool contains(sf::Vector2f pos) const {
    return sf::Rect<float>(getPosition(), getSize()).contains(pos);
  }

  void on_click() {
    if (on_click_callback) {
      on_click_callback();
    }
  }
};

// class TexturedButton : public Button {
//   const sf::Texture *texture_;

// public:
//   TileButton(const sf::Vector2f &size, std::function<void()> callback, const
//   sf::Texture *texture_)
//     : Button(size, callback) {
//       setTexture(texture_)
//     };
// };

#endif
