#include "pin_board/pin_board.h"

#include <iostream>

using std::vector;

namespace pin_board {

PinBoard::PinBoard(PinIndex n)
    : current_status((n + 63) / 64),
      next_status((n + 63) / 64) {}

void PinBoard::Tick() {
    for(int i = 0; i < chips.size(); i++) {
        chips[i]->Tick();
    }
    current_status.swap(next_status);
}

bool PinBoard::GetPin(PinIndex n){
    // the n/64-th number in the vector.
    // the n%64-th bit of the number.
    return current_status[n/64] & (static_cast<int64_t>(1) << (n % 64));
}

void PinBoard::SetPin(PinIndex n, bool result) {
    if (result) {
        next_status[n/64] |= (static_cast<int64_t>(1) << (n % 64));
    } else {
        next_status[n/64] &= ~(static_cast<int64_t>(1) << (n % 64));
    }
}

void PinBoard::PlugChip(chip::Chip* p) {
    chips.push_back(p);
}

} // namespace pin_board
