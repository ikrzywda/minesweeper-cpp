#ifndef VIEW_CONTROLLER_HPP
#define VIEW_CONTROLLER_HPP

#include "BoardView.hpp"
#include "MenuView.hpp"
#include "GameOverView.hpp"
#include "GameControllerSFML.hpp"

#include <SFML/Graphics.hpp>

enum Views { MENU, BOARD, GAME_OVER };

class ViewController {
  sf::RenderWindow &window;
  std::unique_ptr<BoardView> board_view;
  std::unique_ptr<MenuView> menu_view;
  std::unique_ptr<GameOverView> game_over_view;
  GameControllerSFML &game_controller;
  Views current_view;

  void on_game_lost();
  void on_game_won();
  void on_board_update();
  void on_game_start();

  void on_click_game_view(sf::Vector2i mouse_position);
  void on_click_menu_view(sf::Vector2i mouse_position);
  void on_click_game_over_view(sf::Vector2i mouse_position);

  void on_click();

public:
  ViewController(sf::RenderWindow &window, GameState &game_state,
                 GameControllerSFML &game_controller_ref);
  void draw();
};


#endif
