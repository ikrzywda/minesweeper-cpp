#ifndef GUI_VIEW_CONTROLLER
#define GUI_VIEW_CONTROLLER

#include "GUIViewModel.hpp"

#include <SFML/Graphics.hpp>

class GUIViewController {
  GUIViewModel &board;
  sf::RenderWindow &window;

public:
  GUIViewController(GUIViewModel &board_ref, sf::RenderWindow &window_ref)
      : board(board_ref), window(window_ref){};

  void reveal_field(int row, int col);
  void flag_field(int row, int col);
  void run();
};

#endif
