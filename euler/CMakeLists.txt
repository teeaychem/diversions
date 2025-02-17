cmake_minimum_required(VERSION 3.20)
project(smt CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
message("Prefix path: ${CMAKE_PREFIX_PATH}")


find_package(cvc5)


# add_library(CVC5 REQUIRED)
# if(NOT CVC5)
#   message(FATAL_ERROR "cvc5 not found")
#  endif()

add_executable(special_pythagorean_triplet special_pythagorean_triplet.cpp)
target_link_libraries(special_pythagorean_triplet cvc5::cvc5 cvc5::cvc5parser)
