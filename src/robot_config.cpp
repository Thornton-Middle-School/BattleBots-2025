#include "robot_config.h"

motor LeftMotorA = motor(PORT1, ratio18_1, true);   // Left motor A on port 1
motor LeftMotorB = motor(PORT2, ratio18_1, true);    // Left motor B on port 2
motor LeftMotorC = motor(PORT3, ratio18_1, true);   // Left motor C on port 3
motor LeftMotorD = motor(PORT4, ratio18_1, true);    // Left motor D on port 4
motor RightMotorA = motor(PORT5, ratio18_1, false);  // Right motor A on port 5
motor RightMotorB = motor(PORT6, ratio18_1, false);  // Right motor B on port 6
motor RightMotorC = motor(PORT7, ratio18_1, false);  // Right motor C on port 7
motor RightMotorD = motor(PORT8, ratio18_1, false);  // Right motor D on port 8

motor_group Left = motor_group(LeftMotorA, LeftMotorB, LeftMotorC, LeftMotorD);
// Group for Right motors
motor_group Right = motor_group(RightMotorA, RightMotorB, RightMotorC, RightMotorD);

