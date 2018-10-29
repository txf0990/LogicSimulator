#ifndef BASICGATES_H
#define BASICGATES_H

#include <vector>

#include "chip/chip.h"
#include "pin_board/pin_board.h"

namespace chip {

class AndGate : virtual public Chip {
public:
    AndGate(std::vector<int> v, int t, pin_board::PinBoard* p) : input_pin(std::move(v)), output_pin(t), mother(p){
        p->PlugChip(this);
    }
    void Tick();
private:
    std::vector<int> input_pin;
    int output_pin;
    pin_board::PinBoard* mother;
};

class OrGate : virtual public Chip {
public:
    OrGate(std::vector<int> v, int t, pin_board::PinBoard* p) : input_pin(v), output_pin(t), mother(p){
        p->PlugChip(this);
    }
    void Tick();
private:
    std::vector<int> input_pin;
    int output_pin;
    pin_board::PinBoard* mother;
};

class NotGate : virtual public Chip {
public:
    NotGate(int v, int t, pin_board::PinBoard* p) : input_pin(v), output_pin(t), mother(p) {
        p->PlugChip(this);
    }
    void Tick();
private:
    int input_pin;
    int output_pin;
    pin_board::PinBoard* mother;
};

} // namespace chip

#endif  // BASICGATES_H
