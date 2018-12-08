#include "chip/logic_cal.h"

#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "chip/basic_gates.h"
#include "chip/chip_test_util.h"

namespace {

using pin_board::PinBoard;
using pin_board::PinIndex;
using chip::BitNot;
using chip::BitwiseChip;
using std::pair;
using std::vector;

using std::cout;
using std::endl;
using std::ostream;

vector<bool> GenerateTwoNums(int x, int y, int digit) {
    vector<bool> result;
    for(int i = 0; i < digit; i++) {
        result.push_back(static_cast<bool>(x & (1 << i)));
    }
    for(int i = 0; i < digit; i++) {
        result.push_back(static_cast<bool>(y & (1 << i)));
    }
    return result;
}

TEST(BitwiseChipTest, BitNot) {
    PinBoard board(20, 8, 8);
    BitNot::CreateChip(
            board,
            GetVectorPart(board.input_offset, 8),
            GetVectorPart(board.output_offset, 8));
    vector<pair<vector<bool>, vector<bool>>> test_cases;
    for(int i = 0; i < (1 << 8); i++) {
        test_cases.push_back({NumberToPins(i, 8), NumberToPins(~i, 8)});
    }
    TestChipLogic(board, test_cases, 20);
}

TEST(BitwiseChipTest, BitAnd) {
    PinBoard board(100, 8, 4);
    BitwiseChip<chip::AndGate>::CreateChip(
            board,
            GetVectorPart(board.input_offset, 4),
            GetVectorPart(board.input_offset + 4, 4),
            GetVectorPart(board.output_offset, 4));
    vector<pair<vector<bool>, vector<bool>>> test_cases;
    for(int i = 0; i < (1 << 4); i++) {
        for(int j = 0; j < (1 << 4); j++) {
            test_cases.push_back({GenerateTwoNums(i, j, 4), NumberToPins(i & j, 4)});
        }
    }
    TestChipLogic(board, test_cases, 100);
}

TEST(BitwiseChipTest, BitOr) {
    PinBoard board(100, 8, 4);
    BitwiseChip<chip::OrGate>::CreateChip(
            board,
            GetVectorPart(board.input_offset, 4),
            GetVectorPart(board.input_offset + 4, 4),
            GetVectorPart(board.output_offset, 4));
    vector<pair<vector<bool>, vector<bool>>> test_cases;
    for(int i = 0; i < (1 << 4); i++) {
        for(int j = 0; j < (1 << 4); j++) {
            test_cases.push_back({GenerateTwoNums(i, j, 4), NumberToPins(i | j, 4)});
        }
    }
    TestChipLogic(board, test_cases, 100);
}

TEST(BitwiseChipTest, BitNor) {
    PinBoard board(100, 8, 4);
    BitwiseChip<chip::NorGate>::CreateChip(
            board,
            GetVectorPart(board.input_offset, 4),
            GetVectorPart(board.input_offset + 4, 4),
            GetVectorPart(board.output_offset, 4));
    vector<pair<vector<bool>, vector<bool>>> test_cases;
    for(int i = 0; i < (1 << 4); i++) {
        for(int j = 0; j < (1 << 4); j++) {
            test_cases.push_back({GenerateTwoNums(i, j, 4), NumberToPins(~(i | j), 4)});
        }
    }
    TestChipLogic(board, test_cases, 100);
}

TEST(BitwiseChipTest, BitXor) {
    PinBoard board(100, 8, 4);
    BitwiseChip<chip::XorGate>::CreateChip(
            board,
            GetVectorPart(board.input_offset, 4),
            GetVectorPart(board.input_offset + 4, 4),
            GetVectorPart(board.output_offset, 4));
    vector<pair<vector<bool>, vector<bool>>> test_cases;
    for(int i = 0; i < (1 << 4); i++) {
        for(int j = 0; j < (1 << 4); j++) {
            test_cases.push_back({GenerateTwoNums(i, j, 4), NumberToPins(i ^ j, 4)});
        }
    }
    TestChipLogic(board, test_cases, 100);
}

}   // namespace
