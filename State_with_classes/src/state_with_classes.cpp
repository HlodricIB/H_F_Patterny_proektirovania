#include <sstream>
#include "state_with_classes.h"

std::shared_ptr<GumballMachine> GumballMachine::get_ptr(int numberGumballs)
{
    std::shared_ptr<GumballMachine> self_ptr(nullptr);
    auto self = std::shared_ptr<GumballMachine>(new GumballMachine(numberGumballs, self_ptr), [] (GumballMachine*) { });
    return self_ptr;
}

GumballMachine::GumballMachine(int numberGumballs, std::shared_ptr<GumballMachine>& self_ptr): count(numberGumballs)
{
    self_ptr = std::shared_ptr<GumballMachine>(this);
    soldOutState = std::make_shared<SoldOutState>(weak_from_this());
    noQuarterState = std::make_shared<NoQuarterState>(weak_from_this());
    hasQuarterState = std::make_shared<HasQuarterState>(weak_from_this());
    soldState = std::make_shared<SoldState>(weak_from_this());
    winnerState = std::make_shared<WinnerState>(weak_from_this());
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

void State::dispense(std::shared_ptr<GumballMachine> gumballMachine)
{
    if (gumballMachine->getCount() > 0)
    {
        gumballMachine->setState(gumballMachine->getNoQuarterState());
    } else {
        std::cout << "Oops, out of gumballs!" << std::endl;
        gumballMachine->setState(gumballMachine->getSoldOutState());
    }
}

void NoQuarterState::insertQuarter()
{
    std::cout << "You inserted a quarter" << std::endl;
    gumballMachine.lock()->setState(gumballMachine.lock()->getHasQuarterState());
}

void HasQuarterState::ejectQuarter()
{
    std::cout << "Quarter returned" << std::endl;
    gumballMachine.lock()->setState(gumballMachine.lock()->getNoQuarterState());
}

bool HasQuarterState::turnCrank()
{
    std::cout << "You turned..." << std::endl;
    if (d(gen) == 1 && gumballMachine.lock()->getCount() > 1)
    {
        gumballMachine.lock()->setState(gumballMachine.lock()->getWinnerState());
    } else {
        gumballMachine.lock()->setState(gumballMachine.lock()->getSoldState());
    }
    return true;
}

void SoldState::dispense()
{
    gumballMachine.lock()->releaseBall();
    State::dispense(gumballMachine.lock());
}

void SoldOutState::refill()
{
    if (gumballMachine.lock()->getCount() > 0)
    {
        gumballMachine.lock()->setState(gumballMachine.lock()->getNoQuarterState());
    }
}

void WinnerState::dispense()
{
    gumballMachine.lock()->releaseBall();
    gumballMachine.lock()->releaseBall();
    std::cout << "YOU’RE A WINNER! You got two gumballs for your quarter" << std::endl;
    State::dispense(gumballMachine.lock());

}
