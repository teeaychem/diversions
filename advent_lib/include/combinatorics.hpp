#pragma once
#include <iostream>
#include <unordered_set>
#include <vector>

namespace advent {
namespace combinatorics {


template <typename element>
std::vector<std::vector<element>>
permute(std::unordered_set<element> elements) {
  if (elements.empty()) {
    return std::vector<std::vector<element>>{std::vector<element>{}};
  }

  std::vector<std::vector<element>> out_vec;
  for (element e : elements) {
    std::unordered_set<element> elements_without{};
    for (auto other_e : elements) {
      if (e != other_e) {
        elements_without.insert(other_e);
      }
    }

    std::vector<std::vector<element>> subpermutations =
        permute(elements_without);
    for (auto sp : subpermutations) {
      sp.push_back(e);
      out_vec.push_back(sp);
    }
  }
  return out_vec;
}

template <typename element>
void display_permutations(std::vector<std::vector<element>> *permutations) {
  for (size_t p = 0; p < permutations->size(); p++) {
    std::vector<element> permutation = permutations->data()[p];
    std::cout << "(  ";
    for (size_t i = 0; i < permutation.size(); i++) {
      std::cout << permutation[i] << " ";
    }
    std::cout << ")" << std::endl;
  }
}


} // namespace combinatorics
} // namespace aoc
