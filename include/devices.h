#ifndef DEVICES_H
#define DEVICES_H

#include "vex.h"

using namespace vex;

// Required device declarations
extern competition Competition;
extern brain Brain;
extern controller Controller1;
extern controller Controller2;

// Motor and sensor device declarations
extern motor mBackRight;
extern motor mBackLeft;
extern motor mFrontRight;
extern motor mFrontLeft;
extern motor mMidLeft;
extern motor mMidRight;
extern motor mIntake;
extern motor mIntake2;
extern motor mIntake3;
extern distance ringCheck;
extern inertial Inertial;
extern optical colorSens;

// motor group declarations
extern motor_group leftMotors;  // group of all left side drive train motors
extern motor_group rightMotors; // group of all right side drive train motors
extern motor_group allMotors;   // group of all drive train motors

// Digital-out device declarations
extern digital_out sHood;
extern digital_out doinker;
extern digital_out sHood2;
extern digital_out sDoor;
extern digital_out sIntake;

// Limit switch declarations
extern limit limitS;

#endif // DEVICES_H