#include <vex.h>

#include "RobotConfig.h"
#include "Arcade.h"

using namespace std;
using namespace vex;

#define clip(val, minima, maxima) std::max(std::min(val, maxima), minima)

void arcade_drive(int MaxSpeed, bool split)
{
    // Look at x & y axis of right joystick
    int forward = (split ? Controller.Axis3 : Controller.Axis2).position();
    int turn = Controller.Axis1.position();

    // Set speeds
    int leftSpeed = forward + turn;
    int rightSpeed = forward - turn;

    leftSpeed = clip(leftSpeed, -MaxSpeed, MaxSpeed);
    rightSpeed = clip(rightSpeed, -MaxSpeed, MaxSpeed);

    Left.spin(directionType::fwd, leftSpeed, velocityUnits::pct);
    Right.spin(directionType::fwd, rightSpeed, velocityUnits::pct);
}