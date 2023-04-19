#include "src/include/AssetWrappers.hpp"
#include "src/include/GameState.hpp"
#include "src/include/ViewController.hpp"
#include "src/include/GameControllerSFML.hpp"

#include <SFML/Graphics.hpp>

int main() {


  Assets::load_assets();
  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(500, 500)), "SFML works!");

  GameState game_state;
  GameControllerSFML game_controller(game_state);
  ViewController view_controller(window, game_state, game_controller);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::MouseButtonPressed) {
        view_controller.on_click();
      }
    }

    window.clear();
    view_controller.draw();
    window.display();
  }


  return 0;
}
