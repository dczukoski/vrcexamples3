/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       davin                                                     */
/*    Created:      11/5/2023, 10:08:22 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

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
    Controller1.Screen.print("InertialA: %f",InertialA.rotation(degrees));
    Controller1.Screen.setCursor(2,1);
    Controller1.Screen.print("LeftFrontMotor: %f",LeftFrontMotor.position(degrees));
    // Allow other tasks to run
    this_thread::sleep_for(10);
  }
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

void turnLeftF(int target) {   
    //Turn Left by using fuzzy ranges
    InertialA.resetRotation();
    wait(.25, sec); //Sometimes Intertial/Gyro Sensors need some time to settle
    
    double change_point = 45; 
    double fast_speed = 100;
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
    double fast_speed = 100;
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

void driveForwardPH(double distance) {    //inches
    //Drive Forward with Proportional Stop and Proportional Heading Correction
    double heading = InertialA.rotation(degrees); //save heading

    LeftFrontMotor.resetPosition();
  
    double w_radius = 4.0 / 2.0; //wheel
    double r_conv = 3.14159 / 180.0; //radian conversion
    double gear_ratio = 48.0 / 72.0; //drive train gear ratio
    double target = distance / (r_conv * w_radius * gear_ratio);

    while(LeftFrontMotor.position(degrees) < target) {
        //adjust speed to slow down to the target
        double proportion = target - LeftFrontMotor.position(degrees); 
        double kp_d = .05;
        double min_speed = 1;
        double max_speed = 100;
        double speed = proportion * kp_d + min_speed; //one way to break out of the loop

        //adjust to drive straight
        double error = heading-InertialA.rotation(degrees);
        double kp_s = 1;
        double output = error*kp_s;

        double leftSpeed = speed-output;
        double rightSpeed = speed+output;

        if (leftSpeed > 100) leftSpeed = 100;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)
        if (leftSpeed > max_speed) leftSpeed = max_speed;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)
        if (rightSpeed > 100) rightSpeed = 100;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)
        if (rightSpeed > max_speed) rightSpeed = max_speed;     // In old IQ Speed over 100 results in no movement (velocity cannot be > 100)

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
 
    driveForwardP(3*24.0);
    turnLeftP(90);
    driveForwardP(6*24.0);
    turnLeftP(90);
    driveForwardP(3*24.0);

}
