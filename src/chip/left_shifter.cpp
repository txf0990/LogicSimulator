#include <cassert>
#include "mux.h"
#include "left_shifter.h"
#include "chip_test_util.h"

namespace chip {
void LeftShifter32::CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<PinIndex>& input_pins,
            std::vector<PinIndex> shamt,
            const std::vector<PinIndex>& output_pins) {
  assert(shamt.size() == 5);
  assert(input_pins.size() == output_pins.size());
  std::vector<PinIndex> shft1(input_pins.size());
  std::vector<PinIndex> shft2(input_pins.size());
  std::vector<PinIndex> shft4(input_pins.size());
  std::vector<PinIndex> shft8(input_pins.size());
  for(int i = 0; i < input_pins.size(); i++) {
    shft1[i] = mother.AllocatePin();
    shft2[i] = mother.AllocatePin();
    shft4[i] = mother.AllocatePin();
    shft8[i] = mother.AllocatePin();
  }
  LeftShifter::CreateChip(mother, input_pins, 1, shamt[0], shft1);
  LeftShifter::CreateChip(mother, shft1, 2, shamt[1], shft2);
  LeftShifter::CreateChip(mother, shft2, 4, shamt[2], shft4);
  LeftShifter::CreateChip(mother, shft4, 8, shamt[3], shft8);
  LeftShifter::CreateChip(mother, shft8, 16, shamt[4], output_pins);
}

void LeftShifter::CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<PinIndex>& input_pins,
            int shift_num,
            PinIndex if_shift, 
            const std::vector<PinIndex>& output_pins) {
  assert(input_pins.size() == output_pins.size());
  assert(shift_num == 1 || shift_num == 2 || shift_num == 4 || shift_num == 8 || shift_num == 16);
  std::vector<PinIndex> shft(input_pins.size());
  for(int i = 0; i < shift_num; i++) {
    shft[i] = mother.GetZeroPin();
  }
  for(int i = shift_num; i < input_pins.size(); i++) {
    shft[i] = input_pins[i - shift_num];
  }
  Mux::CreateChip(mother, shft, input_pins, if_shift, output_pins);
}
} // namespace chip
