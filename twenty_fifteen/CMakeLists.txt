cmake_minimum_required(VERSION 3.20)
project(advent_of_code_2015)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_compile_options(-pedantic -Wall -Wextra)


add_executable(day_one days/day_one/day_one.cpp)
add_executable(day_two days/day_two/day_two.cpp)
add_subdirectory(days/day_three)


find_package(OpenSSL REQUIRED)

add_executable(day_four  days/day_four/day_four.cpp)

target_link_libraries(day_four PRIVATE OpenSSL::SSL)
target_link_libraries(day_four PRIVATE OpenSSL::Crypto)
