#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <string>
#include <list>
#include <memory>
#include <optional>
#include <map>
#include <vector>
#include <exception>
#include <stack>

class Menu_exception : public std::exception
{
private:
    std::string error;
public:
    Menu_exception(std::string error_): error(error_) { }
    const char* what() const noexcept override { return error.c_str(); }
};

class MenuComponent;

template <class Object> class Iterator
{
public:
    virtual ~Iterator() { }
    virtual std::optional<std::reference_wrapper<Object>> next() = 0;
    virtual bool hasNext() = 0;
    virtual void remove() = 0;
};

class Iterator_adapter : public Iterator<MenuComponent>
{
private:
    std::vector<std::shared_ptr<MenuComponent>>::iterator current;
    std::vector<std::shared_ptr<MenuComponent>>::iterator end;
public:
    Iterator_adapter(std::vector<std::shared_ptr<MenuComponent>>::iterator current_, std::vector<std::shared_ptr<MenuComponent>>::iterator end_): current(current_), end(end_) { }
    std::optional<std::reference_wrapper<MenuComponent>> next() override;
    bool hasNext() override;
    void remove() override { throw Menu_exception("Remove() function is not supported in this version"); }
};

class CompositeIterator : public Iterator<MenuComponent>, public std::enable_shared_from_this<CompositeIterator>
{
private:
    std::stack<std::shared_ptr<Iterator<MenuComponent>>> stack;
public:
    CompositeIterator() = default;
    CompositeIterator(std::shared_ptr<Iterator<MenuComponent>> iterator) { stack.push(iterator); }
    std::optional<std::reference_wrapper<MenuComponent>> next() override;
    bool hasNext() override;
    void remove() override { throw Menu_exception("Remove() function is not supported in this version"); };
};

class NullIterator : public Iterator<MenuComponent>
{
public:
    NullIterator() = default;
    std::optional<std::reference_wrapper<MenuComponent>> next() override { return std::nullopt; }
    bool hasNext() override { return false;}
    void remove() override { throw Menu_exception("Remove() function is not supported in this version"); }
};

class MenuComponent
{
public:
    virtual ~MenuComponent() { }
    virtual void add(std::shared_ptr<MenuComponent>) = 0;
    virtual void remove(std::shared_ptr<MenuComponent>) = 0;
    virtual std::optional<std::shared_ptr<MenuComponent>> getChild(int) const = 0;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::optional<double> getPrice() const = 0;
    virtual std::optional<bool> isVegetarian() const = 0;
    virtual void print() const = 0;
    virtual std::shared_ptr<Iterator<MenuComponent>> createIterator() = 0;
};

class Menu : public MenuComponent
{
private:
    std::vector<std::shared_ptr<MenuComponent>> menuComponents;
    std::string name;
    std::string description;
    std::shared_ptr<Iterator<MenuComponent>> iterator{nullptr};
public:
    Menu() = default;
    Menu(std::string name_, std::string description_): name(name_), description(description_) { }
    void add(std::shared_ptr<MenuComponent> menuComponent) override { menuComponents.push_back(menuComponent); }
    void remove(std::shared_ptr<MenuComponent>) override;
    std::optional<std::shared_ptr<MenuComponent>> getChild(int) const override;
    std::string getName() const override { return name; };
    std::string getDescription() const override { return description;};
    std::optional<double> getPrice() const override { return std::nullopt; };
    std::optional<bool> isVegetarian() const override { return std::nullopt; };
    void print() const override;
    std::shared_ptr<Iterator<MenuComponent>> createIterator() override;
};

class MenuItem : public MenuComponent
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
    void add(std::shared_ptr<MenuComponent>) override { }
    void remove(std::shared_ptr<MenuComponent>) override { }
    std::optional<std::shared_ptr<MenuComponent>> getChild(int) const override { return std::nullopt; }
    std::string getName() const override { return name; }
    std::string getDescription() const override  { return description; }
    std::optional<double> getPrice() const override { return price; }
    std::optional<bool> isVegetarian() const override { return vegetarian; }
    void print() const override;
    std::shared_ptr<Iterator<MenuComponent>> createIterator() override { return std::make_shared<NullIterator>(); };
};

class Waitress
{
private:
    std::shared_ptr<MenuComponent> allMenus;
public:
    Waitress(std::shared_ptr<MenuComponent> allMenus_): allMenus(allMenus_){ }
    void printMenu() const { allMenus->print(); };
    void printVegetarianMenu() const;
};

#endif // COMPOSITE_H
