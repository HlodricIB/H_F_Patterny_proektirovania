#include <iostream>
#include <algorithm>
#include <execution>
#include "composite.h"

std::optional<std::reference_wrapper<MenuComponent>> Iterator_adapter::next()
{
    if (hasNext())
    {
        return std::ref(*(*current++));
    }
    return std::nullopt;
}

bool Iterator_adapter::hasNext()
{
    return current != end ? true : false;
}

std::optional<std::reference_wrapper<MenuComponent>> CompositeIterator::next()
{
    if (hasNext())
    {
        auto iterator = stack.top();
        auto component = iterator->next();
        stack.push(component->get().createIterator());
        return *component;
    }
    return std::nullopt;
}

bool CompositeIterator::hasNext()
{
    if (stack.empty())
    {
        return false;
    }
    auto iterator = stack.top();
    if (!iterator->hasNext())
    {
        stack.pop();
        return hasNext();
    }
    return true;
}

void Menu::remove(std::shared_ptr<MenuComponent> menuComponent)
{
    auto iter = std::find(std::execution::par, menuComponents.begin(), menuComponents.end(), menuComponent);
    if (iter != menuComponents.end())
    {
        menuComponents.erase(iter);
    }
}

std::optional<std::shared_ptr<MenuComponent>> Menu::getChild(int i) const
{
    if (static_cast<std::vector<std::shared_ptr<MenuComponent>>::size_type>(i) > (menuComponents.size() - 1))
    {
        return std::nullopt;
    }
    return menuComponents[i];
}

void Menu::print() const
{
    std::cout << "\n\n" << getName() << ", " << getDescription() << '\n' << "----------------------------------------";
    for (auto& menu_component : menuComponents)
    {
        menu_component -> print();
    }
}

std::shared_ptr<Iterator<MenuComponent>> Menu::createIterator()
{
    if (!iterator)
    {
        iterator = std::make_shared<CompositeIterator>(std::make_shared<Iterator_adapter>(menuComponents.begin(), menuComponents.end()));
    }
    return iterator;
}

void MenuItem::print() const
{
    std::cout << "\n    " << getName();
    if (isVegetarian().has_value() && *isVegetarian())
    {
        std::cout << "(v)";
    }
    std::cout << ", " << getPrice().value() << "  --  " << getDescription();
}

void Waitress::printVegetarianMenu() const
{
    std::cout << "\n\nVEGETARIAN MENU\n----------------------------------------";
    auto iterator = allMenus->createIterator();
    while (iterator->hasNext())
    {
        if (auto component = iterator->next(); component->get().isVegetarian().has_value() && *(component->get().isVegetarian()))
        {
            component->get().print();
        }
    }
}


