cmake_minimum_required(VERSION 3.20)
project(advent_of_code_2015)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_compile_options(-pedantic -Wall -Wextra)


add_executable(day_one days/day_one.cpp)
add_executable(day_two days/day_two.cpp)
add_executable(day_three days/day_three.cpp)

find_package(OpenSSL REQUIRED)

add_executable(day_four days/day_four.cpp)
target_link_libraries(day_four PRIVATE OpenSSL::SSL)

add_executable(day_five days/day_five.cpp)
add_executable(day_six days/day_six.cpp)
add_executable(day_seven days/day_seven.cpp)
add_executable(day_eight days/day_eight.cpp)
add_executable(day_nine days/day_nine.cpp)
add_executable(day_ten days/day_ten.cpp)
add_executable(day_eleven days/day_eleven.cpp)


find_package(nlohmann_json 3.2.0 REQUIRED)
add_executable(day_twelve days/day_twelve.cpp)
target_link_libraries(day_twelve PRIVATE nlohmann_json::nlohmann_json)
