cmake_minimum_required(VERSION 3.14)
project(linked_lists VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTS "Build unit tests" ON)

# библиотека со всеми функциями (без main)
add_library(lists STATIC
    src/singly_list.cpp
    src/doubly_list.cpp
    src/planets.cpp
    src/cycle.cpp
    src/menu.cpp
)
target_include_directories(lists PUBLIC include)
target_compile_options(lists PRIVATE -Wall -Wextra -Wpedantic -Werror)

# программа с меню
add_executable(linked_lists src/main.cpp)
target_link_libraries(linked_lists PRIVATE lists)
target_compile_options(linked_lists PRIVATE -Wall -Wextra -Wpedantic -Werror)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
