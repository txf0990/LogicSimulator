#ifndef CHIP_ADDER_H
#define CHIP_ADDER_H

#include <vector>

#include "chip/chip.h"
#include "pin_board/pin_board.h"

namespace chip {

class Adder_2 : virtual public Chip {
public:
    static void CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<pin_board::PinIndex>& input1_pins,
            const std::vector<pin_board::PinIndex>& input2_pins,
            const pin_board::PinIndex carry_pin,
            const std::vector<pin_board::PinIndex>& output_pins);
};


}  // namespace chip

#endif  // CHIP_ADDER_H
