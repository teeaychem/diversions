#include "utils/display.hpp"
#include "utils/utils.hpp"
#include <cstdint>
#include <iostream>
#include <map>
#include <vector>

template <typename T>
T get_max_rotation(T n) {

  if (n == 0) {
    return 0;
  }

  std::vector<T> digits{};

  while (n != 0) {
    digits.push_back(n % 10);
    n /= 10;
  }

  std::vector<T> rotations{};
  for (T i{0}; i < digits.size(); ++i) {
    T rotation = digits.at(i);
    for (T j{1}; j < digits.size(); ++j) {
      rotation = rotation * 10 + digits.at((i + j) % digits.size());
    }
    rotations.push_back(rotation);
  }

  sort(rotations.begin(), rotations.end(),
       [](const T &a, const T &b) { return b < a; });

  return rotations.front();
}

void circular_primes() {

  std::vector<int64_t> primes = euler::utils::primes_below((int64_t)1'000'000);

  std::map<int64_t, std::vector<int64_t>> digits_to_primes{};

  for (auto it = primes.begin(); it != primes.end(); ++it) {
    int64_t min_rotation = get_max_rotation(*it);

    auto kv = digits_to_primes.find(min_rotation);
    if (kv != digits_to_primes.end()) {
      kv->second.push_back(*it);
    } else {
      std::vector<int64_t> prime_set{*it};
      digits_to_primes.insert_or_assign(min_rotation, prime_set);
    }
  }

  size_t count{0};

  for (auto it = digits_to_primes.begin(); it != digits_to_primes.end(); ++it) {
    size_t digit_count = euler::utils::count_digits(it->first);
    if (digit_count == it->second.size()) {
      std::cout << it->first << "\n";
      count += digit_count;
    }
  }

  for (int64_t d{1}; d < 10; ++d) {
    int64_t repeat = d;
    for (int64_t l{1}; l < 6; ++l) {
      repeat = repeat * 10 + d;
      if (euler::utils::is_prime_by_trial(repeat)) {
        count++;
        std::cout << repeat << "\n";
      }
    }
  }

  std::cout << "Total primes: " << count << "\n";
};
