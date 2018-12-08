#ifndef ALU_ALU_H
#define ALU_ALU_H

#include "chip/chip.h"
#include "pin_board/pin.h"

#include <vector>

namespace chip {

class Alu : public Chip {
public:
    struct AluInternalPins {
      // input
      std::vector<pin_board::PinIndex> func; // 4 bits
      std::vector<pin_board::PinIndex> shamt; // 5 bits
      std::vector<pin_board::PinIndex> a; // 32 bits
      std::vector<pin_board::PinIndex> b; // 32 bits

      // output
      std::vector<pin_board::PinIndex> output; // 32 bits

      // internal
      std::vector<pin_board::PinIndex> add_minus_output; // 32 bits
      std::vector<pin_board::PinIndex> bitwise_output; // 32 bits
      std::vector<pin_board::PinIndex> shift_output; // 32 bits

      // shifter
      pin_board::PinIndex shift_replace;
      pin_board::PinIndex shift_replace_value;
      std::vector<pin_board::PinIndex> shift_pre_output; // 32 bits
      std::vector<pin_board::PinIndex> shift_num; // 32 bits
    };

    static void CreateChip(
        pin_board::PinBoard& mother,
        const std::vector<pin_board::PinIndex>& input1_pins,
        const std::vector<pin_board::PinIndex>& input2_pins,
        const std::vector<pin_board::PinIndex>& shamt,
        const std::vector<pin_board::PinIndex>& func,
        const std::vector<pin_board::PinIndex>& output_pins);

    // helper functions
    static void CalculateAddMinus(
        pin_board::PinBoard& mother,
        AluInternalPins p);

    static void CalculateBitwise(
        pin_board::PinBoard& mother,
        AluInternalPins p);

    static void CalculateShift(
        pin_board::PinBoard& mother,
        AluInternalPins p);

    static void CalculateOutput(
        pin_board::PinBoard& mother,
        AluInternalPins p);
};

} // namespace chip

#endif // ALU_ALU_H
