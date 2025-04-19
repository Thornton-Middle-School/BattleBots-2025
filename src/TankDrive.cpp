#include <vex.h>
#include <algorithm>

#include "RobotConfig.h"
#include "TankDrive.h"

using namespace vex;
using namespace std;

void tank_drive(int MaxSpeed)
{
    // y-axis of left & right joysticks (for corresponding side of drive train)
    int leftSpeed = Controller.Axis3.position();
    int rightSpeed = Controller.Axis2.position();

    // Set speeds
    leftSpeed = leftSpeed * MaxSpeed / 100;
    rightSpeed = rightSpeed * MaxSpeed / 100;

    Left.spin(directionType::fwd, leftSpeed, velocityUnits::pct);
    Right.spin(directionType::fwd, rightSpeed, velocityUnits::pct);
}