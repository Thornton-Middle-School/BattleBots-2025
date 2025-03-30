#include <bits/stdc++.h>

#include "RobotConfig.h"
#include "TankDrive.h"

using namespace vex;
void tank_drive(int MaxSpeed)
{
    while (true)
    {
        // Get the joystick values
        int leftSpeed = Controller1.Axis3.position();
        int rightSpeed = Controller1.Axis2.position();

        // Scale the speeds to the maximum speed
        leftSpeed = leftSpeed * MaxSpeed / 100;
        rightSpeed = rightSpeed * MaxSpeed / 100;

        // Set the motor speeds
        Left.spin(vex::forward, leftSpeed, percent);
        Right.spin(vex::forward, rightSpeed, percent);

        // Allow other tasks to run
        task::sleep(20);
    }
}