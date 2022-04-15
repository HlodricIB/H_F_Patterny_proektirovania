#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <string>
#include <memory>
#include <iostream>
#include <initializer_list>

class Ingredients
{
public:
    Ingredients() = default;
    Ingredients(const Ingredients&) = delete;
    Ingredients& operator=(const Ingredients&) = delete;
    Ingredients& operator=(Ingredients&&) = default;
    virtual ~Ingredients() { }
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
    size_t list_of_veggies;
    std::unique_ptr<std::unique_ptr<Veggies>[]> veggies;
public:
    enum { garlic, onion, mushroom, red_pepper, black_olives, spinach, eggplant };
    Veggies() = default;
    Veggies(std::initializer_list<int> il);
    virtual ~Veggies();
    std::string description() const override;
};

class Garlic : public Veggies
{
    std::string description() const override { return std::string("garlic"); }
};

class Onion : public Veggies
{
    std::string description() const override { return std::string("onion"); }
};

class Mushroom : public Veggies
{
    std::string description() const override { return std::string("mushrooms"); }
};

class RedPepper : public Veggies
{
    std::string description() const override { return std::string("red pepper"); }
};

class BlackOlives : public Veggies
{
    std::string description() const override { return std::string("black olives"); }
};

class Spinach : public Veggies
{
    std::string description() const override { return std::string("spinach"); }
};

class Eggplant : public Veggies
{
    std::string description() const override { return std::string("eggplant"); }
};

class Unknown : public Veggies
{
    std::string description() const override { return std::string("some unknown ingredients"); }
};

class SlicedPepperoni : public Ingredients
{
public:
    std::string description() const override { return std::string("sliced pepperoni"); }
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
private:
    virtual std::unique_ptr<Ingredients> createDough() = 0;
    virtual std::unique_ptr<Ingredients> createSauce() = 0;
    virtual std::unique_ptr<Ingredients> createCheese() = 0;
    virtual std::unique_ptr<Ingredients> createVeggies() = 0;
    virtual std::unique_ptr<Ingredients> createPepperoni() = 0;
    virtual std::unique_ptr<Ingredients> createClams() = 0;
public:
    PizzaIngredientFactory() = default;
    virtual ~PizzaIngredientFactory() { }
};

class NYPizzaIngredientFactory : PizzaIngredientFactory
{
    std::unique_ptr<Ingredients> createDough() { return std::make_unique<ThinCrustDough>(); }
    std::unique_ptr<Ingredients> createSauce() { return std::make_unique<MarinaraSauce>(); }
    std::unique_ptr<Ingredients> createCheese() { return std::make_unique<ReggianoCheese>(); }
    std::unique_ptr<Ingredients> createVeggies()
    {
        return std::make_unique<Veggies>(Veggies::garlic, Veggies::onion, Veggies::mushroom, Veggies::red_pepper);
    }
    std::unique_ptr<Ingredients> createPepperoni() { return std::make_unique<SlicedPepperoni>(); }
    std::unique_ptr<Ingredients> createClams() { return std::make_unique<FreshClams>(); }
};

class Pizza
{
private:
    std::string name;
    std::unique_ptr<Ingredients> dough;
    std::unique_ptr<Ingredients> sauce;
    std::unique_ptr<Ingredients> veggies;
     std::unique_ptr<Ingredients> cheese;
    std::unique_ptr<Ingredients> pepperoni;
    std::unique_ptr<Ingredients> clam;
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
