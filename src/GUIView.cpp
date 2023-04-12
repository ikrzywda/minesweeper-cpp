#include "include/GUIView.hpp"

const sf::Texture *get_field_texture(Field field) {
  sf::Sprite sprite;
  if (!field.is_revealed) {
    return field.has_flag ? &Assets::flag_texture : &Assets::covered;
  } else if (field.has_mine) {
    return &Assets::exploded_texture;
  }
  return &Assets::tile_textures[field.mine_count];
}

MainMenuView::MainMenuView(
    sf::RenderWindow &window, std::function<void()> on_start_game_callback,
    std::function<void()> on_exit_callback,
    std::function<void(GameMode)> on_difficulty_change_callbacks) {
  Button start_game_button = Button(
      sf::Vector2f(100, 50), on_start_game_callback, on_start_game_callback);
  Button exit_button =
      Button(sf::Vector2f(100, 50), on_exit_callback, on_exit_callback);
  Button easy_button = Button(
      sf::Vector2f(100, 50),
      [on_difficulty_change_callbacks]() {
        on_difficulty_change_callbacks(EASY);
      },
      [on_difficulty_change_callbacks]() {
        on_difficulty_change_callbacks(EASY);
      });
  Button medium_button = Button(
      sf::Vector2f(100, 50),
      [on_difficulty_change_callbacks]() {
        on_difficulty_change_callbacks(NORMAL);
      },
      [on_difficulty_change_callbacks]() {
        on_difficulty_change_callbacks(NORMAL);
      });
  Button hard_button = Button(
      sf::Vector2f(100, 50),
      [on_difficulty_change_callbacks]() {
        on_difficulty_change_callbacks(HARD);
      },
      [on_difficulty_change_callbacks]() {
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
  start_game_button.setFillColor(sf::Color::Green);

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

GameView::GameView(
    sf::RenderWindow &window, Board &board_ref,
    std::function<void(unsigned long)> on_field_click_callback,
    std::function<void(unsigned long)> on_field_right_click_callback)
    : board(board_ref) {
  for (int i = 0; i < board.get_board().size(); ++i) {
    Button button(
        sf::Vector2f(50, 50),
        [on_field_click_callback, i]() { on_field_click_callback(i); },
        [on_field_right_click_callback, i]() {
          on_field_right_click_callback(i);
        });
    button.setPosition(sf::Vector2f((i % board.get_width()) * 50,
                                    (i / board.get_width()) * 50));
    this->buttons.push_back(button);
  }
}

void GameView::draw(sf::RenderWindow &window) {
  window.clear();
  for (int i = 0; i < board.get_board().size(); ++i) {
    this->buttons[i].setTexture(get_field_texture(board.get_board()[i]));
    window.draw(this->buttons[i]);
  }
  window.display();
}

ConclusionView::ConclusionView(
    sf::RenderWindow &window, Board &board_ref,
    std::function<void()> return_to_main_menu_callback)
    : board(board_ref) {
  this->conclusion_text = sf::Text("", Assets::font_bold, 24);
  sf::Vector2f button_size(100, 50);
  Button return_to_main_menu_button = Button(
      button_size, return_to_main_menu_callback, return_to_main_menu_callback);
  return_to_main_menu_button.setPosition(
      sf::Vector2f(window.getSize().x / 2 - button_size.x / 2,
                   conclusion_text.getGlobalBounds().top +
                       conclusion_text.getGlobalBounds().height + 50));
  return_to_main_menu_button.setFillColor(sf::Color::Green);
  this->buttons.push_back(return_to_main_menu_button);
};

void ConclusionView::draw(sf::RenderWindow &window) {
  window.clear();
  if (this->board.get_game_state() == FINISHED_WIN) {
    this->conclusion_text.setString("You won!");
  } else {
    this->conclusion_text.setString("You lost!");
  }
  window.draw(this->conclusion_text);
  for (auto &button : this->buttons) {
    window.draw(button);
  }
  window.display();
}

void GUIView::draw() {
  switch (this->current_view) {
  case MAIN_MENU:
    this->main_menu_view.draw(this->window);
    break;
  case GAME:
    this->game_view.draw(this->window);
    break;
  case CONCLUSION: {
    this->conclusion_view.draw(this->window);
    break;
  }
  }
}
