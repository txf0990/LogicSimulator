include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main main.cpp)

add_executable(gtest_test gtest_test.cpp)
target_link_libraries(gtest_test gtest_main)
add_test(gtest_test gtest_test --gtest_color=yes)

add_subdirectory(pin_board)
add_subdirectory(chip)
