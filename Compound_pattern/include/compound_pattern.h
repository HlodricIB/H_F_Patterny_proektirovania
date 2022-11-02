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
    std::weak_ptr<QuackObservable> duck;
    std::vector<std::shared_ptr<Observer>> observers;
public:
    Observable(std::weak_ptr<QuackObservable> duck_): duck(duck_) { }
    void registerObserver(std::shared_ptr<Observer> observer) override { observers.push_back(observer); }
    void notifyObservers() const override;
    void view() { duck.lock(); }
};

class Quackable : public QuackObservable
{
public:
    virtual ~Quackable() { }
    virtual void quack() const = 0;
};

class Observer
{
public:
    ~Observer() { }
    virtual void update(std::shared_ptr<QuackObservable>) = 0;
};

class Quackologist : public Observer
{
public:
    void update(std::shared_ptr<QuackObservable> duck) override { std::cout << "Quackologist: " << duck << " just quacked."; }
};

class MallardDuck : public Quackable, public std::enable_shared_from_this<MallardDuck>
{
private:
    std::shared_ptr<Observable> observable{nullptr};
    MallardDuck(std::shared_ptr<MallardDuck>& self_ptr) { self_ptr = std::shared_ptr<MallardDuck>(this); observable = std::make_shared<Observable>(self_ptr); };
public:
    static std::shared_ptr<MallardDuck> get_instance();
    void quack() const override { std::cout << "Quack" << std::endl; notifyObservers(); }
    void registerObserver(std::shared_ptr<Observer> observer) override { observable->registerObserver(observer); }
    void notifyObservers() const override { observable->notifyObservers(); }
    void view() { observable->view(); }
};

class RedheadDuck : public Quackable, public std::enable_shared_from_this<RedheadDuck>
{
private:
    std::shared_ptr<Observable> observable{nullptr};
public:
    RedheadDuck();
    void quack() const override { std::cout << "Quack" << std::endl; notifyObservers();  }
    void registerObserver(std::shared_ptr<Observer> observer) override { observable->registerObserver(observer); }
    void notifyObservers() const override { observable->notifyObservers(); }
};

class DuckCall : public Quackable, public std::enable_shared_from_this<DuckCall>
{
private:
    std::shared_ptr<Observable> observable{nullptr};
public:
    DuckCall();
    void quack() const override { std::cout << "Kwak" << std::endl; notifyObservers();  }
    void registerObserver(std::shared_ptr<Observer> observer) override { observable->registerObserver(observer); };
    void notifyObservers() const override { observable->notifyObservers(); }
};

class RubberDuck : public Quackable, public std::enable_shared_from_this<RubberDuck>
{
private:
    std::shared_ptr<Observable> observable{nullptr};
public:
    RubberDuck();
    void quack() const override { std::cout << "Squeak" << std::endl; notifyObservers();  }
    void registerObserver(std::shared_ptr<Observer> observer) override { observable->registerObserver(observer); };
    void notifyObservers() const override { observable->notifyObservers(); }
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
    void registerObserver(std::shared_ptr<Observer>) override { std::cout << "At this moment there were no orders for observing gooses,"
                                                                                        " so this method for honkable is not implemented yet" << std::endl; }
    void notifyObservers() const override { std::cout << "At this moment there were no orders for observing gooses,"
                                                                                        " so this method for honkable is not implemented yet" << std::endl; }
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
    void registerObserver(std::shared_ptr<Observer> observer) override { duck->registerObserver(observer); }
    void notifyObservers() const override { duck->notifyObservers(); }
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
    std::shared_ptr<Quackable> createMallardDuck() const override { /*return std::make_shared<MallardDuck>();*/ return MallardDuck::get_instance(); }
    std::shared_ptr<Quackable> createRedheadDuck() const override { return std::make_shared<RedheadDuck>(); }
    std::shared_ptr<Quackable> createDuckCall() const override { return std::make_shared<DuckCall>(); }
    std::shared_ptr<Quackable> createRubberDuck() const override { return std::make_shared<RubberDuck>(); }
    std::shared_ptr<Quackable> createOrdinaryGooseDuck() const override { return std::make_shared<GooseAdapter>(std::make_shared<OrdinaryGoose>()); }
};

class CountingDuckFactory : public AbstractDuckFactory
{
public:
    std::shared_ptr<Quackable> createMallardDuck() const override { return std::make_shared<QuackCounter>(MallardDuck::get_instance()); }
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
    void registerObserver(std::shared_ptr<Observer>) override;
    void notifyObservers() const override { };
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
