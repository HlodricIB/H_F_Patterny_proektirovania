#ifndef ADAPTER_H
#define ADAPTER_H

#include <iostream>
#include <memory>

class Duck
{
public:
    virtual void quack() = 0;
    virtual void fly() = 0;
};

class MallardDuck : public Duck
{
public:
    void quack() override { std::cout << "Quack"; }
    void fly() override { std::cout << "I'm flying"; }
};

class Turkey
{
public:
    virtual void gobble() = 0;
    virtual void fly() = 0;
};

class WildTurkey : public Turkey
{
public:
    void gobble() override { std::cout << "Gobble gobble"; }
    void fly() override { std::cout << "I’m flying a short distance" ; }
};

class TurkeyAdapter : public Duck
{
private:
    std::shared_ptr<Turkey> turkey;
public:
    TurkeyAdapter(std::shared_ptr<Turkey> turkey_): turkey(turkey_) { }
    void quack() override { turkey->gobble(); }
    void fly() override {
        for (int i = 0; i !=5; ++i)
        {
            turkey->fly();
            std::cout << '\n';
        }
    }
};

#endif // ADAPTER_H
