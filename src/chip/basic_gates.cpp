#include <cassert>
#include "basic_gates.h"

namespace chip {

using std::vector;
using pin_board::PinBoard;

void AndGate::Tick() {
    bool result = true;
    for(int i = 0; i < input_pin.size(); i++) {
        result = result & mother->GetPin(input_pin[i]);
    }
    mother->SetPin(output_pin, result);
}

void AndGate::CreateChip(PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins) {
    assert(output_pins.size() == 1);
    std::unique_ptr<AndGate> created = std::make_unique<AndGate>(input_pins, output_pins[0], &mother);
    mother.PlugChip(std::move(created));
}

void OrGate::Tick() {
    bool result = false;
    for(int i = 0; i < input_pin.size(); i++) {
        result = result | mother->GetPin(input_pin[i]);
    }
    mother->SetPin(output_pin, result);
}

void OrGate::CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins) {
    assert(output_pins.size() == 1);
    std::unique_ptr<OrGate> created = std::make_unique<OrGate>(input_pins, output_pins[0], &mother);
    mother.PlugChip(std::move(created));

}

void NotGate::Tick() {
    bool result = !mother->GetPin(input_pin);
    mother->SetPin(output_pin, result);
}

void NotGate::CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins) {
    assert(input_pins.size() == 1 && output_pins.size() == 1);
    std::unique_ptr<NotGate> created = std::make_unique<NotGate>(input_pins[0], output_pins[0], &mother);
    mother.PlugChip(std::move(created));
}

void NandGate::CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins) {
    assert(output_pins.size() == 1);
    PinIndex And_o = mother.AllocatePin();
    AndGate::CreateChip(mother, input_pins, {And_o});
    NotGate::CreateChip(mother, {And_o}, {output_pins[0]});
}

void NorGate::CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins) {
    assert(output_pins.size() == 1);
    PinIndex Or_o = mother.AllocatePin();
    OrGate::CreateChip(mother, input_pins, {Or_o});
    NotGate::CreateChip(mother, {Or_o}, output_pins);
}

void XorGate::CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins) {
    assert(input_pins.size() == 2 && output_pins.size() == 1);
    PinIndex And_o = mother.AllocatePin();
    PinIndex Or_o = mother.AllocatePin();
    PinIndex Not_o = mother.AllocatePin();
    AndGate::CreateChip(mother, input_pins, {And_o});
    NotGate::CreateChip(mother, {And_o}, {Not_o});
    OrGate::CreateChip(mother, input_pins, {Or_o});
    AndGate::CreateChip(mother, {Not_o, Or_o}, {output_pins[0]});
}

}   // namespace chip
