#include <algorithm>
#include <iostream>
#include "observer.h"

void WeatherData::removeObserver(std::shared_ptr<Observer> o)
{
    std::list<std::shared_ptr<Observer>>::iterator iter = std::find(observers.begin(), observers.end(), o);
    if (iter != observers.end())
        observers.erase(iter);
    else
        std::cout << "Specifed observer is not registered" << std::endl;
}

void WeatherData::setMeasurements(double temperature_, double humidity_, double pressure_)
{
    temperature = temperature_;
    humidity = humidity_;
    pressure = pressure_;
    measurementsChanged();
}

void CurrentConditionsDisplay::update(double temperature_, double humidity_, double pressure_)
{
    temperature = temperature_;
    humidity = humidity_;
    pressure = pressure_;
    display();
}

void CurrentConditionsDisplay::display() const
{
    std:: cout << "Current conditions: " << temperature << "F degrees, " << humidity << "% humidity, " << pressure << "bar pressure" << std::endl;
}

void StatisticsDisplay::update(double temperature_, double humidity_, double pressure_)
{
    max_temp = std::max(max_temp, temperature_);
    max_hum = std::max(max_hum, humidity_);
    max_press = std::max(max_press, pressure_);
    min_temp = std::min(min_temp, temperature_);
    min_hum = std::min(min_hum, humidity_);
    min_press = std::min(min_press, pressure_);
    temperature += temperature_;
    humidity += humidity_;
    pressure += pressure_;
    ++count;
    display();
}

void StatisticsDisplay::display() const
{
    std::cout << "Avg/max/min temperature: " << temperature/count << '/' << max_temp << '/' << min_temp << "\n"
                << "Avg/max/min humidity:" << humidity/count << '/' << max_hum << '/' << min_hum << "\n"
                << "Avg/max/min pressure:" << pressure/count << '/' << max_press << '/' << min_press << std::endl;
}
