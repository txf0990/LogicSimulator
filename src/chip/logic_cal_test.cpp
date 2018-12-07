#include "chip/logic_cal.h"

#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "chip/basic_gates.h"
#include "chip/chip_test_util.h"

namespace {

using pin_board::PinBoard;
using pin_board::PinIndex;
using chip::BitNot;
using chip::BitAnd;
using std::pair;
using std::vector;

using std::cout;
using std::endl;
using std::ostream;

void show(const vector<pair<vector<bool>,vector<bool>>>& v) {
    for(int i = 0; i < v.size(); i++) {
        cout << "{";
        for(int j = 0; j < v[i].first.size(); j++) {
            cout << v[i].first[j];
            if (j != v[i].first.size() - 1) cout << " ";
            else cout << "}, {";
        }
        for(int j = 0; j < v[i].second.size(); j++) {
            cout << v[i].second[j];
            if (j != v[i].second.size() - 1) cout << " ";
            else cout << "}" << endl;
        }
    }
}

vector<bool> GenerateTwoNums(int x, int y, int digit) {
    vector<bool> result;
    for(int i = 0; i < digit; i++) {
        result.push_back(static_cast<bool>(x & (1 << i)));
    }
    for(int i = 0; i < digit; i++) {
        result.push_back(static_cast<bool>(y & (1 << i)));
    }
    return result;
}

TEST(LogicCalTest, BitNot) {
    PinBoard mother(20,8,8);
    BitNot::CreateChip(
            mother,
            GetVectorPart(0,8),
            GetVectorPart(8,8)
            );
    vector<pair<vector<bool>, vector<bool>>> test_cases;
    for(int i = 0; i < (1 << 8); i++) {
        test_cases.push_back({NumberToPins(i,8), NumberToPins(~i,8)});
    }
    TestChipLogic(mother, test_cases, 20);
}

TEST(LogicCalTest, BitAnd) {
    PinBoard mother(100,16,8);
    BitAnd::CreateChip(
            mother,
            GetVectorPart(0,8),
            GetVectorPart(8,8),
            GetVectorPart(16,8)
            );
    vector<pair<vector<bool>, vector<bool>>> test_cases;
    for(int i = 0; i < (1 << 8); i++) {
        for(int j = 0; j < (1 << 8); j++) {
            test_cases.push_back({GenerateTwoNums(i,j,8), NumberToPins(i & j,8)});
        }
    }
    TestChipLogic(mother, test_cases, 100);
}

}   // namespace
