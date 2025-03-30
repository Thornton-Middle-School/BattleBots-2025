#include <bits/stdc++.h>
#include <algorithm>

#include "RobotConfig.h"
#include "Arcade.h"

using namespace std;
using namespace vex;

void arcade(int MaxSpeed)
{
    while (true)
    {
        // Get the joystick values
        int forward = Controller1.Axis2.position();
        int turn = Controller1.Axis1.position();

        // Calculate the motor speeds
        int leftSpeed = forward + turn;
        int rightSpeed = forward - turn;

        leftSpeed = max(min(leftSpeed, MaxSpeed), -MaxSpeed);
        rightSpeed = max(min(rightSpeed, MaxSpeed), -MaxSpeed);

        // Set the motor speeds (PLEASE CHECK); TODO
        Left.spin(directionType::fwd, leftSpeed, velocityUnits::pct);
        Right.spin(directionType::fwd, rightSpeed, velocityUnits::pct);

        // Allow other tasks to run
        vex::this_thread::sleep_for(20);
    }
}
