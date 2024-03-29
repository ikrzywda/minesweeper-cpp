#include "include/GameState.hpp"

void GameState::subscribe_to_game_lost(std::function<void()> callback) {
  this->on_game_lost_callbacks.push_back(callback);
  this->board_ref->subscribe_to_game_lost(callback);
}

void GameState::subscribe_to_game_won(std::function<void()> callback) {
  this->on_game_won_callbacks.push_back(callback);
  this->board_ref->subscribe_to_game_won(callback);
}

void GameState::subscribe_to_board_updated(std::function<void()> callback) {
  this->board_ref->subscribe_to_board_updated(callback);
}

void GameState::run_callbacks_game_lost() const {
  for (auto &callback : this->on_game_lost_callbacks) {
    callback();
  }
}

void GameState::run_callbacks_difficulty_updated() const {
  for (auto &callback : this->on_difficulty_updated_callbacks) {
    callback();
  }
}

GameState::GameState() {
  this->game_difficulty = GameDifficulty::EASY;
  this->flags_remaining = 0;
  this->session_start_time = time(nullptr);
  this->time_limit_seconds =
      difficulty_setups.at(game_difficulty).time_limit_seconds;

  this->board_ref =
      std::make_unique<Board>(difficulty_setups.at(game_difficulty).width,
                              difficulty_setups.at(game_difficulty).height,
                              difficulty_setups.at(game_difficulty).mine_count,
                              difficulty_setups.at(game_difficulty).flag_count);
}

bool GameState::create_new_game() {
  this->flags_remaining = 0;
  this->session_start_time = time(nullptr);
  this->time_limit_seconds =
      difficulty_setups.at(this->game_difficulty).time_limit_seconds;

  // this->board_ref = std::make_unique<Board>(30, 30);

  this->board_ref = std::make_unique<Board>(
      difficulty_setups.at(this->game_difficulty).width,
      difficulty_setups.at(this->game_difficulty).height,
      difficulty_setups.at(this->game_difficulty).mine_count,
      difficulty_setups.at(this->game_difficulty).flag_count);

  for (auto &callback : this->on_game_lost_callbacks) {
    this->board_ref->subscribe_to_game_lost(callback);
  }
  for (auto &callback : this->on_game_won_callbacks) {
    this->board_ref->subscribe_to_game_won(callback);
  }

  for (auto &callback : this->on_board_updated_callbacks) {
    this->board_ref->subscribe_to_board_updated(callback);
  }

  return true;
}

unsigned long GameState::get_time_played_seconds() const {
  int time_played = difftime(time(nullptr), this->session_start_time);
  if (time_played < 0) {
    this->run_callbacks_game_lost();
    return 0;
  }
  return time_played;
}

GameDifficulty GameState::get_game_difficulty() const {
  return this->game_difficulty;
}

bool GameState::set_game_difficulty(GameDifficulty difficulty) {
  this->game_difficulty = difficulty;
  this->time_limit_seconds =
      difficulty_setups.at(this->game_difficulty).time_limit_seconds;
  this->run_callbacks_difficulty_updated();
  return true;
}
