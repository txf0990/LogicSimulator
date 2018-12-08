#include "chip/right_shifter.h"

#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "chip/basic_gates.h"
#include "chip/chip_test_util.h"

namespace {

using pin_board::PinBoard;
using pin_board::PinIndex;
using chip::RightShifter32;
using std::pair;
using std::vector;

TEST(RightShifterTest, right_shifter_1_input_5_flag_comp0) {
  PinBoard board(900, 38, 32);
  RightShifter32::CreateChip(
      board,
      GetVectorPart(board.input_offset, 32),
      GetVectorPart(board.input_offset + 32, 5),
      board.input_offset + 37,
      GetVectorPart(board.output_offset, 32));
  vector<pair<vector<bool>, vector<bool>>> test_cases = {
    {GeneratePins({5, 2, 0}, {32, 5, 1}), NumberToPins(1, 32)},
    {GeneratePins({19, 7, 0}, {32, 5, 1}), NumberToPins(0, 32)},
    {GeneratePins({65324, 15, 0}, {32, 5, 1}), NumberToPins(1, 32)},
    {GeneratePins({28, 30, 0}, {32, 5, 1}), NumberToPins(0, 32)},
  };
  TestChipLogic(board, test_cases, 100);
}

TEST(RightShifterTest, right_shifter_1_input_5_flag_comp1) {
  PinBoard board(900, 38, 32);
  RightShifter32::CreateChip(
      board,
      GetVectorPart(board.input_offset, 32),
      GetVectorPart(board.input_offset + 32, 5),
      board.input_offset + 37,
      GetVectorPart(board.output_offset, 32));
  const unsigned int all_one = ~0u;

  vector<pair<vector<bool>, vector<bool>>> test_cases = {
    {GeneratePins({5, 2, 1}, {32, 5, 1}), NumberToPins((5 >> 2) | (all_one << 30), 32)},
    {GeneratePins({19, 7, 1}, {32, 5, 1}), NumberToPins((19 >> 7) | (all_one << 25), 32)},
    {GeneratePins({65324, 15, 1}, {32, 5, 1}), NumberToPins(1 | (all_one << 17), 32)},
    {GeneratePins({28, 30, 1}, {32, 5, 1}), NumberToPins(all_one << 2, 32)},
    {GeneratePins({99573, 6, 1}, {32, 5, 1}), NumberToPins((99573 >> 6) | (all_one << 26), 32)},
  };
  TestChipLogic(board, test_cases, 100);
}

} // namespace
