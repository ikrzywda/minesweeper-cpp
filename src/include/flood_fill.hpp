#ifndef FLOOD_FILL_HPP
#define FLOOD_FILL_HPP

#include <stdexcept>
#include <vector>

template <typename T, typename Predicate, typename Mapping> struct FillData {
  std::vector<T> &board;
  Predicate field_validity_predicate;
  Mapping field_mapping;
  int width, height;
};

template <typename T, typename Predicate, typename Mapping>
bool is_field_valid(unsigned long index,
                    const FillData<T, Predicate, Mapping> &data) {

  if (index >= data.board.size() || index < 0) {
    return false;
  }
  return data.field_validity_predicate(data.board.at(index));
}

template <typename T, typename Predicate, typename Mapping>
void get_adjacent_indices(unsigned long index,
                          std::vector<unsigned long> &adjacent_indices,
                          const FillData<T, Predicate, Mapping> &data) {
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

template <typename T, typename Predicate, typename Mapping>
void flood_fill(std::vector<T> &board, int width, int height,
                Predicate field_validity_predicate, Mapping field_mapping,
                unsigned long start_index) {

  FillData<T, Predicate, Mapping> fill_data = {
      board, field_validity_predicate, field_mapping, width, height,
  };

  std::vector<unsigned long> check_stack(128);
  std::vector<unsigned long> adjacent_indices(4);

  unsigned long current_index;

  if (board.size() < start_index) {
    return;
  }

  board.at(start_index) = field_mapping(board.at(start_index));
  check_stack.push_back(start_index);

  while (!check_stack.empty()) {
    current_index = check_stack.back();
    check_stack.pop_back();
    get_adjacent_indices(current_index, adjacent_indices, fill_data);

    for (auto index : adjacent_indices) {
      if (is_field_valid(index, fill_data)) {
        board.at(index) = field_mapping(board.at(index));
        check_stack.push_back(index);
      }
    }
  }
}

#endif
