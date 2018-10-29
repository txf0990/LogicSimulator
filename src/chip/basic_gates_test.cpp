#include "gtest/gtest.h"
#include "chip/basic_gates.h"

namespace {

using pin_board::PinBoard;
using chip::AndGate;
using chip::OrGate;
using chip::NotGate;
using std::vector;

TEST(BasicGatesTest, AndGate2) {
    PinBoard* board = new PinBoard(10);
    board->SetPin(0, true);
    board->SetPin(1, true);
    board->SetPin(2, false);
    board->SetPin(3, false);

    board->Tick();

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
    board->SetPin(0, true);
    board->SetPin(1, true);
    board->SetPin(2, true);
    board->SetPin(3, false);
    board->SetPin(4, false);
    board->SetPin(5, false);

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
    board->SetPin(0, true);
    board->SetPin(1, true);
    board->SetPin(2, false);
    board->SetPin(3, false);

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
    board->SetPin(0, true);
    board->SetPin(1, true);
    board->SetPin(2, true);
    board->SetPin(3, false);
    board->SetPin(4, false);
    board->SetPin(5, false);

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
    board->SetPin(0, true);
    board->SetPin(1, false);

    board->Tick();

    NotGate* p1 = new NotGate(0, 2, board);
    NotGate* p2 = new NotGate(1, 3, board);

    board->Tick();

    EXPECT_EQ(false, board->GetPin(2));
    EXPECT_EQ(true, board->GetPin(3));
}

/*
TEST(BasicGatesTest, Simple) {
    PinBoard* board = new PinBoard(20);

    board->SetPin(0, true);
    board->SetPin(1, true);
    board->SetPin(3, true);
    board->SetPin(5, true);
    board->SetPin(6, true);
    board->SetPin(8, true);
    board->SetPin(9, true);

    board->SetPin(10, true);
    board->SetPin(11, true);
    board->SetPin(13, true);
    board->SetPin(15, true);
    board->SetPin(16, true);
    board->SetPin(18, true);
    board->SetPin(19, true);
    
    board->Tick();

    EXPECT_EQ(true, board->GetPin(1));
    EXPECT_EQ(false, board->GetPin(2));
    EXPECT_EQ(true, board->GetPin(3));
    EXPECT_EQ(false, board->GetPin(4));
    EXPECT_EQ(true, board->GetPin(8));
    EXPECT_EQ(true, board->GetPin(9));

    AndGate* p1 = new AndGate({0,1,2},3,board);
    OrGate* p2 = new OrGate({4,5,6},7,board);
    OrGate* p3 = new OrGate({10,11,12},13,board);
    AndGate* p4 = new AndGate({14,15,16},17,board);
    NotGate* p5 = new NotGate(8,9,board);
    NotGate* p6 = new NotGate(19,18,board);

    board->Tick();

    EXPECT_EQ(false, board->GetPin(3));
    EXPECT_EQ(true, board->GetPin(7));
    EXPECT_EQ(true, board->GetPin(13));
    EXPECT_EQ(false, board->GetPin(17));
    EXPECT_EQ(true, board->GetPin(8));
    EXPECT_EQ(false, board->GetPin(9));

}
*/

}
