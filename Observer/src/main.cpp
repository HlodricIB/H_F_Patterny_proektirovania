#include <memory>
#include "observer.h"

int main()
{
    WeatherData weatherData;
    std::shared_ptr<Observer> currentDisplay(new CurrentConditionsDisplay);
    std::shared_ptr<Observer> statisticsDisplay(new StatisticsDisplay);
    weatherData.registerObserver(currentDisplay);
    weatherData.registerObserver(statisticsDisplay);
    weatherData.setMeasurements(80, 65, 30.4);
    weatherData.setMeasurements(82, 70, 29.2);
    weatherData.setMeasurements(78, 90, 29.2);
    return 0;
}
