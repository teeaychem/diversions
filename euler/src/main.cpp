#include "problems/problems.hpp"
#include <fstream>
#include <iostream>

int get_int_at_arg(int argc, char *argv[], int arg) {
  if (arg < argc) {
    return atoi(argv[arg]);
  } else {
    std::cout << "Oh no" << "\n";
    std::exit(-1);
  }
}

std::ifstream get_ifsteam_at_arg(int argc, char *argv[], int arg) {
  if (arg < argc) {
    return std::ifstream(argv[arg]);
  } else {
    std::cout << "Could not open file given at argument " << arg - 1 << "\n";
    std::exit(-1);
  }
}

int main(int argc, char *argv[]) {

  if (argc == 1 || atol(argv[1]) <= 0) {
    std::cout << "Problem number" << "\n";
    return -1;
  }

  size_t problem{static_cast<size_t>(atol(argv[1]))};

  if (problem == 1) {

    int limit = get_int_at_arg(argc, argv, 2);
    multiples_of_three_or_five(limit);
  }

  else if (problem == 2) {
    int limit = get_int_at_arg(argc, argv, 2);
    even_fibonacci_numbers(limit);
  }

  else if (problem == 3) {
    int limit = get_int_at_arg(argc, argv, 2);
    largest_prime_factor(limit);
  }

  else if (problem == 4) {
    int limit = get_int_at_arg(argc, argv, 2);
    largest_palindrome_product(limit);
  }

  else if (problem == 5) {
    int n = get_int_at_arg(argc, argv, 2);
    smallest_multiple(n);
  }

  else if (problem == 6) {
    int n = get_int_at_arg(argc, argv, 2);
    sum_square_difference(n);
  }

  else if (problem == 7) {
    int n = get_int_at_arg(argc, argv, 2);
    ith_prime(n);
  }

  else if (problem == 8) {
    int n = get_int_at_arg(argc, argv, 2);
    std::ifstream file = get_ifsteam_at_arg(argc, argv, 3);
    largest_product_in_a_series(n, file);
  }

  else if (problem == 9) {
    special_pythagorean_triplet();
  }

  else if (problem == 10) {
    int n = get_int_at_arg(argc, argv, 2);
    summation_of_primes(n);
  }

  else if (problem == 11) {
    int n = get_int_at_arg(argc, argv, 2);
    std::ifstream file = get_ifsteam_at_arg(argc, argv, 3);
    largest_product_in_a_grid(n, file);
  }

  else if (problem == 12) {
    highly_divisible_triangular_number();
  }

  else if (problem == 13) {
    std::ifstream file = get_ifsteam_at_arg(argc, argv, 2);
    large_sum(file);
  }

  else if (problem == 14) {
    longest_collatz_sequence();
  }

  else if (problem == 15) {
    lattice_paths();
  }

  else if (problem == 16) {
    power_digit_sum();
  }

  else if (problem == 18) {
    std::ifstream file = get_ifsteam_at_arg(argc, argv, 2);
    maximum_path_sum(file);
  }

  else if (problem == 20) {
    factorial_digit_sum();
  }

  else if (problem == 22) {
    std::ifstream file = get_ifsteam_at_arg(argc, argv, 2);
    name_scores(file);
  }

  else if (problem == 25) {
    large_fibonacci();
  }

  else if (problem == 31) {
    coin_sums();
  }

  else {
    std::cout << "Problem not yet attempted" << "\n";
  }
}
