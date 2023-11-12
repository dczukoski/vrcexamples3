/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       davin                                                     */
/*    Created:      11/5/2023, 10:08:22 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "robotconfig.h"

#include "simplemotion.h"
#include "fuzzymotion.h"
#include "proportionalmotion.h"

using namespace vex;

void brainDisplay(){
  while(true){
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("InertialA: %f",InertialA.rotation(degrees));
    Brain.Screen.setCursor(2,1);
    Brain.Screen.print("LeftFrontMotor: %f",LeftFrontMotor.position(degrees));
    // Allow other tasks to run
    this_thread::sleep_for(10);  
    }
}

void controllerDisplay(){
  while(true){
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("InertialA Rot: %f",InertialA.rotation(degrees));
    Controller1.Screen.setCursor(2,1);
    Controller1.Screen.print("InertialA Head: %f",InertialA.heading(degrees));
    Controller1.Screen.setCursor(3,1);
    Controller1.Screen.print("LeftFrontMotor: %f",LeftFrontMotor.position(degrees));
    // Allow other tasks to run
    this_thread::sleep_for(25);
  }
}

void driveForwardPH(double distance) {    //inches
    //Drive Forward with Proportional Stop and Proportional Heading Correction
    InertialA.resetHeading();
    wait(.25, sec); //Intertial Sensors may take some time to settle
    
    double heading = InertialA.heading(degrees); //save heading

    LeftFrontMotor.resetPosition();
  
    double w_radius = 4.0 / 2.0; //wheel
    double r_conv = 3.14159 / 180.0; //radian conversion
    double gear_ratio = 48.0 / 72.0; //drive train gear ratio
    double target = distance / (r_conv * w_radius * gear_ratio);
    
    printf ("start ******************************");

    while(LeftFrontMotor.position(degrees) < target) {
        //adjust speed to slow down to the target
        //double proportion = target - LeftFrontMotor.position(degrees); 
        //double kp_d = .05;
        //double min_speed = 1;
        double max_speed = 100;
        //double speed = proportion * kp_d + min_speed; //one way to break out of the loop

        //adjust to drive straight
        double speed = 25;
        
        double error = heading-InertialA.heading(degrees);
     
        double kp_s = .1;
        double output = error*kp_s;

        double leftSpeed = speed-output;
        double rightSpeed = speed+output;

        printf ("head %f, err %f, ls %f, rs %f | ", heading, error, leftSpeed, rightSpeed);

        //if (leftSpeed > 100) leftSpeed = 100;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)
        //if (leftSpeed > max_speed) leftSpeed = max_speed;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)
        //if (rightSpeed > 100) rightSpeed = 100;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)
        //if (rightSpeed > max_speed) rightSpeed = max_speed;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)

        LeftFrontMotor.spin(fwd, leftSpeed, pct);
        RightFrontMotor.spin(fwd, rightSpeed, pct);
        LeftBackMotor.spin(fwd, leftSpeed, pct);
        RightBackMotor.spin(fwd, rightSpeed, pct);
        LeftStackMotor.spin(fwd, leftSpeed, pct);
        RightStackMotor.spin(fwd, rightSpeed, pct);
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

void intialize() {
    //Calibrate Intertial Sensors
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("InertialA: Calibrating");

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("InertialA: Calibrating");

    InertialA.calibrate();
    // waits for the Inertial Sensor to calibrate
    while (InertialA.isCalibrating()) {
        wait(100, msec);
    }

    //Start Monitoring
    thread t1(brainDisplay);
    thread t2(controllerDisplay);
}

int main() {
    intialize();

    driveForwardF(4000);
    wait(3,sec);
    turnLeftF(90);
    wait(3,sec);
}