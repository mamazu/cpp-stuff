file(GLOB SOURCES
        *.cpp
        *.hpp
        *.h
        )

add_executable(platformer ${SOURCES})

target_compile_options(platformer PRIVATE -Werror -Wall -Wextra -Wpedantic -DDEBUG=1)

target_link_libraries(platformer PRIVATE sfml-graphics)
target_link_libraries(platformer PRIVATE sfml-window)
target_link_libraries(platformer PRIVATE sfml-system)
