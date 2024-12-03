cmake_minimum_required(VERSION 3.20)
project(advent_of_code_twenty_sixteen)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_compile_options(-pedantic -Wall -Wextra)

list(APPEND CMAKE_PREFIX_PATH "../advent_lib/install/")
find_package(advent 0.0.1 CONFIG REQUIRED)

add_executable(day_one days/day_one.cpp)
target_link_libraries(day_one PRIVATE advent::advent)

add_executable(day_two days/day_two.cpp)
target_link_libraries(day_two PRIVATE advent::advent)

add_executable(day_three days/day_three.cpp)

add_executable(day_four days/day_four.cpp)
