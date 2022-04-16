#include "abstract_factory.h"

int main()
{
    std::unique_ptr<PizzaStore> nyPizzaStore = std::make_unique<NYPizzaStore>();
    std::unique_ptr<PizzaStore> chicagoPizzaStore = std::make_unique<ChicagoPizzaStore>();
    auto NY_cheese_pizza = nyPizzaStore->orderPizza(std::string("cheese"));
    std::cout << NY_cheese_pizza->toString() << std::endl;
    std::cout << std::endl;
    auto Chicago_cheese_pizza = chicagoPizzaStore->orderPizza(std::string("cheese"));
    std::cout << Chicago_cheese_pizza->toString() << std::endl;
    std::cout << std::endl;
    auto NY_clam_pizza = nyPizzaStore->orderPizza(std::string("clam"));
    std::cout << NY_clam_pizza->toString() << std::endl;
    std::cout << std::endl;
    auto Chicago_clam_pizza = chicagoPizzaStore->orderPizza(std::string("clam"));
    std::cout << Chicago_clam_pizza->toString() << std::endl;
    return 0;
}
