#include "include/GUIViewModel.hpp"

void GUIViewModel::run_callbacks_mouse_position_updated() {
  for (auto callback : mouse_position_updated_callbacks) {
    callback(this->mouse_position);
  }
}

void GUIViewModel::subscribe_to_mouse_position_updated(
    std::function<void(sf::Vector2i)> callback) {
  mouse_position_updated_callbacks.push_back(callback);
}

void GUIViewModel::set_mouse_position(sf::Vector2i mouse_position) {
  if (this->mouse_position == mouse_position) {
    return;
  }
  this->mouse_position = mouse_position;
  this->run_callbacks_mouse_position_updated();
}
