#include "include/GameState.hpp"

void GameState::subscribe_to_game_lost(std::function<void()> callback) {
  this->on_game_lost_callbacks.push_back(callback);
  this->board_ref->subscribe_to_game_lost(callback);
}

void GameState::subscribe_to_game_won(std::function<void()> callback) {
  this->board_ref->subscribe_to_game_won(callback);
}

void GameState::subscribe_to_board_updated(std::function<void()> callback) {
  this->board_ref->subscribe_to_board_updated(callback);
}

GameState::GameState(GameDifficulty game_difficulty,
                     std::function<void()> on_game_lost_callback,
                     std::function<void()> on_game_won_callback,
                     std::function<void()> on_board_updated_callback) {
  this->game_difficulty = game_difficulty;
  this->flags_remaining = 0;
  this->session_start_time = time(nullptr);
  this->time_limit_seconds =
      difficulty_setups.at(game_difficulty).time_limit_seconds;

  this->board_ref =
      std::make_unique<Board>(difficulty_setups.at(game_difficulty).width,
                              difficulty_setups.at(game_difficulty).height,
                              difficulty_setups.at(game_difficulty).mine_count,
                              difficulty_setups.at(game_difficulty).flag_count);

  this->subscribe_to_board_updated(on_board_updated_callback);
  this->subscribe_to_game_lost(on_game_lost_callback);
  this->subscribe_to_game_won(on_game_won_callback);
}

unsigned long GameState::get_time_played_seconds() const {
  return difftime(time(nullptr), this->session_start_time);
}

GameDifficulty GameState::get_game_difficulty() const {
  return this->game_difficulty;
}
