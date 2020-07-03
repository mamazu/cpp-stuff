cmake_minimum_required(VERSION 3.16)
project(platformer)

set(CMAKE_CXX_STANDARD 17)

add_executable(platformer main.cpp Body.cpp)
target_compile_options(platformer PRIVATE -Werror -Wall -Wextra -Wpedantic)

target_link_libraries(platformer PRIVATE sfml-graphics)
target_link_libraries(platformer PRIVATE sfml-window)
target_link_libraries(platformer PRIVATE sfml-system)
