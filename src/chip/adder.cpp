#include <cassert>
#include "basic_gates.h"
#include "adder.h"

namespace chip {

void Adder::CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins) {
    assert(input_pins.size() == 2 || input_pins.size() == 3);
    if (input_pins.size() == 2) {
        assert(output_pins.size() == 2);
        AndGate::CreateChip(mother, input_pins, {output_pins[0]});
        XorGate::CreateChip(mother, input_pins, {output_pins[1]});
    } else if (input_pins.size() == 3) {
        assert(output_pins.size() == 2);
        PinIndex Xor1_o = mother.AllocatePin();
        PinIndex Xor2_o = mother.AllocatePin();
        PinIndex And1_o = mother.AllocatePin();
        PinIndex And2_o = mother.AllocatePin();
        PinIndex Or1_o = mother.AllocatePin();

        XorGate::CreateChip(mother, {input_pins[0], input_pins[1]}, {Xor1_o});
        XorGate::CreateChip(mother, {Xor1_o, input_pins[2]}, {output_pins[1]});
        AndGate::CreateChip(mother, {input_pins[0], input_pins[1]}, {And1_o});
        OrGate::CreateChip(mother, {input_pins[0], input_pins[1]}, {Or1_o});
        AndGate::CreateChip(mother, {Or1_o, input_pins[2]}, {And2_o});
        OrGate::CreateChip(mother, {And1_o,And2_o}, {output_pins[0]});
    }
}

void Adder_2::CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins) {
    assert(input_pins.size() == 4 && output_pins.size() == 3);
    // if we want to calcualte 01+10, then the input is {0,1,1,0}. output is {0,1,1}
    // if we want to calculate 11+11, then input {1,1,1,1}, output is {1,1,0}
    PinIndex And_o = mother.AllocatePin();
    XorGate::CreateChip(mother, {input_pins[1], input_pins[3]}, {output_pins[2]});
    AndGate::CreateChip(mother, {input_pins[1], input_pins[3]}, {And_o});
    Adder::CreateChip(mother, {And_o, input_pins[0], input_pins[2]}, {output_pins[0], output_pins[1]});
}

}  //  namespace chip
