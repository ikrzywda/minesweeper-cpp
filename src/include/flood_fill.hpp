#ifndef FLOOD_FILL_HPP
#define FLOOD_FILL_HPP

#include <stdexcept>
#include <vector>

template <typename T> struct FillData {
  std::vector<T> &board;
  const std::vector<T> &overridable_values;
  const T overriding_value;
  int width, height;
};

template <typename T>
bool is_field_valid(unsigned long index, const FillData<T> &data) {
  T current_field;

  if (index >= data.board.size() || index < 0) {
    return false;
  }

  current_field = data.board.at(index);

  return current_field != data.overriding_value &&
         std::find(data.overridable_values.begin(),
                   data.overridable_values.end(),
                   current_field) != data.overridable_values.end();
}

template <typename T>
void get_adjacent_indices(unsigned long index,
                          std::vector<unsigned long> &adjacent_indices,
                          const FillData<T> &data) {
  adjacent_indices.clear();
  adjacent_indices.push_back(index - data.width);
  adjacent_indices.push_back(index + data.width);
  adjacent_indices.push_back(index - 1);
  adjacent_indices.push_back(index + 1);
}

template <typename T>
void flood_fill(std::vector<T> &board, int width, int height,
                const std::vector<T> &overridable_values, T overriding_value,
                unsigned long start_index) {

  FillData<T> fill_data = {board, overridable_values, overriding_value, width,
                           height};

  std::vector<unsigned long> check_stack(128);
  std::vector<unsigned long> adjacent_indices(4);
  unsigned long current_index;

  if (board.size() < start_index) {
    return;
  }

  check_stack.push_back(start_index);

  while (!check_stack.empty()) {
    current_index = check_stack.back();
    check_stack.pop_back();
    get_adjacent_indices(current_index, adjacent_indices, fill_data);

    for (auto index : adjacent_indices) {
      if (is_field_valid(index, fill_data)) {
        board.at(index) = overriding_value;
        check_stack.push_back(index);
      }
    }
  }
}

#endif
