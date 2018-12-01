#include "gtest/gtest.h"
#include "pin_board/pin_board.h"

namespace {

using pin_board::PinBoard;

TEST(PinBoardTest, Simple) {
    PinBoard board(200, 10, 20);

    EXPECT_EQ(8, sizeof(int64_t));

    board.SetPin(0, true);
    board.SetPin(51, false);
    board.SetPin(102, true);
    board.SetPin(153, false);
    board.SetPin(199, true);

    board.Tick();

    EXPECT_EQ(true, board.GetPin(0));
    EXPECT_EQ(false, board.GetPin(51));
    EXPECT_EQ(true, board.GetPin(102));
    EXPECT_EQ(false, board.GetPin(153));
    EXPECT_EQ(true, board.GetPin(199));
}

TEST(PinBoardTest, PinAllocationTest) {
    std::unique_ptr<PinBoard> board = std::make_unique<PinBoard> (200, 10, 20);

    EXPECT_EQ(30, board->AllocatePin());
    EXPECT_EQ(31, board->AllocatePin());
    EXPECT_EQ(32, board->AllocatePin());
    EXPECT_EQ(33, board->AllocatePin());
}

}
