#include <memory>
#include <iostream>
#include "factory_method.h"

int main()
{
    auto nyStore = std::make_shared<NYPizzaStore>();
    auto chicagoStore = std::make_shared<ChicagoPizzaStore>();

    auto pizza = nyStore->orderPizza("cheese");
    std::cout << "Ethan ordered a " + pizza->getName() + "\n\n";

    pizza = chicagoStore->orderPizza("cheese");
    std::cout << "Joel ordered a " + pizza->getName() + "\n\n";

    return 0;
}
