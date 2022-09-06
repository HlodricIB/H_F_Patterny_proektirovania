#include <iostream>
#include "state_with_classes.h"

#include <sstream>

int main()
{
    auto gumballMachine = GumballMachine::get_ptr(5);
    auto buf_pointer = std::cout.rdbuf();
    std::cout << static_cast<bool>(buf_pointer) << std::endl;
    std::cout << reinterpret_cast<std::basic_streambuf<char>*>(buf_pointer) << std::endl;
    //std::cout << buf_pointer->pubseekoff(0, std::_S_cur, std::_Ios_Openmode::_S_out) << "First position" << buf_pointer->pubseekoff(0, std::_S_cur, std::_Ios_Openmode::_S_out) << std::endl;
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
