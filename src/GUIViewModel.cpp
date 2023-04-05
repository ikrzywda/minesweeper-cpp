#include "include/GUIViewModel.hpp"

void GUIViewModel::emit_mouse_position_updated() {
  for (auto callback : mouse_position_updated_callbacks) {
    callback(this->mouse_position);
  }
}

void GUIViewModel::subscribe_to_mouse_position_updated(
    std::function<void(sf::Vector2i)> callback) {
  mouse_position_updated_callbacks.push_back(callback);
}

void GUIViewModel::set_mouse_position(sf::Vector2i mouse_position) {
  this->mouse_position = mouse_position;
  this->emit_mouse_position_updated();
}
