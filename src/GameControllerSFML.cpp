#include "include/GameControllerSFML.hpp"

GameControllerSFML::GameControllerSFML(GameState &game_state_ref)
    : game_state(game_state_ref) {}

void GameControllerSFML::uncover_field(unsigned long field_index) {
  this->game_state.board_ref->reveal_field(field_index);
}

void GameControllerSFML::toggle_flag(unsigned long field_index) {
  this->game_state.board_ref->toggle_flag(field_index);
}

void GameControllerSFML::reset_game() { this->game_state.create_new_game(); }

void GameControllerSFML::start_game(GameDifficulty difficulty) {
  this->game_state.set_game_difficulty(difficulty);
  this->game_state.create_new_game();
}
