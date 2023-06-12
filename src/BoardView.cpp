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

  float max_width = this->view_dimensions.x * 0.8;
  float max_height = this->view_dimensions.y * 0.8;
  float horizontal_offset = this->view_dimensions.x * 0.1;
  float vertical_offset = this->view_dimensions.y * 0.2;

  this->flag_count_text.setFont(Assets::font_bold);
  this->flag_count_text.setCharacterSize(15);
  this->flag_count_text.setFillColor(sf::Color::White);
  this->flag_count_text.setPosition(sf::Vector2f(horizontal_offset, 0));
  this->flag_count_text.setString(
      "Flags: " + std::to_string(this->game_state.board_ref->get_flag_count()));

  this->field_dimensions =
      sf::Vector2f(max_width / board_width, max_height / board_height);

  std::vector<Field> game_board = this->game_state.board_ref->get_board();

  for (unsigned long i = 0; i < this->field_rects.size(); i++) {
    this->field_rects[i].setSize(this->field_dimensions);
    this->field_rects[i].setPosition(sf::Vector2f(
        (i % board_width) * this->field_dimensions.x + horizontal_offset,
        (i / board_width) * this->field_dimensions.y + vertical_offset));
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
  window.draw(this->flag_count_text);
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
