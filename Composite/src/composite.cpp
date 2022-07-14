#include <iostream>
#include "composite.h"

DinerMenu::DinerMenu()
{
    addItem("Vegetarian BLT", "(Fakin’) Bacon with lettuce & tomato on whole wheat", true, 2.99);
    addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
    addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
    addItem("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05);
    addItem("Steamed Veggies and Brown Rice", "Steamed vegetables over brown rice", true, 3.99);
    addItem("Pasta", "Spaghetti with Marinara Sauce, and a slice of sourdough bread", false, 3.89);
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
    if (hasNext())
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
    size_t pos_to_remove = position - 1;
    if (items[pos_to_remove].getPrice() > 0)
    {
        while (items[position].getPrice() > 0)
        {
            items[pos_to_remove++] = items[position++];
        }
        items[pos_to_remove] = {};
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
    for (auto& menu : menus)
    {
        printMenu(menu->createIterator());
    }
}

void Waitress::printMenu(std::shared_ptr<Iterator<MenuItem>> iterator) const
{
    while (auto menuItem = iterator->next())
    {
        std::cout << menuItem->get().getName() << ", " << menuItem->get().getPrice() << " == "
                    << menuItem->get().getDescription() << std::endl;
    }
    std::cout << std::endl;
}

std::optional<std::reference_wrapper<MenuItem>> PancakeHouseIterator::next() const
{
    if (position != items->end())
    {
        return *(position++);
    }
    return std::nullopt;
}

void PancakeHouseIterator::remove()
{
    if (position == items->begin())
    {
        std::cout << "You can’t remove an item until you’ve done at least one next()" << std::endl;
        return;
    }
    auto pos_to_remove = position;
    if ((--pos_to_remove)->getPrice() > 0)
    {
       items->erase(pos_to_remove);
    }
}

CafeMenu::CafeMenu()
{
    addItem("Veggie Burger and Air Fries", "Veggie burger on a whole wheat bun, lettuce, tomato, and fries", true, 3.99);
    addItem("Soup of the day", "A cup of the soup of the day, with a side salad", false, 3.69);
    addItem("Burrito", "A large burrito, with whole pinto beans, salsa, guacamole", true, 4.29);
}

std::optional<std::reference_wrapper<MenuItem>> CafeMenuIterator::next() const
{
    if (position != items.end())
    {
        return (position++)->second;
    }
    return std::nullopt;
}

void CafeMenuIterator::remove()
{
    if (position == items.begin())
    {
        std::cout << "You can’t remove an item until you’ve done at least one next()" << std::endl;
        return;
    }
    auto pos_to_remove = position;
    if ((--pos_to_remove)->second.getPrice() > 0)
    {
       items.erase(pos_to_remove);
    }
}


