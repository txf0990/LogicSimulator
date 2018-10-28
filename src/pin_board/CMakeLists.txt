add_library(pin_board pin_board.h pin_board.cpp)

add_executable(pin_board_test pin_board_test.cpp)
target_link_libraries(pin_board_test pin_board)
add_test(pin_board_test pin_board_test --gtest_color=yes)
