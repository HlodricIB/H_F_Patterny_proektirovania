#ifndef FACADE_H
#define FACADE_H

#include<memory>
#include <iostream>
#include <string>

class DvdPlayer
{
private:
    std::string movie;
public:
    DvdPlayer() = default;
    void on() const { std::cout << "Top-O-Line DVD Player on" << std::endl; };
    void play(std::string movie_) { movie = movie_; std::cout << "Top-O-Line DVD Player playing \"" << movie << '\"' << std::endl; }
    const std::string name() const { return "Top-O-Line DVD Player"; }
    void stop() const { std::cout << "Top-O-Line DVD Player stopped \"" << movie << '\"' << std::endl; }
    void eject() const { std::cout << "Top-O-Line DVD Player eject" << std::endl; }
    void off() const { std::cout << "Top-O-Line DVD Player off" << std::endl; }
};

class Amplifier
{
public:
    void on() const { std::cout << "Top-O-Line Amplifier on" << std::endl; }
    void setDvd(std::shared_ptr<DvdPlayer> dvd) const { std::cout << "Top-O-Line Amplifier setting DVD player to " << dvd->name() << std::endl; }
    void setSurroundSound() const { std::cout << "Top-O-Line Amplifier surround sound on (5 speakers, 1 subwoofer)" << std::endl; }
    void setVolume(int v) const { std::cout << "Top-O-Line Amplifier setting volume to " << v << std::endl; }
    void off() const { std::cout << "Top-O-Line Amplifier off" << std::endl; }
};

class Projector
{
public:
    void on() const { std::cout << "Top-O-Line Projector on" << std::endl; }
    void wideScreenMode() const { std::cout << "Top-O-Line Projector in widescreen mode (16x9 aspect ratio)" << std::endl; }
    void off() const { std::cout << "Top-O-Line Projector off" << std::endl; }
};

class TheaterLights
{
public:
    void dim(int d) const { std::cout << "Theater Ceiling Lights dimming to " << d << '%' << std::endl; }
    void on() const { std::cout << "Theater Ceiling Lights on" << std::endl; }

};

class Screen
{
public:
    void down() const { std::cout << "Theater Screen going down" << std::endl; }
    void up() const { std::cout << "Theater Screen going up" << std::endl; }
};

class PopcornPopper
{
public:
    void on() const { std::cout << "Popcorn Popper on" << std::endl; }
    void pop() const { std::cout << "Popcorn Popper popping popcorn!" << std::endl; }
    void off() const { std::cout << "Popcorn Popper off" << std::endl; }
};

class HomeTheaterFacade
{
private:
    std::shared_ptr<Amplifier> amp{nullptr};
    std::shared_ptr<DvdPlayer> dvd{nullptr};
    std::shared_ptr<Projector> projector{nullptr};
    std::shared_ptr<TheaterLights> lights{nullptr};
    std::shared_ptr<Screen> screen{nullptr};
    std::shared_ptr<PopcornPopper> popper{nullptr};
public:
    HomeTheaterFacade(std::shared_ptr<Amplifier> amp_,
                      std::shared_ptr<DvdPlayer> dvd_,
                      std::shared_ptr<Projector> projector_,
                      std::shared_ptr<TheaterLights> lights_,
                      std::shared_ptr<Screen> screen_,
                      std::shared_ptr<PopcornPopper> popper_): amp(amp_), dvd(dvd_), projector(projector_), lights(lights_),
        screen(screen_), popper(popper_) { }
    void watchMovie(std::string);
    void endMovie();
};

#endif // FACADE_H
