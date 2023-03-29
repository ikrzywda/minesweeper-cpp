#include "include/GUIView.hpp"

sf::Color GUIView::get_color(Field field) {
  if (!field.is_revealed) {
    return field.has_flag ? sf::Color::Red : sf::Color::White;
  } else if (field.mine_count == 0) {
    return sf::Color::Green;
  } else {
    return sf::Color::Yellow;
  }

  if (field.has_mine) {
    return sf::Color::Black;
  }
}

void GUIView::game_view() {
  const std::vector<Field> &game_board = this->board.get_board();

  window.clear();
  for (int i = 0; i < game_board.size(); ++i) {
    sf::RectangleShape rect(sf::Vector2f(50, 50));
    rect.setPosition(
        sf::Vector2f(5 / board.get_width() * 50, 5 % board.get_width() * 50));
    rect.setFillColor(sf::Color::White);
    window.draw(rect);
  }
  window.display();
}
