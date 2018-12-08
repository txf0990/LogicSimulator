#include <iostream>

#include "gtest/gtest.h"
#include "chip/chip_test_util.h"
#include "pin_board/pin_board.h"

using pin_board::PinIndex;
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

void AppendPinsByNumber(vector<bool>& array, int number, int size) {
    for(int i = 0; i < size; i++) {
        array.push_back(static_cast<bool>(number & (1 << i)));
    }
}

vector<bool> NumberToPins(int number, int size) {
    vector<bool> result;
    AppendPinsByNumber(result, number, size);
    return result;
}

vector<bool> GeneratePins(vector<int>nums, vector<int>sizes) {
    vector<bool> result;
    assert(nums.size() == sizes.size());
    for (int i = 0; i < nums.size(); i++) {
        AppendPinsByNumber(result, nums[i], sizes[i]);
    }
    return result;
}

vector<PinIndex> GetVectorPart (int begin, int length, const vector<PinIndex>& v) {
    vector<PinIndex> result;
    if (!v.empty()) {
        for(int i = begin; i < begin + length; i++) {
            result.push_back(v[i]);
        }
    } else {
        for(int i = begin; i < begin + length; i++) {
            result.push_back(i);
        }
    }
    return result;
};

