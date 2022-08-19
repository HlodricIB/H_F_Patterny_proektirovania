#include "state_with_classes.h"

#include <random>
#include <map>
#include <iostream>
#include <iomanip>

int main()
{
    //auto gumballMachine = std::make_shared<GumballMachine>(5);
    auto gumballMachine = GumballMachine::get_ptr(5);
    //gumballMachine.reset();
    //std::cout <<gumballMachine->toString() << std::endl;
    /*gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    std::cout <<gumballMachine.toString() << std::endl;
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();*/
    return 0;
}
