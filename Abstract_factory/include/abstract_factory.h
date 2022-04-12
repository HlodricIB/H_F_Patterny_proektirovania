#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <string>
#include <memory>
#include <iostream>

class Ingredients
{
public:
    Ingredients() = default;
    virtual ~Ingredients() { }
    std::string displayIngredients() const { return std::string("Ingredients: "); }
    virtual std::string description() const = 0;
};

class ThinCrustDough : public Ingredients
{
public:
    std::string description() const override { return std::string("thin crust dough"); }
};

class ThickCrustDough : public Ingredients
{
public:
    std::string description() const override { return std::string("thick crust dough"); }
};

class PlumTomatoSauce : public Ingredients
{
public:
    std::string description() const override { return std::string("plum tomato sauce"); }
};

class MarinaraSauce : public Ingredients
{
public:
    std::string description() const override { return std::string("marinara sauce"); }
};

class MozzarellaCheese : public Ingredients
{
public:
    std::string description() const override { return std::string("mozzarella cheese"); }
};

class ReggianoCheese : public Ingredients
{
public:
    std::string description() const override { return std::string("reggiano cheese"); }
};

class Veggies : public Ingredients
{
private:
    std::shared_ptr<std::shared_ptr<Veggies>> veggies;
public:
    std::string description() const override;
};

class FrozenClams : public Ingredients
{
public:
    std::string description() const override { return std::string("frozen clams"); }
};

class FreshClams : public Ingredients
{
public:
    std::string description() const override { return std::string("fresh clams"); }
};

class PizzaIngredientFactory
{
public:
    PizzaIngredientFactory() = default;
    virtual ~PizzaIngredientFactory() { }
    virtual std::shared_ptr<Ingredients> createDough() = 0;
    virtual std::shared_ptr<Ingredients> createSauce() = 0;
    virtual std::shared_ptr<Ingredients> createCheese() = 0;
    virtual std::shared_ptr<Ingredients> createVeggies() = 0;
    virtual std::shared_ptr<Ingredients> createPepperoni() = 0;
    virtual std::shared_ptr<Ingredients> createClams() = 0;

};

class Pizza
{
private:
    std::string name;
    std::shared_ptr<Ingredients> dough;
    std::shared_ptr<Ingredients> sauce;
    std::shared_ptr<Ingredients> veggies;
    std::shared_ptr<Ingredients> pepperoni;
    std::shared_ptr<Ingredients> clam;
    virtual void prepare() const = 0;
    virtual void bake() const { std::cout << "Bake for 25 minutes at 350\n"; }
    virtual void cut() const { std::cout << "Cutting the pizza into diagonal slices\n"; }
    virtual void box() const { std::cout << "Place pizza into original PizzaStore box" << std::endl; }
    void setName(std::string name_) { name = name_; }

public:
    Pizza() { }
    virtual ~Pizza() { }
    std::string getName() const { return name; }
    std::string toString() const;

};

class CheesePizza : public Pizza
{
private:
    std::shared_ptr<PizzaIngredientFactory> ingredientFactory;
public:
    CheesePizza(const std::shared_ptr<PizzaIngredientFactory> ingredientFactory_): Pizza(), ingredientFactory(ingredientFactory_) { }
    void prepare() const override;
};

#endif // ABSTRACT_FACTORY_H
