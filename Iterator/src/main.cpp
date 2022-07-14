#include <iostream>
#include "iterator.h"

int main()
{
    std::shared_ptr<Menu> pancakeHouseMenu = std::make_shared<PancakeHouseMenu>();
    std::shared_ptr<Menu> dinerMenu = std::make_shared<DinerMenu>();
    std::shared_ptr<Menu> cafeMenu = std::make_shared<CafeMenu>();
    Waitress waitress({pancakeHouseMenu, dinerMenu, cafeMenu});
    waitress.printMenu();
    auto pancakeHouseMenu_iter = pancakeHouseMenu->createIterator();
    auto dinerMenu_iter = dinerMenu->createIterator();
    auto cafeMenu_iter = cafeMenu->createIterator();
    std::cout << pancakeHouseMenu_iter->next()->get().getName() << '\n' << pancakeHouseMenu_iter->next()->get().getName() << std::endl;
    std::cout << dinerMenu_iter->next()->get().getName() << '\n' << dinerMenu_iter->next()->get().getName() << std::endl;
    std::cout << cafeMenu_iter->next()->get().getName() << '\n' << cafeMenu_iter->next()->get().getName() << std::endl;
    pancakeHouseMenu_iter->remove();
    dinerMenu_iter->remove();
    cafeMenu_iter->remove();
    waitress.printMenu();
    return 0;
}
