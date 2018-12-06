#include <cassert>
#include "basic_gates.h"
#include "mux.h"
#include "chip_test_util.h"

namespace chip {
void Mux::CreateChip(
        pin_board::PinBoard& mother,
        const std::vector<PinIndex>& input1_pins,
        const std::vector<PinIndex>& input2_pins,
        const PinIndex select_pin,
        const std::vector<PinIndex>& output_pins) {

    assert(input1_pins.size() == input2_pins.size());
    if (input1_pins.size() == 1) {
        PinIndex And1_o = mother.AllocatePin();
        PinIndex And2_o = mother.AllocatePin();
        PinIndex Not_o = mother.AllocatePin();

        AndGate::CreateChip(mother, {input1_pins[0], select_pin}, {And1_o});
        NotGate::CreateChip(mother, {select_pin}, {Not_o});
        AndGate::CreateChip(mother, {input2_pins[0], Not_o}, {And2_o});
        OrGate::CreateChip(mother, {And1_o, And2_o}, {output_pins[0]});
    } else {
        for(int i = 0; i < input1_pins.size(); i++) {
            Mux::CreateChip(mother, {input1_pins[i]},{input2_pins[i]}, select_pin, {output_pins[i]});
        }
    }
}

}   // namespace chip
