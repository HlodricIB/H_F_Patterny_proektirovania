#include <cstring>
#include "abstract_factory.h"

Veggies::Veggies(std::initializer_list<veggie_ingredient> il): list_of_veggies(il.size()), veggies(new std::unique_ptr<VeggieIngredients>[list_of_veggies])
{
    int i = 0;
    for (auto iter = il.begin(); iter != il.end(); ++iter, ++i)
    {
        switch (*iter)
        {
        case (veggie_ingredient::garlic) :
            veggies[i] = std::make_unique<Garlic>();
            break;
        case (veggie_ingredient::onion):
            veggies[i] = std::make_unique<Onion>();
            break;
        case (veggie_ingredient::mushroom):
            veggies[i] = std::make_unique<Mushroom>();
            break;
        case (veggie_ingredient::red_pepper):
            veggies[i] = std::make_unique<RedPepper>();
            break;
        case (veggie_ingredient::black_olives):
            veggies[i] = std::make_unique<BlackOlives>();
            break;
        case (veggie_ingredient::spinach):
            veggies[i] = std::make_unique<Spinach>();
            break;
        case (veggie_ingredient::eggplant):
            veggies[i] = std::make_unique<Eggplant>();
            break;
        default:
            veggies[i] = std::make_unique<Unknown>();
        }
    }
}

std::string Veggies::description() const
{
    std::string veggies_description;
    size_t temp = list_of_veggies - 1;
    for (size_t i = 0; i != temp; ++i)
    {
        veggies_description += veggies[i]->description() + ", ";
    }
    veggies_description += veggies[temp]->description();
    return veggies_description;
}

std::string Pizza::toString() const
{
    std::string pizza_compound = "Compound:";
    if (dough)
    {
        pizza_compound += "\ndough: " + dough->description();
    }
    if (sauce)
    {
        pizza_compound += "\nsauce: " + sauce->description();
    }
    if (veggies)
    {
        pizza_compound += "\nveggies: " + veggies->description();
    }
    if (cheese)
    {
        pizza_compound += "\ncheese: " + cheese->description();
    }
    if (pepperoni)
    {
        pizza_compound += "\npepperoni: " + pepperoni->description();
    }
    if (clam)
    {
        pizza_compound += "\nsauce: " + clam->description();
    }
    return pizza_compound;
}

void CheesePizza::prepare()
{
    std::cout << "Preparing " << name << "\n";
    dough = ingredientFactory->createDough();
    sauce = ingredientFactory->createSauce();
    cheese = ingredientFactory->createCheese();
    veggies = ingredientFactory->createVeggies();
    pepperoni = ingredientFactory->createPepperoni();
    clam = ingredientFactory->createClams();
}

void ClamPizza::prepare()
{
    std::cout << "Preparing " << name << "\n";
    dough = ingredientFactory->createDough();
    sauce = ingredientFactory->createSauce();
    cheese = ingredientFactory->createCheese();
    veggies = ingredientFactory->createVeggies();
    pepperoni = ingredientFactory->createPepperoni();
    clam = ingredientFactory->createClams();
}

void VeggiePizza::prepare()
{
    std::cout << "Preparing " << name << "\n";
    dough = ingredientFactory->createDough();
    sauce = ingredientFactory->createSauce();
    cheese = ingredientFactory->createCheese();
    veggies = ingredientFactory->createVeggies();
    pepperoni = ingredientFactory->createPepperoni();
    clam = ingredientFactory->createClams();
}

void PepperoniPizza::prepare()
{
    std::cout << "Preparing " << name << "\n";
    dough = ingredientFactory->createDough();
    sauce = ingredientFactory->createSauce();
    cheese = ingredientFactory->createCheese();
    veggies = ingredientFactory->createVeggies();
    pepperoni = ingredientFactory->createPepperoni();
    clam = ingredientFactory->createClams();
}

std::unique_ptr<Pizza> PizzaStore::orderPizza(std::string name)
{
    std::unique_ptr<Pizza> pizza = createPizza(name);
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();
    return pizza;
}

std::unique_ptr<Pizza> NYPizzaStore::createPizza(std::string name)
{
    std::unique_ptr<Pizza> pizza;
    if (name == "cheese")
    {
        pizza = std::make_unique<CheesePizza>(std::make_unique<NYPizzaIngredientFactory>());
        pizza->setName(name);
    } else {
        if (name == "veggie")
        {
            pizza = std::make_unique<VeggiePizza>(std::make_unique<NYPizzaIngredientFactory>());
            pizza->setName(name);
        } else {
            if (name == "clam")
            {
                pizza = std::make_unique<ClamPizza>(std::make_unique<NYPizzaIngredientFactory>());
                pizza->setName(name);
            } else {
                if (name == "pepperoni")
                {
                    pizza = std::make_unique<PepperoniPizza>(std::make_unique<NYPizzaIngredientFactory>());
                    pizza->setName(name);
                } else {
                    return nullptr;
                }
            }
        }
    }
    return pizza;
}

std::unique_ptr<Pizza> ChicagoPizzaStore::createPizza(std::string name)
{
    std::unique_ptr<Pizza> pizza;
    if (name == "cheese")
    {
        pizza = std::make_unique<CheesePizza>(std::make_unique<ChicagoPizzaIngredientFactory>());
        pizza->setName(name);
    } else {
        if (name == "veggie")
        {
            pizza = std::make_unique<VeggiePizza>(std::make_unique<ChicagoPizzaIngredientFactory>());
            pizza->setName(name);
        } else {
            if (name == "clam")
            {
                pizza = std::make_unique<ClamPizza>(std::make_unique<ChicagoPizzaIngredientFactory>());
                pizza->setName(name);
            } else {
                if (name == "pepperoni")
                {
                    pizza = std::make_unique<PepperoniPizza>(std::make_unique<ChicagoPizzaIngredientFactory>());
                    pizza->setName(name);
                } else {
                    return nullptr;
                }
            }
        }
    }
    return pizza;
}

