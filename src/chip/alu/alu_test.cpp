#include "chip/alu/alu.h"

#include <tuple>
#include <vector>

#include "gtest/gtest.h"
#include "chip/basic_gates.h"
#include "chip/chip_test_util.h"

namespace {

using chip::Alu;
using std::vector;
using std::pair;
using pin_board::PinBoard;
using pin_board::PinIndex;

TEST(AluTest, BitwiseOutput) {
  PinBoard board(1000, 64 + 5 + 4, 32);
  Alu::AluInternalPins p;
  p.a = GetVectorPart(board.input_offset, 32);
  p.b = GetVectorPart(board.input_offset + 32, 32);
  p.shamt = GetVectorPart(board.input_offset + 64, 5);
  p.func = GetVectorPart(board.input_offset + 69, 4);
  p.output = GetVectorPart(board.output_offset, 32);
  Alu::AllocatePins(board, p);
  p.bitwise_output = p.output;

  Alu::CalculateBitwise(board, p);

  vector<int> config = {32, 32, 5, 4};

  std::function<int(int, int)> bitwise_func[4] = {
    [](int a, int b) { return a & b; },
    [](int a, int b) { return a | b; },
    [](int a, int b) { return a ^ b; },
    [](int a, int b) { return ~(a | b); },
  };
  vector< pair<int, int> > test_numbers = {
    {0, 0},
    {0, ~0},
    {~0, 0},
    {~0, ~0},
    {10235, 78893},
    {49396, 108375},
  };
  vector< pair<vector<bool>, vector<bool>> > test_cases;

  for (const auto& p : test_numbers) {
    int a, b;
    std::tie(a, b) = p;
    for (int i = 0; i < 4; i++) {
      // func code for and/or/xor/nor are 1100(2)=12, 1101(2)=13, 1110(2)=14, 1111(2)=15;
      test_cases.push_back({
          GeneratePins({a, b, 0, 12 + i}, config),
          NumberToPins(bitwise_func[i](a, b), 32)});
    }
  }

  TestChipLogic(board, test_cases, 10);
}

TEST(AluTest, AddMinusOutput) {
  PinBoard board(1000, 64 + 5 + 4, 32);
  Alu::AluInternalPins p;
  p.a = GetVectorPart(board.input_offset, 32);
  p.b = GetVectorPart(board.input_offset + 32, 32);
  p.shamt = GetVectorPart(board.input_offset + 64, 5);
  p.func = GetVectorPart(board.input_offset + 69, 4);
  p.output = GetVectorPart(board.output_offset, 32);
  Alu::AllocatePins(board, p);
  p.add_minus_output = p.output;

  Alu::CalculateAddMinus(board, p);

  vector<int> config = {32, 32, 5, 4};

  std::function<int(int, int)> add_minus_func[4] = {
    [](int a, int b) { return a + b; },
    [](int a, int b) { return a + b; },
    [](int a, int b) { return a - b; },
    [](int a, int b) { return a - b; },
  };
  vector< pair<int, int> > test_numbers = {
    {0, 0},
    {0, ~0},
    {~0, 0},
    {~0, ~0},
    {10235, 78893},
    {49396, 108375},
  };
  vector< pair<vector<bool>, vector<bool>> > test_cases;

  for (const auto& p : test_numbers) {
    int a, b;
    std::tie(a, b) = p;
    for (int i = 0; i < 4; i++) {
      // func code for +/+/-/- are 1000(2)=8, 1001(2)=9, 1010(2)=10, 1011(2)=11;
      test_cases.push_back({
          GeneratePins({a, b, 0, 8 + i}, config),
          NumberToPins(add_minus_func[i](a, b), 32)});
    }
  }

  TestChipLogic(board, test_cases, 100);
}

} // namespace
