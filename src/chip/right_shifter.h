#ifndef CHIP_RIGHT_SHIFTER_H
#define CHIP_RIGHT_SHIFTER_H

#include <vector>

#include "chip/chip.h"
#include "pin_board/pin_board.h"
#include "chip/basic_gates.h"

namespace chip {

class RightShifter32 : virtual public Chip {
public:
    static void CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<PinIndex>& input_pins,
            std::vector<PinIndex> shamt,
            PinIndex complement,
            const std::vector<PinIndex>& output_pins);
};

class RightShifter : virtual public Chip {
public:
    static void CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<PinIndex>& input_pins,
            int shift_num,
            PinIndex if_shift,
            PinIndex complement,
            const std::vector<PinIndex>& output_pins);    // select_pin=1: select shifted. select_pin=0: select origin
};

}   // namespace chip



#endif  // CHIP_RIGHT_SHIFTER_H
