#ifndef GUI_VIEW
#define GUI_VIEW

#include "Board.hpp"

#include <SFML/Graphics.hpp>

class GUIView {
  sf::RenderWindow &window;
  Board &board;
  sf::RectangleShape field_shape;

public:
  GUIView(sf::RenderWindow &window_ref, Board &board_ref)
      : window(window_ref), board(board_ref){};

  sf::Color get_color(Field field);

  void game_view();

  void conclusion_view(GameState game_state);
};

#endif
