#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <string>

class Command;

class Light{
public:
    virtual ~Light() { }
    virtual void on() = 0;
    virtual void off() = 0;
};

class LivingRoomLight : public Light
{
public:
    LivingRoomLight() { }
    void on() override;
    void off() override;
};

class KitchenLight : public Light
{
public:
    KitchenLight() { }
    void on() override;
    void off() override;
};

class NoLight : public Light
{
private:
    std::string place;
public:
    explicit NoLight(std::string place_): place(place_) { }
    void on() override;
    void off() override;
};

class CeilingFan
{
public:
    virtual ~CeilingFan() { }
    virtual void on() = 0;
    virtual void off() = 0;
};

class LivingRoomCeilingFan : public CeilingFan
{
public:
    LivingRoomCeilingFan() { }
    void on() override;
    void off() override;
};

class NoCeilingFan : public CeilingFan
{
private:
    std::string place;
public:
    NoCeilingFan(std::string place_): place(place_) { }
    void on() override;
    void off() override;
};

class GarageDoor
{
public:
    void on();
    void off();
    void stop();
    void lightOn();
    void lightOff();
};

class Stereo
{
public:
    void on();
    void off();
    void setCd();
    void setDvd();
    void setRadio();
    void setVolume(int);
};

class Command_factory
{
private:
    std::shared_ptr<Light> createLight(std::string);
    std::shared_ptr<CeilingFan> createCeilingFan(std::string);
public:
    Command_factory() { }
    ~Command_factory() { }
    std::shared_ptr<Command> createCommand(const std::string, const std::string);
};

class Command
{
public:
    virtual ~Command() { }
    virtual void execute() = 0;
};

class LightOnCommand : public Command
{
private:
    std::shared_ptr<Light> receiver{nullptr};
public:
    LightOnCommand(std::shared_ptr<Light> receiver_): receiver(receiver_) { }
    void execute() override;
};

class LightOffCommand : public Command
{
private:
    std::shared_ptr<Light> receiver{nullptr};
public:
    LightOffCommand(std::shared_ptr<Light> receiver_): receiver(receiver_) { }
    void execute() override;
};

class StereoOnWithCDCommand : public Command
{
private:
    std::shared_ptr<Stereo> receiver{nullptr};
public:
    StereoOnWithCDCommand(std::shared_ptr<Stereo> receiver_): receiver(receiver_) { }
    void execute() override;
};

class StereoOnWithDVDCommand : public Command
{
private:
    std::shared_ptr<Stereo> receiver{nullptr};
public:
    StereoOnWithDVDCommand(std::shared_ptr<Stereo> receiver_): receiver(receiver_) { }
    void execute() override;
};

class StereoOnWithRadioCommand : public Command
{
private:
    std::shared_ptr<Stereo> receiver{nullptr};
public:
    StereoOnWithRadioCommand(std::shared_ptr<Stereo> receiver_): receiver(receiver_) { }
    void execute() override;
};

class StereoOffCommand : public Command
{
private:
    std::shared_ptr<Stereo> receiver{nullptr};
public:
    StereoOffCommand(std::shared_ptr<Stereo> receiver_): receiver(receiver_) { }
    void execute() override;
};

class CeilingFanOnCommand : public Command
{
private:
    std::shared_ptr<CeilingFan> receiver{nullptr};
public:
    CeilingFanOnCommand(std::shared_ptr<CeilingFan> receiver_): receiver(receiver_) { }
    void execute() override;
};

class CeilingFanOffCommand : public Command
{
private:
    std::shared_ptr<CeilingFan> receiver{nullptr};
public:
    CeilingFanOffCommand(std::shared_ptr<CeilingFan> receiver_): receiver(receiver_) { }
    void execute() override;
};

class GarageDoorUpCommand : public Command
{
private:
    std::shared_ptr<GarageDoor> receiver{nullptr};
public:
    GarageDoorUpCommand(std::shared_ptr<GarageDoor> receiver_): receiver(receiver_) { }
    void execute() override;
};

class GarageDoorDownCommand : public Command
{
private:
    std::shared_ptr<GarageDoor> receiver{nullptr};
public:
    GarageDoorDownCommand(std::shared_ptr<GarageDoor> receiver_): receiver(receiver_) { }
    void execute() override;
};

class noCommand : public Command
{
public:
    void execute() override;
};

class RemoteControl
{
private:
    static const size_t slots{12};
    std::shared_ptr<Command> onCommands[slots];
    std::shared_ptr<Command> offCommands[slots];
public:
    RemoteControl();
    void setCommand(size_t, std::shared_ptr<Command>, std::shared_ptr<Command>);
    void onButtonWasPushed(size_t) const;
    void offButtonWasPushed(size_t) const;
    std::string toString() const;
};


#endif // COMMAND_H
