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
  GUIViewModel board(10, 10, DEBUG);
  GUIViewController controller(board, window);
  MainMenuView main_menu_view(
      window, [&controller]() { controller.start_game(); },
      [&window]() { window.close(); }, [](GameMode game_mode) {});

  GameView game_view(
      window, board,
      [&controller](unsigned long field_index) {
        controller.reveal_field(field_index);
      },
      [&controller](unsigned long field_index) {
        controller.flag_field(field_index);
      });
  GUIView view(window, board, main_menu_view, game_view);

  controller.run();
  return 0;
}
