/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       simplemotion.cpp                                                  */
/*    Author:       davin                                                     */
/*    Created:      11/5/2023, 10:08:22 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "proportionalmotion.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
extern vex::brain       Brain;

// define your global instances of motors as extern here

// VEXcode device constructors
extern controller Controller1;

// Six Motor Blue Gear Drive
extern motor LeftFrontMotor;
extern motor RightFrontMotor;
extern motor LeftBackMotor;
extern motor RightBackMotor;
extern motor LeftStackMotor;
extern motor RightStackMotor;

//Sensors
extern inertial InertialA;

void turnLeftP(double target) {   
    //Propotional Turn Left
    InertialA.resetRotation();
    wait(.25, sec); //Intertial Sensors may take some time to settle
    
    //set a timeout for the loop
    double timeout = 5;
    time_t endtime = time(0) + timeout;
    
    while(InertialA.rotation(degrees) > -target) {
        double proportion = target + InertialA.rotation(degrees); 
        double kp = .35;
        double min_speed = .25;
        double speed = proportion * kp + min_speed; //one way to break out of the loop

        LeftFrontMotor.spin(reverse, speed, pct);
        RightFrontMotor.spin(fwd, speed, pct);
        LeftBackMotor.spin(reverse, speed, pct);
        RightBackMotor.spin(fwd, speed, pct);
        LeftStackMotor.spin(reverse, speed, pct);
        RightStackMotor.spin(fwd, speed, pct);

        if (time(NULL) > endtime) break; //break out of loop
    }

    //stopping with break may allow kp and/or minspeed to be higher
    LeftFrontMotor.setStopping(brake);
    RightFrontMotor.setStopping(brake);
    LeftBackMotor.setStopping(brake);
    RightBackMotor.setStopping(brake);
    LeftStackMotor.setStopping(brake);
    RightStackMotor.setStopping(brake);

    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();
    LeftStackMotor.stop();
    RightStackMotor.stop();

    //put breaking back to coast after hanging out
    wait(25, msec);
    
    LeftFrontMotor.setStopping(coast);
    RightFrontMotor.setStopping(coast);
    LeftBackMotor.setStopping(coast);
    RightBackMotor.setStopping(coast);
    LeftStackMotor.setStopping(coast);
    RightStackMotor.setStopping(coast);
}

void turnRightP(double target) {   
    //Propotional Turn Left
    InertialA.resetRotation();
    wait(.25, sec); //Intertial Sensors may take some time to settle
    
    //set a timeout for the loop
    double timeout = 5;
    time_t endtime = time(0) + timeout;
    
    while(InertialA.rotation(degrees) < target) {
        double proportion = target + InertialA.rotation(degrees); 
        double kp = .35;
        double min_speed = .25;
        double speed = proportion * kp + min_speed; //one way to break out of the loop

        LeftFrontMotor.spin(fwd, speed, pct);
        RightFrontMotor.spin(reverse, speed, pct);
        LeftBackMotor.spin(fwd, speed, pct);
        RightBackMotor.spin(reverse, speed, pct);
        LeftStackMotor.spin(fwd, speed, pct);
        RightStackMotor.spin(reverse, speed, pct);

        if (time(NULL) > endtime) break; //break out of loop
    }

    //stopping with break may allow kp and/or minspeed to be higher
    LeftFrontMotor.setStopping(brake);
    RightFrontMotor.setStopping(brake);
    LeftBackMotor.setStopping(brake);
    RightBackMotor.setStopping(brake);
    LeftStackMotor.setStopping(brake);
    RightStackMotor.setStopping(brake);

    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();
    LeftStackMotor.stop();
    RightStackMotor.stop();

    //put breaking back to coast after hanging out
    wait(25, msec);
    
    LeftFrontMotor.setStopping(coast);
    RightFrontMotor.setStopping(coast);
    LeftBackMotor.setStopping(coast);
    RightBackMotor.setStopping(coast);
    LeftStackMotor.setStopping(coast);
    RightStackMotor.setStopping(coast);
}

void driveForwardP(double distance) {   //inches
    //Drive Forward Proportional
    LeftFrontMotor.resetPosition();
  
    //Convert Inches to Motor Encoder Degrees
    double w_radius = 4.0 / 2.0; //wheel
    double r_conv = 3.14159 / 180.0; //radian conversion
    double gear_ratio = 48.0 / 72.0; //drive train gear ratio
    double target = distance / (r_conv * w_radius * gear_ratio);

    while(LeftFrontMotor.position(degrees) < target) {
        double proportion = target - LeftFrontMotor.position(degrees); 
        double kp = .05;
        double min_speed = 1;
        double max_speed = 100;
        double speed = proportion * kp + min_speed; //one way to break out of the loop

        if (speed > 100) speed = 100;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)
        if (speed > max_speed) speed = max_speed;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)

        LeftFrontMotor.spin(fwd, speed, pct);
        RightFrontMotor.spin(fwd, speed, pct);
        LeftBackMotor.spin(fwd, speed, pct);
        RightBackMotor.spin(fwd, speed, pct);
        LeftStackMotor.spin(fwd, speed, pct);
        RightStackMotor.spin(fwd, speed, pct);

    }

    //stopping with break may allow kp and/or minspeed to be higher
    LeftFrontMotor.setStopping(brake);
    RightFrontMotor.setStopping(brake);
    LeftBackMotor.setStopping(brake);
    RightBackMotor.setStopping(brake);
    LeftStackMotor.setStopping(brake);
    RightStackMotor.setStopping(brake);

    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();
    LeftStackMotor.stop();
    RightStackMotor.stop();

    //put breaking back to coast after hanging out
    wait(25, msec);

    LeftFrontMotor.setStopping(coast);
    RightFrontMotor.setStopping(coast);
    LeftBackMotor.setStopping(coast);
    RightBackMotor.setStopping(coast);
    LeftStackMotor.setStopping(coast);
    RightStackMotor.setStopping(coast);
}

void driveReverseP(double distance) {   //inches
    //Drive Forward with Proportional Stop
    LeftFrontMotor.resetPosition();
  
    //Convert Inches to Motor Encoder Degrees
    double w_radius = 4.0 / 2.0; //wheel
    double r_conv = 3.14159 / 180.0; //radian conversion
    double gear_ratio = 48.0 / 72.0; //drive train gear ratio
    double target = distance / (r_conv * w_radius * gear_ratio);

    while(LeftFrontMotor.position(degrees) > -target) {
        double proportion = target - LeftFrontMotor.position(degrees); 
        double kp = .05;
        double min_speed = 1;
        double max_speed = 100;
        double speed = proportion * kp + min_speed; //one way to break out of the loop

        if (speed > 100) speed = 100;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)
        if (speed > max_speed) speed = max_speed;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)

        LeftFrontMotor.spin(reverse, speed, pct);
        RightFrontMotor.spin(reverse, speed, pct);
        LeftBackMotor.spin(reverse, speed, pct);
        RightBackMotor.spin(reverse, speed, pct);
        LeftStackMotor.spin(reverse, speed, pct);
        RightStackMotor.spin(reverse, speed, pct);

    }

    //stopping with break may allow kp and/or minspeed to be higher
    LeftFrontMotor.setStopping(brake);
    RightFrontMotor.setStopping(brake);
    LeftBackMotor.setStopping(brake);
    RightBackMotor.setStopping(brake);
    LeftStackMotor.setStopping(brake);
    RightStackMotor.setStopping(brake);

    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();
    LeftStackMotor.stop();
    RightStackMotor.stop();

    //put breaking back to coast after hanging out
    wait(25, msec);

    LeftFrontMotor.setStopping(coast);
    RightFrontMotor.setStopping(coast);
    LeftBackMotor.setStopping(coast);
    RightBackMotor.setStopping(coast);
    LeftStackMotor.setStopping(coast);
    RightStackMotor.setStopping(coast);
}
