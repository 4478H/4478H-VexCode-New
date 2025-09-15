/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton.cpp                                                 */
/*    Author:       4478H                                                     */
/*    Created:       2025                                                     */
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
    {"Skills", skillsAuto, 1},         // Route 4
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
void blueLeftAuto(int i)
{
//Drives to Loader
drivePID(31);
//Turn to loader
inert(90);
// intake balls
intake();
wait(1,sec);
//go to long goal
inert(180);
drivePID(36);
//load long goal
sHood.set(false);
sHood2.set(false);
intake();
wait(1,sec);
intakeStop();
// get first set middle balls
drivePID(-1);
inert(90);
drivePID(19);
}
void adaptive(int i)
{
  drivePID(-50);
}