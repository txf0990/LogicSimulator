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
    std::unique_ptr<PinBoard> board = std::make_unique<PinBoard> (10,2,2);
    
    InitPins(board.get(), {
        {0, true},
        {1, true},
        {2, false},
        {3, false}
    });

    board->Tick();

    std::unique_ptr<Chip> p1 = std::make_unique<AndGate>(std::vector<PinIndex>({0,1}), 4, board.get());
    board->PlugChip(std::move(p1));
    std::unique_ptr<Chip> p2 = std::make_unique<AndGate>(std::vector<PinIndex>({0,2}), 5, board.get());
    board->PlugChip(std::move(p2));
    std::unique_ptr<Chip> p3 = std::make_unique<AndGate>(std::vector<PinIndex>({2,3}), 6, board.get());
    board->PlugChip(std::move(p3));

    board->Tick();

    EXPECT_EQ(true, board->GetPin(4));
    EXPECT_EQ(false, board->GetPin(5));
    EXPECT_EQ(false, board->GetPin(6));
}

TEST(BasicGatesTest, AndGate3) {
    std::unique_ptr<PinBoard> board = std::make_unique<PinBoard> (10,2,2);

    InitPins(board.get(), {
        {0, true},
        {1, true},
        {2, true},
        {3, false},
        {4, false},
        {5, false},
    });

    board->Tick();

    std::unique_ptr<Chip> p1 = std::make_unique<AndGate>(std::vector<PinIndex>({0,1,2}), 6, board.get());
    board->PlugChip(std::move(p1));
    std::unique_ptr<Chip> p2 = std::make_unique<AndGate>(std::vector<PinIndex>({0,2,3}), 7, board.get());
    board->PlugChip(std::move(p2));
    std::unique_ptr<Chip> p3 = std::make_unique<AndGate>(std::vector<PinIndex>({0,3,4}), 8, board.get());
    board->PlugChip(std::move(p3));
    std::unique_ptr<Chip> p4 = std::make_unique<AndGate>(std::vector<PinIndex>({3,4,5}), 9, board.get());
    board->PlugChip(std::move(p4));

    board->Tick();

    EXPECT_EQ(true, board->GetPin(6));
    EXPECT_EQ(false, board->GetPin(7));
    EXPECT_EQ(false, board->GetPin(8));
    EXPECT_EQ(false, board->GetPin(9));
}

TEST(BasicGatesTest, OrGate2) {
    std::unique_ptr<PinBoard> board = std::make_unique<PinBoard> (10,2,2);

    InitPins(board.get(), {
        {0, true},
        {1, true},
        {2, false},
        {3, false},
    });

    board->Tick();

    std::unique_ptr<Chip> p1 = std::make_unique<OrGate>(std::vector<PinIndex>({0,1}), 4, board.get());
    board->PlugChip(std::move(p1));
    std::unique_ptr<Chip> p2 = std::make_unique<OrGate>(std::vector<PinIndex>({0,2}), 5, board.get());
    board->PlugChip(std::move(p2));
    std::unique_ptr<Chip> p3 = std::make_unique<OrGate>(std::vector<PinIndex>({2,3}), 6, board.get());
    board->PlugChip(std::move(p3));

    board->Tick();

    EXPECT_EQ(true, board->GetPin(4));
    EXPECT_EQ(true, board->GetPin(5));
    EXPECT_EQ(false, board->GetPin(6));
}

TEST(BasicGatesTest, OrGate3) {
    std::unique_ptr<PinBoard> board = std::make_unique<PinBoard> (10,2,2);

    InitPins(std::move(board.get()), {
        {0, true},
        {1, true},
        {2, true},
        {3, false},
        {4, false},
        {5, false},
    });

    board->Tick();

    std::unique_ptr<Chip> p1 = std::make_unique<OrGate>(std::vector<PinIndex>({0,1,2}), 6, board.get());
    board->PlugChip(std::move(p1));
    std::unique_ptr<Chip> p2 = std::make_unique<OrGate>(std::vector<PinIndex>({0,2,3}), 7, board.get());
    board->PlugChip(std::move(p2));
    std::unique_ptr<Chip> p3 = std::make_unique<OrGate>(std::vector<PinIndex>({0,3,4}), 8, board.get());
    board->PlugChip(std::move(p3));
    std::unique_ptr<Chip> p4 = std::make_unique<OrGate>(std::vector<PinIndex>({3,4,5}), 9, board.get());
    board->PlugChip(std::move(p4));

    board->Tick();

    EXPECT_EQ(true, board->GetPin(6));
    EXPECT_EQ(true, board->GetPin(7));
    EXPECT_EQ(true, board->GetPin(8));
    EXPECT_EQ(false, board->GetPin(9));
}

TEST(BasicGatesTest, NotGate) {
    std::unique_ptr<PinBoard> board = std::make_unique<PinBoard> (4,1,1);

    InitPins(board.get(), {
        {0, true},
        {1, false},
    });

    board->Tick();

    std::unique_ptr<Chip> p1 = std::make_unique<NotGate>(0, 2, board.get());
    board->PlugChip(std::move(p1));
    std::unique_ptr<Chip> p2 = std::make_unique<NotGate>(1, 3, board.get());
    board->PlugChip(std::move(p2));

    board->Tick();

    EXPECT_EQ(false, board->GetPin(2));
    EXPECT_EQ(true, board->GetPin(3));
}

TEST(BasicGatesTest, NANDGate) {
    PinBoard board(10,2,1);
    NandGate::CreateChip(board, {0,1}, {2});
    TestChipLogic(
            board,
            {
                {false, false},
                {false, true},
                {true, false},
                {true, true},
            },
            {
                {true},
                {true},
                {true},
                {false},
            });
}

TEST(BasicGatesTest, XorGate) {
    PinBoard board(10,2,1);
    XorGate::CreateChip(board, {0,1}, {2});
    TestChipLogic(
            board,
            {
                {false, false},
                {false, true},
                {true, false},
                {true, true},
            },
            {
                {false},
                {true},
                {true},
                {false},
            });
}
}
