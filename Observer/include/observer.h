#ifndef OBSERVER_H
#define OBSERVER_H

#include <list>
#include <memory>
#include <climits>

class Observer
{
public:
    Observer() { }
    virtual ~Observer() { }

    virtual void update(double, double, double) = 0;
};

class Subject
{
public:
    Subject() { }
    virtual ~Subject() { }

    virtual void registerObserver(std::shared_ptr<Observer>) = 0;
    virtual void removeObserver(std::shared_ptr<Observer>) = 0;
    virtual void notifyObservers() const = 0;
};

class DisplayElement
{
public:
    DisplayElement() { }
    virtual ~DisplayElement() { }

    virtual void display() const = 0;
};

class WeatherData : public Subject
{
private:
    std::list<std::shared_ptr<Observer>> observers;
    double temperature, humidity, pressure;
    void measurementsChanged() { notifyObservers(); }
public:
    WeatherData(): temperature{0}, humidity{0}, pressure{0} { }
    void registerObserver(std::shared_ptr<Observer> o) override { observers.push_back(o); }
    void removeObserver(std::shared_ptr<Observer>) override;
    void notifyObservers() const override
    {
        for (const auto& i : observers)
            i->update(temperature, humidity, pressure);
    }

    void setMeasurements(double, double, double);
};

class CurrentConditionsDisplay : public Observer, public DisplayElement
{
private:
    double temperature{0}, humidity{0}, pressure{0};
public:
    void update(double, double, double) override;
    void display() const override;
};

class StatisticsDisplay : public Observer, public DisplayElement
{
private:
    double temperature{0}, humidity{0}, pressure{0}, max_temp{0}, max_hum{0}, max_press{0}, min_temp{INT_MAX}, min_hum{INT_MAX}, min_press{INT_MAX};
    int count{0};
public:
    void update(double, double, double) override;
    void display() const override;
};

#endif // OBSERVER_H
