#include "chip/alu/alu.h"

#include "chip/logic_cal.h"
#include "chip/mux.h"
#include "pin_board/pin_board.h"

#include <cassert>

namespace chip {

using pin_board::PinBoard;
using pin_board::PinIndex;

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
}

void Alu::CalculateOutput(
    pin_board::PinBoard& board,
    AluInternalPins p) {
}

}  // namespace chip
