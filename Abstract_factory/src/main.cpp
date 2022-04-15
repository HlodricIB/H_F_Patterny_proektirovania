#include "abstract_factory.h"

int main()
{
    std::shared_ptr<Ingredients> Dough = std::make_shared<ThickCrustDough>();
    Dough->displayIngredients();
    Dough->description();
    Veggies v1({Veggies::garlic});
    Veggies v2;
    v1 = (std::move(v2));
    return 0;
}
