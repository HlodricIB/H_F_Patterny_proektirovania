#include "compound_pattern.h"

int QuackCounter::numberOfQuacks = 0;

void DuckSimulator::simulate(std::shared_ptr<AbstractDuckFactory> duckFactory)
{
    auto redheadDuck = duckFactory->createRedheadDuck();
    auto duckCall = duckFactory->createDuckCall();
    auto rubberDuck = duckFactory->createRubberDuck();
    auto gooseDuck = duckFactory->createOrdinaryGooseDuck();
    std::cout << "Duck Simulator: With Composite — Flocks" << std::endl;

    std::shared_ptr<Flock> flockOfDucks = std::make_shared<Flock>();

    flockOfDucks->add(redheadDuck);
    flockOfDucks->add(duckCall);
    flockOfDucks->add(rubberDuck);
    flockOfDucks->add(gooseDuck);

    std::shared_ptr<Flock> flockOfMallards = std::make_shared<Flock>();

    auto mallardOne = duckFactory->createMallardDuck();
    auto mallardTwo = duckFactory->createMallardDuck();
    auto mallardThree = duckFactory->createMallardDuck();
    auto mallardFour = duckFactory->createMallardDuck();

    flockOfMallards->add(mallardOne);
    flockOfMallards->add(mallardTwo);
    flockOfMallards->add(mallardThree);
    flockOfMallards->add(mallardFour);

    flockOfDucks->add(flockOfMallards);

    std::cout << "\nDuck Simulator: Whole Flock Simulation" << std::endl;
    flockOfDucks->quack();

    std::cout << "\nDuck Simulator: Mallard Flock Simulation" << std::endl;
    flockOfMallards->quack();

    std::cout << "\nThe ducks quacked " << QuackCounter::getQuacks() << " times\n" << std::endl;
}

MallardDuck::MallardDuck()
{
    auto self_ptr = std::shared_ptr<MallardDuck>(this);
    observable = std::make_shared<Observable>(shared_from_this());
}

void Flock::quack() const
{
    for (auto& quacker : quackers)
    {
        quacker->quack();
    }
}

void Observable::notifyObservers() const
{
    for (auto& observer : observers)
    {
        observer->update(duck);
    }
}

void GooseDuckSimulator::simulate(std::shared_ptr<AbstractGooseDuckFactory> gooseDuckFactory)
{
    auto gooseDuck = gooseDuckFactory->createOrdinaryGooseDuck();

    std::cout << "GooseDuck Simulator: With Abstract Factory" << std::endl;

    simulate(gooseDuck);
}

void GooseSimulator::simulate(std::shared_ptr<AbstractGooseFactory> gooseFactory)
{
    auto ordinaryGoose = gooseFactory->createOrdinaryGoose();

    std::cout << "Goose Simulator: With Abstract Factory" << std::endl;

    simulate(ordinaryGoose);
}
