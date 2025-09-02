/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton.cpp                                                 */
/*    Author:       4478B                                                     */
/*    Created:      Sat Nov 16 2024                                           */
/*    Description:  auton selector and auton routes                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "auton.h"
#include "devices.h"
#include "movement.h"
#include "vex.h"
#include "main.h"
#include <iostream>
using namespace vex;

/*
 * Framework for the autonomous selector.
 * Add/remove routines by editing the "routines" array below.
 */

// Full definition of AutonRoutine struct
struct AutonRoutine
{
  const char *displayName;
  std::function<void(int)> routine;
  int multiplier;
};

// Define the routines array
static const AutonRoutine ROUTINES[] = {
    {"Red Goal Side Two Top Rings", rightAuto, 1},      // Route 1
    {"Red 3 Ring, Ring side", halfAWP, -1},    // Route 2
    {"Elim Blue 4 Ring, Ring Side ", AWP, 1}, // Route 3
    {"Skills", skillsAuto, 1},         // Route 4
    {"Elim Red 4 Ring, Ring Side ", AWP, -1},                   // Route 5
    {"Blue 3 Ring, Ring side", halfAWP, 1},  // Route 6
    {"Blue Goal Side Two Top Rings", rightAuto, -1}, // Route 7
    {"Red AWP Goal Side, Full Field, 3 Ring", blueLeftAuto, 1}  // Route 8
};

// Create static instance
static AutonSelector instance;

// Constructor implementation
AutonSelector::AutonSelector() : routines(ROUTINES),
                                 currentSelection(5), // Start with AWP (Route 5)
                                 routineCount(sizeof(ROUTINES) / sizeof(ROUTINES[0]))
{
}

void AutonSelector::nextSelection()
{
  currentSelection = (currentSelection % routineCount) + 1;
  displayCurrentSelection();
}

void AutonSelector::displayCurrentSelection()
{
  Brain.Screen.clearLine();
  printCenter(routines[currentSelection - 1].displayName);
}

void AutonSelector::runSelectedAuton()
{
  const AutonRoutine &selected = routines[currentSelection - 1];
  selected.routine(selected.multiplier);
}

int AutonSelector::getCurrentSelection() const
{
  return currentSelection;
}

// Global instance getter implementation
AutonSelector &getAutonSelector()
{
  return instance;
}

//=============================================================================

/* Autonomous routines */
void skillsAuto(int i)
{

}
void blueRightAuto(int i) // i is if its inversed or not (1 = regular, -1 = inversed)
{

}
void blueLeftAuto(int i)
{
//Drives to Loader
drivePID(31);
//Turn to loader
inert(90);
// inatke balls



}
void redleftAuto(int i)
{

}
void rightAuto(int i) // inverse is blue left
{
  
}
void AWP(int i)
{
 
}
void halfAWP(int i) // this is daniel hand redleft and blueright
{
  
}
void adaptive(int i)
{
  drivePID(-50);
}