#include "chip/left_shifter.h"

#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "chip/basic_gates.h"
#include "chip/chip_test_util.h"

namespace {

using pin_board::PinBoard;
using pin_board::PinIndex;
using chip::LeftShifter32;
using std::pair;
using std::vector;

TEST(LeftShifterTest, left_shifter_1_input_5_flag) {
  PinBoard mother(900, 37, 32);
  LeftShifter32::CreateChip(
      mother,
      GetVectorPart(0,32),
      GetVectorPart(32,5),
      GetVectorPart(37,32));
  vector<pair<vector<bool>, vector<bool>>> test_cases = {
    {GeneratePins({5,2},{32,5}),NumberToPins(20,32)},
    {GeneratePins({19,7},{32,5}),NumberToPins(2432,32)},
    {GeneratePins({65324,15},{32,5}),NumberToPins(2140536832,32)},
    {GeneratePins({28,30},{32,5}),NumberToPins(0,32)},
  };
  TestChipLogic(mother, test_cases, 100);
}


} // namespace
