#ifndef CHIP_CHIPTESTUTIL_H
#define CHIP_CHIPTESTUTIL_H

#include <vector>
#include "chip/chip.h"
#include "pin_board/pin_board.h"

bool TestChipLogic(
        pin_board::PinBoard& board,
        const std::vector<std::vector<bool>>& input,
        const std::vector<std::vector<bool>>& output,
        int latency = 10);

#endif // CHIP_CHIPTESTUTIL_H
