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

bool TestChipLogic(
        PinBoard& board,
        const std::vector<
            std::pair<
                std::vector<bool>,
                std::vector<bool>
            >
        >& input_output,
        int latency) {
    vector<bool> cal_output(input_output[0].second.size());
    for(int i = 0; i < input_output.size(); i++) {
        for(int j = 0; j < latency; j++) {
            board.SetInput(input_output[i].first);
            board.Tick();
        }
        board.GetOutput(cal_output);
        for(int j = 0; j < input_output[i].second.size(); j++) {
            EXPECT_EQ(input_output[i].second[j], cal_output[j])
                << "expected_output[" << i << "][" << j << "] "
                << "!= cal_output[" << j << "]";
        }
    }
    return true;
}

vector<bool> NumberToPins(int n, int size) {
    vector<bool> result;
    for(int i = 0; i < size; i++) {
        result.push_back(n & (1 << i));
    }
    return result;
}
