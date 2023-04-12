#include "include/GUIView.hpp"

MainMenuView::MainMenuView(
    sf::RenderWindow &window, std::function<void()> on_start_game_callback,
    std::function<void()> on_exit_callback,
    std::function<void(GameMode)> on_difficulty_change_callbacks) {
  Button start_game_button =
      Button(sf::Vector2f(100, 50), on_start_game_callback);
  Button exit_button = Button(sf::Vector2f(100, 50), on_exit_callback);
  Button easy_button =
      Button(sf::Vector2f(100, 50), [on_difficulty_change_callbacks]() {
        on_difficulty_change_callbacks(EASY);
      });
  Button medium_button =
      Button(sf::Vector2f(100, 50), [on_difficulty_change_callbacks]() {
        on_difficulty_change_callbacks(NORMAL);
      });
  Button hard_button =
      Button(sf::Vector2f(100, 50), [on_difficulty_change_callbacks]() {
        on_difficulty_change_callbacks(HARD);
      });
  this->menu_text = sf::Text("Minesweeper", Assets::font_bold, 24);

  /* Generated with GPT to arrange components */
  menu_text.setCharacterSize(24);
  menu_text.setPosition(sf::Vector2f(
      window.getSize().x / 2.0f - menu_text.getGlobalBounds().width / 2.0f,
      50.0f));

  sf::Vector2f button_size(100.0f, 50.0f);

  start_game_button.setPosition(sf::Vector2f(
      window.getSize().x / 2.0f - button_size.x / 2.0f,
      menu_text.getPosition().y + menu_text.getGlobalBounds().height + 50.0f));

  easy_button.setPosition(
      sf::Vector2f(start_game_button.getPosition().x - button_size.x - 25.0f,
                   start_game_button.getPosition().y + button_size.y + 50.0f));
  medium_button.setPosition(
      sf::Vector2f(start_game_button.getPosition().x,
                   start_game_button.getPosition().y + button_size.y + 50.0f));
  hard_button.setPosition(
      sf::Vector2f(start_game_button.getPosition().x + button_size.x + 25.0f,
                   start_game_button.getPosition().y + button_size.y + 50.0f));

  exit_button.setPosition(
      sf::Vector2f(window.getSize().x / 2.0f - button_size.x / 2.0f,
                   window.getSize().y - button_size.y - 50.0f));

  buttons.push_back(start_game_button);
  buttons.push_back(exit_button);
  buttons.push_back(easy_button);
  buttons.push_back(medium_button);
  buttons.push_back(hard_button);
}

void MainMenuView::draw(sf::RenderWindow &window) {
  window.clear();
  window.draw(this->menu_text);

  for (auto &button : this->buttons) {
    window.draw(button);
  }

  window.display();
}

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
