#include "chip/alu/alu.h"

#include "chip/adder.h"
#include "chip/left_shifter.h"
#include "chip/logic_cal.h"
#include "chip/mux.h"
#include "pin_board/pin_board.h"
#include "chip/right_shifter.h"

#include <cassert>

#include <iostream>

namespace chip {

using pin_board::PinBoard;
using pin_board::PinIndex;
using std::vector;

void Alu::CreateChip(
    pin_board::PinBoard& board,
    const std::vector<PinIndex>& input1_pins,
    const std::vector<PinIndex>& input2_pins,
    const std::vector<PinIndex>& shamt,
    const std::vector<PinIndex>& func,
    const std::vector<PinIndex>& output_pins) {

  assert(input1_pins.size() == 32);
  assert(input2_pins.size() == 32);
  assert(shamt.size() == 5);
  assert(func.size() == 4);
  assert(output_pins.size() == 32);

  AluInternalPins p;
  // Setup Input and Output
  p.a = input1_pins;
  p.b = input2_pins;
  p.shamt = shamt;
  p.func = func;
  p.output = output_pins;

  Alu::AllocatePins(board, p);
}

void Alu::AllocatePins(PinBoard& board, AluInternalPins& p) {
  // Allocate pins for alu
  p.add_minus_output = board.AllocatePins(32);
  p.bitwise_output = board.AllocatePins(32);
  p.shift_output = board.AllocatePins(32);
  p.shift_replace = board.AllocatePin();
  p.shift_replace_value = board.AllocatePin();
  p.shift_pre_output = board.AllocatePins(32);
  p.shift_num = board.AllocatePins(32);
}

void Alu::CalculateAddMinus(
    pin_board::PinBoard& board,
    AluInternalPins p) {
  auto xor_output = board.AllocatePins(32);
  std::vector<PinIndex> f1_32(32, p.func[1]);
  BitwiseChip<XorGate>::CreateChip(board, p.b, f1_32, xor_output);
  auto adder_output = p.add_minus_output;
  adder_output.push_back(board.AllocatePin());
  chip::Adder_2::CreateChip(board, p.a, xor_output, p.func[1], adder_output);
}

void Alu::CalculateBitwise(
    pin_board::PinBoard& board,
    AluInternalPins p) {
  auto and_or_output = board.AllocatePins(32);
  auto and_output = board.AllocatePins(32);
  auto or_output = board.AllocatePins(32);
  Mux::CreateChip(board, and_output, or_output, p.func[0], and_or_output);
  BitwiseChip<AndGate>::CreateChip(board, p.a, p.b, and_output);
  BitwiseChip<OrGate>::CreateChip(board, p.a, p.b, or_output);

  auto xor_nor_output = board.AllocatePins(32);
  auto xor_output = board.AllocatePins(32);
  auto nor_output = board.AllocatePins(32);
  Mux::CreateChip(board, xor_output, nor_output, p.func[0], xor_nor_output);
  BitwiseChip<XorGate>::CreateChip(board, p.a, p.b, xor_output);
  BitwiseChip<NorGate>::CreateChip(board, p.a, p.b, nor_output);

  Mux::CreateChip(board, and_or_output, xor_nor_output, p.func[1], p.bitwise_output);
}

void Alu::CalculateShift(
    pin_board::PinBoard& board,
    AluInternalPins p) {
  vector<PinIndex> shift_5_bit = board.AllocatePins(5);
  Mux::CreateChip(board, p.shamt, {p.a[0],p.a[1],p.a[2],p.a[3],p.a[4]}, p.func[2], shift_5_bit);
  PinIndex shift_complement_value = board.AllocatePin();
  AndGate::CreateChip(board, {p.func[0], p.b[31]}, {shift_complement_value});
  vector<PinIndex> left_shifter_result_32_bit = board.AllocatePins(32);
  vector<PinIndex> right_shifter_result_32_bit = board.AllocatePins(32);
  chip::LeftShifter32::CreateChip(
      board,
      p.b,
      shift_5_bit,
      left_shifter_result_32_bit);
  chip::RightShifter32::CreateChip(
      board,
      p.b,
      shift_5_bit,
      shift_complement_value,
      right_shifter_result_32_bit);  
  Mux::CreateChip(
      board,
      left_shifter_result_32_bit,
      right_shifter_result_32_bit,
      p.func[1],
      p.shift_output);
}

void Alu::CalculateOutput(
    pin_board::PinBoard& board,
    AluInternalPins p) {
  }
}  // namespace chip
