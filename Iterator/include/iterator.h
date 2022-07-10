#ifndef ITERATOR_H
#define ITERATOR_H

#include <string>
#include <list>
#include <memory>
#include <optional>

class MenuItem
{
private:
    std::string name;
    std::string description;
    bool vegetarian{false};
    double price{-1};
public:
    MenuItem () = default;
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
    virtual bool isNext() const = 0;
    virtual void remove() = 0;
};

class DinerMenuIterator : public Iterator<MenuItem>
{
private:
    std::shared_ptr<MenuItem[]> items{nullptr};
    mutable int position{0};
public:
    DinerMenuIterator(std::shared_ptr<MenuItem[]> items_): items(items_) { }
    std::optional<std::reference_wrapper<MenuItem>> next() const override;
    bool isNext() const override { return items[position].getPrice() < 0 ? false : true; }
    void remove() override;
};

class PancakeHouseIterator : public Iterator<MenuItem>
{
private:
    std::shared_ptr<std::list<MenuItem>> items{nullptr};
    std::list<MenuItem>::const_iterator position{ items->begin() };
public:


};

class DinerMenu{
private:
    static constexpr size_t MAX_ITEMS{6};
    size_t numberOfItems{0};
    std::shared_ptr<MenuItem[]> menuItems{new MenuItem[MAX_ITEMS]};
public:
    DinerMenu();
    void addItem(const std::string&, const std::string&, bool, double);
    std::shared_ptr<Iterator<MenuItem>> createIterator() { return std::make_shared<DinerMenuIterator>(menuItems); }
};

class PancakeHouseMenu{
private:
    std::list<MenuItem> menuItems;
public:
    PancakeHouseMenu();
    void addItem(const std::string& name, const std::string& description, bool vegetarian, double price)
    {
        menuItems.emplace_back(name, description, vegetarian, price);
    }
    std::shared_ptr<Iterator<MenuItem>> createIterator() { return std::make_shared<PancakeHouseIterator>(menuItems); }
};

class Waitress
{
private:
    std::shared_ptr<PancakeHouseMenu> panCakeHouseMenu{nullptr};
    std::shared_ptr<DinerMenu> dinerMenu{nullptr};
    void printMenu(std::shared_ptr<Iterator<MenuItem>>) const;
public:
    Waitress(std::shared_ptr<PancakeHouseMenu> panCakeHouseMenu_, std::shared_ptr<DinerMenu> dinerMenu_):
        panCakeHouseMenu(panCakeHouseMenu_), dinerMenu(dinerMenu_) { }
    void printMenu() const;
};





#endif // ITERATOR_H
