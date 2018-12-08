#ifndef ALU_ALU_H
#define ALU_ALU_H

#include "chip/chip.h"
#include "pin_board/pin.h"

#include <vector>

namespace chip {

class Alu : public Chip {
public:
    static void CreateChip(
        pin_board::PinBoard& mother,
        const std::vector<pin_board::PinIndex>& input1_pins,
        const std::vector<pin_board::PinIndex>& input2_pins,
        const std::vector<pin_board::PinIndex>& shamt,
        const std::vector<pin_board::PinIndex>& func,
        const std::vector<pin_board::PinIndex>& output_pins);
};

} // namespace chip

#endif // ALU_ALU_H
