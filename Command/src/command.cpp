#include <iostream>
#include <sstream>
#include <iomanip>
#include <boost/core/demangle.hpp>
#include "command.h"

void Light::on()
{
    std::cout << location << " light is on" << std::endl;
}

void Light::off()
{
    std::cout << location << " light is off" << std::endl;
}

void CeilingFan::high()
{
    speed = static_cast<int_least8_t>(Speed::HIGH);
    std::cout << location << " ceiling fan is on high" << std::endl;
}

void CeilingFan::medium()
{
    speed = static_cast<int_least8_t>(Speed::MEDIUM);
    std::cout << location << " ceiling fan is on medium" << std::endl;
}

void CeilingFan::low()
{
    speed = static_cast<int_least8_t>(Speed::LOW);
    std::cout << location << " ceiling fan is on low" << std::endl;
}

void CeilingFan::off()
{
    speed = static_cast<int_least8_t>(Speed::OFF);
    std::cout << location << " ceiling fan is off" << std::endl;
}

int_least8_t CeilingFan::getSpeed() const
{
    return speed;
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
    std::cout << location << " stereo is on" << std::endl;
}

void Stereo::off()
{
    std::cout << location << " stereo is off" << std::endl;
}

void Stereo::setCd()
{
    std::cout << location << " stereo is set for CD input" << std::endl;
}

void Stereo::setDvd()
{
    std::cout << location << " stereo is set for DVD input" << std::endl;
}

void Stereo::setRadio()
{
    std::cout << location << " stereo is set for radio" << std::endl;
}

void Stereo::setVolume(int v)
{
    std::cout << location << " stereo volume set to " << v << std::endl;
}

void LightOnCommand::execute()
{
    receiver->on();
}

void LightOnCommand::undo()
{
    receiver->off();
}

void LightOffCommand::execute()
{
    receiver->off();
}

void LightOffCommand::undo()
{
    receiver->on();
}

void StereoOnWithCDCommand::execute()
{
    receiver->on();
    receiver->setCd();
    receiver->setVolume(11);
}

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

void CeilingFanHighCommand::execute()
{
    prevSpeed = receiver->getSpeed();
    receiver->high();
}

void CeilingFanHighCommand::undo()
{
    CeilingFanUndo(receiver, prevSpeed);
}

void CeilingFanMediumCommand::execute()
{
    prevSpeed = receiver->getSpeed();
    receiver->medium();
}

void CeilingFanMediumCommand::undo()
{
    CeilingFanUndo(receiver, prevSpeed);
}

void CeilingFanOffCommand::execute()
{
    prevSpeed = receiver->getSpeed();
    receiver->off();
}

void CeilingFanOffCommand::undo()
{
    CeilingFanUndo(receiver, prevSpeed);
}

void CeilingFanUndo(const std::shared_ptr<CeilingFan> receiver, const int_least8_t prevSpeed)
{
    if (prevSpeed == static_cast<int_least8_t>(CeilingFan::Speed::HIGH) || prevSpeed == -1)
    {
        receiver->high();
    } else
    {
        if (prevSpeed == static_cast<int_least8_t>(CeilingFan::Speed::MEDIUM))
        {
            receiver->medium();
        } else
        {
            if (prevSpeed == static_cast<int_least8_t>(CeilingFan::Speed::LOW))
            {
                receiver->low();
            } else
            {
                if (prevSpeed == static_cast<int_least8_t>(CeilingFan::Speed::OFF))
                {
                    receiver->off();
                }
            }
        }
    }
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

void MacroCommand::execute()
{
    for(auto& i : commands)
    {
        i->execute();
    }
}

void MacroCommand::undo()
{
    for(auto& i : commands)
    {
        i->undo();
    }
}

RemoteControl::RemoteControl(): undoCommand{std::make_shared<noCommand>()}
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

void RemoteControl::onButtonWasPushed(size_t slot)
{
    onCommands[slot]->execute();
    undoCommand = onCommands[slot];
}

void RemoteControl::offButtonWasPushed(size_t slot)
{
    offCommands[slot]->execute();
    undoCommand = offCommands[slot];
}

void RemoteControl::undoButtonWasPushed() const
{
    undoCommand->undo();
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
    auto undo_command = demangle(typeid (*undoCommand).name());
    stringBuff << "[undo]\t" << undo_command;
    return stringBuff.str();
}

RemoteControlWithLambda::RemoteControlWithLambda()
{
    for (size_t i = 0; i != slots; ++i)
    {
        onCommands[i] = [ ] ( ) { };
        offCommands[i] = [ ] ( ) { };
    }
}

void RemoteControlWithLambda::setCommand(size_t slot,  std::function<void()> onCommand,  std::function<void()> offCommand)
{
    onCommands[slot] = onCommand;
    offCommands[slot] = offCommand;
}

void RemoteControlWithLambda::onButtonWasPushed(size_t slot)
{
    onCommands[slot]();
}

void RemoteControlWithLambda::offButtonWasPushed(size_t slot)
{
    offCommands[slot]();
}

std::string RemoteControlWithLambda::toString() const
{
    using boost::core::demangle;
    std::stringstream stringBuff;
    size_t max_size = 0;
    for (const auto& i : onCommands)
    {
        auto temp_size = demangle(typeid(i).name()).size();
        max_size = std::max(max_size, temp_size);
    }

    stringBuff << "\n------ Remote Control -------\n";
    for (size_t i = 0; i != slots; ++i)
    {
        auto on_command = demangle(typeid(onCommands[i]).name());
        auto temp_size = max_size - on_command.size();
        auto off_command = demangle(typeid(offCommands[i]).name());
        stringBuff << "[slot " << i << "]\t" << on_command << std::string(temp_size, ' ') << '\t'
                    << off_command << "\n";
    }
    return stringBuff.str();
}
