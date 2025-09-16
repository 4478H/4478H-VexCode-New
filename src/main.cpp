/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       4478H                                                     */
/*    Created:      2025                                                      */
/*    Description:  Competition functions                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "main.h"
#include "devices.h"
#include "movement.h"
#include "auton.h"
#include "vex.h"
#include "odometry.h"
#include <iostream>
#include <string>
#include <mutex>

using namespace vex;

void pre_auton(void)
{
  sHood.set(false);
  sHood2.set(false);
  Inertial.calibrate();
  while (Inertial.isCalibrating())
  { // pauses while calibrating IMU
    Brain.Screen.clearScreen();
    printCenter("Inertial Sensor Calibrating");
    wait(50, msec);
  }
  Controller1.rumble("-"); // rumble indicates finished calibration
  Brain.Screen.clearScreen();

  // vex::thread odom(odometry); // after calibrated, can start odometry
  // vex::thread odomData(odomDataCollection);

  AutonSelector &selector = getAutonSelector();
  selector.displayCurrentSelection();
  Brain.Screen.pressed([]()
                       { getAutonSelector().nextSelection(); });

  vex ::wait(4, sec);
}

vex::thread intakeThread;

void autonomous(void)
{
  // intakeThread = vex::thread(colorSortRed);
  // colorSortRed();

  // Calibrates motor encoders to reduce drift
  allMotors.setPosition(0, deg);


  // Performs selected autonomous route
  getAutonSelector().runSelectedAuton();

  // Stops motors to prevent crossing field
  allMotors.stop();
}

bool hood = false;
bool hood2 = false;
bool doink = false;
bool door = false;
bool upInt = false;
bool macro = false;
int count = 0;
bool running = false;
double pollingRate;       // Polling rate in ms // Target position in degrees




void handleTuner()
{
  if (Controller1.ButtonY.pressing())
  {
    std::cout << "enabling tunePID." << std::endl;
    tunePID();
  }
}

void handleMacro()
{
  if (Controller1.ButtonX.pressing())
  {
    macro = !macro; // Toggle macro state
    if (!macro)
      count = 0; // Reset count when turning off
    // Debounce delay to prevent multiple toggles
    wait(240, msec);
  }
  if (macro)
  {
    if (count >= 150)
    { // After ~0.5s of reversing
      macro = false;
      count = 0;
    }
    else if (count >= 4)
    { // After 80ms of ring detection
      mIntake.spin(reverse, 100, pct);
      mIntake2.spin(reverse, 100, pct);
      mIntake3.spin(reverse, 100, pct);
      count++;
    }
    else
    { // Initial forward motion
      mIntake.spin(fwd, 100, pct);
      mIntake2.spin(fwd, 100, pct);
      mIntake3.spin(fwd, 100, pct);
      if (block.objectDistance(inches) <= 1.5)
      {
        count++;
      }
    }
  }
}

void handleIntake()
{
  if (Controller1.ButtonY.pressing())
  {
    mIntake.spin(fwd, 100, pct);
    mIntake2.spin(fwd, 100, pct);
    mIntake3.spin(fwd, 100, pct);
  }
  else if (Controller1.ButtonRight.pressing())
  {
    mIntake.spin(reverse, 100, pct);
    mIntake2.spin(fwd, 100, pct);
    mIntake3.spin(reverse, 100, pct);
  }
  else if (macro == false)
  {
    mIntake.stop();
    mIntake2.stop();
    mIntake3.stop();
  }

  if (Controller1.ButtonUp.pressing())
  {
    mIntake.spin(fwd,90,pct);
    mIntake3.spin(fwd,100,pct);
  }
else if(Controller1.ButtonDown.pressing())
{
  mIntake.spin(fwd,100,pct);
  mIntake2.spin(fwd,100,pct);
  mIntake3.spin(reverse,100,pct);
}
}
/*
void handleDoinky()
{
  if (Controller1.ButtonLeft.pressing())
  {
    doink = !doink; // Toggle clamp state
    doinker.set(doink);
    // Debounce delay to prevent multiple toggles
    wait(240, msec);
  }
}
  */
void handleHood()
{
  if (Controller1.ButtonB.pressing())
  {
    hood = !hood; // Toggle clamp state
    hood2 = !hood2; // Toggle clamp2 state
    sHood.set(hood);
    sHood2.set(hood2);
    // Debounce delay to prevent multiple toggles
    wait(240, msec);
  }
}



void usercontrol(void)
{
  allMotors.stop(coast);

  while (true)
  {

    leftMotors.spin(forward, logDriveJoystick(Controller1.Axis3.position(percent)), pct);
    rightMotors.spin(forward, logDriveJoystick(Controller1.Axis2.position(percent)), pct);

    // handleTuner(); // *** DISABLE DURING COMPS ***
    // handleMacro();
    handleIntake();
    handleHood();

    vex ::wait(20, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    vex ::wait(100, msec);
  }
}

/*
The overloaded function updateController is optimized
to only change the values necessary for increased responsiveness.
1. Updates whole screen (most time-consuming)
2. Updates magnitude (least time-consuming)
3. Changes one line (somewhat time-consuming)
*/
// for changing whole screen
void updateController(double kP, double kI, double kD, int sel, double mag)
{
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(sel + 1, 1);
  Controller1.Screen.print("*"); // creates marker for current selected value
  Controller1.Screen.setCursor(1, 2);
  Controller1.Screen.print(kP);
  Controller1.Screen.setCursor(2, 2);
  Controller1.Screen.print(kI);
  Controller1.Screen.setCursor(3, 2);
  Controller1.Screen.print(kD); // prints P I D on new lines
  Controller1.Screen.setCursor(2, 14);
  Controller1.Screen.print(mag);
}
// for changing just magnitude
void updateController(double mag)
{
  Controller1.Screen.setCursor(2, 14);
  Controller1.Screen.print(mag);
}
// for changing one line
void updateController(double val, double sel, double mag)
{
  sel += 1;
  Controller1.Screen.clearLine(sel);
  Controller1.Screen.setCursor(sel, 1);
  Controller1.Screen.print("*");
  Controller1.Screen.setCursor(sel, 2);
  Controller1.Screen.print(val);
  if (sel == 2)
  {
    updateController(mag);
  }
}

void printCenter(const char *input)
{
  // Screen Size (x,y) = (480, 240)
  int width = Brain.Screen.getStringWidth(input);
  int xOffset = 240 - width / 2;
  if (width <= 480)
  {
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(xOffset, 120, input);
  }
}