#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Board.hpp"

#include <ctime>
#include <vector>

enum GameDifficulty { EASY, NORMAL, HARD };

struct DifficultySetup {
  int width;
  int height;
  int mine_count;
  int flag_count;
  int time_limit_seconds;
};

static const std::vector<DifficultySetup> difficulty_setups = {
    {9, 9, 10, 10, 300}, {16, 16, 40, 40, 300}, {30, 30, 99, 99, 300}};

class GameState {
  time_t session_start_time;
  int time_limit_seconds;
  unsigned int flags_remaining;
  GameDifficulty game_difficulty;

  std::vector<std::function<void()>> on_difficulty_updated_callbacks;
  std::vector<std::function<void()>> on_game_lost_callbacks;
  std::vector<std::function<void()>> on_game_won_callbacks;
  std::vector<std::function<void()>> on_board_updated_callbacks;

  void run_callbacks_game_lost() const;
  void run_callbacks_difficulty_updated() const;

public:
  GameState();
  bool create_new_game();
  std::unique_ptr<Board> board_ref;
  unsigned long get_time_played_seconds() const;
  GameDifficulty get_game_difficulty() const;
  bool set_game_difficulty(GameDifficulty difficulty);

  void subscribe_to_game_lost(std::function<void()> callback);
  void subscribe_to_game_won(std::function<void()> callback);
  void subscribe_to_board_updated(std::function<void()> callback);
  void subscribe_to_difficulty_updated(std::function<void()> callback);
};

#endif // GAME_STATE_HPP
