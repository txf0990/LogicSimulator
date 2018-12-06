#include "chip/mux.h"

#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "chip/basic_gates.h"
#include "chip/chip_test_util.h"

namespace {

using pin_board::PinBoard;
using pin_board::PinIndex;
using chip::Mux;
using std::pair;
using std::vector;

void GenerateAndTest(int digit) {
    PinBoard board(digit * 10, 1 + 2 * digit, digit);
    Mux::CreateChip(board, GetVectorPart(1, digit), GetVectorPart(digit + 1, digit), 0, GetVectorPart(2 * digit + 1, digit));
    vector<pair<vector<bool>, vector<bool>>> test_cases;
    vector<int> s = {1, digit, digit};      // input sizes: select_pin, input1, input2.
    for(int select = 0; select <= 1; select++) {
        for(int n1 = 0; n1 < (1 << digit); n1++) {
            for(int n2 = 0; n2 < (1 << digit); n2++) {
                if (select == 0) {
                    test_cases.push_back({GeneratePins({select, n1, n2}, s), NumberToPins(n2,digit)});
                } else {
                    test_cases.push_back({GeneratePins({select, n1, n2}, s), NumberToPins(n1,digit)});
                }
            }
        }
    }
    TestChipLogic(board, test_cases, 20);
} 

TEST(MuxTest, Mux_2_input_1_digit) {
    int digit = 1;
    GenerateAndTest(digit);
}

TEST(MuxTest, Mux_2_input_2_digit) {
    int digit = 2;
    GenerateAndTest(digit);
}

TEST(MuxTest, Mux_2_input_4_digit) {
    int digit = 4;
    GenerateAndTest(digit);
}

TEST(MuxTest, Mux_2_input_8_digit) {
    int digit = 8;
    GenerateAndTest(digit);
}


}   // namespace
