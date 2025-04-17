/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Varun                                                   */
/*    Created:      2/28/2025, 12:41:41 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "RobotConfig.h"
#include "TankDrive.h"
#include "Arcade.h"

#include <bits/stdc++.h>

using namespace std;
using namespace vex;

#define eq5(a, b, c, d, e) (a == b && b == c && c == d && d == e)

vex::brain Brain;
auto &screen = Brain.Screen;

void UpdateScreen(string current, string howtotoggle)
{
    screen.clearScreen();

    screen.setCursor(1, 1);
    screen.print(current);

    screen.setCursor(5, 1);
    screen.print(howtotoggle);
}

int main()
{
    bool tank = true;
    screen.setFont(mono20);

    UpdateScreen("Using Tank Drive", "Press A to switch to Arcade");

    while (true)
    {
        if (eq5(Controller1.Axis1.position(), Controller1.Axis2.position(), Controller1.Axis3.position(), Controller1.Axis4.position(), 0)) {
            Left.stop(V5MotorBrakeMode::hold);
            Right.stop(V5MotorBrakeMode::hold);
        }

        if (tank)
        {
            tank_drive(75);
        }
        else
        {
            arcade(75);
        }

        if (Controller1.ButtonA.pressing() && tank)
        {
            tank = false;
            UpdateScreen("Using Arcade Drive", "Press X to switch to Tank");
        }

        if (Controller1.ButtonX.pressing() && !tank)
        {
            tank = true;
            UpdateScreen("Using Tank Drive", "Press A to switch to Arcade");
        }
    }

    return 0;
}
