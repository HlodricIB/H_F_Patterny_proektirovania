#include "compound_pattern.h"

int QuackCounter::numberOfQuacks = 0;

void DuckSimulator::simulate(std::shared_ptr<AbstractDuckFactory> duckFactory)
{
    auto redheadDuck = duckFactory->createRedheadDuck();
    auto duckCall = duckFactory->createDuckCall();
    auto rubberDuck = duckFactory->createRubberDuck();
    auto gooseDuck = duckFactory->createOrdinaryGooseDuck();
    std::cout << "Duck Simulator: With Observer" << std::endl;

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

    auto quackologist = std::make_shared<Quackologist>();

    flockOfDucks->registerObserver(quackologist);

    simulate(flockOfDucks);

    std::cout << "\nThe ducks quacked " << QuackCounter::getQuacks() << " times\n" << std::endl;
}

const std::map<std::string, std::string> Quackologist::duck_types {
    {"MallardDuck", "Mallard Duck"},
    {"RedheadDuck", "Redhead Duck"},
    {"DuckCall", "Duck Call"},
    {"RubberDuck", "Rubber Duck"},
    {"GooseAdapter", "Goose pretending to be a Duck"}
};

void Quackologist::update(std::shared_ptr<QuackObservable> duck)
{
    auto duck_type = boost::typeindex::type_id_runtime(*duck).pretty_name();
    auto event = duck_types.find(duck_type);
    std::cout << "Quackologist: ";
    if (event != duck_types.end())
    {
        std::cout << event->second;
    } else {
        std::cout << "Unknown creature";
    }
    std::cout << " just quacked.\n";
}

MallardDuck::MallardDuck(std::shared_ptr<MallardDuck>& self_ptr)
{
    self_ptr = std::shared_ptr<MallardDuck>(this);
    observable = std::make_shared<Observable>(self_ptr);
}

std::shared_ptr<MallardDuck> MallardDuck::get_instance()
{
    std::shared_ptr<MallardDuck> self_ptr{nullptr};
    new MallardDuck(self_ptr);
    return self_ptr;
}

RedheadDuck::RedheadDuck(std::shared_ptr<RedheadDuck>& self_ptr)
{
    self_ptr = std::shared_ptr<RedheadDuck>(this);
    observable = std::make_shared<Observable>(self_ptr);
}

std::shared_ptr<RedheadDuck> RedheadDuck::get_instance()
{
    std::shared_ptr<RedheadDuck> self_ptr{nullptr};
    new RedheadDuck(self_ptr);
    return self_ptr;
}

DuckCall::DuckCall(std::shared_ptr<DuckCall>& self_ptr)
{
    self_ptr = std::shared_ptr<DuckCall>(this);
    observable = std::make_shared<Observable>(self_ptr);
}

std::shared_ptr<DuckCall> DuckCall::get_instance()
{
    std::shared_ptr<DuckCall> self_ptr{nullptr};
    new DuckCall(self_ptr);
    return self_ptr;
}

RubberDuck::RubberDuck(std::shared_ptr<RubberDuck>& self_ptr)
{
    self_ptr = std::shared_ptr<RubberDuck>(this);
    observable = std::make_shared<Observable>(self_ptr);
}

std::shared_ptr<RubberDuck> RubberDuck::get_instance()
{
    std::shared_ptr<RubberDuck> self_ptr{nullptr};
    new RubberDuck(self_ptr);
    return self_ptr;
}

GooseAdapter::GooseAdapter(std::shared_ptr<Honkable> goose_, std::shared_ptr<GooseAdapter>& self_ptr): goose(goose_)
{
    self_ptr = std::shared_ptr<GooseAdapter>(this);
    observable = std::make_shared<Observable>(self_ptr);
}

std::shared_ptr<GooseAdapter> GooseAdapter::get_instance(std::shared_ptr<Honkable> goose_)
{
    std::shared_ptr<GooseAdapter> self_ptr{nullptr};
    new GooseAdapter(goose_, self_ptr);
    return self_ptr;
}

void Flock::quack() const
{
    for (auto& quacker : quackers)
    {
        quacker->quack();
    }
}

void Flock::registerObserver(std::shared_ptr<Observer> observer)
{
    for (auto& quacker : quackers)
    {
        quacker->registerObserver(observer);
    }
}

void Observable::notifyObservers() const
{
    for (auto& observer : observers)
    {
        observer->update(duck.lock());
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
