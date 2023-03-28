#ifndef FIELD_HPP
#define FIELD_HPP

#include <iostream>
#include <string>

struct Field {
  bool has_mine = false;
  bool has_flag = false;
  bool is_revealed = false;
  int mine_count = 0;

  Field(bool has_mine, bool has_flag, bool is_revealed);
  Field();

  std::string get_debug_str();
  std::string get_display_str();
};

#endif
