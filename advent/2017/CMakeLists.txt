cmake_minimum_required(VERSION 3.20)
project(advent_of_code_twenty_sixteen)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(OpenSSL REQUIRED)

add_compile_options(-pedantic -Wall -Wextra)

list(APPEND CMAKE_PREFIX_PATH "../advent_lib/install/")
find_package(advent 0.0.1 CONFIG REQUIRED)

add_executable(20171201 days/20171201.cpp)
target_link_libraries(20171201 PRIVATE advent::advent)
