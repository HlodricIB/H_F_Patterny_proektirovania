#include <memory>
#include "template_method.h"

int main()
{
    auto teaHook = std::make_shared<TeaWithHook>();
    auto coffeeHook = std::make_shared<CoffeeWithHook>();
    std::cout << "Making tea...\n";
    teaHook->prepareRecipe();
    std::cout << "Making coffee...\n";
    coffeeHook->prepareRecipe();
    return 0;
}
