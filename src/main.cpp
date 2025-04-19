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

using namespace vex;

// Brain should be defined by default
brain Brain;

// START V5 MACROS
#define waitUntil(condition) \
    do                       \
    {                        \
        wait(5, msec);       \
    } while (!(condition))

#define repeat(iterations) \
    for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS

// generating and setting random seed
void initializeRandomSeed()
{
    int systemTime = Brain.Timer.systemHighResolution();
    double batteryCurrent = Brain.Battery.current();
    double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

    // Combine these values into a single integer
    int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

    // Set the seed
    srand(seed);
}

void vexcodeInit()
{

    // Initializing random seed.
    initializeRandomSeed();
}

// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName)
{
    printf("VEXPlaySound:%s\n", soundName);
    wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration

// Include the V5 Library
#include "vex.h"
#include <RobotConfig.h>
#include <Arcade.h>
#include <TankDrive.h>

// Allows for easier use of the VEX Library
using namespace vex;
using namespace std;

#define eq5(a, b, c, d, e) (a == b && b == c && c == d && d == e)

// For showing what drive control method is used + how to switch
void UpdateScreen(string mode, string togglemethod)
{
    screen.clearScreen();

    screen.setCursor(1, 1);
    screen.print("%s", mode.c_str());

    screen.setCursor(5, 1);
    screen.print("%s", togglemethod.c_str());
}

// Switching drive methods
bool tank = true;

void useTank()
{
    tank = true;
    UpdateScreen("Using Tank Drive", "Press A to switch to Arcade");
}

void useArcade()
{
    tank = false;
    UpdateScreen("Using Arcade Drive", "Press X to switch to Tank");
}

int main()
{
    // Initialization & Callbacks
    vexcodeInit();

    screen.setFont(mono20);

    useTank();

    Controller.ButtonA.pressed(useArcade);
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

        // Drive (MaxSpeed is 75 to not compromise torque as much)
        if (tank)
        {
            tank_drive(75);
        }
        else
        {
            arcade_drive(75);
        }

        // Reduce overhead & let other tasks run
        this_thread::sleep_for(20);
    }

    return 0;
}