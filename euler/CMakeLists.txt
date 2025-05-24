cmake_minimum_required(VERSION 3.20)
project(smt CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(cvc5)


# add_library(CVC5 REQUIRED)
# if(NOT CVC5)
#   message(FATAL_ERROR "cvc5 not found")
#  endif()

add_executable(multiples_of_three_or_five multiples_of_three_or_five.cpp)

add_executable(even_fibonacci_numbers even_fibonacci_numbers.cpp)

add_executable(largest_prime_factor largest_prime_factor.cpp)

add_executable(largest_palindrome_product largest_palindrome_product.cpp)

add_executable(smallest_multiple smallest_multiple.cpp)

add_executable(sum_square_difference sum_square_difference.cpp)

add_executable(10001st_prime 10001st_prime.cpp)

add_executable(largest_product_in_a_series largest_product_in_a_series.cpp)

add_executable(special_pythagorean_triplet special_pythagorean_triplet.cpp)
target_link_libraries(special_pythagorean_triplet cvc5::cvc5 cvc5::cvc5parser)

add_executable(summation_of_primes summation_of_primes.cpp)

add_executable(largest_product_in_a_grid largest_product_in_a_grid.cpp)

add_executable(highly_divisible_triangular_number highly_divisible_triangular_number.cpp)

add_executable(large_sum large_sum.cpp)

add_executable(longest-collatz-sequence longest-collatz-sequence.cpp)

add_executable(factorial-digit-sum factorial-digit-sum.cpp)

add_executable(maximum-path-sum-1 maximum-path-sum-1.cpp)
