#include "factory_method.h"

std::shared_ptr<Pizza> PizzaStore::orderPizza(std::string type)
{
    std::shared_ptr<Pizza> pizza = createPizza(type);
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();

    return pizza;
}

std::shared_ptr<Pizza> NYPizzaStore::createPizza(std::string item)
{
    if (item == "cheese")
    {
        return std::make_shared<NYStyleCheesePizza>();
    } else {
        if (item == "veggie")
        {
            return std::shared_ptr<NYStyleVeggiePizza>();
        } else {
            if (item == "clam")
            {
                return std::shared_ptr<NYStyleClamPizza>();
            } else {
                if (item == "pepperoni")
                {
                    return std::shared_ptr<NYStylePepperoniPizza>();
                } else {
                    return nullptr;
                }
            }
        }
    }
}

std::shared_ptr<Pizza> ChicagoPizzaStore::createPizza(std::string item)
{
    if (item == "cheese")
    {
        return std::make_shared<ChicagoStyleCheesePizza>();
    } else {
        if (item == "veggie")
        {
            return std::shared_ptr<ChicagoStyleVeggiePizza>();
        } else {
            if (item == "clam")
            {
                return std::shared_ptr<ChicagoStyleClamPizza>();
            } else {
                if (item == "pepperoni")
                {
                    return std::shared_ptr<ChicagoStylePepperoniPizza>();
                } else {
                    return nullptr;
                }
            }
        }
    }
}

void Pizza::prepare() const
{
    std::cout << "Preparing " + name;
    std::cout << "\nTossing dough (" + dough + ")...";
    std::cout << "\nAdding sauce (" + sauce + ")...";
    std::cout << "\nAdding toppings:";
    for (const auto& i : toppings)
    {
        std::cout << "\n \t" << i;
    }
    std::cout << std::endl;
}
