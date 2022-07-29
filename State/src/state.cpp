#include <iostream>
#include <sstream>
#include "state.h"

GumballMachine::GumballMachine(int count_): count(count_)
{
    if (count > 0)
    {
        state = static_cast<int>(states::NO_QUARTER);
    }
}

void GumballMachine::insertQuarter()
{
    switch (state)
    {
    case static_cast<int>(states::HAS_QUARTER):
        std::cout << "You can’t insert another quarter" << std::endl;
        break;
    case static_cast<int>(states::NO_QUARTER):
        state = static_cast<int>(states::HAS_QUARTER);
        std::cout << "You inserted a quarter" << std::endl;
        break;
    case static_cast<int>(states::SOLD_OUT):
        std::cout << "You can’t insert a quarter, the machine is sold out" << std::endl;
        break;
    case static_cast<int>(states::SOLD):
        std::cout << "Please wait, we’re already giving you a gumball" << std::endl;
        break;
    }
}

void GumballMachine::ejectQuarter()
{
    switch (state)
    {
    case static_cast<int>(states::HAS_QUARTER):
        std::cout << "Quarter returned" << std::endl;
        state = static_cast<int>(states::NO_QUARTER);
        break;
    case static_cast<int>(states::NO_QUARTER):
        std::cout << "You haven’t inserted a quarter" << std::endl;
        break;
    case static_cast<int>(states::SOLD_OUT):
        std::cout << "You can’t eject, you haven’t inserted a quarter yet" << std::endl;
        break;
    case static_cast<int>(states::SOLD):
        std::cout << "You can’t eject, you haven’t inserted a quarter yet" << std::endl;
        break;
    }
}

void GumballMachine::turnCrank()
{
    switch (state)
    {
    case static_cast<int>(states::HAS_QUARTER):
        std::cout << "You turned..." << std::endl;
        state = static_cast<int>(states::SOLD);
        dispense();
        break;
    case static_cast<int>(states::NO_QUARTER):
        std::cout << "You turned but there’s no quarter" << std::endl;
        break;
    case static_cast<int>(states::SOLD_OUT):
        std::cout << "You turned, but there are no gumballs" << std::endl;
        break;
    case static_cast<int>(states::SOLD):
        std::cout << "Turning twice doesn’t get you another gumball!" << std::endl;
        break;
    }
}

void GumballMachine::dispense()
{
    switch (state)
    {
    case static_cast<int>(states::HAS_QUARTER):
        std::cout << "No gumball dispensed" << std::endl;
        break;
    case static_cast<int>(states::NO_QUARTER):
        std::cout << "You need to pay first" << std::endl;
        break;
    case static_cast<int>(states::SOLD_OUT):
        std::cout << "No gumball dispensed" << std::endl;
        break;
    case static_cast<int>(states::SOLD):
        std::cout << "A gumball comes rolling out the slot" << std::endl;
        --count;
        if (count == 0)
        {
            std::cout << "Oops, out of gumballs!" << std::endl;
            state = static_cast<int>(states::SOLD_OUT);
        } else {
            state = static_cast<int>(states::NO_QUARTER);
        }
        break;
    default:
        std::cout << "Uncertain state" << std::endl;
    }
}

const char* GumballMachine::state_description(int en) const
{
    switch (en)
    {
    case static_cast<int>(states::HAS_QUARTER):
        return "Machine has quarter\n";
        break;
    case static_cast<int>(states::NO_QUARTER):
        return "Machine is waiting for quarter\n";
        break;
    case static_cast<int>(states::SOLD_OUT):
        return "Machine is sold out\n";
        break;
    case static_cast<int>(states::SOLD):
        return "Machine sold a gumball to you\n";
        break;
    default:
        return "Machine is in uncertain state\n";
    }
}

std::string GumballMachine::toString() const
{
    std::ostringstream info;
    info << "\nMighty Gumball, Inc.\nInventory: " << count << " gumballs\n" << state_description(state);
    return info.str();
}


