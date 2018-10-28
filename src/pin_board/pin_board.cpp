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
    // the n/64 th number.
    // the n%64 th digit from the left. (starting from 0)
    // & (1 << (63 - (n%64)))
    return current_status[n/64] & (1 << (63 - (n % 64)));
}

void PinBoard::SetPin(PinIndex n, bool result) {
    // Compiler error!
    // next_status[n/64] & (1 << (63 - (n % 64))) = result;
}

} // namespace pin_board
