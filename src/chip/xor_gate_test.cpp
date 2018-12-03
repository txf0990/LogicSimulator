#include "gtest/gtest.h"
#include "chip/basic_gates.h"
#include "chip/chip_test_util.h"

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
using std::vector;

TEST(NANDGateTest, Simple) {
    PinBoard board(10,2,1);
    PinIndex i = board.AllocatePin();
    AndGate::CreateChip(board, {0,1},{i});
    NotGate::CreateChip(board, {i}, {2});
    TestChipLogic(
            board,
            {
                {false, false},
                {false, true},
                {true, false},
                {true, true},
            },
            {
                {true},
                {true},
                {true},
                {false},
            });
}

TEST(XorGateTest, Simple) {
    PinBoard board(10,2,1);
    PinIndex AND_o = board.AllocatePin();
    PinIndex OR_o = board.AllocatePin();
    PinIndex NOT_o = board.AllocatePin();
    AndGate::CreateChip(board, {0,1},{AND_o});
    OrGate::CreateChip(board, {0,1},{OR_o});
    NotGate::CreateChip(board, {AND_o}, {NOT_o});
    AndGate::CreateChip(board, {NOT_o, OR_o}, {2});
    TestChipLogic(
            board,
            {
                {false, false},
                {false, true},
                {true, false},
                {true, true},
            },
            {
                {false},
                {true},
                {true},
                {false},
            });
}

}
