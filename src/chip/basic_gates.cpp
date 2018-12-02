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
   //TODO: assert output pin has size == 1.
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
   //TODO: assert output pin has size == 1.
    std::unique_ptr<OrGate> created = std::make_unique<OrGate>(input_pins, output_pins[0], &mother);
    mother.PlugChip(std::move(created));

}

void NotGate::Tick() {
    bool result = !mother->GetPin(input_pin);
    mother->SetPin(output_pin, result);
}

void NotGate::CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins) {
   //TODO: assert both input pin and output pin have size == 1.
    std::unique_ptr<NotGate> created = std::make_unique<NotGate>(input_pins[0], output_pins[0], &mother);
    mother.PlugChip(std::move(created));
}
}   // namespace chip
