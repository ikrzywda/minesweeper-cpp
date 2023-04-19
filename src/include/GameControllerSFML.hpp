#ifndef GAME_CONTROLLER_SFML_HPP
#define GAME_CONTROLLER_SFML_HPP

#include "GameState.hpp"

#include <SFML/Graphics.hpp>

class GameControllerSFML {
  GameState &game_state;

public:
  GameControllerSFML(GameState &game_state_ref);
  void uncover_field(unsigned long field_index);
  void toggle_flag(unsigned long field_index);
  void reset_game();
  void start_game(GameDifficulty difficulty);
};

#endif
