#ifndef PINBOARD_H
#define PINBOARD_H

#include <cstdint>
#include <memory>
#include <vector>

#include "chip/chip.h"

namespace pin_board {

typedef std::size_t PinIndex;

class PinBoard {
public:
    PinBoard(PinIndex n, PinIndex x, PinIndex y);
    ~PinBoard() = default;
    PinBoard(const PinBoard&) = delete;
    PinBoard(PinBoard&&) = delete;
    PinBoard& operator= (const PinBoard&) = delete;
    PinBoard& operator= (PinBoard&&) = delete;

    void Tick();
    bool GetPin(PinIndex);
    void SetPin(PinIndex, bool);
    PinIndex AllocatePin();
    void PlugChip(std::unique_ptr<chip::Chip>);

private:
    std::vector<int64_t> current_status;
    std::vector<int64_t> next_status;
    PinIndex input_num = 0;
    PinIndex output_num = 0;
    PinIndex allocated_pin = 0;
    std::vector<std::unique_ptr<chip::Chip>> chips;
};

} // namespace pin_board

#endif // #define PINBOARD_H
