#include <iostream>
#include "command.h"

int main()
{
    auto remoteControl = std::make_unique<RemoteControl>();

    auto command_Factory = std::make_unique<Command_factory>();

    auto livingRoomLightOn = command_Factory->createCommand(std::string("LightOnCommand"), std::string("Living Room"));
    auto livingRoomLightOff = command_Factory->createCommand(std::string("LightOffCommand"), std::string("Living Room"));
    auto kitchenLightOn = command_Factory->createCommand(std::string("LightOnCommand"), std::string("Kitchen"));
    auto kitchenLightOff = command_Factory->createCommand(std::string("LightOffCommand"), std::string("Kitchen"));
    auto gardenLightOn = command_Factory->createCommand(std::string("LightOnCommand"), std::string("Garden"));
    auto gardenLightOff = command_Factory->createCommand(std::string("LightOffCommand"), std::string("Garden"));

    auto ceilingFanOn = command_Factory->createCommand(std::string("CeilingFanOnCommand"), std::string("Living Room"));
    auto ceilingFanOff = command_Factory->createCommand(std::string("CeilingFanOffCommand"), std::string("Living Room"));
    auto garageCeilingFanOn = command_Factory->createCommand(std::string("CeilingFanOnCommand"), std::string("Garage"));
    auto garageCeilingFanOff = command_Factory->createCommand(std::string("CeilingFanOffCommand"), std::string("Garage"));

    auto garageDoorUp = command_Factory->createCommand(std::string("GarageDoorUpCommand"), std::string());
    auto garageDoorDown = command_Factory->createCommand(std::string("GarageDoorDownCommand"), std::string());

    auto stereoOnWithCD = command_Factory->createCommand(std::string("StereoOnWithCDCommand"), std::string());
    auto stereoOnWithDVD= command_Factory->createCommand(std::string("StereoOnWithDVDCommand"), std::string());
    auto stereoOnWithRadio= command_Factory->createCommand(std::string("StereoOnWithRadioCommand"), std::string());
    auto stereoOff = command_Factory->createCommand(std::string("StereoOffCommand"), std::string());

    remoteControl->setCommand(0, livingRoomLightOn, livingRoomLightOff);
    remoteControl->setCommand(1, kitchenLightOn, kitchenLightOff);
    remoteControl->setCommand(2, gardenLightOn, gardenLightOff);
    remoteControl->setCommand(3, ceilingFanOn, ceilingFanOff);
    remoteControl->setCommand(4, garageCeilingFanOn, garageCeilingFanOff);
    remoteControl->setCommand(5, garageDoorUp, garageDoorDown);
    remoteControl->setCommand(6, stereoOnWithCD, stereoOff);
    remoteControl->setCommand(7, stereoOnWithDVD, stereoOff);
    remoteControl->setCommand(8, stereoOnWithRadio, stereoOff);
    std::cout << remoteControl->toString() << std::endl;
    remoteControl->onButtonWasPushed(0);
    remoteControl->offButtonWasPushed(0);
    remoteControl->onButtonWasPushed(1);
    remoteControl->offButtonWasPushed(1);
    remoteControl->onButtonWasPushed(2);
    remoteControl->offButtonWasPushed(2);
    remoteControl->onButtonWasPushed(3);
    remoteControl->offButtonWasPushed(3);
    remoteControl->onButtonWasPushed(4);
    remoteControl->offButtonWasPushed(4);
    remoteControl->onButtonWasPushed(5);
    remoteControl->offButtonWasPushed(5);
    remoteControl->onButtonWasPushed(6);
    remoteControl->offButtonWasPushed(6);
    remoteControl->onButtonWasPushed(7);
    remoteControl->offButtonWasPushed(7);
    remoteControl->onButtonWasPushed(8);
    remoteControl->offButtonWasPushed(8);
    return 0;
}
