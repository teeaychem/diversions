cmake_minimum_required(VERSION 3.20)
project(advent_of_code_twenty_fifteen)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_compile_options(-pedantic -Wall -Wextra)

list(APPEND CMAKE_PREFIX_PATH "../advent_lib/install/")
find_package(advent 0.0.1 CONFIG REQUIRED)

# find_package(OpenSSL REQUIRED)


add_executable(day_one days/day_one.cpp)
add_executable(day_two days/day_two.cpp)
add_executable(day_three days/day_three.cpp)

# add_executable(day_four days/day_four.cpp)
# target_link_libraries(day_four PRIVATE OpenSSL::SSL)

add_executable(day_five days/day_five.cpp)
add_executable(day_six days/day_six.cpp)
add_executable(day_seven days/day_seven.cpp)
add_executable(day_eight days/day_eight.cpp)

add_executable(day_nine days/day_nine.cpp)
target_link_libraries(day_nine PRIVATE advent::advent)

add_executable(day_ten days/day_ten.cpp)
add_executable(day_eleven days/day_eleven.cpp)

# fails to be found …
# find_package(nlohmann_json CONFIG REQUIRED)
# add_executable(day_twelve days/day_twelve.cpp)
# target_link_libraries(day_twelve PRIVATE nlohmann_json::nlohmann_json)

add_executable(day_thirteen days/day_thirteen.cpp)
target_link_libraries(day_thirteen PRIVATE advent::advent)

add_executable(day_fourteen days/day_fourteen.cpp)
add_executable(day_fifteen days/day_fifteen.cpp)

add_executable(day_sixteen days/day_sixteen.cpp)

add_executable(day_seventeen days/day_seventeen.cpp)
target_link_libraries(day_seventeen PRIVATE advent::advent)

add_executable(day_eighteen days/day_eighteen.cpp)
add_executable(day_nineteen days/day_nineteen.cpp)
# add_executable(day_twenty days/day_twenty.cpp)
add_executable(day_twentyone days/day_twentyone.cpp)
add_executable(day_twentytwo days/day_twentytwo.cpp)
add_executable(day_twentythree days/day_twentythree.cpp)

add_executable(day_twentyfour days/day_twentyfour.cpp)
target_link_libraries(day_twentyfour PRIVATE advent::advent)
