/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Pranav Maddineedi & Varun Chinthoju                       */
/*    Created:      2/28/2025, 12:41:41 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Pragma: Automatically generated

#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "vex.h"
#include "RobotConfig.h"
#include "Arcade.h"
#include "TankDrive.h"

// Allows for easier use of the VEX Library
using namespace vex;
using namespace std;

#define eq5(a, b, c, d, e) (a == b && a == c && a == d && a == e)

void vexcodeInit()
{
    // Initializing random seed.
    int systemTime = Brain.Timer.systemHighResolution();
    double batteryCurrent = Brain.Battery.current();
    double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

    // Combine these values into a single integer
    int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

    // Set the seed
    srand(seed);
}

// For showing what drive control method is used + how to switch
void UpdateControllerScreen(string mode, string togglemethod)
{
    Controller.Screen.clearScreen();

    Controller.Screen.setCursor(1, 1);
    Controller.Screen.print("%s", mode.c_str());

    Controller.Screen.setCursor(5, 1);
    Controller.Screen.print("%s", togglemethod.c_str());
}

// Switching drive methods
enum class DriveMode
{
    Tank,
    Arcade,
    SplitArcade
};

DriveMode method = DriveMode::Tank;

void useTank()
{
    method = DriveMode::Tank;
    UpdateControllerScreen("Using Tank Drive", "Press A to switch to Arcade or B to switch to Split Arcade");
    tank_drive(75);
}

void useSplitArcade()
{
    method = DriveMode::SplitArcade;
    UpdateControllerScreen("Using Split Arcade Drive", "Press X to switch to Tank or A to switch to Arcade");
    arcade_drive(75, true);
}

void useArcade()
{
    method = DriveMode::Arcade;
    UpdateControllerScreen("Using Arcade Drive", "Press X to switch to Tank or B to switch to Split Arcade");
    arcade_drive(75, false);
}

int main()
{
    // Initialization & Callbacks
    vexcodeInit();

    useTank();
    screen.setFont(mono20);

    Controller.ButtonA.pressed(useArcade);
    Controller.ButtonB.pressed(useSplitArcade);
    Controller.ButtonX.pressed(useTank);

    // Main Loop
    while (true)
    {
        // Hold everything still if joysticks' states are unchanged
        if (eq5(Controller.Axis1.position(), Controller.Axis2.position(), Controller.Axis3.position(), Controller.Axis4.position(), 0))
        {
            Left.stop(brakeType::hold);
            Right.stop(brakeType::hold);
        }

        // Reduce overhead & let other tasks run
        this_thread::sleep_for(20);
    }

    return 0;
}