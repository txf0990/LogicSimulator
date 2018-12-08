#include "chip/adder.h"

#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "chip/basic_gates.h"
#include "chip/chip_test_util.h"

namespace {

using pin_board::PinBoard;
using pin_board::PinIndex;
using chip::Adder_2;
using std::pair;
using std::vector;

void GenerateAndTest(int digit) {
    PinBoard board(digit * 20, 1 + 2 * digit, digit + 1);
    Adder_2::CreateChip(
        board,
        GetVectorPart(board.input_offset + 1, digit),
        GetVectorPart(board.input_offset + digit + 1, digit),
        board.input_offset,
        GetVectorPart(board.output_offset, digit + 1));
    vector<pair<vector<bool>, vector<bool>>> test_cases;
    vector<int> s = {1, digit, digit};      // input sizes: select_pin, input1, input2.
    for(int carry = 0; carry <= 1; carry++) {
        for(int n1 = 0; n1 < (1 << digit); n1++) {
            for(int n2 = 0; n2 < (1 << digit); n2++) {
                test_cases.push_back({
                    GeneratePins({ carry, n1, n2 }, s),
                    NumberToPins(carry + n1 + n2, digit + 1)
                });
            }
        }
    }
    TestChipLogic(board, test_cases, 20);
} 

TEST(AdderTest, Adder_2_input_1_digit_carry) {
    int digit = 1;
    GenerateAndTest(digit);
}

TEST(AdderTest, Adder_2_input_2_digit_carry) {
    int digit = 2;
    GenerateAndTest(digit);
}

TEST(AdderTest, Adder_2_input_4_digit_carry) {
    int digit = 4;
    GenerateAndTest(digit);
}

/*
TEST(AdderTest, Adder_2_input_8_digit_carry) {
    int digit = 8;
    GenerateAndTest(digit);
}
*/

TEST(AdderTest, Adder_2_input_16_digit_carry) {
    PinBoard board(320, 33, 17);
    Adder_2::CreateChip(
        board,
        GetVectorPart(board.input_offset + 1, 16),
        GetVectorPart(board.input_offset + 17,16),
        board.input_offset,
        GetVectorPart(board.output_offset, 17));
    vector<int> s = {1, 16, 16}; // input sizes
    TestChipLogic(
            board,
            {
                { GeneratePins({1, 65535, 65535}, s), NumberToPins(131071,17) },
                { GeneratePins({0, 65535, 65535}, s), NumberToPins(131070,17) },
                { GeneratePins({1, 0, 65535}, s), NumberToPins(65536,17) },
                { GeneratePins({0, 65535, 0}, s), NumberToPins(65535,17) },
                { GeneratePins({1, 56939, 12035}, s), NumberToPins(68975,17) },
                { GeneratePins({1, 47803, 59648}, s), NumberToPins(107452,17) },
            },
            100);
}

}
