#ifndef FACTORY_METHOD_H
#define FACTORY_METHOD_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>

class Pizza;

class PizzaStore
{
protected:
    virtual std::shared_ptr<Pizza> createPizza(std::string) = 0;
public:
    PizzaStore() { }
    virtual ~PizzaStore() { };
    std::shared_ptr<Pizza> orderPizza(std::string style);    
};

class NYPizzaStore : public PizzaStore
{
public:
    std::shared_ptr<Pizza> createPizza(std::string) override;
};

class ChicagoPizzaStore : public PizzaStore
{
public:
    std::shared_ptr<Pizza> createPizza(std::string) override;
};

class Pizza{
    friend class PizzaStore;
private:
    std::string name, dough, sauce;
protected:
    std::vector<std::string> toppings;
    void prepare() const;
    virtual void bake() const { std::cout << "Bake for 25 minutes at 350\n"; }
    virtual void cut() const { std::cout << "Cutting the pizza into diagonal slices\n"; }
    virtual void box() const { std::cout << "Place pizza into original PizzaStore box" << std::endl; }
public:
    Pizza(const char* n, const char* d, const char* s): name(n), dough(d), sauce(s) { }
    virtual ~Pizza () { };
    std::string getName() const { return name; }
};

class NYStyleCheesePizza : public Pizza
{
public:
    NYStyleCheesePizza(): Pizza("NY Style Sauce and Cheese Pizza", "Thin Crust Dough", "Marinara Sauce")
    {
        toppings.push_back(std::string("Grated Reggiano Cheese"));
    }
};

class NYStyleVeggiePizza : public Pizza
{
public:
    NYStyleVeggiePizza(): Pizza("NY Style Veggie Pizza", "Veggie Crust Dough", "Veggie Sauce")
    {
        toppings.push_back(std::string("no toppings"));
    }
};

class NYStyleClamPizza : public Pizza
{
public:
    NYStyleClamPizza(): Pizza("NY Style Clam Pizza", "Clam Crust Dough", "Clam Sauce")
    {
        toppings.push_back(std::string("no toppings"));
    }
};

class NYStylePepperoniPizza : public Pizza
{
public:
    NYStylePepperoniPizza(): Pizza("NY Style Pepperoni Pizza", "Pepperoni Crust Dough", "Pepperoni Sauce")
    {
        toppings.push_back(std::string("no toppings"));
    }
};

class ChicagoStyleCheesePizza : public Pizza
{
public:
    ChicagoStyleCheesePizza(): Pizza("Chicago Style Deep Dish Cheese Pizza", "Extra Thick Crust Dough", "Plum Tomato Sauce")
    {
        toppings.push_back(std::string("Shredded Mozzarella Cheese"));
    }
    void cut() const override { std::cout << "Cutting the pizza into square slices\n"; }
};

class ChicagoStyleVeggiePizza : public Pizza
{
public:
    ChicagoStyleVeggiePizza(): Pizza("Chicago Style Veggie Pizza", "Veggie Crust Dough", "Veggie Sauce")
    {
        toppings.push_back(std::string("no toppings"));
    }
};

class ChicagoStyleClamPizza : public Pizza
{
public:
    ChicagoStyleClamPizza(): Pizza("Chicago Style Clam Pizza", "Clam Crust Dough", "Clam Sauce")
    {
        toppings.push_back(std::string("no toppings"));
    }
};

class ChicagoStylePepperoniPizza : public Pizza
{
public:
    ChicagoStylePepperoniPizza(): Pizza("Chicago Style Pepperoni Pizza", "Pepperoni Crust Dough", "Pepperoni Sauce")
    {
        toppings.push_back(std::string("no toppings"));
    }
};


#endif // FACTORY_METHOD_H
