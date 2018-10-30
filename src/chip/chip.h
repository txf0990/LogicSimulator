#ifndef CHIP_H
#define CHIP_H

namespace chip {

class Chip {
public:
    virtual ~Chip() = default;
    virtual void Tick() = 0;
};

}

#endif  // #define CHIP_H
