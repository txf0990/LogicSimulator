#ifndef CHIP_LOGIC_CAL_H
#define CHIP_LOGIC_CAL_H

#include <cassert>
#include <vector>

#include "chip/chip.h"
#include "pin_board/pin_board.h"
#include "chip/basic_gates.h"

namespace chip {

class BitNot : virtual public Chip {
public:
    static void CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<PinIndex>& input_pins,
            const std::vector<PinIndex>& output_pins
            );
};

template<typename ChipType> class BitwiseChip {
public:
    static void CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<PinIndex>& input1_pins,
            const std::vector<PinIndex>& input2_pins,
            const std::vector<PinIndex>& output_pins) {
        assert(input1_pins.size() == input2_pins.size());
        assert(input1_pins.size() == output_pins.size());
        for(int i = 0; i < input1_pins.size(); i++) {
            ChipType::CreateChip(mother, {input1_pins[i], input2_pins[i]}, {output_pins[i]});
        }
    }
};

}   // namespace chip



#endif  // CHIP_LOGIC_CAL_H
