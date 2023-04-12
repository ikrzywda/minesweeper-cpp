#include "include/GUIViewModel.hpp"

void GUIViewModel::subscribe_to_left_mouse_click(
    std::function<void(sf::Vector2i)> callback) {
  left_mouse_click_callbacks.push_back(callback);
}

void GUIViewModel::dispatch_right_mouse_click(sf::Vector2i mouse_position) {
  for (auto callback : right_mouse_click_callbacks) {
    callback(mouse_position);
  }
}

void GUIViewModel::dispatch_left_mouse_click(sf::Vector2i mouse_position) {
  for (auto callback : left_mouse_click_callbacks) {
    callback(mouse_position);
  }
}

void GUIViewModel::subscribe_to_right_mouse_click(
    std::function<void(sf::Vector2i)> callback) {
  right_mouse_click_callbacks.push_back(callback);
}
