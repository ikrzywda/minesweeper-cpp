#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "GameState.hpp"

class GameController {
protected:
  GameState &game_state;

public:
  GameController(GameState &game_state_ref);

  virtual void uncover_field(unsigned long field_index);
  virtual void toggle_flag(unsigned long field_index);
  virtual void reset_game();
  virtual void start_game(GameDifficulty game_difficulty);
  virtual void pause_game();
  virtual void resume_game();
  virtual void stop_game();
  virtual void exit_game();
};

#endif
