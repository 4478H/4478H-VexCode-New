#ifndef AUTON_H
#define AUTON_H

#include <functional>

// Forward declarations of autonomous functions
void skillsAuto(int direction);
void blueLeftAuto(int direction);

// Forward declaration of internal structs/classes
struct AutonRoutine;

class AutonSelector {
private:
    const AutonRoutine* routines;  // Pointer to array of routines
    int currentSelection;          // Current selected routine
    int routineCount;             // Total number of routines

public:
    AutonSelector();  // Constructor
    void nextSelection();
    void displayCurrentSelection();
    void runSelectedAuton();
    int getCurrentSelection() const;
};

// Global instance getter
AutonSelector& getAutonSelector();


// Forward declarations for autonomous routes
void skillsAuto(int i);
void blueLeftAuto(int i);
void adaptive();

#endif // AUTON_H