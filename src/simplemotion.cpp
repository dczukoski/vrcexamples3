/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       simplemotion.cpp                                                  */
/*    Author:       davin                                                     */
/*    Created:      11/5/2023, 10:08:22 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "simplemotion.h"

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

void driveForward(double distance, double speed) {   
   //Drive Forward Simple
   LeftFrontMotor.setPosition(0,degrees);
   while(LeftFrontMotor.position(degrees)<distance){
  
        LeftFrontMotor.spin(fwd, speed, pct);
        RightFrontMotor.spin(fwd, speed, pct);
        LeftBackMotor.spin(fwd, speed, pct);
        RightBackMotor.spin(fwd, speed, pct);
        LeftStackMotor.spin(fwd, speed, pct);
        RightStackMotor.spin(fwd, speed, pct);
    }

    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();
    LeftStackMotor.stop();
    RightStackMotor.stop();
}

void driveReverse(double distance, double speed) {   
   //Drive Reverse Simple
   LeftFrontMotor.setPosition(0,degrees);
   while(LeftFrontMotor.position(degrees) > -distance){
  
        LeftFrontMotor.spin(reverse, speed, pct);
        RightFrontMotor.spin(reverse, speed, pct);
        LeftBackMotor.spin(reverse, speed, pct);
        RightBackMotor.spin(reverse, speed, pct);
        LeftStackMotor.spin(reverse, speed, pct);
        RightStackMotor.spin(reverse, speed, pct);
    }

    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();
    LeftStackMotor.stop();
    RightStackMotor.stop();
}

void turnLeft(int target) {   
    //Simple Turn Left
    InertialA.resetRotation();
    wait(.25, sec); //Sometimes Intertial/Gyro Sensors need some time to settle
    
    while(InertialA.rotation(degrees) > -target) {
        int speed = 5;  

        LeftFrontMotor.spin(reverse, speed, pct);
        RightFrontMotor.spin(fwd, speed, pct);
        LeftBackMotor.spin(reverse, speed, pct);
        RightBackMotor.spin(fwd, speed, pct);
        LeftStackMotor.spin(reverse, speed, pct);
        RightStackMotor.spin(fwd, speed, pct);
    }

    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();
    LeftStackMotor.stop();
    RightStackMotor.stop();
}

void turnRight(int target) {   
    //Simple Turn Right
    InertialA.resetRotation();
    wait(.25, sec); //Sometimes Intertial/Gyro Sensors need some time to settle
    
    while(InertialA.rotation(degrees) < target) {
        int speed = 5;  

        LeftFrontMotor.spin(fwd, speed, pct);
        RightFrontMotor.spin(reverse, speed, pct);
        LeftBackMotor.spin(fwd, speed, pct);
        RightBackMotor.spin(reverse, speed, pct);
        LeftStackMotor.spin(fwd, speed, pct);
        RightStackMotor.spin(reverse, speed, pct);
    }

    LeftFrontMotor.stop();
    RightFrontMotor.stop();
    LeftBackMotor.stop();
    RightBackMotor.stop();
    LeftStackMotor.stop();
    RightStackMotor.stop();
}
