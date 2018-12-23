#include "pin_board/pin_board.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

using std::vector;
using std::string;

namespace pin_board {

PinBoard::PinBoard(PinIndex n, PinIndex x, PinIndex y)
    : input_offset(2),
      output_offset(2 + x),
      free_pin_offset(2 + x + y),
      current_status((2 + n + 63) / 64),
      next_status((2 + n + 63) / 64),
      input_num(x), output_num(y),
      total_pin_num(n + 2),
      allocated_pin(2 + x + y){
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

void PinBoard::EntitlePins(string name, vector<PinIndex> pins) {
  auto result = named_pins.insert(
      std::pair<const string, vector<PinIndex>>(name, pins));
  // Not overwriting an existing name
  assert(result.second);
}

PinIndex PinBoard::AllocatePin(string name) {
  if (!name.empty()) {
    EntitlePins(name, {allocated_pin});
  }
  allocated_pin++;
  assert(allocated_pin < total_pin_num);
  return allocated_pin - 1;
}

std::vector<PinIndex> PinBoard::AllocatePins(size_t size, string name) {
  assert(allocated_pin + size < total_pin_num);
  std::vector<PinIndex> result;
  for (size_t i = 0; i < size; i++) {
    result.push_back(allocated_pin);
    ++allocated_pin;
  }
  if (!name.empty()) {
    EntitlePins(name, result);
  }
  return result;
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

string PinBoard::NamedPinsStatus() {
  std::ostringstream oss;
  long long num;
  long long bit;
  for (const auto& p : named_pins) {
    oss << p.first << ": {";
    num = 0;
    bit = 1;
    for (size_t i = 0; i < p.second.size(); i++) {
      int v = GetPin(p.second[i]) ? 1 : 0;
      num |= bit * v;
      bit <<= 1;
      oss << v;
    }
    oss << "(" << num << ")}\n";
  }
  return oss.str();
}

} // namespace pin_board
