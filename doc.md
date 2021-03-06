In this project, we will implement a PinBoard class. This class has following functionalities.
1. There could be multiple chips on a PinBoard. Each chip has corresponding  (multiple) input pins and output pins. 
2. Given the current status of each pin on the board, we should be able to get the status of them at the end of each tick.

```c++
class PinBoard {
public:
    void Tick();    // this funcion calculates the next_status according to current_status.
    bool GetPin(int);    // get the status of the pin #?
    void SetPin(int, bool)   // set the status of pin #? to bool?

private:
    vector<int64_t> current_status;    // the current status(before each tick)
    vector<int64_t> next_status;    // the status after each tick
    vector<Chip*> chips;     // a list of chips that sitting on the board.
}
```

```c++
class Chip {
public:
    virtual void Tick() = 0;
}

class SomeChip : virtual public Chip {
public:
    void Tick();        // use mother->GetStatus and mother->SetStatus to change. the chip itself does not store any status.
private:
    vector<int> input_pin;  // where input pins locate.
    vector<int> output_pin; // where output pins locate.
    PinBoard* mother;       // where the chip sits on.
}
```
