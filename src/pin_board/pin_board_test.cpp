#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "pin_board/pin_board.h"

namespace {

using ::testing::ElementsAre;
using pin_board::PinBoard;

TEST(PinBoardTest, Simple) {
    PinBoard board(200, 10, 20);

    EXPECT_EQ(8, sizeof(int64_t));

    board.SetPin(2, true);
    board.SetPin(51, false);
    board.SetPin(102, true);
    board.SetPin(153, false);
    board.SetPin(199, true);

    board.Tick();

    EXPECT_EQ(true, board.GetPin(2));
    EXPECT_EQ(false, board.GetPin(51));
    EXPECT_EQ(true, board.GetPin(102));
    EXPECT_EQ(false, board.GetPin(153));
    EXPECT_EQ(true, board.GetPin(199));
}

TEST(PinBoardTest, PinAllocationTest) {
    PinBoard board(200, 10, 20);

    EXPECT_EQ(board.free_pin_offset, board.AllocatePin());
    EXPECT_EQ(board.free_pin_offset + 1, board.AllocatePin());
    EXPECT_EQ(board.free_pin_offset + 2, board.AllocatePin());
    EXPECT_EQ(board.free_pin_offset + 3, board.AllocatePin());
}

TEST(PinBoardTest, PinsAllocationTest) {
    PinBoard board(200, 10, 20);

    auto i = board.free_pin_offset;

    EXPECT_THAT(board.AllocatePins(4), ElementsAre(i, i + 1, i + 2, i + 3));
}

}
