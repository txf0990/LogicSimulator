#include "gtest/gtest.h"
#include "chip/basic_gates.h"
#include "chip/chip_test_util.h"

//#include <utility>
#include <memory>
#include <vector>

namespace {

using pin_board::PinBoard;
using pin_board::PinIndex;
using chip::Chip;
using chip::AndGate;
using chip::OrGate;
using chip::NotGate;
using chip::NandGate;
using chip::NorGate;
using chip::XorGate;
using std::vector;

void InitPins(PinBoard* board, std::vector<std::pair<PinIndex, bool>> input) {
    for (const auto& p : input) {
        board->SetPin(p.first, p.second);
    }
    board->Tick();
    for (const auto& p : input) {
        board->SetPin(p.first, p.second);
    }
}

TEST(BasicGatesTest, AndGate2) {
    PinBoard board(10,2,1);

    AndGate::CreateChip(
        board,
        GetVectorPart(board.input_offset, 2),
        {board.output_offset});

    TestChipLogic(
        board,
        {
          { {true, true}, {true} },
          { {true, false}, {false} },
          { {false, true}, {false} },
          { {false, false}, {false} },
        }
    );
}

TEST(BasicGatesTest, AndGate3) {
    PinBoard board(10,3,1);

    AndGate::CreateChip(
        board,
        GetVectorPart(board.input_offset, 3),
        {board.output_offset});

    TestChipLogic(
        board,
        {
          { {true, true, true}, {true} },
          { {true, true, false}, {false} },
          { {true, false, true}, {false} },
          { {false, true, true}, {false} },
          { {true, false, false}, {false} },
          { {false, true, false}, {false} },
          { {false, false, true}, {false} },
          { {false, false, false}, {false} },
        }
    );
}

TEST(BasicGatesTest, OrGate2) {
    PinBoard board(10,2,1);

    OrGate::CreateChip(
        board,
        GetVectorPart(board.input_offset, 2),
        {board.output_offset});

    TestChipLogic(
        board,
        {
          { {true, true}, {true} },
          { {true, false}, {true} },
          { {false, true}, {true} },
          { {false, false}, {false} },
        }
    );
}

TEST(BasicGatesTest, OrGate3) {
    PinBoard board(10,3,1);

    OrGate::CreateChip(
        board,
        GetVectorPart(board.input_offset, 3),
        {board.output_offset});

    TestChipLogic(
        board,
        {
          { {true, true, true}, {true} },
          { {true, true, false}, {true} },
          { {true, false, true}, {true} },
          { {false, true, true}, {true} },
          { {true, false, false}, {true} },
          { {false, true, false}, {true} },
          { {false, false, true}, {true} },
          { {false, false, false}, {false} },
        }
    );
}

TEST(BasicGatesTest, NotGate) {
    PinBoard board(10,1,1);

    NotGate::CreateChip(
        board,
        { board.input_offset },
        { board.output_offset });

    TestChipLogic(
        board,
        {
          { {true}, {false} },
          { {false}, {true} },
        }
    );
}

TEST(BasicGatesTest, NandGate) {
    PinBoard board(10,2,1);

    NandGate::CreateChip(
        board,
        GetVectorPart(board.input_offset, 2),
        {board.output_offset});

    TestChipLogic(
        board,
        {
          { {true, true}, {false} },
          { {true, false}, {true} },
          { {false, true}, {true} },
          { {false, false}, {true} },
        }
    );
}

TEST(BasicGatesTest, NorGate) {
    PinBoard board(10,2,1);

    NorGate::CreateChip(
        board,
        GetVectorPart(board.input_offset, 2),
        {board.output_offset});

    TestChipLogic(
        board,
        {
          { {true, true}, {false} },
          { {true, false}, {false} },
          { {false, true}, {false} },
          { {false, false}, {true} },
        }
    );
}

TEST(BasicGatesTest, XorGate) {
    PinBoard board(10,2,1);

    XorGate::CreateChip(
        board,
        GetVectorPart(board.input_offset, 2),
        {board.output_offset});

    TestChipLogic(
        board,
        {
          { {true, true}, {false} },
          { {true, false}, {true} },
          { {false, true}, {true} },
          { {false, false}, {false} },
        }
    );
}

} // namespace
