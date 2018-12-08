#include <cassert>
#include "mux.h"
#include "left_shifter.h"
#include "chip_test_util.h"

namespace chip {

using pin_board::PinIndex;

void LeftShifter32::CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<PinIndex>& input_pins,
            std::vector<PinIndex> shamt,
            const std::vector<PinIndex>& output_pins) {
  assert(shamt.size() == 5);
  assert(input_pins.size() == output_pins.size());
  assert(input_pins.size() == 32);
  std::vector<PinIndex> shift1(input_pins.size());
  std::vector<PinIndex> shift2(input_pins.size());
  std::vector<PinIndex> shift4(input_pins.size());
  std::vector<PinIndex> shift8(input_pins.size());
  for(int i = 0; i < input_pins.size(); i++) {
    shift1[i] = mother.AllocatePin();
    shift2[i] = mother.AllocatePin();
    shift4[i] = mother.AllocatePin();
    shift8[i] = mother.AllocatePin();
  }
  LeftShifter::CreateChip(mother, input_pins, 1, shamt[0], shift1);
  LeftShifter::CreateChip(mother, shift1, 2, shamt[1], shift2);
  LeftShifter::CreateChip(mother, shift2, 4, shamt[2], shift4);
  LeftShifter::CreateChip(mother, shift4, 8, shamt[3], shift8);
  LeftShifter::CreateChip(mother, shift8, 16, shamt[4], output_pins);
}

void LeftShifter::CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<PinIndex>& input_pins,
            int shift_num,
            PinIndex if_shift, 
            const std::vector<PinIndex>& output_pins) {
  assert(input_pins.size() == output_pins.size());
  assert(shift_num == 1 || shift_num == 2 || shift_num == 4 || shift_num == 8 || shift_num == 16);
  std::vector<PinIndex> shift(input_pins.size());
  for(int i = 0; i < shift_num; i++) {
    shift[i] = mother.GetZeroPin();
  }
  for(int i = shift_num; i < input_pins.size(); i++) {
    shift[i] = input_pins[i - shift_num];
  }
  Mux::CreateChip(mother, input_pins, shift, if_shift, output_pins);
}
} // namespace chip
