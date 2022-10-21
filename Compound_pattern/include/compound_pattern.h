#ifndef COMPOUND_PATTERN_H
#define COMPOUND_PATTERN_H

#include <memory>
#include <iostream>
#include <vector>

class Observer;

class QuackObservable
{
public:
    virtual ~QuackObservable() { }
    virtual void registerObserver(std::shared_ptr<Observer>) = 0;
    virtual void notifyObservers() const = 0;
};

class Observable : public QuackObservable
{
private:
    std::shared_ptr<QuackObservable> duck{nullptr};
    std::vector<std::shared_ptr<Observer>> observers;
public:
    Observable(std::shared_ptr<QuackObservable> duck_): duck(duck_) { }
    void registerObserver(std::shared_ptr<Observer> observer) override { observers.push_back(observer); }
    void notifyObservers() const override;
};

class Quackable : public QuackObservable
{
public:
    virtual ~Quackable() { }
    virtual void quack() const = 0;
};

class MallardDuck : public Quackable, public std::enable_shared_from_this<MallardDuck>
{
private:
    std::shared_ptr<Observable> observable{nullptr};
public:
    MallardDuck();
    void quack() const override { std::cout << "Quack" << std::endl; }
    void registerObserver(std::shared_ptr<Observer> observer) override
};

class RedheadDuck : public Quackable
{
public:
    void quack() const override { std::cout << "Quack" << std::endl; }
};

class DuckCall : public Quackable
{
public:
    void quack() const override { std::cout << "Kwak" << std::endl; }
};

class RubberDuck : public Quackable
{
public:
    void quack() const override { std::cout << "Squeak" << std::endl; }
};

class Honkable
{
public:
    virtual ~Honkable() { }
    virtual void honk() const = 0;
};

class OrdinaryGoose : public Honkable
{
public:
    void honk() const override { std::cout << "Honk" << std::endl; }
};

class GooseAdapter : public Quackable
{
private:
    std::shared_ptr<Honkable> goose{nullptr};
public:
    GooseAdapter(std::shared_ptr<Honkable> goose_): goose(goose_) { }
    void quack() const override { goose->honk(); }
};

class QuackCounter : public Quackable
{
private:
    std::shared_ptr<Quackable> duck{nullptr};
    static int numberOfQuacks;
public:
    QuackCounter(std::shared_ptr<Quackable> duck_): duck(duck_) { }
    void quack() const override { duck->quack(); ++numberOfQuacks; }
    static int getQuacks() { return numberOfQuacks; }
};

class AbstractDuckFactory
{
public:
    virtual ~AbstractDuckFactory() { }
    virtual std::shared_ptr<Quackable> createMallardDuck() const = 0;
    virtual std::shared_ptr<Quackable> createRedheadDuck() const = 0;
    virtual std::shared_ptr<Quackable> createDuckCall() const = 0;
    virtual std::shared_ptr<Quackable> createRubberDuck() const = 0;
    virtual std::shared_ptr<Quackable> createOrdinaryGooseDuck() const = 0;
};

class DuckFactory : public AbstractDuckFactory
{
public:
    std::shared_ptr<Quackable> createMallardDuck() const override { return std::make_shared<MallardDuck>(); }
    std::shared_ptr<Quackable> createRedheadDuck() const override { return std::make_shared<RedheadDuck>(); }
    std::shared_ptr<Quackable> createDuckCall() const override { return std::make_shared<DuckCall>(); }
    std::shared_ptr<Quackable> createRubberDuck() const override { return std::make_shared<RubberDuck>(); }
    std::shared_ptr<Quackable> createOrdinaryGooseDuck() const override { return std::make_shared<GooseAdapter>(std::make_shared<OrdinaryGoose>()); }
};

class CountingDuckFactory : public AbstractDuckFactory
{
public:
    std::shared_ptr<Quackable> createMallardDuck() const override { return std::make_shared<QuackCounter>(std::make_shared<MallardDuck>()); }
    std::shared_ptr<Quackable> createRedheadDuck() const override { return std::make_shared<QuackCounter>(std::make_shared<RedheadDuck>()); }
    std::shared_ptr<Quackable> createDuckCall() const override { return std::make_shared<QuackCounter>(std::make_shared<DuckCall>()); }
    std::shared_ptr<Quackable> createRubberDuck() const override { return std::make_shared<QuackCounter>(std::make_shared<RubberDuck>()); }
    std::shared_ptr<Quackable> createOrdinaryGooseDuck() const override { return std::make_shared<GooseAdapter>(std::make_shared<OrdinaryGoose>()); }
};

class Flock : public Quackable
{
private:
    std::vector<std::shared_ptr<Quackable>> quackers;
public:
    void add(std::shared_ptr<Quackable> quacker) { quackers.push_back(quacker); }
    void quack() const override;
};

class AbstractGooseFactory
{
public:
    virtual ~AbstractGooseFactory() { }
    virtual std::shared_ptr<Honkable> createOrdinaryGoose() const = 0;

};

class GooseFactory : public AbstractGooseFactory
{
public:
    std::shared_ptr<Honkable> createOrdinaryGoose() const override { return std::make_shared<OrdinaryGoose>(); }
};

class AbstractGooseDuckFactory
{
public:
    virtual ~AbstractGooseDuckFactory() { }
    virtual std::shared_ptr<Quackable> createOrdinaryGooseDuck() const = 0;
};

class GooseDuckFactory : public AbstractGooseDuckFactory
{
public:
    std::shared_ptr<Quackable> createOrdinaryGooseDuck() const override { return std::make_shared<GooseAdapter>(std::make_shared<OrdinaryGoose>()); }
};

class DuckSimulator
{
private:
    void simulate(std::shared_ptr<Quackable> duck) { duck->quack(); }
public:
    void simulate(std::shared_ptr<AbstractDuckFactory>);
};

class GooseSimulator
{
private:
    void simulate(std::shared_ptr<Honkable> goose) { goose->honk(); }
public:
    void simulate(std::shared_ptr<AbstractGooseFactory>);
};

class GooseDuckSimulator
{
private:
    void simulate(std::shared_ptr<Quackable> gooseDuck) { gooseDuck->quack(); }
public:
    void simulate(std::shared_ptr<AbstractGooseDuckFactory>);
};
#endif // COMPOUND_PATTERN_H
