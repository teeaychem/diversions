#pragma once
#include <iostream>
#include <unordered_set>
#include <vector>

template <typename element>
void size_k_vectors_helper(std::vector<std::vector<element>> &variations,
                           std::vector<element> &used, std::vector<element> &v,
                           int k) {
  if (k == 0) {
    std::vector<element> the_copy = used;
    variations.push_back(the_copy);
  } else if (v.empty()) {
    return;
  } else {
    element last = v.back();
    v.pop_back();
    size_k_vectors_helper(variations, used, v, k);
    used.push_back(last);
    size_k_vectors_helper(variations, used, v, k - 1);
    used.pop_back();
    v.push_back(last);
  }
}

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
void display_permutations(std::vector<std::vector<element>> &permutations) {
  for (size_t p = 0; p < permutations.size(); p++) {
    std::vector<element> permutation = permutations.data()[p];
    std::cout << "( ";
    for (size_t i = 0; i < permutation.size(); i++) {
      std::cout << permutation[i] << " ";
    }
    std::cout << ")" << std::endl;
  }
}

template <typename element>
std::vector<std::vector<element>> size_k_vectors(std::vector<element> const &v,
                                                 int k) {
  std::vector<std::vector<element>> variations{};
  std::vector<element> buffer;
  std::vector<element> vc = v;
  size_k_vectors_helper(variations, buffer, vc, k);
  return variations;
}

} // namespace combinatorics
} // namespace advent
