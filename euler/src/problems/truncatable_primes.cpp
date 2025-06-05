#include "utils/utils.hpp"

#include <cstdint>
#include <deque>
#include <iostream>
#include <set>

using namespace std;

/*
Quite a messy approach.

The idea is to build up a list of primes which are truncatable from the right.
This is fairly simple, as the initial digit must be a prime and larger primes
can be found by inspecting extensions of smaller primes, implemented here
through a queue of primes to inspect.

This terminates reasonably quickly, and so testing for whether the primes are
truncatable from the left can also be done in reasonable time.
 */
void truncatable_primes() {

  set<int64_t> right_ok{};

  int64_t digit_primes[] = {2, 3, 5, 7};

  deque<int64_t> right_todo{};
  for (int64_t d : digit_primes) {
    right_todo.push_back(d);
  }

  while (!right_todo.empty()) {

    int64_t todo = right_todo.front();
    right_todo.pop_front();

    todo *= 10;

    bool limit = true;

    for (int64_t d{1}; d < 10; d += 2) {
      int64_t extended = todo + d;
      if (euler::utils::is_prime_by_trial(extended)) {
        limit = false;
        right_todo.push_back(extended);
        right_ok.insert(extended);
      }
    }
  }

  size_t count{0};
  int64_t sum{0};

  for (int64_t p : right_ok) {

    int64_t p_l = p;
    while (0 != p_l && euler::utils::is_prime_by_trial(p_l)) {
      p_l = euler::utils::remove_first_digit(p_l);
    }

    if (p_l == 0) {
      cout << p << "\n";
      count++;
      sum += p;
    }
  }

  cout << "\n"
       << count << "\n"
       << sum << "\n";
}
