#include "devices.h"

// Required device definitions
competition Competition;
brain Brain;
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

// Motor and sensor device definitions
motor mBackRight = motor(PORT1, ratio6_1, false);
motor mBackLeft = motor(PORT10, ratio6_1, true);
motor mFrontRight = motor(PORT13, ratio6_1, false);
motor mFrontLeft = motor(PORT11, ratio6_1, true);
motor mMidLeft = motor(PORT9, ratio6_1, true);
motor mMidRight = motor(PORT6, ratio6_1, false);
motor mIntake = motor(PORT3, ratio18_1, false);
motor mIntake2 = motor(PORT8, ratio18_1, false);
motor mIntake3 = motor(PORT18, ratio18_1, true);
distance blockCheck = distance(PORT17);
inertial Inertial = inertial(PORT20);
optical colorSens = optical(PORT19);

// Motor group definitions
motor_group leftMotors = motor_group(mBackLeft, mMidLeft, mFrontLeft);                                    // group of all left side drive train motors
motor_group rightMotors = motor_group(mBackRight, mMidRight, mFrontRight);                                // group of all right side drive train motors
motor_group allMotors = motor_group(mBackLeft, mMidLeft, mFrontLeft, mBackRight, mMidRight, mFrontRight); // group of all drive train motors

// Digital-out device definitions
digital_out sHood = digital_out(Brain.ThreeWirePort.B);
digital_out sHood2 = digital_out(Brain.ThreeWirePort.A);
digital_out doinker = digital_out(Brain.ThreeWirePort.C);

digital_out sDoor = digital_out(Brain.ThreeWirePort.F);
digital_out sIntake = digital_out(Brain.ThreeWirePort.D);

// Limit switch definitions
limit limitS = limit(Brain.ThreeWirePort.E);