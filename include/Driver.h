#pragma once
#include "vex.h"

// Constants
#define RELEASED_THRESHOLD 5
#define MAX_SPEED 75
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
    bool hold();
    int accelerate(int current, int target);
    void tank();
    void arcade(bool split);

public:
    Driver();
    void drive(DriveMode mode);
};