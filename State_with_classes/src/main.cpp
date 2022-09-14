#include <iostream>
#include "state_with_classes.h"

#include <sstream>

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
    std::cout <<gumballMachine->toString() << std::endl;
    return 0;
}
