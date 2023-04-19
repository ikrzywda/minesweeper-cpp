#ifndef BOARD_DISPLAY_HPP
#define BOARD_DISPLAY_HPP

#include "Board.hpp"
#include "TextViewController.hpp"

#include <iostream>
#include <map>

// class TextView {
//   Board &board;
//   TextViewController &controller;
//   std::string field_to_str(Field field);
//   void game_view();
//   void conclusion_view(GameState game_state);

// public:
//   TextView(Board &board_ref, TextViewController &controller_ref)
//       : board(board_ref), controller(controller_ref) {
//     board.subscribe_to_board_updated([this]() { this->game_view(); });
//     board.subscribe_to_game_state_updated([this](GameState game_state) {
//       this->conclusion_view(game_state);
//       this->game_view();
//     });
//   }
// };

#endif
