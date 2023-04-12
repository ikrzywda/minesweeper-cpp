#ifndef GUI_VIEW_HPP
#define GUI_VIEW_HPP

#include "AssetWrappers.hpp"
#include "GUIViewModel.hpp"
#include "View.hpp"

#include <SFML/Graphics.hpp>

const sf::Texture *get_field_texture(Field field);
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

class GameView : public ButtonView {
  Board &board;

public:
  GameView(sf::RenderWindow &window, Board &board_ref,
           std::function<void(unsigned long)> on_field_click_callback);
  virtual ~GameView() = default;
  virtual void draw(sf::RenderWindow &window) override;
};

class ConclusionView : public ButtonView {
  std::function<void()> return_to_main_menu_callback;

public:
  explicit ConclusionView(sf::RenderWindow &window,
                          std::function<void()> return_to_main_menu_callback);
  virtual ~ConclusionView() = default;
  virtual void draw(sf::RenderWindow &window) override;
};

enum View { MAIN_MENU, GAME, CONCLUSION };
class GUIView {

  View current_view = MAIN_MENU;
  sf::RenderWindow &window;
  GUIViewModel &board;
  sf::RectangleShape field_shape;

  MainMenuView &main_menu_view;
  GameView &game_view;
  void draw();

public:
  GUIView(sf::RenderWindow &window_ref, GUIViewModel &board_ref,
          MainMenuView &main_menu_view_ref, GameView &game_view_ref)
      : window(window_ref), board(board_ref),
        main_menu_view(main_menu_view_ref), game_view(game_view_ref) {
    board.subscribe_to_game_state_updated([this](GameState game_state) {
      std::cout << "Game state updated" << std::endl;
      switch (game_state) {
      case UNKNOWN: {
        this->current_view = MAIN_MENU;
        break;
      }
      case RUNNING: {
        this->current_view = GAME;
        break;
      }
      default: {
        this->current_view = MAIN_MENU;
        break;
      }
      }
      this->draw();
    });
    board.subscribe_to_board_updated([this]() { this->draw(); });
    board.subscribe_to_mouse_position_updated(
        [this](sf::Vector2i mouse_position) {
          switch (this->current_view) {
          case MAIN_MENU: {
            this->main_menu_view.handle_click(sf::Vector2f(mouse_position));
            break;
          }
          case GAME: {
            this->game_view.handle_click(sf::Vector2f(mouse_position));
            break;
          }
          case CONCLUSION: {
            break;
          }
          }
        });
    this->draw();
  };
};

#endif
