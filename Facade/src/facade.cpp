#include "facade.h"

void HomeTheaterFacade::watchMovie(std::string movie)
{
    std::cout << "Get ready to watch a movie..." << std::endl;
    popper->on();
    popper->pop();
    lights->dim(10);
    screen->down();
    projector->on();
    projector->wideScreenMode();
    amp->on();
    amp->setDvd(dvd);
    amp->setSurroundSound();
    amp->setVolume(5);
    dvd->on();
    dvd->play(movie);
}

void  HomeTheaterFacade::endMovie()
{
    std::cout << "Shutting movie theater down..." << std::endl;
    popper->off();
    lights->on();
    screen->up();
    projector->off();
    amp->off();
    dvd->stop();
    dvd->eject();
    dvd->off();
}
