#ifndef PINBOARD_H
#define PINBOARD_H

#include <vector>

class Chip;
class PinBoard {
public:
    PinBoard(size_t n);
    ~PinBoard() = default;
    PinBoard(const PinBoard&) = delete;
    PinBoard(PinBoard&&) = delete;
    PinBoard& operator= (const PinBoard&) = delete;
    PinBoard& operator= (PinBoard&&) = delete;

    void Tick();
    bool GetPin(int);
    void SetPin(int, bool);

private:
    vector<int64_t> current_status;
    vector<int64_t> next_status;
    vector<Chip*> chips;
}

class Chip {
public:
    virtual void Tick() = 0;
}



#endif // #define PINBOARD_H
