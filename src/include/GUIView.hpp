#ifndef GUI_VIEW_HPP
#define GUI_VIEW_HPP

#include "AssetWrappers.hpp"
#include "GUIViewModel.hpp"
#include "View.hpp"

#include <SFML/Graphics.hpp>

class MainMenuView : public ButtonView {
  std::function<void()> on_start_game_callback;
  std::function<void()> on_exit_callback;
  std::function<void(GameMode)> on_difficulty_change_callback;
  sf::Text menu_text;

public:
  explicit MainMenuView(
      sf::RenderWindow &window, std::function<void()> on_start_game_callback,
      std::function<void()> on_exit_callback,
      std::function<void(GameMode)> on_difficulty_change_callbacks);
  virtual ~MainMenuView() = default;
  virtual void draw(sf::RenderWindow &window) override;
};

class GUIView {
  sf::RenderWindow &window;
  GUIViewModel &board;
  sf::RectangleShape field_shape;

  // MainMenuView &main_menu_view;
  void conclusion_view(GameState game_state);
  void game_view();
  sf::Color get_color(Field field);
  const sf::Texture *get_field_texture(Field field);

public:
  GUIView(sf::RenderWindow &window_ref, GUIViewModel &board_ref)
      : window(window_ref), board(board_ref) {
    board.subscribe_to_board_updated([this]() { this->game_view(); });
    // board.subscribe_to_game_state_updated([this](GameState game_state) {
    // this->conclusion_view(game_state);
    // });
    board.subscribe_to_mouse_position_updated(
        [this](sf::Vector2i mouse_position) {
          std::cout << mouse_position.x << " " << mouse_position.y << std::endl;
          this->game_view(); // todo: change to generic view update
        });
  };
};

#endif
