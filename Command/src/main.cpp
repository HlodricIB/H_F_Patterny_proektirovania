#include <iostream>
#include "command.h"

int main()
{
    {
        //First version, without undo()
        std::cout << "First version, without undo():\n" << std::flush;
        auto remoteControl = std::make_unique<RemoteControl>();

        auto livingRoomLight = std::make_shared<Light>("Living room");
        auto kitchenLight = std::make_shared<Light>("Kitchen");
        auto ceilingFan = std::make_shared<CeilingFan>("Living room");
        auto garageDoor = std::make_shared<GarageDoor>();
        auto stereo = std::make_shared<Stereo>("Living room");

        auto livingRoomLightOn = std::make_shared<LightOnCommand>(livingRoomLight);
        auto livingRoomLightOff = std::make_shared<LightOffCommand>(livingRoomLight);
        auto kitchenLightOn = std::make_shared<LightOnCommand>(kitchenLight);
        auto kitchenLightOff = std::make_shared<LightOffCommand>(kitchenLight);
        auto ceilingFanHigh = std::make_shared<CeilingFanHighCommand>(ceilingFan);
        auto ceilingFanOff = std::make_shared<CeilingFanOffCommand>(ceilingFan);
        auto garageDoorUp = std::make_shared<GarageDoorUpCommand>(garageDoor);
        auto garageDoorDown = std::make_shared<GarageDoorDownCommand>(garageDoor);
        auto stereoOnWithCD = std::make_shared<StereoOnWithCDCommand>(stereo);
        auto stereoOnWithDVD = std::make_shared<StereoOnWithDVDCommand>(stereo);
        auto stereoOnWithRadio = std::make_shared<StereoOnWithRadioCommand>(stereo);
        auto stereoOff = std::make_shared<StereoOffCommand>(stereo);

        remoteControl->setCommand(0, livingRoomLightOn, livingRoomLightOff);
        remoteControl->setCommand(1, kitchenLightOn, kitchenLightOff);
        remoteControl->setCommand(2, ceilingFanHigh, ceilingFanOff);
        remoteControl->setCommand(3, garageDoorUp, garageDoorDown);
        remoteControl->setCommand(4, stereoOnWithCD, stereoOff);
        remoteControl->setCommand(5, stereoOnWithDVD, stereoOff);
        remoteControl->setCommand(6, stereoOnWithRadio, stereoOff);
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
    }

    {
        //Second version, undo() added
        std::cout << "\nSecond version, undo() added:\n" << std::flush;
        auto remoteControl = std::make_unique<RemoteControl>();

        auto livingRoomLight = std::make_shared<Light>("Living room");
        auto ceilingFan = std::make_shared<CeilingFan>("Living room");

        auto livingRoomLightOn = std::make_shared<LightOnCommand>(livingRoomLight);
        auto livingRoomLightOff = std::make_shared<LightOffCommand>(livingRoomLight);

        auto ceilingFanHigh = std::make_shared<CeilingFanHighCommand>(ceilingFan);
        auto ceilingFanMedium = std::make_shared<CeilingFanMediumCommand>(ceilingFan);
        auto ceilingFanOff = std::make_shared<CeilingFanOffCommand>(ceilingFan);

        remoteControl->setCommand(0, livingRoomLightOn, livingRoomLightOff);
        remoteControl->setCommand(1, ceilingFanMedium, ceilingFanOff);
        remoteControl->setCommand(2, ceilingFanHigh, ceilingFanOff);

        remoteControl->onButtonWasPushed(0);
        remoteControl->offButtonWasPushed(0);
        std::cout << remoteControl->toString() << std::endl;
        remoteControl->undoButtonWasPushed();
        remoteControl->offButtonWasPushed(0);
        remoteControl->onButtonWasPushed(0);
        std::cout << remoteControl->toString() << std::endl;
        remoteControl->undoButtonWasPushed();

        std::cout << std::endl;

        remoteControl->onButtonWasPushed(1);
        remoteControl->offButtonWasPushed(1);
        std::cout << remoteControl->toString() << std::endl;
        remoteControl->undoButtonWasPushed();
        remoteControl->onButtonWasPushed(2);
        std::cout << remoteControl->toString() << std::endl;
        remoteControl->undoButtonWasPushed();
    }

    {
        //Third version, Macrocommand added
        std::cout << "\nThird version, Macrocommand added:\n" << std::flush;
        auto remoteControl = std::make_unique<RemoteControl>();

        auto livingRoomLight = std::make_shared<Light>("Living room");
        auto ceilingFan = std::make_shared<CeilingFan>("Living room");
        auto stereo = std::make_shared<Stereo>("Living room");

        auto livingRoomLightOn = std::make_shared<LightOnCommand>(livingRoomLight);
        auto livingRoomLightOff = std::make_shared<LightOffCommand>(livingRoomLight);
        auto ceilingFanHigh = std::make_shared<CeilingFanHighCommand>(ceilingFan);
        auto ceilingFanOff = std::make_shared<CeilingFanOffCommand>(ceilingFan);

        std::vector<std::shared_ptr<Command>> partyOn = {livingRoomLightOn, ceilingFanHigh};
        std::vector<std::shared_ptr<Command>> partyOff = {livingRoomLightOff, ceilingFanOff};
        auto partyOnMacro = std::make_shared<MacroCommand>(partyOn);
        auto partyOffMacro = std::make_shared<MacroCommand>(partyOff);

        remoteControl->setCommand(0, partyOnMacro, partyOffMacro);
        std::cout << remoteControl->toString() << std::endl;
        std::cout << "---Pushing Macro On---\n" << std::flush;
        remoteControl->onButtonWasPushed(0);
        std::cout << "---Pushing Macro Off---\n" << std::flush;
        remoteControl->offButtonWasPushed(0);
        std::cout << "---Pushing undo---\n" << std::flush;
        remoteControl->undoButtonWasPushed();
    }

    {
        //Fourth version, lambdas added
        std::cout << "\nFourth version, lambdas added:\n" << std::flush;
        auto remoteControlWithLambda = std::make_unique<RemoteControlWithLambda>();

        auto livingRoomLight = std::make_shared<Light>("Living room");
        auto kitchenLight = std::make_shared<Light>("Kitchen");
        auto ceilingFan = std::make_shared<CeilingFan>("Living room");
        auto garageDoor = std::make_shared<GarageDoor>();
        auto stereo = std::make_shared<Stereo>("Living room");

        auto stereoOnWithCD = [stereo] ( ) {
            stereo->on();
            stereo->setCd();
            stereo->setVolume(11);
        };

        remoteControlWithLambda->setCommand(0, std::bind(&Light::on, livingRoomLight), std::bind(&Light::off, livingRoomLight));
        remoteControlWithLambda->setCommand(1, std::bind(&Light::on, kitchenLight), std::bind(&Light::off, kitchenLight));
        remoteControlWithLambda->setCommand(2, std::bind(&CeilingFan::high, ceilingFan), std::bind(&CeilingFan::off, ceilingFan));
        remoteControlWithLambda->setCommand(3, std::bind(&GarageDoor::on, garageDoor), std::bind(&GarageDoor::off, garageDoor));
        remoteControlWithLambda->setCommand(4, stereoOnWithCD, std::bind(&Stereo::off, stereo));
        std::cout << remoteControlWithLambda->toString() << std::endl;
        remoteControlWithLambda->onButtonWasPushed(0);
        remoteControlWithLambda->offButtonWasPushed(0);
        remoteControlWithLambda->onButtonWasPushed(1);
        remoteControlWithLambda->offButtonWasPushed(1);
        remoteControlWithLambda->onButtonWasPushed(2);
        remoteControlWithLambda->offButtonWasPushed(2);
        remoteControlWithLambda->onButtonWasPushed(3);
        remoteControlWithLambda->offButtonWasPushed(3);
        remoteControlWithLambda->onButtonWasPushed(4);
        remoteControlWithLambda->offButtonWasPushed(4);
    }
    return 0;
}
