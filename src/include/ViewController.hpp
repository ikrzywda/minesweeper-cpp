#ifndef VIEW_CONTROLLER_HPP
#define VIEW_CONTROLLER_HPP

#include "BoardView.hpp"

#include <SFML/Graphics.hpp>

enum Views { MENU, BOARD, GAME_OVER };

class ViewController {
  sf::RenderWindow &window;
  BoardView &board_view;
  Views current_view;

  void on_game_lost();
  void on_game_won();
  void on_board_update();
  void on_game_start();

public:
  ViewController(sf::RenderWindow &window, GameState &game_state,
                 BoardView &board_view_ref);
  void draw();
};

#endif
