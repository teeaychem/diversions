#include <utility>
#include <vector>
namespace euler {
namespace utils {

template <typename T>
void next_permutation(std::vector<T> &v) {
  size_t size = v.size();

  size_t pivot{size - 2};

  for (auto it = v.rbegin() + 1; it != v.rend(); ++it) {
    if (*it < *(it - 1)) {
      goto use_pivot;
    } else {
      --pivot;
    }
  }

reverse:

  std::reverse(v.begin(), v.end());
  return;

use_pivot:

  size_t until_pivot = size - 1 - pivot;
  T pivot_value = v.at(pivot);

  for (auto it = v.rbegin(); it != v.rend() && 0 < until_pivot; ++it) {
    if (pivot_value < *it) {
      std::swap(v.at(pivot), *it);
      break;
    }

    --until_pivot;
  }

  std::reverse(v.begin() + pivot + 1, v.end());
  return;
}

template <typename T>
std::vector<std::pair<T, T>> divisor_pairs(T n) {

  std::vector<std::pair<T, T>> pairs{{1, n}};

  for (T d{2}; d * d <= n; ++d) {
    if (n % d == 0) {
      pairs.push_back(std::make_pair(d, n / d));
    }
  }

  return pairs;
}

template <typename T>
std::vector<T> primes_below(T n) {

  std::vector<bool> sieve = std::vector(n, true);
  sieve.at(0) = false;
  sieve.at(1) = false;

  std::vector<T> primes{2};

  T prime{2};

  while (prime < n) {
  sieve_factors:
    for (T factor{2}; (prime * factor) < n; ++factor) {
      sieve.at(prime * factor) = false;
    }

  find_next_prime:
    ++prime;

    for (; prime < n; ++prime) {

      if (sieve.at(prime)) {
        primes.push_back(prime);
        goto sieve_factors;
      }
    }
  }

  return primes;
}

template <typename T>
bool is_prime_by_trial(T n) {

  if (n < 2) {
    return false;
  }

  for (T i{2}; (i * i) <= n; ++i) {
    if (n % i == 0) {
      return false;
    }
  }

  return true;
}

template <typename T>
size_t count_digits(T n) {
  std::vector<T> digits{};

  if (n == 0) {

    return 1;
  }

  size_t count{0};

  while (n != 0) {
    count++;
    n /= 10;
  }

  return count;
}

template <typename T>
std::vector<T> get_digits_reversed(T n) {
  std::vector<T> digits{};

  if (n == 0) {
    digits.push_back(0);
    return digits;
  }

  while (n != 0) {
    digits.push_back(n % 10);
    n /= 10;
  }

  return digits;
}

template <typename T>
T digits_sorted(T n) {

  std::vector<T> digits = get_digits_reversed(n);

  sort(digits.begin(), digits.end(),
       [](T const &a, T const &b) { return b < a; });

  T sorted{0};

  size_t idx{0};
  for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
    sorted += *it * pow(10, idx);
    idx++;
  }

  return sorted;
}

} // namespace utils
} // namespace euler
