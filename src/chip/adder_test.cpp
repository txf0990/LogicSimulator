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
using std::pair;
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
    PinBoard board(20,3,2);
    Adder_2::CreateChip(board, {1}, {2}, 0, {3,4});
    vector<int> s = {1, 1, 1}; // input sizes

    TestChipLogic(
            board,
            {
                { GeneratePins({0, 0, 0}, s), NumberToPins(0,2) },
                { GeneratePins({0, 0, 1}, s), NumberToPins(1,2) },
                { GeneratePins({0, 1, 0}, s), NumberToPins(1,2) },
                { GeneratePins({1, 0, 0}, s), NumberToPins(1,2) },
                { GeneratePins({0, 1, 1}, s), NumberToPins(2,2) },
                { GeneratePins({1, 0, 1}, s), NumberToPins(2,2) },
                { GeneratePins({1, 1, 0}, s), NumberToPins(2,2) },
                { GeneratePins({1, 1, 1}, s), NumberToPins(3,2) },
            }
            );
}

TEST(AdderTest, Adder_2_input_2_digit_carry) {
    PinBoard board(40,5,3);
    Adder_2::CreateChip(board, {1,2}, {3,4}, 0, {5,6,7});
    vector<int> s = {1, 2, 2}; // input sizes

    vector<pair<vector<bool>, vector<bool>>> test_cases;

    for (int carry = 0; carry <= 1; carry++) {
      for (int n1 = 0; n1 <= 3; n1++) {
        for (int n2 = 0; n2 <= 3; n2++) {
          test_cases.push_back({
              GeneratePins({carry, n1, n2}, s),
              NumberToPins(carry + n1 + n2, 3)
          });
        }
      }
    }

    TestChipLogic(board, test_cases, 20);
}

TEST(AdderTest, Adder_2_input_4_digit_carry) {
    PinBoard board(80,9,5);
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
    PinBoard board(160,17,9);
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
    PinBoard board(320,33,17);
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
