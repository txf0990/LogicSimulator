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
                {false, true},
                {false, true},
                {true, false},
            });
}

TEST(AdderTest, ThreeInput) {
    PinBoard board(10,3,2);
    Adder::CreateChip(board, {0,1,2}, {3,4});
    TestChipLogic(
            board,
            {
                {false, false, false},
                {false, false, true},
                {false, true, false},
                {true, false, false},
                {false, true, true},
                {true, false, true},
                {true, true, false},
                {true, true, true},
            },
            {
                {false, false},
                {false, true},
                {false, true},
                {false, true},
                {true, false},
                {true, false},
                {true, false},
                {true, true},
            });
}

TEST(Adder_2Test, Simple) {
    PinBoard board(20,4,3);
    Adder_2::CreateChip(board, {0,1,2,3}, {4,5,6});
    TestChipLogic(
            board,
            {
                {false, false, false, false},
                {false, false, false, true},
                {false, false, true, false},
                {false, false, true, true},
                {false, true, false, false},
                {false, true, false, true},
                {false, true, true, false},
                {false, true, true, true},
                {true, false, false, false},
                {true, false, false, true},
                {true, false, true, false},
                {true, false, true, true},
                {true, true, false, false},
                {true, true, false, true},
                {true, true, true, false},
                {true, true, true, true},
            },
            {
                {false, false, false},
                {false, false, true},
                {false, true, false},
                {false, true, true},
                {false, false, true},
                {false, true, false},
                {false, true, true},
                {true, false, false},
                {false, true, false},
                {false, true, true},
                {true, false, false},
                {true, false, true},
                {false, true, true},
                {true, false, false},
                {true, false, true},
                {true, true, false},
            },
            20);
}
}
