#ifndef CHIP_CHIP_H
#define CHIP_CHIP_H

namespace pin_board {
    class PinBoard;
}

namespace chip {

class Chip {
public:
    virtual ~Chip() = default;
    virtual void Tick() = 0;
    void SetMother(pin_board::PinBoard* p) {
        mother = p;
    }
protected:
    pin_board::PinBoard* mother;
};

}

#endif  // CHIP_CHIP_H
