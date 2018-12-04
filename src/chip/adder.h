#ifndef CHIP_ADDER_H
#define CHIP_ADDER_H

#include <vector>

#include "chip/chip.h"
#include "pin_board/pin_board.h"
#include "chip/basic_gates.h"

namespace chip {

class Adder : virtual public Chip {
public:
    static void CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins);
};

class Adder_2 : virtual public Chip {
public:
    static void CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input1_pins, const std::vector<PinIndex>& input2_pins, const std::vector<PinIndex>& output_pins);
};


}  // namespace chip

#endif  // CHIP_ADDER_H
