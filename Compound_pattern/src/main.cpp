#include <iostream>
#include "compound_pattern.h"

int main()
{
    DuckSimulator duckSimulator;
    std::shared_ptr<AbstractDuckFactory> duckFactory = std::make_shared<CountingDuckFactory>();
    duckSimulator.simulate(duckFactory);
    GooseDuckSimulator gooseDuckSimulator;
    std::shared_ptr<AbstractGooseDuckFactory> gooseDuckFactory = std::make_shared<GooseDuckFactory>();
    gooseDuckSimulator.simulate(gooseDuckFactory);
    GooseSimulator gooseSimulator;
    std::shared_ptr<AbstractGooseFactory> gooseFactory = std::make_shared<GooseFactory>();
    gooseSimulator.simulate(gooseFactory);
    return 0;
}
