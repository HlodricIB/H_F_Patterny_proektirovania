#include "state_with_classes.h"

#include <random>
#include <map>
#include <iostream>
#include <iomanip>

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d({90, 10});
    std::map<int, int> map;
    for(int n=0; n<10000; ++n)
    {
        ++map[d(gen)];
    }
    for(const auto& [num, count] : map)
    {
        std::cout << num << " generated " << std::setw(4) << count << " times\n";
    }
    return 0;
}
