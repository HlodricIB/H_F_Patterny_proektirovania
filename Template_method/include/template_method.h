#ifndef TEMPLATE_METHOD_H
#define TEMPLATE_METHOD_H

#include <iostream>
#include <string>

class CaffeineBeverageWithHook
{
public:
    virtual ~CaffeineBeverageWithHook() { }
    virtual void prepareRecipe() final;
    virtual void brew() = 0;
    virtual void addCondiments() = 0;
    void boilWater() { std::cout << "Boiling water\n"; }
    void pourInCup() { std::cout << "Pouring into cup\n"; }
    virtual bool customerWantsCondiments() { return true; }
};

bool getCondimentsInfo(const std::string&);

class CoffeeWithHook : public CaffeineBeverageWithHook
{
public:
    void brew() override { std::cout << "Dripping Coffee through filter\n"; }
    void addCondiments() override { std::cout << "Adding Sugar and Milk\n"; }
    bool customerWantsCondiments() override { return getCondimentsInfo("Would you like milk and sugar with your coffee (y/n)? "); }
};

class TeaWithHook : public CaffeineBeverageWithHook
{
public:
    void brew() override { std::cout << "Steeping the tea\n"; }
    void addCondiments() override { std::cout << "Adding Lemon\n"; }
    bool customerWantsCondiments() override { return getCondimentsInfo("Would you like lemon with your tea (y/n)? "); }
};



#endif // TEMPLATE_METHOD_H
