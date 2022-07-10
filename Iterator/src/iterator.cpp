#include <iostream>
#include "iterator.h"

DinerMenu::DinerMenu()
{
    addItem("Vegetarian BLT", "(Fakin’) Bacon with lettuce & tomato on whole wheat", true, 2.99);
    addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
    addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
    addItem("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05);
}

void DinerMenu::addItem(const std::string& name, const std::string& description, bool vegetarian, double price)
{
    size_t max_items_real = MAX_ITEMS - 1;
    if (numberOfItems != max_items_real)
    {
        menuItems[numberOfItems++] = {name, description, vegetarian, price};
    } else {
        std::cout << "Sorry, menu is full! Can’t add item to menu" << std::endl;
    }
    menuItems[numberOfItems] = { };
}

std::optional<std::reference_wrapper<MenuItem>> DinerMenuIterator::next() const
{
    if (isNext())
    {
        return items[position++];
    }
    return std::nullopt;
}

void DinerMenuIterator::remove()
{
    if (position <= 0)
    {
        std::cout << "You can’t remove an item until you’ve done at least one next()" << std::endl;
        return;
    }
    int pos_to_remove = position - 1;
    if (items[pos_to_remove].getPrice() > 0)
    {
        while (items[position].getPrice() > 0)
        {
            items[pos_to_remove] = items[position++];
        }
        return;
    }
}

PancakeHouseMenu::PancakeHouseMenu()
{
    addItem("K&B’s Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99);
    addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
    addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
    addItem("Waffles", "Waffles, with your choice of blueberries or strawberries", true, 3.59);
}

void Waitress::printMenu() const
{
    auto pancakeIterator = panCakeHouseMenu->createIterator();
    auto dinerIterator = dinerMenu->createIterator();
    std::cout << "MENU\n----\nBREAKFAST" << std::endl;
    printMenu(pancakeIterator);
    std::cout << "\nLUNCH" << std::endl;
    printMenu(dinerIterator);
}

void Waitress::printMenu(std::shared_ptr<Iterator<MenuItem>> iterator) const
{
    while (auto menuItem = iterator->next())
    {
        std::cout << menuItem->get().getName() << ", " << menuItem->get().getPrice() << " == "
                    << menuItem->get().getDescription();
    }

}


