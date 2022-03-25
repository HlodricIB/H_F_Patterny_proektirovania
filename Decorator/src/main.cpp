#include <memory>
#include <iostream>
#include "decorator.h"

int main()
{
    std::shared_ptr<Beverage> beverage = std::make_shared<Espresso>();
    std::cout << beverage->getDescription() << " $" << beverage->cost() << std::endl;

    std::shared_ptr<Beverage> beverage2 = std::make_shared<DarkRoast>();
    beverage2 = std::make_shared<Mocha>(beverage2.get());
    beverage2 = std::make_shared<Mocha>(beverage2.get());
    beverage2 = std::make_shared<Whip>(beverage2.get());
    std::cout << beverage2->getDescription() << " $" << beverage2->cost() << std::endl;

    std::shared_ptr<Beverage> beverage3 = std::make_shared<HouseBlend>();
    beverage3 = std::make_shared<Soy>(beverage3.get());
    beverage3 = std::make_shared<Mocha>(beverage3.get());
    beverage3 = std::make_shared<Whip>(beverage3.get());
    std::cout << beverage3->getDescription() << " $" << beverage3->cost() << std::endl;
    return 0;
}
