#include "include/GameControllerSFML.hpp"

GameControllerSFML::GameControllerSFML(GameState &game_state_ref,
                                       sf::RenderWindow &window_ref)
    : GameController(game_state_ref), window(window_ref) {}

void GameControllerSFML::uncover_field(unsigned long field_index) {
  this->game_state.board_ref->reveal_field(field_index);
}

void GameControllerSFML::toggle_flag(unsigned long field_index) {
  this->game_state.board_ref->toggle_flag(field_index);
}

void GameControllerSFML::reset_game() {
  this->game_state.create_new_game(this->game_state.get_game_difficulty());
}

void GameControllerSFML::start_game(GameDifficulty game_difficulty) {
  this->game_state.create_new_game(game_difficulty);
}

void GameControllerSFML::pause_game() {}

void GameControllerSFML::resume_game() {}

void GameControllerSFML::stop_game() {}

void GameControllerSFML::exit_game() {}
