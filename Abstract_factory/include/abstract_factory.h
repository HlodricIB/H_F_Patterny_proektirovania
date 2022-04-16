#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <string>
#include <memory>
#include <iostream>
#include <string>
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

class VeggieIngredients
{
public:
    enum ingredients { garlic, onion, mushroom, red_pepper, black_olives, spinach, eggplant };
    VeggieIngredients() = default;
    virtual ~VeggieIngredients() { };
    virtual std::string description() const = 0;
};

using veggie_ingredient = VeggieIngredients::ingredients;

class Garlic : public VeggieIngredients
{
public:
    std::string description() const override { return std::string("garlic"); }
};

class Onion : public VeggieIngredients
{
public:
    std::string description() const override { return std::string("onion"); }
};

class Mushroom : public VeggieIngredients
{
public:
    std::string description() const override { return std::string("mushrooms"); }
};

class RedPepper : public VeggieIngredients
{
public:
    std::string description() const override { return std::string("red pepper"); }
};

class BlackOlives : public VeggieIngredients
{
public:
    std::string description() const override { return std::string("black olives"); }
};

class Spinach : public VeggieIngredients
{
public:
    std::string description() const override { return std::string("spinach"); }
};

class Eggplant : public VeggieIngredients
{
public:
    std::string description() const override { return std::string("eggplant"); }
};

class Unknown : public VeggieIngredients
{
public:
    std::string description() const override { return std::string("some unknown ingredients"); }
};

class Veggies : public Ingredients
{
private:
    size_t list_of_veggies{0};
    std::unique_ptr<std::unique_ptr<VeggieIngredients>[]> veggies{0};
    std::string description() const override;
public:    
    Veggies() = default;
    explicit Veggies(std::initializer_list<veggie_ingredient> il);
    virtual ~Veggies() { };
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
public:
    PizzaIngredientFactory() = default;
    virtual ~PizzaIngredientFactory() { }
    virtual std::unique_ptr<Ingredients> createDough() = 0;
    virtual std::unique_ptr<Ingredients> createSauce() = 0;
    virtual std::unique_ptr<Ingredients> createCheese() = 0;
    virtual std::unique_ptr<Ingredients> createVeggies() = 0;
    virtual std::unique_ptr<Ingredients> createPepperoni() = 0;
    virtual std::unique_ptr<Ingredients> createClams() = 0;
};

class NYPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
    std::unique_ptr<Ingredients> createDough() { return std::make_unique<ThinCrustDough>(); }
    std::unique_ptr<Ingredients> createSauce() { return std::make_unique<MarinaraSauce>(); }
    std::unique_ptr<Ingredients> createCheese() { return std::make_unique<ReggianoCheese>(); }
    std::unique_ptr<Ingredients> createVeggies()
    {
        return std::make_unique<Veggies>(std::initializer_list<veggie_ingredient>{veggie_ingredient::garlic, veggie_ingredient::onion, veggie_ingredient::mushroom, veggie_ingredient::red_pepper});
    }
    std::unique_ptr<Ingredients> createPepperoni() { return std::make_unique<SlicedPepperoni>(); }
    std::unique_ptr<Ingredients> createClams() { return std::make_unique<FreshClams>(); }
};

class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
    std::unique_ptr<Ingredients> createDough() { return std::make_unique<ThickCrustDough>(); }
    std::unique_ptr<Ingredients> createSauce() { return std::make_unique<PlumTomatoSauce>(); }
    std::unique_ptr<Ingredients> createCheese() { return std::make_unique<MozzarellaCheese>(); }
    std::unique_ptr<Ingredients> createVeggies()
    {
        return std::make_unique<Veggies>(std::initializer_list<veggie_ingredient>{veggie_ingredient::black_olives, veggie_ingredient::spinach, veggie_ingredient::eggplant});
    }
    std::unique_ptr<Ingredients> createPepperoni() { return std::make_unique<SlicedPepperoni>(); }
    std::unique_ptr<Ingredients> createClams() { return std::make_unique<FrozenClams>(); }
};

class Pizza
{
    friend class PizzaStore;
private:
    virtual void prepare()= 0;
    virtual void bake() const { std::cout << "Bake for 25 minutes at 350\n"; }
    virtual void cut() const { std::cout << "Cutting the pizza into diagonal slices\n"; }
    virtual void box() const { std::cout << "Place pizza into original PizzaStore box" << std::endl; }
protected:
    std::string name;
    std::unique_ptr<Ingredients> dough;
    std::unique_ptr<Ingredients> sauce;
    std::unique_ptr<Ingredients> cheese;
    std::unique_ptr<Ingredients> veggies;
    std::unique_ptr<Ingredients> pepperoni;
    std::unique_ptr<Ingredients> clam;
public:
    Pizza() = default;
    virtual ~Pizza() { }
    void setName(std::string name_) { name = name_; }
    std::string getName() const { return name; }
    std::string toString() const;
};

class CheesePizza : public Pizza
{
private:
    std::unique_ptr<PizzaIngredientFactory> ingredientFactory;
public:
    CheesePizza(std::unique_ptr<PizzaIngredientFactory> ingredientFactory_): Pizza(), ingredientFactory(std::move(ingredientFactory_)) { }
    void prepare() override;
};

class VeggiePizza : public Pizza
{
private:
    std::unique_ptr<PizzaIngredientFactory> ingredientFactory;
public:
    VeggiePizza(std::unique_ptr<PizzaIngredientFactory> ingredientFactory_): Pizza(), ingredientFactory(std::move(ingredientFactory_)) { }
    void prepare() override;
};

class ClamPizza : public Pizza
{
private:
    std::unique_ptr<PizzaIngredientFactory> ingredientFactory;
public:
    ClamPizza(std::unique_ptr<PizzaIngredientFactory> ingredientFactory_): Pizza(), ingredientFactory(std::move(ingredientFactory_)) { }
    void prepare() override;
};

class PepperoniPizza : public Pizza
{
private:
    std::unique_ptr<PizzaIngredientFactory> ingredientFactory;
public:
    PepperoniPizza(std::unique_ptr<PizzaIngredientFactory> ingredientFactory_): Pizza(), ingredientFactory(std::move(ingredientFactory_)) { }
    void prepare() override;
};

class PizzaStore
{
private:
    virtual std::unique_ptr<Pizza> createPizza(std::string) = 0;
public:
    PizzaStore() = default;
    std::unique_ptr<Pizza> orderPizza(std::string);
    virtual ~PizzaStore() { };
};

class NYPizzaStore : public PizzaStore
{
public:
    std::unique_ptr<Pizza> createPizza(std::string) override;
};

class ChicagoPizzaStore : public PizzaStore
{
public:
    std::unique_ptr<Pizza> createPizza(std::string) override;
};

#endif // ABSTRACT_FACTORY_H
