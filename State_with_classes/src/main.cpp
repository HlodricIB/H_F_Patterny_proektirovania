#include <iostream>
#include "state_with_classes.h"

int main()
{
    auto gumballMachine = GumballMachine::get_ptr(5);
    std::cout <<gumballMachine->toString() << std::endl;
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    std::cout <<gumballMachine->toString() << std::endl;
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    gumballMachine->insertQuarter();
    gumballMachine->turnCrank();
    return 0;
}
