#ifndef CHIP_LEFT_SHIFTER_H
#define CHIP_LEFT_SHIFTER_H

#include <vector>

#include "chip/chip.h"
#include "pin_board/pin_board.h"
#include "chip/basic_gates.h"

namespace chip {

class LeftShifter : virtual public Chip {
public:
    static void CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<PinIndex>& input_pins,
            const std::vector<PinIndex>& output_pins,
            vector<PinIndex> diff_bit,
            vector<PinIndex> if_shift);
};

class LeftShifterBit : virtual public Chip {
public:
    static void CreateChip(
            pin_board::PinBoard& mother,
            const std::vector<PinIndex>& input_pins,
            const std::vector<PinIndex>& output_pins,
            int diff_bit,
            vector<PinIndex> if_shift);
};

}   // namespace chip



#endif  // CHIP_LEFT_SHIFTER_H
