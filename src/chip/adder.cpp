#include <cassert>
#include "basic_gates.h"
#include "adder.h"
#include "chip_test_util.h"

namespace chip {

void Adder_2::CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input1_pins, const std::vector<PinIndex>& input2_pins, const PinIndex carry_pin, const std::vector<PinIndex>& output_pins) {
    assert(input1_pins.size() == input2_pins.size());
    // input_pins = {low_dig, high_dig}
    // output_pins = {low_dig, high_dig}
    // if we want to calcualte 01+10, then the input is {1,0},{0,1}. output is {1,1,0}
    // if we want to calculate 11+11, then input {1,1},{1,1}, output is {0,1,1}
    if (input1_pins.size() == 1) {
//        Adder_2::CreateChip(mother, {input1_pins[0], input2_pins[0], carry_pin}, output_pins);
        PinIndex Xor1_o = mother.AllocatePin();
        PinIndex Xor2_o = mother.AllocatePin();
        PinIndex And1_o = mother.AllocatePin();
        PinIndex And2_o = mother.AllocatePin();
        PinIndex Or1_o = mother.AllocatePin();

        XorGate::CreateChip(mother, {input1_pins[0], input2_pins[0]}, {Xor1_o});
        XorGate::CreateChip(mother, {Xor1_o, carry_pin}, {output_pins[0]});
        AndGate::CreateChip(mother, {input1_pins[0], input2_pins[0]}, {And1_o});
        OrGate::CreateChip(mother, {input1_pins[0], input2_pins[0]}, {Or1_o});
        AndGate::CreateChip(mother, {Or1_o, carry_pin}, {And2_o});
        OrGate::CreateChip(mother, {And1_o,And2_o}, {output_pins[1]});
    } else {
        assert(input1_pins.size() % 2 == 0);
        int digit = input1_pins.size();
        PinIndex Adder_o = mother.AllocatePin();
        std::vector<PinIndex> output = GetVectorPart(0, digit / 2, output_pins);
        output.push_back(Adder_o);
        Adder_2::CreateChip(
                mother, 
                GetVectorPart(0, digit / 2, input1_pins),
                GetVectorPart(0, digit / 2, input2_pins),
                carry_pin, 
                output
                );
        output.clear();
        output = GetVectorPart(digit / 2, digit / 2 + 1, output_pins);
        Adder_2::CreateChip(
                mother,
                GetVectorPart(digit / 2, digit / 2, input1_pins),
                GetVectorPart(digit / 2, digit / 2, input2_pins),
                Adder_o,
                output
                );
    }
}

}  //  namespace chip
