#pragma once
#include "vex.h"

// The threshold for the axes to be considered released
#define RELEASED_THRESHOLD 5

// The maximum speed of the robot in percent
#define MAX_SPEED 75

// The acceleration factor for the motors (between 0 & 1).
// For now it's 1.0f, but it can be simply changed
#define ACCELERATION 1.0f

// Which drive method to use
enum class DriveMode
{
    Tank,
    Arcade,
    SplitArcade
};

// controls the drive train
class Driver
{
private:
    bool released(int value);
    bool hold(const DriveMode &mode);
    int accelerate(int current, int target);
    void tank();
    void arcade(bool split);

public:
    Driver();
    void drive(const DriveMode &mode);
};