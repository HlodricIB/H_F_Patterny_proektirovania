#ifndef STATE_WITH_CLASSES_H
#define STATE_WITH_CLASSES_H

#include <memory>
#include <iostream>
#include <random>

class GumballMachine;

class State
{
protected:
    void dispense(std::shared_ptr<GumballMachine>);
public:
    virtual void insertQuarter() { std::cout << "Please wait, we’re already giving you a gumballs" << std::endl; }
    virtual void ejectQuarter() { std::cout << "Sorry, you already turned the crank" << std::endl; }
    virtual bool turnCrank() { std::cout << "Turning twice doesn’t get you another gumball!" << std::endl; return false; }
    virtual void dispense() = 0;
    virtual void refill() { }
    virtual std::string toString() const = 0;
};

class GumballMachine : public std::enable_shared_from_this<GumballMachine>
{
private:
    GumballMachine(int, std::shared_ptr<GumballMachine>&);
    std::shared_ptr<State> soldOutState{nullptr};
    std::shared_ptr<State> noQuarterState{nullptr};
    std::shared_ptr<State> hasQuarterState{nullptr};
    std::shared_ptr<State> soldState{nullptr};
    std::shared_ptr<State> winnerState{nullptr};
    std::shared_ptr<State> state{nullptr};
    int count{0};
public:
    static std::shared_ptr<GumballMachine> get_ptr(int);
    ~GumballMachine() { std::cout << "Destructor called" << std::endl; }
    void insertQuarter() { state->insertQuarter(); }
    void ejectQuarter() { state->ejectQuarter(); }
    void turnCrank() { state->turnCrank(); state->dispense(); }
    void setState(std::shared_ptr<State> state_) { state = state_; }
    void releaseBall();
    std::shared_ptr<State> getNoQuarterState() const { return noQuarterState; }
    std::shared_ptr<State> getSoldOutState() const { return soldOutState; }
    std::shared_ptr<State> getHasQuarterState() const { return hasQuarterState; }
    std::shared_ptr<State> getSoldState() const { return soldState; }
    std::shared_ptr<State> getWinnerState() const { return winnerState; }
    int getCount() const { return count; }
    void refill(int);
    std::string toString() const;
};

class NoQuarterState : public State
{
private:
    std::shared_ptr<GumballMachine> gumballMachine{nullptr};
public:
    explicit NoQuarterState(std::shared_ptr<GumballMachine> gumballMachine_): gumballMachine(gumballMachine_) { }
    void insertQuarter() override;
    void ejectQuarter() override { std::cout << "You haven’t inserted a quarter" << std::endl; };
    bool turnCrank() override { std::cout << "You turned, but there’s no quarter" << std::endl; return false;}
    void dispense() override { std::cout << "You need to pay first" << std::endl; }
    //void refill() override { }
    std::string toString() const override { return "Machine is waiting for quarter\n"; }
};

class HasQuarterState : public State
{
private:
    std::shared_ptr<GumballMachine> gumballMachine{nullptr};
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::discrete_distribution<> d{{90, 10}};
public:
    explicit HasQuarterState(std::shared_ptr<GumballMachine> gumballMachine_): gumballMachine(gumballMachine_) { }
    void insertQuarter() override { std::cout << "You can’t insert another quarter" << std::endl; }
    void ejectQuarter() override;
    bool turnCrank() override;
    void dispense() override { std::cout << "You need to pay first" << std::endl; }
    //void refill() override { }
    std::string toString() const override { return "Machine has quarter\n"; }
};

class SoldState : public State
{
private:
    std::shared_ptr<GumballMachine> gumballMachine{nullptr};
public:
    explicit SoldState(std::shared_ptr<GumballMachine> gumballMachine_): gumballMachine(gumballMachine_) { }
    //void insertQuarter() override { std::cout << "Please wait, we’re already giving you a gumball" << std::endl; }
    //void ejectQuarter() override { std::cout << "Sorry, you already turned the crank" << std::endl; }
    //void turnCrank() override { std::cout << "Turning twice doesn’t get you another gumball!" << std::endl; }
    void dispense() override;
    //void refill() override { }
    std::string toString() const override { return "Machine sold a gumball to you\n"; }
};

class SoldOutState : public State
{
private:
    std::shared_ptr<GumballMachine> gumballMachine{nullptr};
public:
    explicit SoldOutState(std::shared_ptr<GumballMachine> gumballMachine_): gumballMachine(gumballMachine_) { }
    void insertQuarter() override { std::cout << "You can’t insert a quarter, the machine is sold out" << std::endl; }
    void ejectQuarter() override { std::cout << "You can’t eject, you haven’t inserted a quarter yet" << std::endl; }
    bool turnCrank() override { std::cout << "You turned, but there are no gumballs" << std::endl; return false;}
    void dispense() override { std::cout << "No gumball dispensed" << std::endl; }
    void refill() override;
    std::string toString() const override { return "Machine is sold out\n"; }

};

class WinnerState : public State
{
private:
    std::shared_ptr<GumballMachine> gumballMachine{nullptr};
public:
    explicit WinnerState(std::shared_ptr<GumballMachine> gumballMachine_): gumballMachine(gumballMachine_) { }
    //void insertQuarter() override { std::cout << "Please wait, we’re already giving you a gumballs" << std::endl; }
    //void ejectQuarter() override { std::cout << "Sorry, you already turned the crank" << std::endl; }
    //void turnCrank() override { std::cout << "Turning twice doesn’t get you another gumball!" << std::endl; }
    void dispense() override;
    //void refill() override { }
    std::string toString() const override { return "Machine in a winner state\n"; }
};

#endif // STATE_WITH_CLASSES_H
