#include "pin_board/pin_board.h"

#include <cassert>
#include <iostream>

using std::vector;

namespace pin_board {

PinBoard::PinBoard(PinIndex n, PinIndex x, PinIndex y)
    : input_offset(0),
      output_offset(x),
      free_pin_offset(x + y),
      current_status((n + 2 + 63) / 64),
      next_status((n + 2 + 63) / 64),
      input_num(x), output_num(y),
      total_pin_num(n + 2),
      allocated_pin(x + y){
      }

void PinBoard::Tick() {
    SetPin(GetZeroPin(), false);
    SetPin(GetOnePin(), true);
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

void PinBoard::SetCurrentPin(PinIndex n, bool result) {
    if (result) {
        current_status[n/64] |= (static_cast<int64_t>(1) << (n % 64));
    } else {
        current_status[n/64] &= ~(static_cast<int64_t>(1) << (n % 64));
    }
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
    assert(allocated_pin < total_pin_num - 2);
    return allocated_pin - 1;
}

void PinBoard::PlugChip(std::unique_ptr<chip::Chip> p) {
    p->SetMother(this);
    chips.push_back(std::move(p));
}

void PinBoard::SetInput(const vector<bool>& input, int offset) {
    for(int i = 0; i < input.size(); i++) {
        SetPin(input_offset + offset + i, input[i]);
    }
}
void PinBoard::GetOutput(vector<bool>& output, int offset) {
    for(int i = 0; i < output.size(); i++) {
        output[i] = GetPin(output_offset + offset + i);
    }
}
} // namespace pin_board
