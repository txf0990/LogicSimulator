#include <cassert>
#include "basic_gates.h"
#include "left_shifter.h"
#include "chip_test_util.h"

namespace chip {
void LeftShifter::CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<PinIndex>& input_pins,
            const std::vector<PinIndex>& output_pins,
            vector<PinIndex> diff_bit,
            vector<PinIndex> if_shift) {
  assert(diff_bit.size() == 5);
  assert(if_shift.size() == 1);
  assert(input_pins.size() == output.pins.size());
  
  chip



}

void LeftShifterBit::CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<PinIndex>& input_pins,
            const std::vector<PinIndex>& output_pins,
            int diff_bit) {
  assert(input_pins.size() * 2 == output_pins.size());
  assert(diff_bit == 1 || diff_bit == 2 || diff_bit == 4 || diff_bit == 8);
  for(int i = 0; i < input_pins.size(); i++) {
    output_pins[i] = input_pins[i];
  }
  for(int i = input_pins.size(); i < output_pins.size() - diff_bit; i++) {
    output_pins[i] = input_pins[i - input_pins.size];
  }
  for(int i = output_pins.size() - diff_bit; i < output_pins.size(); i++) {
    output_pins[i] = 0;
  }
}
} // namespace chip
