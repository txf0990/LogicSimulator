#include <cassert>
#include "basic_gates.h"
#include "logic_cal.h"
#include "chip_test_util.h"

namespace chip {

using pin_board::PinIndex;

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

}   // namespace chip
