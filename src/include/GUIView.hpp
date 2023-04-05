#ifndef GUI_VIEW_HPP
#define GUI_VIEW_HPP

#include "GUIViewModel.hpp"

#include <SFML/Graphics.hpp>

class GUIView {
  sf::RenderWindow &window;
  GUIViewModel &board;
  sf::RectangleShape field_shape;
  void game_view();
  // void conclusion_view(GameState game_state);
  sf::Color get_color(Field field);

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
