#include "gtest/gtest.h"
#include "chip/basic_gates.h"

//#include <utility>
#include <vector>

namespace {

using pin_board::PinBoard;
using pin_board::PinIndex;
using chip::AndGate;
using chip::OrGate;
using chip::NotGate;
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
    PinBoard* board = new PinBoard(10);
    InitPins(board, {
        {0, true},
        {1, true},
        {2, false},
        {3, false}
    });

    AndGate* p1 = new AndGate({0,1}, 4, board);
    AndGate* p2 = new AndGate({0,2}, 5, board);
    AndGate* p3 = new AndGate({2,3}, 6, board);

    board->Tick();

    EXPECT_EQ(true, board->GetPin(4));
    EXPECT_EQ(false, board->GetPin(5));
    EXPECT_EQ(false, board->GetPin(6));
}

TEST(BasicGatesTest, AndGate3) {
    PinBoard* board = new PinBoard(10);
    InitPins(board, {
        {0, true},
        {1, true},
        {2, true},
        {3, false},
        {4, false},
        {5, false},
    });

    board->Tick();

    AndGate* p1 = new AndGate({0,1,2}, 6, board);
    AndGate* p2 = new AndGate({0,2,3}, 7, board);
    AndGate* p3 = new AndGate({0,3,4}, 8, board);
    AndGate* p4 = new AndGate({3,4,5}, 9, board);

    board->Tick();

    EXPECT_EQ(true, board->GetPin(6));
    EXPECT_EQ(false, board->GetPin(7));
    EXPECT_EQ(false, board->GetPin(8));
    EXPECT_EQ(false, board->GetPin(9));
}

TEST(BasicGatesTest, OrGate2) {
    PinBoard* board = new PinBoard(10);
    InitPins(board, {
        {0, true},
        {1, true},
        {2, false},
        {3, false},
    });

    board->Tick();

    OrGate* p1 = new OrGate({0,1}, 4, board);
    OrGate* p2 = new OrGate({0,2}, 5, board);
    OrGate* p3 = new OrGate({2,3}, 6, board);

    board->Tick();

    EXPECT_EQ(true, board->GetPin(4));
    EXPECT_EQ(true, board->GetPin(5));
    EXPECT_EQ(false, board->GetPin(6));
}

TEST(BasicGatesTest, OrGate3) {
    PinBoard* board = new PinBoard(10);
    InitPins(board, {
        {0, true},
        {1, true},
        {2, true},
        {3, false},
        {4, false},
        {5, false},
    });

    board->Tick();

    OrGate* p1 = new OrGate({0,1,2}, 6, board);
    OrGate* p2 = new OrGate({0,2,3}, 7, board);
    OrGate* p3 = new OrGate({0,3,4}, 8, board);
    OrGate* p4 = new OrGate({3,4,5}, 9, board);

    board->Tick();

    EXPECT_EQ(true, board->GetPin(6));
    EXPECT_EQ(true, board->GetPin(7));
    EXPECT_EQ(true, board->GetPin(8));
    EXPECT_EQ(false, board->GetPin(9));
}

TEST(BasicGatesTest, NotGate) {
    PinBoard* board = new PinBoard(4);
    InitPins(board, {
        {0, true},
        {1, false},
    });

    board->Tick();

    NotGate* p1 = new NotGate(0, 2, board);
    NotGate* p2 = new NotGate(1, 3, board);

    board->Tick();

    EXPECT_EQ(false, board->GetPin(2));
    EXPECT_EQ(true, board->GetPin(3));
}

}
