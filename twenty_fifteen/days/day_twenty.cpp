#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

void sieve_of_eratosthenes(int n, function<void(int)> f) {
  vector<int> the_primes;
  vector<bool> the_a = vector(n, true);
  for (int i = 2; i < sqrt(n); i++) {
    if (the_a[i] == true) {
      for (int j = i * i; j < n; j += i) {
        the_a[j] = false;
      }
    }
  }
  cout << "applying" << endl;
  for (int k = 0; k < n; k++) {
    if (the_a[k]) {
      f(k);
    }
  }
}

int count_presents(int house) {
  int total = 0;
  for (int j = 1; j <= house; j++) {
    if ((house % j) == 0) {
      total += (10 * j);
    }
  }
  cout << "house: " << house << " gets: " << total << endl;
  return total;
}

int factorial(int n) {
  if (n == 0) {
    return 1;
  } else {
    return n * factorial(n - 1);
  }
}

int main(int argc, char **argv) {

  uint n = ???;
  for (int i = 1;; i++) {
    if (factorial(i) > n) {
      cout << i << endl;
      int every_house = 0;
      for (int j = 0; j <= i; j++) {
        every_house |= (1 << j);
      }
      cout << "eh " << every_house << endl;
      cout << count_presents(every_house) << endl;
      break;
    }
  }

  // auto check_total = [n](int p) {
  //   if (count_presents(p) >= n) {
  //     cout << p << endl;
  //   }
  // };

  auto get_prime_limit = [n](uint p) {
    if (p >= n) {
      cout << "limit: " << p << endl;
      exit(1);
    }
  };
  // sieve_of_eratosthenes(n * 2, get_prime_limit);
  // int prime_limit = ???;
  // vector<int> the_primes{};
  // auto get_primes = [&the_primes](int p) { the_primes.push_back(p); };
  // sieve_of_eratosthenes(prime_limit, get_primes);
  // cout << "the " << the_primes.size() << " th prime" << endl;

  vector<uint> ok_houses{};
  uint total_houses = ???;
  vector<uint> presents_at_house = vector(total_houses + 1, (uint)0);
  for (uint elf = 1; elf < total_houses; elf++) {
    // for (uint house = elf; house < total_houses; house += elf) {
    uint limit = min(total_houses, elf * 50);
    for (uint house = elf; house < limit; house += elf) {
      presents_at_house[house] += 11 * elf;
      if (presents_at_house[house] >= n) {
        ok_houses.push_back(house);
      }
    }
  }
  sort(ok_houses.begin(), ok_houses.end(), less<uint>());
  cout << ok_houses.front() << endl;



  return 0;
}
