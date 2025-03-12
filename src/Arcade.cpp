#include <bits/stdc++.h>
#include <algorithm>

#include "robot_config.h"
#include "Arcade.h"

using namespace std;
using namespace vex;

void Arcade(motor_group Left_motors, motor_group Right_motors, int Max_Speed)
{
    while (true)
    {
        // Get the joystick values
        int forward = Controller1.Axis3.position();
        int turn = Controller1.Axis1.position();

        // Calculate the motor speeds
        int leftSpeed = forward + turn;
        int rightSpeed = forward - turn;

        leftSpeed = max(min(leftSpeed, Max_Speed), -Max_Speed);
        rightSpeed = max(min(rightSpeed, Max_Speed), -Max_Speed);

        // Set the motor speeds (PLEASE CHECK); TODO
        Left_motors.spin(directionType::fwd, leftSpeed, velocityUnits::pct);
        Right_motors.spin(directionType::fwd, rightSpeed, velocityUnits::pct);

        // Allow other tasks to run
        vex::this_thread::sleep_for(20);
    }
}
