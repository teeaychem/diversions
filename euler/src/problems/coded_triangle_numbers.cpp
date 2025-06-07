#include <cstdint>
#include <fstream>
#include <iostream>

#include "utils/utils.hpp"

bool triangle_number(int64_t n) {

  auto pairs = euler::utils::divisor_pairs(2 * n);
  for (auto pair : pairs) {
    if (abs(pair.first - pair.second) == 1) {
      return true;
    }
  }

  return false;
}

void coded_triangle_numbers(std::ifstream &file) {

  std::string line;
  std::string word;
  int64_t word_value{0};
  size_t count{0};

  if (file.is_open()) {
    while (getline(file, line)) {
      for (char c : line) {
        if (c == ',') {

          if (triangle_number(word_value)) {
            std::cout << word << " " << word_value << "\n";
            count++;
          }

          word.clear();
          word_value = 0;
        } else if (c == '\"') {
        } else {
          word.push_back(c);
          word_value += (c - 'A') + 1;
        }
      }
    }
    file.close();
  } else {
    std::cout << "Unable to open file" << "\n";
  }

  std::cout << count << "\n";
};
