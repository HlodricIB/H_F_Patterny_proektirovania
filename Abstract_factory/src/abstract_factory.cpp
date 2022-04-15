#include <cstring>
#include "abstract_factory.h"

Veggies::Veggies(std::initializer_list<int> il): list_of_veggies(il.size()), veggies(new std::unique_ptr<Veggies>[list_of_veggies])
{
    int i = 0;
    for (auto iter = il.begin(); iter != il.end(); ++iter, ++i)
    {
        switch (*iter)
        {
        case (garlic) :
            veggies[i] = std::make_unique<Veggies>(new Garlic());
            break;
        case (onion):
            veggies[i] = std::make_unique<Veggies>(new Onion());
            break;
        case (mushroom):
            veggies[i] = std::make_unique<Veggies>(new Mushroom());
            break;
        case (red_pepper):
            veggies[i] = std::make_unique<Veggies>(new RedPepper());
            break;
        case (black_olives):
            veggies[i] = std::make_unique<Veggies>(new BlackOlives());
            break;
        case (spinach):
            veggies[i] = std::make_unique<Veggies>(new Spinach());
            break;
        case (eggplant):
            veggies[i] = std::make_unique<Veggies>(new Eggplant());
            break;
        default:
            veggies[i] = std::make_unique<Veggies>(new Unknown());
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
        pizza_compound += "\nveggies: " + sauce->description();
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
