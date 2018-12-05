#include <cassert>
#include "basic_gates.h"
#include "adder.h"
#include "chip_test_util.h"

namespace chip {

void Adder::CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins) {
    assert(input_pins.size() == 2 || input_pins.size() == 3);

    if (input_pins.size() == 2) {
        assert(output_pins.size() == 2);
        AndGate::CreateChip(mother, input_pins, {output_pins[1]});
        XorGate::CreateChip(mother, input_pins, {output_pins[0]});
    } else if (input_pins.size() == 3) {
        assert(output_pins.size() == 2);
        PinIndex Xor1_o = mother.AllocatePin();
        PinIndex Xor2_o = mother.AllocatePin();
        PinIndex And1_o = mother.AllocatePin();
        PinIndex And2_o = mother.AllocatePin();
        PinIndex Or1_o = mother.AllocatePin();

        XorGate::CreateChip(mother, {input_pins[0], input_pins[1]}, {Xor1_o});
        XorGate::CreateChip(mother, {Xor1_o, input_pins[2]}, {output_pins[0]});
        AndGate::CreateChip(mother, {input_pins[0], input_pins[1]}, {And1_o});
        OrGate::CreateChip(mother, {input_pins[0], input_pins[1]}, {Or1_o});
        AndGate::CreateChip(mother, {Or1_o, input_pins[2]}, {And2_o});
        OrGate::CreateChip(mother, {And1_o,And2_o}, {output_pins[1]});
    }
}

void Adder_2::CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input1_pins, const std::vector<PinIndex>& input2_pins, const PinIndex carry_pin, const std::vector<PinIndex>& output_pins) {
    assert(input1_pins.size() == input2_pins.size());
    // input_pins = {low_dig, high_dig}
    // output_pins = {low_dig, high_dig}
    // if we want to calcualte 01+10, then the input is {1,0},{0,1}. output is {1,1,0}
    // if we want to calculate 11+11, then input {1,1},{1,1}, output is {0,1,1}
    if (input1_pins.size() == 1) {
//        Adder::CreateChip(mother, {input1_pins[0], input2_pins[0], carry_pin}, output_pins);
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
    } else if (input1_pins.size() == 2) { 
        PinIndex Adder_o = mother.AllocatePin();
        Adder_2::CreateChip(mother, {input1_pins[0]}, {input2_pins[0]}, carry_pin, {output_pins[0], Adder_o});
        Adder_2::CreateChip(mother, {input1_pins[1]}, {input2_pins[1]}, Adder_o, {output_pins[1], output_pins[2]});
    } else if (input1_pins.size() == 4) {
        PinIndex Adder_o = mother.AllocatePin();
        Adder_2::CreateChip(mother, {input1_pins[0], input1_pins[1]}, {input2_pins[0], input2_pins[1]}, carry_pin, {output_pins[0], output_pins[1], Adder_o});
        Adder_2::CreateChip(mother, {input1_pins[2], input1_pins[3]}, {input2_pins[2], input2_pins[3]}, Adder_o, {output_pins[2], output_pins[3], output_pins[4]});
    } else if (input1_pins.size() == 8) {
        PinIndex Adder_o = mother.AllocatePin();
        std::vector<PinIndex> output = GetVectorPart(0, 4, output_pins);
        output.push_back(Adder_o);
        Adder_2::CreateChip(
                mother, 
                GetVectorPart(0, 4, input1_pins),
                GetVectorPart(0, 4, input2_pins),
                carry_pin, 
                output
                );
        output.clear();
        output = GetVectorPart(4, 5, output_pins);
        Adder_2::CreateChip(
                mother, 
                GetVectorPart(4, 4, input1_pins),
                GetVectorPart(4, 4, input2_pins),
                Adder_o, 
                output
                );
    } else if (input1_pins.size() == 16) {
        PinIndex Adder_o = mother.AllocatePin();
        std::vector<PinIndex> output = GetVectorPart(0, 8, output_pins);
        output.push_back(Adder_o);
        Adder_2::CreateChip(
                mother, 
                GetVectorPart(0,8, input1_pins),
                GetVectorPart(0,8, input2_pins),
                carry_pin, 
                output
                );
        output.clear();
        output = GetVectorPart(8, 9, output_pins);
        Adder_2::CreateChip(
                mother, 
                GetVectorPart(8,8, input1_pins),
                GetVectorPart(8,8, input2_pins),
                Adder_o, 
                output
                );
    } else if (input1_pins.size() == 32) {
        PinIndex Adder_o = mother.AllocatePin();
        std::vector<PinIndex> output = GetVectorPart(0, 16, output_pins);
        output.push_back(Adder_o);
        Adder_2::CreateChip(
                mother, 
                GetVectorPart(0, 16, input1_pins),
                GetVectorPart(0, 16, input2_pins),
                carry_pin, 
                output
                );
        output.clear();
        output = GetVectorPart(16, 17, output_pins);
        Adder_2::CreateChip(
                mother,
                GetVectorPart(16, 16, input1_pins),
                GetVectorPart(16, 16, input2_pins),
                Adder_o,
                output
                );
    }
}

}  //  namespace chip
