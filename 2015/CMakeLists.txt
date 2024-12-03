cmake_minimum_required(VERSION 3.20)
project(advent_of_code_twenty_fifteen)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_compile_options(-pedantic -Wall -Wextra)

list(APPEND CMAKE_PREFIX_PATH "../advent_lib/install/")
find_package(advent 0.0.1 CONFIG REQUIRED)

find_package(OpenSSL REQUIRED)

# hard coded as fails to be found otherwise…
set(nlohmann_json_DIR ../vcpkg_installed/arm64-linux/share/nlohmann_json/)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(20151201 days/20151201.cpp)
add_executable(20151202 days/20151202.cpp)
add_executable(20151203 days/20151203.cpp)

add_executable(20151204 days/20151204.cpp)
target_link_libraries(20151204 PRIVATE OpenSSL::SSL)

add_executable(20151205 days/20151205.cpp)
add_executable(20151206 days/20151206.cpp)
add_executable(20151207 days/20151207.cpp)
add_executable(20151208 days/20151208.cpp)

add_executable(20151209 days/20151209.cpp)
target_link_libraries(20151209 PRIVATE advent::advent)

add_executable(20151210 days/20151210.cpp)
add_executable(20151211 days/20151211.cpp)

add_executable(20151212 days/20151212.cpp)
target_link_libraries(20151212 PRIVATE nlohmann_json::nlohmann_json)

add_executable(20151213 days/20151213.cpp)
target_link_libraries(20151213 PRIVATE advent::advent)

add_executable(20151214 days/20151214.cpp)
add_executable(20151215 days/20151215.cpp)

add_executable(20151216 days/20151216.cpp)

add_executable(20151217 days/20151217.cpp)
target_link_libraries(20151217 PRIVATE advent::advent)

add_executable(20151218 days/20151218.cpp)
add_executable(20151219 days/20151219.cpp)
add_executable(20151220 days/20151220.cpp)
add_executable(20151221 days/20151221.cpp)
add_executable(20151222 days/20151222.cpp)
add_executable(20151223 days/20151223.cpp)

add_executable(20151224 days/20151224.cpp)
target_link_libraries(20151224 PRIVATE advent::advent)

add_executable(20151225 days/20151225.cpp)
