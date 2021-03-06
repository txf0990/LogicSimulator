#ifndef CHIP_MUX_H
#define CHIP_MUX_H

#include <vector>

#include "chip/chip.h"
#include "pin_board/pin_board.h"
#include "chip/basic_gates.h"

namespace chip {

class Mux : virtual public Chip {
public:
    static void CreateChip(
            pin_board::PinBoard& board,
            const std::vector<pin_board::PinIndex>& input0_pins,
            const std::vector<pin_board::PinIndex>& input1_pins,
            const pin_board::PinIndex select_pin,
            const std::vector<pin_board::PinIndex>& output_pins);  // select_pin = 1: select second input; select_pin = 2: select first input;
};


}   // namespace chip



#endif  // CHIP_MUX_H
