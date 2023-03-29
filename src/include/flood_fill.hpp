#ifndef FLOOD_FILL_HPP
#define FLOOD_FILL_HPP

#include <stdexcept>
#include <vector>

template <typename T> struct FillData {
  std::vector<T> &board;
  std::function<bool(T &)> mutating_predicate;
  int width, height;
};

template <typename T>
bool is_field_valid(unsigned long index, const FillData<T> &data) {

  if (index >= data.board.size() || index < 0) {
    return false;
  }
  return data.mutating_predicate(data.board.at(index));
}

template <typename T>
void get_adjacent_indices(unsigned long index,
                          std::vector<unsigned long> &adjacent_indices,
                          const FillData<T> &data) {
  unsigned long current_row = index / data.width;
  adjacent_indices.clear();
  adjacent_indices.push_back(index - data.width);
  adjacent_indices.push_back(index + data.width);

  // validate that column offset does not overflow to different row
  if ((index - 1) / data.width == current_row) {
    adjacent_indices.push_back(index - 1);
  }
  if ((index + 1) / data.width == current_row) {
    adjacent_indices.push_back(index + 1);
  }
}

template <typename T>
void flood_fill(std::vector<T> &board, int width, int height,
                std::function<bool(T &)> mutating_predicate,
                unsigned long start_index) {

  FillData<T> fill_data = {
      board,
      mutating_predicate,
      width,
      height,
  };

  std::vector<unsigned long> check_stack(128);
  std::vector<unsigned long> adjacent_indices(4);

  unsigned long current_index;

  if (board.size() < start_index) {
    return;
  }

  fill_data.mutating_predicate(board.at(start_index));
  check_stack.push_back(start_index);

  while (!check_stack.empty()) {
    current_index = check_stack.back();
    check_stack.pop_back();
    get_adjacent_indices(current_index, adjacent_indices, fill_data);

    for (auto index : adjacent_indices) {
      if (is_field_valid(index, fill_data)) {
        check_stack.push_back(index);
      }
    }
  }
}

#endif
