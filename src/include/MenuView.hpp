#ifndef MENU_VIEW_HPP
#define MENU_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <map>

#include "GameState.hpp"
#include "TextButtonView.hpp"

static const std::map<GameDifficulty, std::string> game_difficulty_names = {
    {EASY, "Easy"}, {NORMAL, "Normal"}, {HARD, "Hard"}};

class MenuView {
  GameState &game_state;
  sf::RectangleShape background;

  sf::Text title;
  sf::Text difficulty_title;
  std::unique_ptr<TextButtonView> new_game_button;
  std::unique_ptr<TextButtonView> exit_game_button;

  std::unique_ptr<TextButtonView> easy_difficulty_button;
  std::unique_ptr<TextButtonView> normal_difficulty_button;
  std::unique_ptr<TextButtonView> hard_difficulty_button;

  std::vector<sf::RectangleShape> difficulty_buttons;

  std::vector<std::function<void()>> new_game_click_handlers;
  std::vector<std::function<void()>> exit_game_click_handlers;
  std::vector<std::function<void(GameDifficulty)>> difficulty_click_handlers;

  void run_new_game_click_handlers();
  void run_exit_game_click_handlers();
  void run_difficulty_click_handlers(GameDifficulty difficulty);

 public:
  MenuView(sf::Vector2f view_position, sf::Vector2f view_dimensions,
           GameState &game_state);
  void set_size(sf::Vector2f view_dimensions);
  void set_position(sf::Vector2f view_position);

  void subscribe_to_new_game_click(std::function<void()> handler);
  void subscribe_to_exit_game_click(std::function<void()> handler);
  void subscribe_to_difficulty_click(
      std::function<void(GameDifficulty)> handler);
  void run_click_handlers(sf::Vector2i mouse_position);

  void draw(sf::RenderWindow &window) const;
};

#endif
