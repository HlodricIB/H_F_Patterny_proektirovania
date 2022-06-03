#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <string>
#include <vector>
#include <functional>

class Command;

class Light
{
private:
    std::string location;
public:
    Light(const std::string& location_): location(location_) { }
    ~Light() { }
    void on();
    void off();
};

class CeilingFan
{
private:
    int_least8_t speed{0};
    std::string location;
public:
    enum class Speed : int_least8_t
    {
        HIGH = 3,
        MEDIUM = 2,
        LOW = 1,
        OFF = 0
    };
    CeilingFan(const std::string& location_): location(location_) { }
    ~CeilingFan() { }
    void high();
    void medium();
    void low();
    void off();
    int_least8_t getSpeed() const;
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
private:
    std::string location;
public:
    Stereo(const std::string& location_): location(location_) { }
    ~Stereo() { }
    void on();
    void off();
    void setCd();
    void setDvd();
    void setRadio();
    void setVolume(int);
};

class Command
{
public:
    virtual ~Command() { }
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class LightOnCommand : public Command
{
private:
    std::shared_ptr<Light> receiver{nullptr};
public:
    LightOnCommand(std::shared_ptr<Light> receiver_): receiver(receiver_) { }
    ~LightOnCommand() { }
    void execute() override;
    void undo() override;
};

class LightOffCommand : public Command
{
private:
    std::shared_ptr<Light> receiver{nullptr};
public:
    LightOffCommand(std::shared_ptr<Light> receiver_): receiver(receiver_) { }
    ~LightOffCommand() { }
    void execute() override;
    void undo() override;
};

class StereoOnWithCDCommand : public Command
{
private:
    std::shared_ptr<Stereo> receiver{nullptr};
public:
    StereoOnWithCDCommand(std::shared_ptr<Stereo> receiver_): receiver(receiver_) { }
    ~StereoOnWithCDCommand() { }
    void execute() override;
    void undo() override { };
};

class StereoOnWithDVDCommand : public Command
{
private:
    std::shared_ptr<Stereo> receiver{nullptr};
public:
    StereoOnWithDVDCommand(std::shared_ptr<Stereo> receiver_): receiver(receiver_) { }
    ~StereoOnWithDVDCommand() { }
    void execute() override;
    void undo() override { };
};

class StereoOnWithRadioCommand : public Command
{
private:
    std::shared_ptr<Stereo> receiver{nullptr};
public:
    StereoOnWithRadioCommand(std::shared_ptr<Stereo> receiver_): receiver(receiver_) { }
    ~StereoOnWithRadioCommand() { }
    void execute() override;
    void undo() override { };
};

class StereoOffCommand : public Command
{
private:
    std::shared_ptr<Stereo> receiver{nullptr};
public:
    StereoOffCommand(std::shared_ptr<Stereo> receiver_): receiver(receiver_) { }
    ~StereoOffCommand() { }
    void execute() override;
    void undo() override { };
};

class CeilingFanHighCommand : public Command
{
private:
    std::shared_ptr<CeilingFan> receiver{nullptr};
    int_least8_t prevSpeed;
public:
    CeilingFanHighCommand(std::shared_ptr<CeilingFan> receiver_): receiver(receiver_) { }
    ~CeilingFanHighCommand() { }
    void execute() override;
    void undo() override;
};

class CeilingFanMediumCommand : public Command
{
private:
    std::shared_ptr<CeilingFan> receiver{nullptr};
    int_least8_t prevSpeed;
public:
    CeilingFanMediumCommand(std::shared_ptr<CeilingFan> receiver_): receiver(receiver_) { }
    CeilingFanMediumCommand() { }
    void execute() override;
    void undo() override;
};

class CeilingFanOffCommand : public Command
{
private:
    std::shared_ptr<CeilingFan> receiver{nullptr};
    int_least8_t prevSpeed;
public:
    CeilingFanOffCommand(std::shared_ptr<CeilingFan> receiver_): receiver(receiver_) { }
    CeilingFanOffCommand() { }
    void execute() override;
    void undo() override;
};

void CeilingFanUndo(const std::shared_ptr<CeilingFan>, int_least8_t);

class GarageDoorUpCommand : public Command
{
private:
    std::shared_ptr<GarageDoor> receiver{nullptr};
public:
    GarageDoorUpCommand(std::shared_ptr<GarageDoor> receiver_): receiver(receiver_) { }
    ~GarageDoorUpCommand() { }
    void execute() override;
    void undo() override { };
};

class GarageDoorDownCommand : public Command
{
private:
    std::shared_ptr<GarageDoor> receiver{nullptr};
public:
    GarageDoorDownCommand(std::shared_ptr<GarageDoor> receiver_): receiver(receiver_) { }
    ~GarageDoorDownCommand() { }
    void execute() override;
    void undo() override { };
};

class noCommand : public Command
{
public:
    void execute() override;
    void undo() override { execute(); };
};

class MacroCommand : public Command
{
private:
    std::vector<std::shared_ptr<Command>> commands;
public:
    MacroCommand(std::vector<std::shared_ptr<Command>> commands_): commands(commands_) { }
    void execute() override;
    void undo() override;
};

class RemoteControl
{
private:
    static const size_t slots{12};
    std::shared_ptr<Command> undoCommand;
    std::shared_ptr<Command> onCommands[slots];
    std::shared_ptr<Command> offCommands[slots];
public:
    RemoteControl();
    void setCommand(size_t, std::shared_ptr<Command>, std::shared_ptr<Command>);
    void onButtonWasPushed(size_t);
    void offButtonWasPushed(size_t);
    void undoButtonWasPushed() const;
    std::string toString() const;
};

class RemoteControlWithLambda
{
private:
    static const size_t slots{12};
    std::function<void()> onCommands[slots];
    std::function<void()> offCommands[slots];
public:
    RemoteControlWithLambda();
    void setCommand(size_t, std::function<void()>, std::function<void()>);
    void onButtonWasPushed(size_t);
    void offButtonWasPushed(size_t);
    std::string toString() const;
};

#endif // COMMAND_H
