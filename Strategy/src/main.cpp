#include <memory>
#include "strategy_ducks.h"

int main()
{
    MallardDuck mallard;
    mallard.display();
    mallard.swim();
    mallard.performFly();
    mallard.performQuack();

    ModelDuck model;
    model.display();
    model.swim();
    model.performFly();
    model.performQuack();
    model.setFlyBehavior(std::make_shared<FlyRocketPowered>());
    model.performFly();
    return 0;
}

