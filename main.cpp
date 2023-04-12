#include "src/include/AssetWrappers.hpp"
#include "src/include/Board.hpp"
#include "src/include/GUIView.hpp"
#include "src/include/GUIViewController.hpp"
#include "src/include/GUIViewModel.hpp"
#include "src/include/TextView.hpp"
#include "src/include/TextViewController.hpp"
#include "src/include/View.hpp"

#include <SFML/Graphics.hpp>

int main() {
  Assets::load_assets();
  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(500, 500)), "Dupa");

  MainMenuView main_menu_view(
      window, []() { std::cout << "Start game" << std::endl; },
      []() { std::cout << "Exit" << std::endl; },
      [](GameMode game_mode) {
        std::cout << "Difficulty changed" << std::endl;
      });

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        main_menu_view.handle_click(
            sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
      }
    }
    main_menu_view.draw(window);
  }
  // GUIViewModel board(10, 10, DEBUG);
  // GUIViewController controller(board, window);
  // GUIView view(window, board);

  // // controller.run();
  // controller.reveal_field(6, 2);
  // controller.run();
  // view.game_view();

  // Board board(10, 10, DEBUG);
  // board.debug_display();
  // TextViewController controller(board);
  // TextView view(board, controller);

  // controller.run();
  return 0;
}
