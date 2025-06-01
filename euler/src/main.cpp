#include "problems/problems.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {

  if (argc == 1 || atol(argv[1]) <= 0) {
    std::cout << "Problem number" << "\n";
    return -1;
  }

  auto int_arg = [&argc, &argv](int arg) {
    if (arg < argc) {
      return atoi(argv[arg]);
    } else {
      std::cout << "Oh no" << "\n";
      std::exit(-1);
    }
  };

  auto ifstream_arg = [&argc, &argv](int arg) {
    if (arg < argc) {
      return std::ifstream(argv[arg]);
    } else {
      std::cout << "Could not open file given at argument " << arg - 1 << "\n";
      std::exit(-1);
    }
  };

  size_t problem{static_cast<size_t>(atol(argv[1]))};

  switch (problem) {
  case 1: {
    multiples_of_three_or_five(int_arg(2));
  } break;

  case 2: {
    even_fibonacci_numbers(int_arg(2));
  } break;

  case 3: {
    largest_prime_factor(int_arg(2));
  } break;

  case 4: {
    largest_palindrome_product(int_arg(2));
  } break;

  case 5: {
    smallest_multiple(int_arg(2));
  } break;

  case 6: {
    sum_square_difference(int_arg(2));
  } break;

  case 7: {
    ith_prime(int_arg(2));
  } break;

  case 8: {
    std::ifstream file = ifstream_arg(3);
    largest_product_in_a_series(int_arg(2), file);
  } break;

  case 9: {
    special_pythagorean_triplet();
  } break;

  case 10: {
    summation_of_primes(int_arg(2));
  } break;

  case 11: {
    std::ifstream file = ifstream_arg(3);
    largest_product_in_a_grid(int_arg(2), file);
  } break;

  case 12:
    highly_divisible_triangular_number();
    break;

  case 13: {
    std::ifstream file = ifstream_arg(2);
    large_sum(file);
  } break;

  case 14:
    longest_collatz_sequence();
    break;

  case 15:
    lattice_paths();
    break;

  case 16:
    power_digit_sum();
    break;

  case 17:
    number_letter_counts();
    break;

  case 18: {
    std::ifstream file = ifstream_arg(2);
    maximum_path_sum(file);
  } break;

  case 19:
    counting_sundays();
    break;

  case 20:
    factorial_digit_sum();
    break;

  case 21:
    amicable_numbers();
    break;

  case 22: {
    std::ifstream file = ifstream_arg(2);
    name_scores(file);
  } break;

  case 23: {
    non_abundant_sums();
  } break;

  case 24: {
    lexicographic_permutations();
  } break;

  case 25: {
    large_fibonacci();
  } break;

  case 26: {
    reciprocal_cycles();
  } break;

  case 27: {
    quadratic_primes();
  } break;

  case 31: {
    coin_sums();
  } break;

  default:
    std::cout << "Problem not yet attempted" << "\n";
  }
}
