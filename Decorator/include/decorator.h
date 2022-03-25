#ifndef DECORATOR_H
#define DECORATOR_H

#include <string>
#include <memory>

class Beverage
{
private:
    std::string description;
public:
    Beverage(): description("Unknown beverage") {}
    Beverage(const char* description_): description(description_) { }
    std::string getDescription() const { return description; }
    virtual double cost() const = 0;
    virtual ~Beverage() { }
};

class CondimentDecorator : public Beverage
{
public:
    CondimentDecorator() { }
    virtual std::string getDescription() const = 0;
};

class Espresso : public Beverage
{
public:
    Espresso(): Beverage("Espresso") { }
    double cost() const override { return 1.99; }
};

class HouseBlend : public Beverage
{
public:
    HouseBlend(): Beverage("House Blend Coffee") { }
    double cost() const override { return 0.89; }
};

class DarkRoast : public Beverage
{
public:
    DarkRoast(): Beverage("Dark Roast Coffee") { }
    double cost() const override { return 0.99; }
};

class Mocha : public CondimentDecorator
{
private:
    std::shared_ptr<Beverage> beverage;
public:
    Mocha(Beverage* beverage_): beverage{beverage_} { }
    std::string getDescription() const override { return beverage->getDescription() + ", Mocha"; }
    double cost() const override { return 0.20 + beverage->cost(); }
};

class Soy : public CondimentDecorator
{
private:
    std::shared_ptr<Beverage> beverage;
public:
    Soy(Beverage* beverage_): beverage{beverage_} { }
    std::string getDescription() const override { return beverage->getDescription() + ", Soy"; }
    double cost() const override { return 0.15 + beverage->cost(); }
};

class Whip : public CondimentDecorator
{
private:
    std::shared_ptr<Beverage> beverage;
public:
    Whip(Beverage* beverage_): beverage{beverage_} { }
    std::string getDescription() const override { return beverage->getDescription() + ", Whip"; }
    double cost() const override { return 0.10 + beverage->cost(); }
};

#endif // DECORATOR_H
