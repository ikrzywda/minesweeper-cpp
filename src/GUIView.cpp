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
  unsigned long mouse_field_index =
      this->board.mouse_position.x / 50 +
      this->board.mouse_position.y / 50 * board.get_width();

  window.clear();
  for (int i = 0; i < game_board.size(); ++i) {
    sf::RectangleShape rect(sf::Vector2f(50, 50));
    rect.setPosition(sf::Vector2f((i % board.get_width()) * 50,
                                  (i / board.get_width()) * 50));
    if (i == mouse_field_index) {
      rect.setFillColor(sf::Color::Blue);
    } else {
      rect.setFillColor(this->get_color(game_board[i]));
    }
    window.draw(rect);
  }
  window.display();
}
