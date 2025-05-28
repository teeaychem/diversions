cmake_minimum_required(VERSION 4.0)
project(euler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(cvc5)

find_package(BigInt CONFIG REQUIRED PATHS "../sea/libs/bigint/install/")
message("PREFIX ${CMAKE_PREFIX_PATH}")

message("PREFIX ${PROJECT_SOURCE_DIR}")

add_executable(euler)
target_sources(euler PRIVATE src/main.cpp)
target_include_directories(euler PRIVATE "${PROJECT_SOURCE_DIR}/src")
add_subdirectory(src)

target_link_libraries(euler cvc5::cvc5 cvc5::cvc5parser BigInt::BigInt)

install(TARGETS euler)
