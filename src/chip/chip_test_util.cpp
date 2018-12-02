#include "gtest/gtest.h"
#include "chip/chip_test_util.h"
#include "pin_board/pin_board.h"

using pin_board::PinBoard;
using std::vector;

bool TestChipLogic(
        PinBoard& board,
        const vector<vector<bool>>& input,
        const vector<vector<bool>>& expected_output,
        int latency) {
    vector<bool> cal_output(expected_output[0].size());
    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < latency; j++) {
            board.SetInput(input[i]);
            board.Tick();
        }
        board.GetOutput(cal_output);
        for(int j = 0; j < expected_output[i].size(); j++) {
            EXPECT_EQ(expected_output[i][j], cal_output[j])
                << "expected_output[" << i << "][" << j << "] "
                << "!= cal_output[" << j << "]";
        }
    }
    return true;
}
