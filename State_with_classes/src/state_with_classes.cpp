#include <sstream>
#include "state_with_classes.h"

GumballMachine::GumballMachine(int numberGumballs_, std::shared_ptr<State> soldOutState_, std::shared_ptr<State> noQuarterState_, std::shared_ptr<State> hasQuarterState_,
               std::shared_ptr<State> soldState_):
    soldOutState(soldOutState_), noQuarterState(noQuarterState_), hasQuarterState(hasQuarterState_), soldState(soldState_), count(numberGumballs_)
{
    if (count > 0)
    {
        state = noQuarterState;
    } else {
        state = soldOutState;
    }
}

void GumballMachine::releaseBall()
{
    std::cout << "A gumball comes rolling out the slot..." << std::endl;
    if (count > 0)
    {
        --count;
    }
}

void GumballMachine::refill(int count_)
{
    count += count_;
    std::cout << "The gumball machine was just refilled; it's new count is: " << count << std::endl;
    state->refill();
}

std::string GumballMachine::toString() const
{
    std::ostringstream info;
    info << "\nMighty Gumball, Inc.\nInventory: " << count << " gumballs\n" << state->toString();
    return info.str();
}

void State::dispense()
{

}

void NoQuarterState::insertQuarter()
{
    std::cout << "You inserted a quarter" << std::endl;
    gumballMachine->setState(gumballMachine->getHasQuarterState());
}

void HasQuarterState::ejectQuarter()
{
    std::cout << "Quarter returned" << std::endl;
    gumballMachine->setState(gumballMachine->getNoQuarterState());
}

void HasQuarterState::turnCrank()
{
    std::cout << "You turned..." << std::endl;
    if (d(gen) == 1 && gumballMachine->getCount() > 1)
    {
        gumballMachine->setState(gumballMachine->getWinnerState());
        return ;
    }
    gumballMachine->setState(gumballMachine->getSoldState());
}

void SoldState::dispense()
{
    gumballMachine->releaseBall();
    if (gumballMachine->getCount() > 0)
    {
        gumballMachine->setState(gumballMachine->getNoQuarterState());
    } else {
        std::cout << "Oops, out of gumballs!" << std::endl;
        gumballMachine->setState(gumballMachine->getSoldOutState());
    }
}

void SoldOutState::refill()
{
    if (gumballMachine->getCount() > 0)
    {
        gumballMachine->setState(gumballMachine->getNoQuarterState());
    }
}

void WinnerState::dispense()
{
    gumballMachine->releaseBall();
    gumballMachine->releaseBall();
    std::cout << "YOU’RE A WINNER! You got two gumballs for your quarter" << std::endl;
    if (gumballMachine->getCount() > 0)
    {
        gumballMachine->setState(gumballMachine->getNoQuarterState());
    } else {
        std::cout << "Oops, out of gumballs!" << std::endl;
        gumballMachine->setState(gumballMachine->getSoldOutState());
    }
}
