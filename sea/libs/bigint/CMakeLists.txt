cmake_minimum_required(VERSION 4.0)

project(
    BigInt
    VERSION 0.0.1
    LANGUAGES CXX
    DESCRIPTION "A simple BigInt library"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTS "Build tests" ON)

add_library(${PROJECT_NAME})

target_sources(
    ${PROJECT_NAME}
    PRIVATE
        src/comparisons.cpp
        src/convenience.cpp
        src/conversion.cpp
        src/operators.cpp
        src/int.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/include
        FILES include/BigInt.hpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(BUILD_TESTS)
    message("Seting up tests…")
    message("Possibly fetching and building Catch2…")
    include(FetchContent)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG
            v3.4.0 # or a later release
    )

    FetchContent_MakeAvailable(Catch2)
    message("Building tests…")

    add_executable(tests tests/tests.cpp)
    target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
    target_link_libraries(tests PRIVATE ${PROJECT_NAME})
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(installation)
