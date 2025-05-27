cmake_minimum_required(VERSION 4.0)
project(euler CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(cvc5)

find_package(BigInt CONFIG REQUIRED PATHS "../sea/libs/bigint/install/")
message("PREFIX ${CMAKE_PREFIX_PATH}")

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
target_link_libraries(large_sum PRIVATE BigInt::BigInt)

add_executable(longest_collatz_sequence longest_collatz_sequence.cpp)

add_executable(maximum_path_sum maximum_path_sum.cpp)
