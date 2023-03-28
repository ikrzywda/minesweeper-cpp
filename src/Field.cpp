#include "include/Field.hpp"

Field::Field(bool has_mine, bool has_flag, bool is_revealed) {
  this->has_mine = has_mine;
  this->has_flag = has_flag;
  this->is_revealed = is_revealed;
}

Field::Field() {
  this->has_mine = false;
  this->has_flag = false;
  this->is_revealed = false;
}

std::string Field::get_debug_str() {
  std::string flag_mine = this->has_mine ? "M" : ".";
  std::string has_flag = this->has_flag ? "f" : ".";
  std::string is_revealed = this->is_revealed ? "r" : ".";

  return "[" + flag_mine + has_flag + is_revealed +
         std::to_string(this->mine_count) + "]";
}

std::string Field::get_display_str() {
  if (this->has_mine) {
    return "x";
  } else if (this->has_flag) {
    return "l";
  } else {
    return "o";
  }
}
