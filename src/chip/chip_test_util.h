#ifndef CHIP_CHIPTESTUTIL_H
#define CHIP_CHIPTESTUTIL_H

#include <vector>
#include "chip/chip.h"
#include "pin_board/pin_board.h"

// Deprecated: DO NOT USE
bool TestChipLogic(
        pin_board::PinBoard& board,
        const std::vector<std::vector<bool>>& input,
        const std::vector<std::vector<bool>>& output,
        int latency = 10);

bool TestChipLogic(
        pin_board::PinBoard& board,
        const std::vector<
            std::pair<
                std::vector<bool>,
                std::vector<bool>
            >
        >& input_output,
        int latency = 10);

std::vector<bool> NumberToPins(int n, int size);

#endif // CHIP_CHIPTESTUTIL_H
