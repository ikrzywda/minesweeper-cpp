#include "include/BoardView.hpp"

BoardView::BoardView(GameState &game_state, sf::Vector2f view_position,
                     sf::Vector2f view_dimensions)
    : game_state(game_state) {
  this->view_position = view_position;
  this->view_dimensions = view_dimensions;
  this->field_dimensions = sf::Vector2f(
      view_dimensions.x / this->game_state.board_ref->get_width(),
      view_dimensions.y / this->game_state.board_ref->get_height());
  this->field_rects =
      std::vector<sf::RectangleShape>(this->game_state.board_ref->get_width() *
                                      this->game_state.board_ref->get_height());

  for (auto &rect : this->field_rects) {
    rect.setSize(this->field_dimensions);
    rect.setTexture(&Assets::covered);
  }
  this->update();
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
  int board_height = this->game_state.board_ref->get_height();

  if (field_rects.size() != board_width * board_height) {
    this->field_rects =
        std::vector<sf::RectangleShape>(board_width * board_height);
  }

  this->field_dimensions = sf::Vector2f(view_dimensions.x / board_width,
                                        view_dimensions.y / board_height);

  std::vector<Field> game_board = this->game_state.board_ref->get_board();

  for (unsigned long i = 0; i < this->field_rects.size(); i++) {
    this->field_rects[i].setSize(this->field_dimensions);
    this->field_rects[i].setPosition(
        sf::Vector2f((i % board_width) * this->field_dimensions.x,
                     (i / board_width) * this->field_dimensions.y));
    this->field_rects[i].setTexture(this->get_field_texture(game_board[i]));
  }
}

sf::Vector2f BoardView::get_size() const { return this->view_dimensions; }
sf::Vector2f BoardView::get_position() const { return this->view_position; }
sf::Vector2f BoardView::get_field_dimensions() const {
  return this->field_dimensions;
}

void BoardView::draw(sf::RenderWindow &window) const {
  for (auto &rect : this->field_rects) {
    window.draw(rect);
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

void BoardView::run_click_handlers(sf::Vector2i mouse_position) {
  sf::Vector2f mouse_position_f = sf::Vector2f(mouse_position);
  if (mouse_position_f.x < this->view_position.x ||
      mouse_position_f.y < this->view_position.y ||
      mouse_position_f.x > this->view_position.x + this->view_dimensions.x ||
      mouse_position_f.y > this->view_position.y + this->view_dimensions.y) {
    return;
  }

  for (size_t i = 0; i < this->field_rects.size(); i++) {
    if (this->field_rects[i].getGlobalBounds().contains(mouse_position_f)) {
      this->run_field_click_handlers(i);
      this->update();
      break;
    }
  }
}
