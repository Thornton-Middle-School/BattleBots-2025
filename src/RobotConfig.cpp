#include <vex.h>
#include "RobotConfig.h"

using namespace vex;

brain Brain;
brain::lcd &screen = Brain.Screen;

controller Controller = controller();

motor LeftMotorA = motor(PORT1, ratio18_1, true);
motor LeftMotorB = motor(PORT2, ratio18_1, true);
motor LeftMotorC = motor(PORT3, ratio18_1, true);
motor LeftMotorD = motor(PORT4, ratio18_1, true);
motor RightMotorA = motor(PORT5, ratio18_1, false);
motor RightMotorB = motor(PORT6, ratio18_1, false);
motor RightMotorC = motor(PORT7, ratio18_1, false);
motor RightMotorD = motor(PORT8, ratio18_1, false);

motor_group Left = motor_group(LeftMotorA, LeftMotorB, LeftMotorC, LeftMotorD);
motor_group Right = motor_group(RightMotorA, RightMotorB, RightMotorC, RightMotorD);
