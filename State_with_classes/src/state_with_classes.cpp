#include <sstream>
#include "state_with_classes.h"

std::shared_ptr<GumballMachine> GumballMachine::get_ptr(int numberGumballs)
{
    std::shared_ptr<GumballMachine> shared_this(nullptr, [] (GumballMachine*) { std::cout << "Shared_this destructor called" << std::endl; });
    std::shared_ptr<GumballMachine>(new GumballMachine(numberGumballs, shared_this), [] (GumballMachine*) { });
    return shared_this;
}

GumballMachine::GumballMachine(int numberGumballs, std::shared_ptr<GumballMachine>& self_ptr): count(numberGumballs)
{
    auto lambda_deleter = [this] (GumballMachine* gumballMachine)
    {
        if (weak_from_this().expired())
        {
            return ;
        }
        delete gumballMachine;
    };
    auto self_shared = std::shared_ptr<GumballMachine>(this, lambda_deleter);
    self_ptr.reset(this);
    //auto self_shared = std::shared_ptr<GumballMachine>(this);
    soldOutState = std::make_shared<SoldOutState>(shared_from_this());
    noQuarterState = std::make_shared<NoQuarterState>(shared_from_this());
    //hasQuarterState = std::make_shared<HasQuarterState>(shared_from_this());
    //soldState = std::make_shared<SoldState>(shared_from_this());
    //winnerState = std::make_shared<WinnerState>(shared_from_this());
    //soldOutState.reset(new SoldOutState(self_shared));
    //noQuarterState.reset(new NoQuarterState(self_shared));
    //hasQuarterState.reset(new HasQuarterState(self_shared));
    //soldState.reset(new SoldState(self_shared));
    //winnerState.reset(new WinnerState(self_shared));

    /*if (count > 0)
    {
        state = noQuarterState;
    } else {
        state = soldOutState;
    }*/
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
    gumballMachine->setState(gumballMachine->getHasQuarterState());
}

void HasQuarterState::ejectQuarter()
{
    std::cout << "Quarter returned" << std::endl;
    gumballMachine->setState(gumballMachine->getNoQuarterState());
}

bool HasQuarterState::turnCrank()
{
    std::cout << "You turned..." << std::endl;
    if (d(gen) == 1 && gumballMachine->getCount() > 1)
    {
        gumballMachine->setState(gumballMachine->getWinnerState());
    } else {
        gumballMachine->setState(gumballMachine->getSoldState());
    }
    return true;
}

void SoldState::dispense()
{
    gumballMachine->releaseBall();
    State::dispense(gumballMachine);
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
    State::dispense(gumballMachine);

}
