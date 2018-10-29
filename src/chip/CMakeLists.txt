add_library(basic_gates basic_gates.h basic_gates.cpp)

add_executable(basic_gates_test basic_gates_test.cpp)
target_link_libraries(basic_gates_test basic_gates)
target_link_libraries(basic_gates_test pin_board)
target_link_libraries(basic_gates_test gtest_main)
add_test(basic_gates_test basic_gates_test --gtest_color=yes)
