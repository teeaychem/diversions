#include "utils/utils.hpp"
#include <cstdint>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

void prime_permutations() {
  std::vector<int64_t> primes = euler::utils::primes_below((int64_t)10000);

  std::vector<int64_t> four_primes{};

  // Filter primes up to four digits to exactly four digits.
  for (auto it = primes.begin(); it != primes.end(); ++it) {
    if (1000 <= *it) {
      four_primes.push_back(*it);
    }
  }

  std::map<int64_t, std::vector<int64_t>> four_permutation_primes{};

  // For each permutation, figure out which primes are a permutation by checking the ordered digits.
  for (int64_t digits{1111}; digits <= 9999; ++digits) {
    int64_t permutation = euler::utils::digits_reverse_sorted(digits);

    if (four_permutation_primes.contains(permutation)) {
      continue;
    }

    std::vector<int64_t> primes{};

    for (auto it2 = four_primes.begin(); it2 != four_primes.end(); ++it2) {
      if (permutation == euler::utils::digits_reverse_sorted(*it2)) {
        primes.push_back(*it2);
      }
    }

    four_permutation_primes[permutation] = primes;
  }

  // For each permutation, create a map of differences to prime pairs.
  for (auto x : four_permutation_primes) {
    if (2 <= x.second.size()) {

      std::map<size_t, std::vector<int64_t>> differences{};

      for (size_t i{0}; i < x.second.size() - 1; ++i) {

        int64_t a = x.second.at(i);

        for (size_t j{i + 1}; j < x.second.size(); ++j) {

          int64_t b = x.second.at(j);

          std::vector<int64_t> &d = differences[abs(b - a)];

          d.push_back(a);
          d.push_back(b);
        }
      }

      for (auto a : differences) {
        if (3 <= a.second.size()) {
          std::cout << x.first << " :: \t";
          std::cout << a.first << "\t : ";
          for (auto b : a.second) {
            std::cout << "\t" << b << " ";
          }

          if (a.second[1] == a.second[2]) {
            std::cout << " !";
          }

          std::cout << "\n";
        }
      }
    }
  }
}
