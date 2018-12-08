#include "chip/alu/alu.h"

#include "pin_board/pin_board.h"

namespace chip {

using pin_board::PinIndex;

static void CreateChip(
    pin_board::PinBoard& mother,
    const std::vector<PinIndex>& input1_pins,
    const std::vector<PinIndex>& input2_pins,
    const std::vector<PinIndex>& shamt,
    const std::vector<PinIndex>& func,
    const std::vector<PinIndex>& output_pins) {
}

}  // namespace chip
