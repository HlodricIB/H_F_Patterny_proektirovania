#include"facade.h"

int main()
{
    auto amp = std::make_shared<Amplifier>();
    auto dvd = std::make_shared<DvdPlayer>();
    auto projector = std::make_shared<Projector>();
    auto lights = std::make_shared<TheaterLights>();
    auto screen = std::make_shared<Screen>();
    auto popper = std::make_shared<PopcornPopper>();

    auto homeTheater =  std::make_shared<HomeTheaterFacade>(amp, dvd, projector, lights, screen, popper);
    homeTheater->watchMovie("Raiders of the Lost Ark");
    homeTheater->endMovie();
    return 0;
}
