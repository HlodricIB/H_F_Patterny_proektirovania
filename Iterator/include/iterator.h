#ifndef ITERATOR_H
#define ITERATOR_H

#include <string>
#include <list>
#include <memory>
#include <optional>
#include <map>
#include <vector>

class MenuItem
{
private:
    std::string name;
    std::string description;
    bool vegetarian{false};
    double price{-1};
public:
    MenuItem() = default;
    MenuItem(const std::string& name_, const std::string& description_, bool vegetarian_, double price_):
        name(name_), description(description_), vegetarian(vegetarian_), price(price_) { }
    std::string getName() { return name; }
    std::string getDescription() { return description; }
    double getPrice() { return price; }
    bool isVegetarian() { return vegetarian; }
};

template <class Object> class Iterator
{
public:
    virtual std::optional<std::reference_wrapper<Object>> next() const = 0;
    virtual bool hasNext() const = 0;
    virtual void remove() = 0;
};

class DinerMenuIterator : public Iterator<MenuItem>
{
private:
    std::shared_ptr<MenuItem[]> items{nullptr};
    mutable size_t position{0};
public:
    DinerMenuIterator(std::shared_ptr<MenuItem[]> items_): items(items_) { }
    std::optional<std::reference_wrapper<MenuItem>> next() const override;
    bool hasNext() const override { return items[position].getPrice() < 0 ? false : true; }
    void remove() override;
};

class PancakeHouseIterator : public Iterator<MenuItem>
{
private:
    std::shared_ptr<std::list<MenuItem>> items{nullptr};
    mutable std::list<MenuItem>::iterator position;
public:
    PancakeHouseIterator(std::shared_ptr<std::list<MenuItem>> items_): items(items_), position(items->begin()) { }
    std::optional<std::reference_wrapper<MenuItem>> next() const override;
    bool hasNext() const override { return position->getPrice() < 0 ? false : true; }
    void remove() override;
};

class CafeMenuIterator : public Iterator<MenuItem>
{
private:
    std::map<std::string, MenuItem>& items;
    mutable std::map<std::string, MenuItem>::iterator position;
public:
    CafeMenuIterator(std::map<std::string, MenuItem>& items_): items(items_), position(items.begin()) { }
    std::optional<std::reference_wrapper<MenuItem>> next() const override;
    bool hasNext() const override { return position->second.getPrice() < 0 ? false : true; }
    void remove() override;
};

class Menu
{
public:
    virtual std::shared_ptr<Iterator<MenuItem>> createIterator() = 0;
};

class DinerMenu : public Menu
{
private:
    static constexpr size_t MAX_ITEMS{7};
    size_t numberOfItems{0};
    std::shared_ptr<MenuItem[]> menuItems{new MenuItem[MAX_ITEMS]};
public:
    DinerMenu();
    void addItem(const std::string&, const std::string&, bool, double);
    std::shared_ptr<Iterator<MenuItem>> createIterator() override { return std::make_shared<DinerMenuIterator>(menuItems); }
};

class PancakeHouseMenu : public Menu
{
private:
    std::shared_ptr<std::list<MenuItem>> menuItems{new std::list<MenuItem>};
public:
    PancakeHouseMenu();
    void addItem(const std::string& name, const std::string& description, bool vegetarian, double price)
    {
        menuItems->emplace_back(name, description, vegetarian, price);
    }
    std::shared_ptr<Iterator<MenuItem>> createIterator() override { return std::make_shared<PancakeHouseIterator>(menuItems); }
};

class CafeMenu : public Menu
{
private:
    std::map<std::string, MenuItem> menuItems{};
public:
    CafeMenu();
    void addItem(const std::string& name, const std::string& description, bool vegetarian, double price)
    {
        menuItems.emplace(std::piecewise_construct,
                          std::forward_as_tuple(name),
                          std::forward_as_tuple(name, description, vegetarian, price));
    }
    std::shared_ptr<Iterator<MenuItem>> createIterator() override { return std::make_shared<CafeMenuIterator>(menuItems); }

};

class Waitress
{
private:
    std::vector<std::shared_ptr<Menu>> menus;
    void printMenu(std::shared_ptr<Iterator<MenuItem>>) const;
public:
    Waitress(std::vector<std::shared_ptr<Menu>> menus_): menus(menus_){ }
    void printMenu() const;
};





#endif // ITERATOR_H
