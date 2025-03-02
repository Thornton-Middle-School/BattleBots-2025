#include <algorithm>
#include <utility>

#include "robot-config.h"

#include "Arcade.h"

void Arcade(motor_group Left_motors, motor_group Right_motors, int Max_Speed) {


while (true) {
    // Get the joystick values
    int forward = Controller1.Axis3.position();
    int turn = Controller1.Axis1.position();

    // Calculate the motor speeds
    int leftSpeed = forward + turn;
    int rightSpeed = forward - turn;

    // Scale the speeds to the maximum speed
    leftSpeed = std::clamp(leftSpeed, -Max_Speed, Max_Speed);
    rightSpeed = std::clamp(rightSpeed, -Max_Speed, Max_Speed);

    // Set the motor speeds
    Left_motors.spin(forward, leftSpeed, velocityUnits::pct);
    Right_motors.spin(forward, rightSpeed, velocityUnits::pct);

    // Allow other tasks to run
    vex::task::sleep(20);
    }
}
