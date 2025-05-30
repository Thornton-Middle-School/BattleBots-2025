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
#include "Driver.h"

// Allows for easier use of the VEX Library
using namespace vex;
using namespace std;

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
    screen.clearScreen();

    screen.setCursor(1, 1);
    screen.print("%s", mode.c_str());

    screen.newLine();
    screen.print("%s", togglemethod.c_str());
}

// Switching drive methods
DriveMode current_mode = DriveMode::Tank;
Driver driver = Driver();

void useTank()
{
    current_mode = DriveMode::Tank;
    UpdateControllerScreen("Using Tank Drive", "Press A to switch to Arcade or B to switch to Split Arcade");
}

void useSplitArcade()
{
    current_mode = DriveMode::SplitArcade;
    UpdateControllerScreen("Using Split Arcade Drive", "Press X to switch to Tank or A to switch to Arcade");
}

void useArcade()
{
    current_mode = DriveMode::Arcade;
    UpdateControllerScreen("Using Arcade Drive", "Press X to switch to Tank or B to switch to Split Arcade");
}

int main()
{
    // Initialization & Callbacks
    vexcodeInit();

    useTank();

    Controller.ButtonA.pressed(useArcade);
    Controller.ButtonB.pressed(useSplitArcade);
    Controller.ButtonX.pressed(useTank);

    // Main Loop
    while (true)
    {
        driver.drive(current_mode);

        // Reduce overhead & let other tasks run
        this_thread::sleep_for(20);
    }

    return 0;
}
