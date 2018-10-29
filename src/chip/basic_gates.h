#ifndef BASICGATES_H
#define BASICGATES_H

#include <vector>

#include "chip/chip.h"
#include "pin_board/pin_board.h"

namespace chip {

class AndGate : virtual public Chip {
public:
    AndGate(vector<int> v, int t, PinBoard* p) : input_pin(std::move(v)), output_pin(t), mother(p){}
    void Tick();
private:
    vector<int> input_pin;
    int output_pin;
    PinBoard* mother;
};

class OrGate : virtual public Chip {
public:
    OrGate(vector<int> v, int t, PinBoard* p) : input_pin(v), output_pin(t), mother(p){}
    void Tick();
private:
    vector<int> input_pin;
    int output_pin;
    PinBoard* mother;
};

class NotGate : virtual public Chip {
public:
    NotGate(int v, int t, PinBoard* p) : input_pin(v), output_pin(t), mother(p) {}
    void Tick();
private:
    int input_pin;
    int output_pin;
    PinBoard* mother;
};

} // namespace chip

#endif  // BASICGATES_H
