#include <algorithm>
#include <utility>

#include "robot-config.h"
#include "tank_drive.h"

using namespace vex;
void tank_drive(motor_group Left_motors, motor_group Right_motors, int Max_Speed) {
    while (true) {
        // Get the joystick values
        int leftSpeed = Controller1.Axis3.position();
        int rightSpeed = Controller1.Axis2.position();

        // Scale the speeds to the maximum speed
        leftSpeed = leftSpeed * Max_Speed / 100;
        rightSpeed = rightSpeed * Max_Speed / 100;

        // Set the motor speeds
        Left_motors.spin(forward, leftSpeed, percent);
        Right_motors.spin(forward, rightSpeed, percent);

        // Allow other tasks to run
        task::sleep(20);
    }
}