#ifndef PINBOARD_PINBOARD_H
#define PINBOARD_PINBOARD_H

#include "pin_board/pin.h"
#include "chip/chip.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace pin_board {

class PinBoard {
public:
    PinBoard(PinIndex n, PinIndex x, PinIndex y);
    ~PinBoard() = default;
    PinBoard(const PinBoard&) = delete;
    PinBoard(PinBoard&&) = delete;
    PinBoard& operator= (const PinBoard&) = delete;
    PinBoard& operator= (PinBoard&&) = delete;

    void Tick();
    bool GetPin(PinIndex pin);
    void SetPin(PinIndex pin, bool val);
    PinIndex AllocatePin();
    std::vector<PinIndex> AllocatePins(size_t size);
    void PlugChip(std::unique_ptr<chip::Chip> chip);

    void SetInput(const std::vector<bool>& input, int offset = 0);
    void GetOutput(std::vector<bool>& output, int offset = 0);
    PinIndex GetZeroPin() {return 0;}
    PinIndex GetOnePin() {return 1;}

    const PinIndex input_offset;
    const PinIndex output_offset;
    const PinIndex free_pin_offset;
private:
    // Used for ZeroPin and OnePin
    void SetCurrentPin(PinIndex pin, bool val);

    std::vector<int64_t> current_status;
    std::vector<int64_t> next_status;
    PinIndex input_num = 0;
    PinIndex output_num = 0;
    PinIndex total_pin_num = 0;
    PinIndex allocated_pin = 0;
    std::vector<std::unique_ptr<chip::Chip>> chips;
};

} // namespace pin_board

#endif // PINBOARD_PINBOARD_H
