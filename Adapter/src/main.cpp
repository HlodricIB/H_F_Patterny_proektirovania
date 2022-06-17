#include "adapter.h"

void testDuck(std::shared_ptr<Duck> duck)
{
    duck->quack();
    std::cout << '\n';
    duck->fly();
}

int main()
{
    std::shared_ptr<Duck> duck = std::make_shared<MallardDuck>();

    std::shared_ptr<Turkey> turkey = std::make_shared<WildTurkey>();
    std::shared_ptr<Duck> turkeyAdapter = std::make_shared<TurkeyAdapter>(turkey);

    std::cout << "The Turkey says...\n";
    turkey->gobble();
    std::cout << '\n';
    turkey->fly();

     std::cout << "\nThe Duck says...\n";
     testDuck(duck);

     std::cout << "\nThe TurkeyAdapter says...\n";
     testDuck(turkeyAdapter);
    return 0;
}
