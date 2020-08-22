file(GLOB SOURCES
        *.cpp
        *.hpp
        *.h
        )

add_executable(tests ${SOURCES})

target_compile_options(tests PRIVATE -Werror -Wall -Wextra -Wpedantic -DDEBUG=1)

target_link_libraries(tests PRIVATE sfml-graphics)
target_link_libraries(tests PRIVATE sfml-window)
target_link_libraries(tests PRIVATE sfml-system)
target_link_libraries(tests PRIVATE boost_unit_test_framework)
