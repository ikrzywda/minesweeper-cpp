#ifndef GAME_CONTROLLER_SFML_HPP
#define GAME_CONTROLLER_SFML_HPP

#include <SFML/Graphics.hpp>

#include "GameController.hpp"

class GameControllerSFML {
  GameState &game_state;

public:
  GameControllerSFML(GameState &game_state_ref);
  void uncover_field(unsigned long field_index);
  void toggle_flag(unsigned long field_index);
  void reset_game();
  void start_game();
};

#endif
