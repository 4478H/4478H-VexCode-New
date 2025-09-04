#ifndef MOVEMENT_H
#define MOVEMENT_H

// General Utilities
double turnSlew(double val);
void inertClamp(double t);

// PID Driving
void drivePID(double inches, double kP = 110, double kI = 0, double kD = 0.15, double goalThreshold = 30);
void tunerDrivePID(double inches, double kP = 110, double kI = 0, double kD = 0.15, int ID = -1);
void tunePID();
void GraphPID(double rangeP, double rangeD, double guessP, double guessD, int sqrtTests);

// PID Turning
void inert(double target, double kP = 0.499, double kI = 0, double kD = 0.002);

// Open-loop Driving
void driveInches(double fwdVal, int veloc, bool clamping = false);
void driveInchesClamp(double fwdVal, int veloc);
void colorSortRed();
void intake();
void intakeStop();
void intakeDegWait(int degree, int velocit);
void intakeDeg(int degree, int velocit);
// Log Drive
double logDriveJoystick(double joystickPCT);

#endif // MOVEMENT_H