#include <iostream>
#include "state.h"

int main()
{
    GumballMachine gumballMachine(5);

    std::cout << gumballMachine.toString() << std::endl;

    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();

    std::cout << gumballMachine.toString() << std::endl;

    gumballMachine.insertQuarter();
    gumballMachine.ejectQuarter();
    gumballMachine.turnCrank();

    std::cout << gumballMachine.toString() << std::endl;

    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.ejectQuarter();

    std::cout << gumballMachine.toString() << std::endl;

    gumballMachine.insertQuarter();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();

    std::cout << gumballMachine.toString() << std::endl;
    return 0;
}
