#include "abstract_factory.h"

int main()
{
    std::shared_ptr<Ingredients> Dough = std::make_shared<ThickCrustDough>();
    Dough->displayIngredients();
    Dough->description();

    return 0;
}
