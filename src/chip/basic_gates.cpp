#include "basic_gates.h"

namespace chip {

using std::vector;

void AndGate::Tick() {
    bool result = true;
    for(int i = 0; i < input_pin.size(); i++) {
        result = result & mother->GetPin(input_pin[i]);
    }
    mother->SetPin(output_pin, result);
}

void OrGate::Tick() {
    bool result = false;
    for(int i = 0; i < input_pin.size(); i++) {
        result = result | mother->GetPin(input_pin[i]);
    }
    mother->SetPin(output_pin, result);
}

void NotGate::Tick() {
    bool result = !mother->GetPin(input_pin);
    mother->SetPin(output_pin, result);
}

}   // namespace chip
