#include <iostream>
#include <sstream>
#include <iomanip>
#include <boost/core/demangle.hpp>
#include "command.h"

void LivingRoomLight::on()
{
    std::cout << "Living Room light is on" << std::endl;
}

void LivingRoomLight::off()
{
    std::cout << "Living Room light is off" << std::endl;
}

void KitchenLight::on()
{
    std::cout << "Kitchen light is on" << std::endl;
}

void KitchenLight::off()
{
    std::cout << "Kitchen light is off" << std::endl;
}

void NoLight::on()
{
    std::cout << "There is no light in specified place: " << place << std::endl;
}

void NoLight::off()
{
    std::cout << "There is no light in specified place: " << place << std::endl;
}

void LivingRoomCeilingFan::on()
{
    std::cout << "Living Room ceiling fan is on high" << std::endl;
}

void LivingRoomCeilingFan::off()
{
    std::cout << "Living Room ceiling fan is off" << std::endl;
}

void NoCeilingFan::on()
{
    std::cout << "There is no ceiling fan in specified place: " << place << std::endl;
}

void NoCeilingFan::off()
{
    std::cout << "There is no ceiling fan in specified place: " << place << std::endl;
}

void GarageDoor::on()
{
    std::cout << "Garage door opened" << std::endl;
}

void GarageDoor::off()
{
    std::cout << "Garage door closed" << std::endl;
}

void GarageDoor::stop()
{
    std::cout << "Garage door stopped" << std::endl;
}

void GarageDoor::lightOn()
{
    std::cout << "Garage light is on" << std::endl;
}

void GarageDoor::lightOff()
{
    std::cout << "Garage light is off" << std::endl;
}

void Stereo::on()
{
    std::cout << "Living Room stereo is on" << std::endl;
}

void Stereo::off()
{
    std::cout << "Living Room stereo is off" << std::endl;
}

void Stereo::setCd()
{
    std::cout << "Living Room stereo is set for CD input" << std::endl;
}

void Stereo::setDvd()
{
    std::cout << "Living Room stereo is set for DVD input" << std::endl;
}

void Stereo::setRadio()
{
    std::cout << "Living Room stereo is set for radio" << std::endl;
}

void Stereo::setVolume(int v)
{
    std::cout << "Living Room Stereo volume set to " << v << std::endl;
}

std::shared_ptr<Command> Command_factory::createCommand(std::string command, std::string place)
{
    if (command == "LightOnCommand")
    {
        return std::make_shared<LightOnCommand>(createLight(place));
    } else
    {
        if (command == "LightOffCommand")
        {
            return std::make_shared<LightOffCommand>(createLight(place));
        } else
        {
            if (command == "StereoOnWithCDCommand")
            {
                return std::make_shared<StereoOnWithCDCommand>(std::make_shared<Stereo>());
            } else
            {
                if (command == "StereoOffCommand")
                {
                    return std::make_shared<StereoOffCommand>(std::make_shared<Stereo>());
                } else
                {
                    if (command == "CeilingFanOnCommand")
                    {
                        return std::make_shared<CeilingFanOnCommand>(createCeilingFan(place));
                    } else
                    {
                        if (command == "CeilingFanOffCommand")
                        {
                            return std::make_shared<CeilingFanOffCommand>(createCeilingFan(place));
                        } else
                        {
                            if (command == "GarageDoorUpCommand")
                            {
                                return std::make_shared<GarageDoorUpCommand>(std::make_shared<GarageDoor>());
                            } else
                            {
                                if (command == "GarageDoorDownCommand")
                                {
                                    return std::make_shared<GarageDoorDownCommand>(std::make_shared<GarageDoor>());
                                } else
                                {
                                    if (command == "StereoOnWithDVDCommand")
                                    {
                                        return std::make_shared<StereoOnWithDVDCommand>(std::make_shared<Stereo>());
                                    } else
                                    {
                                        if (command == "StereoOnWithRadioCommand")
                                        {
                                            return std::make_shared<StereoOnWithRadioCommand>(std::make_shared<Stereo>());
                                        } else
                                        {
                                            return std::make_shared<noCommand>();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

std::shared_ptr<Light> Command_factory::createLight(std::string place)
{
    if (place == "Living Room")
    {
        return std::make_shared<LivingRoomLight>();
    } else
    {
        if (place == "Kitchen")
        {
            return std::make_shared<KitchenLight>();
        } else
        {
            return std::make_shared<NoLight>(place);
        }
    }
}

std::shared_ptr<CeilingFan> Command_factory::createCeilingFan(std::string place)
{
    if (place == "Living Room")
    {
        return std::make_shared<LivingRoomCeilingFan>();
    } else
    {
        return std::make_shared<NoCeilingFan>(place);
    }
}

void LightOnCommand::execute()
{
    receiver->on();
}

void LightOffCommand::execute()
{
    receiver->off();
}

void StereoOnWithCDCommand::execute()
{
    receiver->on();
    receiver->setCd();
    receiver->setVolume(11);
}
\
void StereoOnWithDVDCommand::execute()
{
    receiver->on();
    receiver->setDvd();
    receiver->setVolume(12);
}

void StereoOnWithRadioCommand::execute()
{
    receiver->on();
    receiver->setRadio();
    receiver->setVolume(13);
}

void StereoOffCommand::execute()
{
    receiver->off();
}

void CeilingFanOnCommand::execute()
{
    receiver->on();
}

void CeilingFanOffCommand::execute()
{
    receiver->off();
}

void GarageDoorUpCommand::execute()
{
    receiver->on();
    receiver->stop();
    receiver->lightOn();
}

void GarageDoorDownCommand::execute()
{
    receiver->off();
    receiver->stop();
    receiver->lightOff();
}

void noCommand::execute()
{
    std::cout << "No command is set for that slot" << std::endl;
}

RemoteControl::RemoteControl()
{
    for (size_t i = 0; i != slots; ++i)
    {
        onCommands[i] = std::make_shared<noCommand>();
        offCommands[i] = std::make_shared<noCommand>();
    }
}

void RemoteControl::setCommand(size_t slot, std::shared_ptr<Command> onCommand, std::shared_ptr<Command> offCommand)
{
    onCommands[slot] = onCommand;
    offCommands[slot] = offCommand;
}

void RemoteControl::onButtonWasPushed(size_t slot) const
{
    onCommands[slot]->execute();
}

void RemoteControl::offButtonWasPushed(size_t slot) const
{
    offCommands[slot]->execute();
}

std::string RemoteControl::toString() const
{
    using boost::core::demangle;
    std::stringstream stringBuff;
    size_t max_size = 0;
    for (const auto& i : onCommands)
    {
        auto temp_size = demangle(typeid(*i).name()).size();
        max_size = std::max(max_size, temp_size);
    }

    stringBuff << "\n------ Remote Control -------\n";
    for (size_t i = 0; i != slots; ++i)
    {
        auto on_command = demangle(typeid(*(onCommands[i])).name());
        auto temp_size = max_size - on_command.size();
        auto off_command = demangle(typeid(*(offCommands[i])).name());
        stringBuff << "[slot " << i << "]\t" << on_command << std::string(temp_size, ' ') << '\t'
                    << off_command << "\n";
    }
    return stringBuff.str();
}
