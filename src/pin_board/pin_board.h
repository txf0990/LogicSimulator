#ifndef PINBOARD_H
#define PINBOARD_H

#include <cstdint>
#include <vector>

#include "chip/chip.h"

namespace pin_board {

typedef std::size_t PinIndex;

class PinBoard {
public:
    PinBoard(PinIndex n);
    ~PinBoard() = default;
    PinBoard(const PinBoard&) = delete;
    PinBoard(PinBoard&&) = delete;
    PinBoard& operator= (const PinBoard&) = delete;
    PinBoard& operator= (PinBoard&&) = delete;

    void Tick();
    bool GetPin(PinIndex);
    void SetPin(PinIndex, bool);
    void PlugChip(chip::Chip*);

private:
    std::vector<int64_t> current_status;
    std::vector<int64_t> next_status;
    std::vector<chip::Chip*> chips;
};

} // namespace pin_board

#endif // #define PINBOARD_H
