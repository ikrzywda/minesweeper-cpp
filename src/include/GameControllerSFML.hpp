#ifndef GAME_CONTROLLER_SFML_HPP
#define GAME_CONTROLLER_SFML_HPP

#include <SFML/Graphics.hpp>

#include "GameController.hpp"

class GameControllerSFML : public GameController {
  sf::RenderWindow &window;
  unsigned long
  get_field_index_from_mouse_position(sf::Vector2i mouse_position);

public:
  GameControllerSFML(GameState &game_state_ref, sf::RenderWindow &window);
  void uncover_field(unsigned long field_index) override;
  void toggle_flag(unsigned long field_index) override;
  void reset_game() override;
  void start_game(GameDifficulty game_difficulty) override;
  void pause_game() override;
  void resume_game() override;
  void stop_game() override;
  void exit_game() override;
};

#endif
