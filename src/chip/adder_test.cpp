#include "gtest/gtest.h"
#include "chip/basic_gates.h"
#include "chip/chip_test_util.h"
#include "chip/adder.h"

//#include <utility>
#include <memory>
#include <vector>

namespace {

using pin_board::PinBoard;
using pin_board::PinIndex;
using chip::Chip;
using chip::AndGate;
using chip::OrGate;
using chip::NotGate;
using chip::NandGate;
using chip::XorGate;
using chip::Adder;
using chip::Adder_2;
using std::vector;

TEST(AdderTest, TwoInput) {
    PinBoard board(10,2,2);
    Adder::CreateChip(board, {0,1}, {2,3});
    TestChipLogic(
            board,
            {
                {false, false},
                {false, true},
                {true, false},
                {true, true},
            },
            {
                {false, false},
                {true, false},
                {true, false},
                {false, true},
            });
}

TEST(AdderTest, Adder_2_input_1_digit_carry) {
    PinBoard board(10,3,2);
    Adder_2::CreateChip(board, {1}, {2}, 0, {3,4});
    TestChipLogic(
            board,
            {
                { {false, false, false}, NumberToPins(0,2) },
                { {false, false, true}, NumberToPins(1,2) },
                { {false, true, false}, NumberToPins(1,2) },
                { {true, false, false}, NumberToPins(1,2) },
                { {false, true, true}, NumberToPins(2,2) },
                { {true, false, true}, NumberToPins(2,2) },
                { {true, true, false}, NumberToPins(2,2) },
                { {true, true, true}, NumberToPins(3,2) },
            }
            );
}

TEST(AdderTest, Adder_2_input_2_digit_carry) {
    PinBoard board(20,5,3);
    Adder_2::CreateChip(board, {1,2}, {3,4}, 0, {5,6,7});
    TestChipLogic(
            board,
            {
                { {false, false, false, false, false}, NumberToPins(0, 3) },
                { {false, false, false, true, false}, NumberToPins(1, 3) },
                { {false, false, false, false, true}, NumberToPins(2, 3) },
                { {false, false, false, true, true}, NumberToPins(3, 3) },
                { {false, true, false, false, false}, NumberToPins(1, 3) },
                { {false, true, false, true, false}, NumberToPins(2, 3) },
                { {false, true, false, false, true}, NumberToPins(3, 3) },
                { {false, true, false, true, true}, NumberToPins(4, 3) },
                { {false, false, true, false, false}, NumberToPins(2, 3) },
                { {false, false, true, true, false}, NumberToPins(3, 3) },
                { {false, false, true, false, true}, NumberToPins(4, 3) },
                { {false, false, true, true, true}, NumberToPins(5, 3) },
                { {false, true, true, false, false}, NumberToPins(3, 3) },
                { {false, true, true, true, false}, NumberToPins(4, 3) },
                { {false, true, true, false, true}, NumberToPins(5, 3) },
                { {false, true, true, true, true}, NumberToPins(6, 3) },

                { {true, false, false, false, false}, NumberToPins(1, 3) },
                { {true, false, false, true, false}, NumberToPins(2, 3) },
                { {true, false, false, false, true}, NumberToPins(3, 3) },
                { {true, false, false, true, true}, NumberToPins(4, 3) },
                { {true, true, false, false, false}, NumberToPins(2, 3) },
                { {true, true, false, true, false}, NumberToPins(3, 3) },
                { {true, true, false, false, true}, NumberToPins(4, 3) },
                { {true, true, false, true, true}, NumberToPins(5, 3) },
                { {true, false, true, false, false}, NumberToPins(3, 3) },
                { {true, false, true, true, false}, NumberToPins(4, 3) },
                { {true, false, true, false, true}, NumberToPins(5, 3) },
                { {true, false, true, true, true}, NumberToPins(6, 3) },
                { {true, true, true, false, false}, NumberToPins(4, 3) },
                { {true, true, true, true, false}, NumberToPins(5, 3) },
                { {true, true, true, false, true}, NumberToPins(6, 3) },
                { {true, true, true, true, true}, NumberToPins(7, 3) },
            },
            20);
}
}
