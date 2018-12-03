#ifndef CHIP_BASICGATES_H
#define CHIP_BASICGATES_H

#include <vector>

#include "chip/chip.h"
#include "pin_board/pin_board.h"

namespace chip {

using pin_board::PinIndex;

class AndGate : virtual public Chip {
public:
    AndGate(std::vector<PinIndex> v, PinIndex t, pin_board::PinBoard* p) : input_pin(std::move(v)), output_pin(t), mother(p){
    }
    ~AndGate() = default;
    void Tick();
    static void CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins);
private:
    std::vector<PinIndex> input_pin;
    PinIndex output_pin;
    pin_board::PinBoard* mother;
};

class OrGate : virtual public Chip {
public:
    OrGate(std::vector<PinIndex> v, PinIndex t, pin_board::PinBoard* p) : input_pin(v), output_pin(t), mother(p){
    }
    ~OrGate() = default;
    void Tick();
    static void CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins);
private:
    std::vector<PinIndex> input_pin;
    PinIndex output_pin;
    pin_board::PinBoard* mother;
};

class NotGate : virtual public Chip {
public:
    NotGate(PinIndex v, PinIndex t, pin_board::PinBoard* p) : input_pin(v), output_pin(t), mother(p) {
    }
    ~NotGate() = default;
    void Tick();
    static void CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins);
private:
    PinIndex input_pin;
    PinIndex output_pin;
    pin_board::PinBoard* mother;
};

class NandGate : virtual public Chip {
public:
    static void CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins);
};
    
class XorGate : virtual public Chip {
public:
    static void CreateChip(pin_board::PinBoard& mother, const std::vector<PinIndex>& input_pins, const std::vector<PinIndex>& output_pins);
};

} // namespace chip

#endif  // CHIP_BASICGATES_H
