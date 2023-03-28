#ifndef FLOOD_FILL_HPP
#define FLOOD_FILL_HPP

#include <stdexcept>
#include <vector>

template <typename T, typename Predicate> struct FillData {
  std::vector<T> &board;
  Predicate field_validity_predicate;
  const T overriding_value;
  int width, height;
};

template <typename T, typename Predicate>
bool is_field_valid(unsigned long index, const FillData<T, Predicate> &data) {

  if (index >= data.board.size() || index < 0) {
    return false;
  }
  return data.field_validity_predicate(data.board.at(index));
}

template <typename T, typename Predicate>
void get_adjacent_indices(unsigned long index,
                          std::vector<unsigned long> &adjacent_indices,
                          const FillData<T, Predicate> &data) {
  adjacent_indices.clear();
  adjacent_indices.push_back(index - data.width);
  adjacent_indices.push_back(index + data.width);

  // validate that column offset does not overflow to different row
  if (index % data.width != 0) {
    adjacent_indices.push_back(index - 1);
  }
  if (index % data.width != 1) {
    adjacent_indices.push_back(index + 1);
  }
}

template <typename T, typename Predicate>
void flood_fill(std::vector<T> &board, int width, int height,
                Predicate field_validity_predicate, T overriding_value,
                unsigned long start_index) {

  FillData<T, Predicate> fill_data = {
      board, field_validity_predicate, overriding_value, width, height,
  };

  std::vector<unsigned long> check_stack(128);
  std::vector<unsigned long> adjacent_indices(4);

  unsigned long current_index;

  if (board.size() < start_index) {
    return;
  }

  board.at(start_index) = overriding_value;
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
