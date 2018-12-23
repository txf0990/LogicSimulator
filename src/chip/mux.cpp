#include <cassert>
#include "basic_gates.h"
#include "mux.h"
#include "chip_test_util.h"

namespace chip {

using pin_board::PinIndex;

void Mux::CreateChip(
        pin_board::PinBoard& board,
        const std::vector<PinIndex>& input0_pins,
        const std::vector<PinIndex>& input1_pins,
        const PinIndex select_pin,
        const std::vector<PinIndex>& output_pins) {

    assert(input0_pins.size() == input1_pins.size());
    assert(input0_pins.size() == output_pins.size());
    if (input0_pins.size() == 1) {
        PinIndex And1_o = board.AllocatePin();
        PinIndex And2_o = board.AllocatePin();
        PinIndex Not_o = board.AllocatePin();

        AndGate::CreateChip(board, {input1_pins[0], select_pin}, {And1_o});
        NotGate::CreateChip(board, {select_pin}, {Not_o});
        AndGate::CreateChip(board, {input0_pins[0], Not_o}, {And2_o});
        OrGate::CreateChip(board, {And1_o, And2_o}, {output_pins[0]});
    } else {
        for(int i = 0; i < input1_pins.size(); i++) {
            Mux::CreateChip(board, {input0_pins[i]}, {input1_pins[i]}, select_pin, {output_pins[i]});
        }
    }
}

}   // namespace chip
