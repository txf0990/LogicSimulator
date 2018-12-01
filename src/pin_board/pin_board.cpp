#include "pin_board/pin_board.h"

#include <iostream>

using std::vector;

namespace pin_board {

PinBoard::PinBoard(PinIndex n, PinIndex x, PinIndex y)
    : current_status((n + 63) / 64),
      next_status((n + 63) / 64), input_num(x), output_num(y), allocated_pin(x + y){
      }

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

PinIndex PinBoard::AllocatePin() {
    allocated_pin++;
    return allocated_pin - 1;
}

void PinBoard::PlugChip(std::unique_ptr<chip::Chip> p) {
    p->SetMother(this);
    chips.push_back(std::move(p));
}

} // namespace pin_board
