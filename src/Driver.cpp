#include "Driver.h"
#include "RobotConfig.h"
#include <stdexcept>
#include <vector>
#include <map>

using namespace vex;
using namespace std;

// Whether or not a specific axis of the controller is basically zero
bool Driver::released(int axis)
{
    return abs(axis) <= RELEASED_THRESHOLD;
}

// Hold the robot completely still if the joystick is in a neutral position
bool Driver::hold(const DriveMode &mode)
{
    // Only check the axes that are used in the current mode
    int first = Controller.Axis1.position();
    int second = Controller.Axis2.position();
    int third = Controller.Axis3.position();
    int fourth = Controller.Axis4.position();

    map<DriveMode, vector<int>> axes = {
        {DriveMode::Tank, {second, third}},
        {DriveMode::Arcade, {first, second}},
        {DriveMode::SplitArcade, {first, third}},
    };

    bool should_hold = true;

    for (int axis : axes[mode])
    {
        if (!released(axis))
        {
            should_hold = false;
            break;
        }
    }

    // Hold & report
    if (should_hold)
    {
        Left.stop(brakeType::hold);
        Right.stop(brakeType::hold);
    }

    return should_hold;
}

// Accelerate the motors' speed by a factor of ACCELERATION to the target speed
int Driver::accelerate(int current, int target)
{
    return current + (target - current) * ACCELERATION;
}

// Tank drive
void Driver::tank()
{
    // Calculate target speed based on joystick position
    int leftTarget = Controller.Axis3.position();
    int rightTarget = Controller.Axis2.position();

    leftTarget = leftTarget * MAX_SPEED / 100;
    rightTarget = rightTarget * MAX_SPEED / 100;

    // current speed of motors
    int leftCurrent = Left.velocity(velocityUnits::pct);
    int rightCurrent = Right.velocity(velocityUnits::pct);

    // accelerate to target speed
    int leftSpeed = accelerate(leftCurrent, leftTarget);
    int rightSpeed = accelerate(rightCurrent, rightTarget);

    Left.spin(directionType::fwd, leftSpeed, velocityUnits::pct);
    Right.spin(directionType::fwd, rightSpeed, velocityUnits::pct);
}

// Arcade drive (split or not)
void Driver::arcade(bool split)
{
    // Calculate target speed based on joystick position
    int forward = (split ? Controller.Axis3 : Controller.Axis2).position();
    int turn = Controller.Axis1.position();

    int leftTarget = forward + turn;
    int rightTarget = forward - turn;

    leftTarget = leftTarget * MAX_SPEED / 100;
    rightTarget = rightTarget * MAX_SPEED / 100;

    // current speed of motors
    int leftCurrent = Left.velocity(velocityUnits::pct);
    int rightCurrent = Right.velocity(velocityUnits::pct);

    // accelerate to target speed
    int leftSpeed = accelerate(leftCurrent, leftTarget);
    int rightSpeed = accelerate(rightCurrent, rightTarget);

    Left.spin(directionType::fwd, leftSpeed, velocityUnits::pct);
    Right.spin(directionType::fwd, rightSpeed, velocityUnits::pct);
}

Driver::Driver() {}

void Driver::drive(const DriveMode &mode)
{
    if (hold(mode))
    {
        return;
    }

    switch (mode)
    {
    case DriveMode::Tank:
        tank();
        break;
    case DriveMode::Arcade:
        arcade(false);
        break;
    case DriveMode::SplitArcade:
        arcade(true);
        break;
    default:
        // could throw an error here, but the robot shouldn't stop working
        tank();
        break;
    }
}