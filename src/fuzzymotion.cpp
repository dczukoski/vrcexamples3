/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       simplemotion.cpp                                                  */
/*    Author:       davin                                                     */
/*    Created:      11/5/2023, 10:08:22 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "fuzzymotion.h"

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

void driveForwardF(double distance) {   
   //Drive Forward Simple
   LeftFrontMotor.setPosition(0,degrees);
   
    double change_point = distance / 3; 
    double fast_speed = 50;
    double slow_speed = 5;  
   
    while(LeftFrontMotor.position(degrees)<change_point){
       int speed = fast_speed;  
  
        LeftFrontMotor.spin(fwd, speed, pct);
        RightFrontMotor.spin(fwd, speed, pct);
        LeftBackMotor.spin(fwd, speed, pct);
        RightBackMotor.spin(fwd, speed, pct);
        LeftStackMotor.spin(fwd, speed, pct);
        RightStackMotor.spin(fwd, speed, pct);
    }

    while(LeftFrontMotor.position(degrees)<distance){
       int speed = slow_speed;  
  
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

void driveReverseF(double distance) {   
   //Drive Forward Simple
   LeftFrontMotor.setPosition(0,degrees);
   
    double change_point = distance / 3; 
    double fast_speed = -50;
    double slow_speed = -5;  
   
    while(LeftFrontMotor.position(degrees)>-change_point){
       int speed = fast_speed;  
  
        LeftFrontMotor.spin(fwd, speed, pct);
        RightFrontMotor.spin(fwd, speed, pct);
        LeftBackMotor.spin(fwd, speed, pct);
        RightBackMotor.spin(fwd, speed, pct);
        LeftStackMotor.spin(fwd, speed, pct);
        RightStackMotor.spin(fwd, speed, pct);
    }

    while(LeftFrontMotor.position(degrees)>-distance){
       int speed = slow_speed;  
  
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


void turnLeftF(int target) {   
    //Turn Left by using fuzzy ranges
    InertialA.resetRotation();
    wait(.25, sec); //Sometimes Intertial/Gyro Sensors need some time to settle
    
    double change_point = 45; 
    double fast_speed = 50;
    double slow_speed = 5;

    while(InertialA.rotation(degrees) > -target + change_point) {
        int speed = fast_speed;  

        LeftFrontMotor.spin(reverse, speed, pct);
        RightFrontMotor.spin(fwd, speed, pct);
        LeftBackMotor.spin(reverse, speed, pct);
        RightBackMotor.spin(fwd, speed, pct);
        LeftStackMotor.spin(reverse, speed, pct);
        RightStackMotor.spin(fwd, speed, pct);
    }

    while(InertialA.rotation(degrees) > -target) {
        int speed = slow_speed;  

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

void turnRightF(int target) {   
    //Turn Left by using fuzzy ranges
    InertialA.resetRotation();
    wait(.25, sec); //Sometimes Intertial/Gyro Sensors need some time to settle
    
    double change_point = 45; 
    double fast_speed = 50;
    double slow_speed = 5;

    while(InertialA.rotation(degrees) < target - change_point) {
        int speed = fast_speed;  

        LeftFrontMotor.spin(fwd, speed, pct);
        RightFrontMotor.spin(reverse, speed, pct);
        LeftBackMotor.spin(fwd, speed, pct);
        RightBackMotor.spin(reverse, speed, pct);
        LeftStackMotor.spin(fwd, speed, pct);
        RightStackMotor.spin(reverse, speed, pct);
    }

    while(InertialA.rotation(degrees) < target) {
        int speed = slow_speed;  

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

