#ifndef STRATEGY_DUCKS_H
#define STRATEGY_DUCKS_H

#include <iostream>
#include <memory>

class FlyBehavior
{
public:
    FlyBehavior() { };
    virtual ~FlyBehavior() { };
    virtual void fly() const = 0;
};

class FlyWithWings : public FlyBehavior
{
public:
    void fly() const override { std::cout << "I'm flying!" << std::endl; }
};

class FlyNoWay : public FlyBehavior
{
public:
    void fly() const override { std::cout << "I can't fly" << std::endl; }
};

class FlyRocketPowered : public FlyBehavior
{
    void fly() const override { std::cout << "I'm flying with a rocket!" << std::endl; }
};

class QuackBehavior
{
public:
    QuackBehavior() { };
    virtual ~QuackBehavior() { };
    virtual void quack() const = 0;
};

class Quack : public QuackBehavior
{
public:
    void quack() const override { std::cout << "Quack" << std::endl; }
};

class MuteQuack : public QuackBehavior
{
public:
    void quack() const override { std::cout << "<< Silence >>" << std::endl; }
};

class Squeak : public QuackBehavior
{
public:
    void quack() const override { std::cout << "Squeak" << std::endl; }
};


class Duck
{
private:
    std::shared_ptr<FlyBehavior> flyBehavior{nullptr};
    std::shared_ptr<QuackBehavior> quackBehavior{nullptr};
protected:
    void setflyBehavior(std::shared_ptr<FlyBehavior> FB) { flyBehavior = FB; }
    void setquackBehavior(std::shared_ptr<QuackBehavior> QB) { quackBehavior = QB; }
public:
    Duck() { };
    virtual ~Duck() { };
    void performQuack() const { quackBehavior->quack(); };
    void swim() const { std::cout << "All ducks float, even decoys!" << std::endl; };
    virtual void display() const = 0;
    void performFly() const { flyBehavior->fly(); };
    void setFlyBehavior(std::shared_ptr<FlyBehavior> fb) { flyBehavior = fb; }
    void setQuackBehavior(std::shared_ptr<QuackBehavior> qb) { quackBehavior = qb; }
};

class MallardDuck : public Duck
{
public:
    MallardDuck(): Duck() {
        setflyBehavior(std::make_shared<FlyWithWings>());
        setquackBehavior(std::make_shared<Quack>());
    }
    void display() const override { std::cout << "I'm a real Mallard duck!" << std::endl; }
};

class ModelDuck : public Duck
{
public:
    ModelDuck() {
        setflyBehavior(std::make_shared<FlyNoWay>());
        setquackBehavior(std::make_shared<Quack>());
    }
    void display() const override { std::cout << "I'm a model duck!" << std::endl; }
};

#endif // STRATEGY_DUCKS_H
