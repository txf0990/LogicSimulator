#include "pin_board/pin_board.h"

using std::vector;

namespace pin_board {

PinBoard::PinBoard(PinIndex n) {
    vector<int64_t> current_status(n);
    vector<int64_t> next_status(n);
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
        current_status[n/64] |= (static_cast<int64_t>(1) << (n % 64));
    } else {
        current_status[n/64] &= ~(static_cast<int64_t>(1) << (n % 64));
    }
}

} // namespace pin_board
