#include <cassert>
#include "mux.h"
#include "right_shifter.h"
#include "chip_test_util.h"

namespace chip {
void RightShifter32::CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<PinIndex>& input_pins,
            std::vector<PinIndex> shamt,
            PinIndex complement,
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
  RightShifter::CreateChip(mother, input_pins, 1, shamt[0], complement, shift1);
  RightShifter::CreateChip(mother, shift1, 2, shamt[1], complement, shift2);
  RightShifter::CreateChip(mother, shift2, 4, shamt[2], complement, shift4);
  RightShifter::CreateChip(mother, shift4, 8, shamt[3], complement, shift8);
  RightShifter::CreateChip(mother, shift8, 16, shamt[4], complement, output_pins);
}

void RightShifter::CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<PinIndex>& input_pins,
            int shift_num,
            PinIndex if_shift, 
            PinIndex complement,
            const std::vector<PinIndex>& output_pins) {
  assert(input_pins.size() == output_pins.size());
  assert(shift_num == 1 || shift_num == 2 || shift_num == 4 || shift_num == 8 || shift_num == 16);
  std::vector<PinIndex> shifted_result(input_pins.size());

  for(int i = 0; i < shift_num; i++) {
    shifted_result[input_pins.size() - 1 - i] = complement;
  }
  for(int i = 0; i < input_pins.size() - shift_num; i++) {
    shifted_result[i] = input_pins[i + shift_num];
  }
  Mux::CreateChip(mother, shifted_result, input_pins, if_shift, output_pins);
}

} // namespace chip
