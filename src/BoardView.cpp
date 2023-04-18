#include "include/BoardView.hpp"

BoardView::BoardView(sf::Vector2f view_position, sf::Vector2f view_dimensions,
                     GameState &game_state)
    : game_state(game_state) {
  this->view_position = view_position;
  this->view_dimensions = view_dimensions;
  this->field_rects =
      std::vector<sf::RectangleShape>(this->game_state.board_ref->get_width() *
                                      this->game_state.board_ref->get_height());

  for (auto &rect : this->field_rects) {
    rect.setSize(this->field_dimensions);
    rect.setTexture(&Assets::covered);
  }
}

const sf::Texture *BoardView::get_field_texture(Field field) {
  sf::Sprite sprite;
  if (!field.is_revealed) {
    return field.has_flag ? &Assets::flag_texture : &Assets::covered;
  } else if (field.has_mine) {
    return &Assets::exploded_texture;
  }
  return &Assets::tile_textures[field.mine_count];
}

int BoardView::get_field_size() {
  int board_width = this->game_state.board_ref->get_width();
  int board_height = this->game_state.board_ref->get_height();
}

void BoardView::set_size(sf::Vector2f view_dimensions) {
  this->view_dimensions = view_dimensions;
  this->field_dimensions = sf::Vector2f(
      view_dimensions.x / this->game_state.board_ref->get_width(),
      view_dimensions.y / this->game_state.board_ref->get_height());
  for (auto &rect : this->field_rects) {
    rect.setSize(this->field_dimensions);
  }
}

void BoardView::set_position(sf::Vector2f view_position) {
  this->view_position = view_position;
}

void BoardView::update() {
  int board_width = this->game_state.board_ref->get_width();
  std::vector<Field> game_board = this->game_state.board_ref->get_board();

  for (unsigned long i = 0; i < this->field_rects.size(); i++) {
    this->field_rects.at(i).setPosition(
        sf::Vector2f((i % board_width) * this->field_dimensions.x,
                     (i / board_width) * this->field_dimensions.y));
    this->field_rects.at(i).setTexture(this->get_field_texture(game_board[i]));
  }
}

sf::Vector2f BoardView::get_size() const { return this->view_dimensions; }
sf::Vector2f BoardView::get_position() const { return this->view_position; }
sf::Vector2f BoardView::get_field_dimensions() const {
  return this->field_dimensions;
}

void BoardView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (auto &rect : this->field_rects) {
    target.draw(rect);
  }
}

void BoardView::subscribe_to_field_click(
    std::function<void(unsigned long)> handler) {
  this->field_click_handlers.push_back(handler);
}

void BoardView::run_field_click_handlers(unsigned long field_index) {
  for (auto &handler : this->field_click_handlers) {
    handler(field_index);
  }
}
