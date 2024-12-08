cmake_minimum_required(VERSION 3.20)
project(advent_of_code_twenty_sixteen)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenSSL REQUIRED)

add_compile_options(-pedantic -Wall -Wextra)

list(APPEND CMAKE_PREFIX_PATH "../advent_lib/install/")
find_package(advent 0.0.1 CONFIG REQUIRED)

add_executable(20161201 days/20161201.cpp)
target_link_libraries(20161201 PRIVATE advent::advent)

add_executable(20161202 days/20161202.cpp)
target_link_libraries(20161202 PRIVATE advent::advent)

add_executable(20161203 days/20161203.cpp)

add_executable(20161204 days/20161204.cpp)

add_executable(20161205 days/20161205.cpp)
target_link_libraries(20161205 PRIVATE OpenSSL::SSL)

add_executable(20161206 days/20161206.cpp)
add_executable(20161207 days/20161207.cpp)
add_executable(20161208 days/20161208.cpp)
add_executable(20161209 days/20161209.cpp)
add_executable(20161210 days/20161210.cpp)

add_executable(20161211 days/20161211.cpp)
target_link_libraries(20161211 PRIVATE advent::advent)
