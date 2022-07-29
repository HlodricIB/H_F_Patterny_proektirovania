#ifndef STATE_H
#define STATE_H

#include<string>

class GumballMachine
{
private:
    enum class states : int
    {
        SOLD_OUT,
        NO_QUARTER,
        HAS_QUARTER,
        SOLD
    };
    int state{static_cast<int>(states::SOLD_OUT)};
    int count{0};
    void dispense();
    const char* state_description(int) const;
public:
    GumballMachine(int);
    void insertQuarter();
    void ejectQuarter();
    void turnCrank();
    std::string toString() const;
};

#endif // STATE_H
