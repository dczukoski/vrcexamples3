#include "vex.h"
#include "robotconfig.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
// VEXcode device constructors
controller Controller1 = controller(primary);

// Six Motor Blue Gear Drive
motor LeftFrontMotor = motor(PORT17, ratio6_1, true);
motor RightFrontMotor = motor(PORT15, ratio6_1, false);
motor LeftBackMotor = motor(PORT20, ratio6_1, true);
motor RightBackMotor = motor(PORT12, ratio6_1, false);
motor LeftStackMotor = motor(PORT5, ratio6_1, false);
motor RightStackMotor = motor(PORT3, ratio6_1, true);

//Sensors
inertial InertialA = inertial(PORT10);