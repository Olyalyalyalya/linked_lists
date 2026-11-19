include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(list_tests
    test_singly_list.cpp
    test_doubly_list.cpp
    test_planets.cpp
    test_cycle.cpp
)
target_link_libraries(list_tests PRIVATE lists GTest::gtest_main)
target_compile_options(list_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)

include(GoogleTest)
gtest_discover_tests(list_tests)
