#include "include/GUIView.hpp"

const sf::Texture *GUIView::get_field_texture(Field field) {
  sf::Sprite sprite;
  if (!field.is_revealed) {
    return field.has_flag ? &Assets::flag_texture : &Assets::covered;
  } else if (field.has_mine) {
    return &Assets::exploded_texture;
  }
  return &Assets::tile_textures[field.mine_count];
}

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
    rect.setTexture(this->get_field_texture(game_board[i]));
    window.draw(rect);
  }
  window.display();
}
