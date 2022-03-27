#ifndef FACTORY_METHOD_H
#define FACTORY_METHOD_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>

class Pizza;

class PizzaStore
{
private:
    virtual std::shared_ptr<Pizza> createPizza(std::string) = 0;
public:
    std::shared_ptr<Pizza> orderPizza(std::string style);
};



class Pizza{
    friend class PizzaStore;
private:
    std::string name, dough, sauce;
    std::vector<std::string> toppings;
protected:
    void prepare() const;
    virtual void bake() const { std::cout << "Bake for 25 minutes at 350\n"; }
    virtual void cut() const { std::cout << "Cutting the pizza into diagonal slices\n"; }
    virtual void box() const { std::cout << "Place pizza into original PizzaStore box" << std::endl; }
public:
    std::string getName() const { return name; }
};

class NYStyleCheesePizza : public Pizza
{


};

class NYStyleVeggiePizza : public Pizza
{

};

class NYStyleClamPizza : public Pizza
{

};

class NYStylePepperoniPizza : public Pizza
{

};

class ChicagoStyleCheesePizza : public Pizza
{

};

class ChicagoStyleVeggiePizza : public Pizza
{

};

class ChicagoStyleClamPizza : public Pizza
{

};

class ChicagoStylePepperoniPizza : public Pizza
{

};


#endif // FACTORY_METHOD_H
