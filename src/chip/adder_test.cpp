#include "chip/adder.h"

#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "chip/basic_gates.h"
#include "chip/chip_test_util.h"

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

TEST(AdderTest, Adder_2_input_4_digit_carry) {
    PinBoard board(20,9,5);
    Adder_2::CreateChip(board, GetVectorPart(1,4), GetVectorPart(5,4), 0, GetVectorPart(9,5));
    TestChipLogic(
            board,
            {
                { {true, true, true, true, true, true, true, true, true}, NumberToPins(31,5) },
                { {true, false, true, true, true, true, false, true, true}, NumberToPins(28,5) },
                { {false, true, true, false, true, true, false, true, false}, NumberToPins(16,5) },
                { {true, false, true, false, true, false, true, false, true}, NumberToPins(21,5) },
                { {false, false, false, false, false, false, false, false, false}, NumberToPins(0,5) },
                { {true, true, true, true, true, false, false, false, false}, NumberToPins(16,5) },
                { {true, false, false, false, false, true, true, true, true}, NumberToPins(16,5) },
                { {false, false, false, false, false, true, true, true, true}, NumberToPins(15,5) },
                { {false, true, false, false, false, true, true, true, true}, NumberToPins(16,5) },
            },
            20);
}

TEST(AdderTest, Adder_2_input_8_digit_carry) {
    PinBoard board(30,17,9);
    Adder_2::CreateChip(board, GetVectorPart(1,8), GetVectorPart(9,8), 0, GetVectorPart(17,9));
    TestChipLogic(
            board,
            {
                { {1,  1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1}, NumberToPins(511,9) },
                { {0,  1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1}, NumberToPins(510,9) },
                { {1,  0,0,0,0,0,0,0,0,  1,1,1,1,1,1,1,1}, NumberToPins(256,9) },
                { {0,  0,0,0,0,0,0,0,0,  1,1,1,1,1,1,1,1}, NumberToPins(255,9) },
                { {0,  0,1,1,0,1,0,1,1,  1,0,1,1,1,0,1,0}, NumberToPins(307,9) },
            },
            20);
}

TEST(AdderTest, Adder_2_input_16_digit_carry) {
    PinBoard board(100,33,17);
    Adder_2::CreateChip(board, GetVectorPart(1,16), GetVectorPart(17,16), 0, GetVectorPart(33,17));
    TestChipLogic(
            board,
            {
                { {1,  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, NumberToPins(131071,17) },
                { {0,  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, NumberToPins(131070,17) },
                { {1,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, NumberToPins(65536,17) },
                { {0,  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, NumberToPins(65535,17) },
                { {1,  1,1,0,1,1,1,1,0,0,1,1,0,1,0,1,1,  0,0,1,0,1,1,1,1,0,0,0,0,0,0,1,1}, NumberToPins(104304,17) },
                { {1,  1,1,0,0,1,0,1,1,1,1,1,1,0,0,1,0,  0,0,1,0,0,0,0,1,1,0,1,1,1,0,1,1}, NumberToPins(77144, 17) },
            },
            100);
}

}
