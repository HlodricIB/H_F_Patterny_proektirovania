#ifndef STATE_WITH_CLASSES_H
#define STATE_WITH_CLASSES_H

#include <memory>
#include <iostream>

class State
{
public:
    virtual void insertQuarter() = 0;
    virtual void ejectQuarter() = 0;
    virtual void turnCrank() = 0;
    virtual void dispense() = 0;
    virtual void refill() = 0;
};

class GumballMachine
{
private:
    std::shared_ptr<State> soldOutState{nullptr};
    std::shared_ptr<State> noQuarterState{nullptr};
    std::shared_ptr<State> hasQuarterState{nullptr};
    std::shared_ptr<State> soldState{nullptr};
    std::shared_ptr<State> state{nullptr};
    int count{0};
public:
    GumballMachine(int, std::shared_ptr<State>, std::shared_ptr<State>, std::shared_ptr<State>, std::shared_ptr<State>);
    void insertQuarter() { state->insertQuarter(); }
    void ejectQuarter() { state->ejectQuarter(); }
    void turnCrank() { state->turnCrank(); state->dispense(); }
    void setState(std::shared_ptr<State> state_) { state = state_; }
    void releaseBall();
    std::shared_ptr<State> getNoQuarterState() const { return noQuarterState; }
    std::shared_ptr<State> getSoldOutState() const { return soldOutState; }
    std::shared_ptr<State> getHasQuarterState() const { return hasQuarterState; }
    std::shared_ptr<State> getSoldState() const { return soldState; }
    void refill(int);
};

class NoQuarterState : public State
{
private:
    std::shared_ptr<GumballMachine> gumballMachine{nullptr};
public:
    explicit NoQuarterState(std::shared_ptr<GumballMachine> gumballMachine_): gumballMachine(gumballMachine_) { }
    void insertQuarter() override;
    void ejectQuarter() override { std::cout << "You haven’t inserted a quarter" << std::endl; };
    void turnCrank() override { std::cout << "You turned, but there’s no quarter" << std::endl; }
    void dispense() override { std::cout << "You need to pay first" << std::endl; }
    void refill() override { }
};

class HasQuarterState : public State
{
private:
    std::shared_ptr<GumballMachine> gumballMachine{nullptr};
public:
    explicit HasQuarterState(std::shared_ptr<GumballMachine> gumballMachine_): gumballMachine(gumballMachine_) { }
    void insertQuarter() override { std::cout << "You can’t insert another quarter" << std::endl; };

    void ejectQuarter() override;
    void turnCrank() override;
    void dispense() override { std::cout << "You need to pay first" << std::endl; }
    void refill() override { }
};

class SoldState : public State
{
private:
    std::shared_ptr<GumballMachine> gumballMachine{nullptr};
public:
    explicit SoldState(std::shared_ptr<GumballMachine> gumballMachine_): gumballMachine(gumballMachine_) { }

};

class SoldOutState : public State
{
private:
    std::shared_ptr<GumballMachine> gumballMachine{nullptr};
public:
    explicit SoldOutState(std::shared_ptr<GumballMachine> gumballMachine_): gumballMachine(gumballMachine_) { }

};

class WinnerState : public State
{
private:
    std::shared_ptr<GumballMachine> gumballMachine{nullptr};
public:
    explicit WinnerState(std::shared_ptr<GumballMachine> gumballMachine_): gumballMachine(gumballMachine_) { }

};





#endif // STATE_WITH_CLASSES_H
