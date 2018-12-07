#include <cassert>
#include "basic_gates.h"
#include "logic_cal.h"
#include "chip_test_util.h"

namespace chip {
void BitNot::CreateChip(
        pin_board::PinBoard& mother,
        const std::vector<PinIndex>& input_pins,
        const std::vector<PinIndex>& output_pins
        ) {
    assert(input_pins.size() == output_pins.size());
    for(int i = 0; i < input_pins.size(); i++) {
        NotGate::CreateChip(mother, {input_pins[i]}, {output_pins[i]});
    }

}

void BitAnd::CreateChip(
        pin_board::PinBoard& mother,
        const std::vector<PinIndex>& input1_pins,
        const std::vector<PinIndex>& input2_pins,
        const std::vector<PinIndex>& output_pins) {
    assert(input1_pins.size() == input2_pins.size());
    assert(input1_pins.size() == output_pins.size());
    for(int i = 0; i < input1_pins.size(); i++) {
        AndGate::CreateChip(mother, {input1_pins[i], input2_pins[i]}, {output_pins[i]});
    }
}





}   // namespace chip
