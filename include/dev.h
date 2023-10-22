#pragma once
#include "autoPath.h"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "lemlib/api.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "autoPath.h"
#include <cstdio>
#include <memory>


class DevPidTune {
    private:
     pros::Controller* devControl;
     lemlib::ChassisController_t* fwd;
     lemlib::ChassisController_t* turn;
     lemlib::Chassis* chassis;
     lemlib::Drivetrain_t* drivetrain;
     lemlib::OdomSensors_t* sensors;

     Routes* automatic;

    
    public:
     static int selector;
     static double increment;
     enum LatTurn {FWD, TURN};
     static LatTurn fwdTurn;
     DevPidTune(pros::Controller* dev, lemlib::ChassisController_t* foward, lemlib::ChassisController_t* turning, 
                Routes* route, lemlib::Chassis* controlchassis, lemlib::Drivetrain_t* drive, 
                lemlib::OdomSensors_t* sensor){
        devControl = dev;
        fwd = foward;
        turn = turning;
        automatic = route;
        chassis = controlchassis;
        drivetrain = drive;
        sensors = sensor;

     }
     inline void changeKp(double num, LatTurn setting) {
        if (setting == FWD) {
            fwd->kP += num;
        } else if (setting == TURN) {
            turn->kP += num;
        }
     }
     inline void changeKd(double num, LatTurn setting) {
        if (setting == FWD) {
            fwd->kD += num;
        } else if (setting == TURN) {
            turn->kD += num;
        }
     }
     inline void changeSmolError(double num, LatTurn setting) {
        if (setting == FWD) {
            fwd->smallError += num;
        } else if (setting == TURN) {
            turn->smallError += num;
        }
     }
     inline void changeSmolTimeout(double num, LatTurn setting) {
        if (setting == FWD) {
            fwd->smallErrorTimeout += num;
        } else if (setting == TURN) {
            turn->smallErrorTimeout += num;
        }
     }
     inline void changeLargeError(double num, LatTurn setting) {
        if (setting == FWD) {
            fwd->largeError += num;
        } else if (setting == TURN) {
            turn->largeError += num;
        }
     }
     inline void changeLargeErrorTimeout(double num, LatTurn setting) {
        if (setting == FWD) {
            fwd->largeErrorTimeout += num;
        } else if (setting == TURN) {
            turn->largeErrorTimeout += num;
        }
     }
     inline void changeSlew(double num, LatTurn setting) {
        if (setting == FWD) {
            fwd->slew += num;
        } else if (setting == TURN) {
            turn->slew += num;
        }
     }
     inline void increaseIncrement() {
        increment *= 10;
     }
     inline void decreaseIncrement() {
        increment /= 10;
     }
     inline void changeSetting(double num, LatTurn setting) {
        switch (selector) {
            case 1:
                changeKp(num, setting);
                break;
            case 2:
                changeKd(num, setting);
                break;
            case 3:
                changeSmolError(num, setting);
                break;
            case 4:
                changeSmolTimeout(num, setting);
                break;
            case 5:
                changeLargeError(num, setting);
                break;
            case 6:
                changeLargeErrorTimeout(num, setting);
                break;
            case 7:
                changeSlew(num, setting);
                break;

        }
     }
     inline void switchFwdTurn() {
        if (fwdTurn == FWD) { fwdTurn = TURN; }
        else if (fwdTurn == TURN) { fwdTurn = FWD; }
     }
     inline void restPosition() {
        chassis->setPose(0, 0, 0);
     }
     inline void run() {
        auto chas = std::make_unique<lemlib::Chassis>(*drivetrain, *fwd, *turn, *sensors);
        switch(fwdTurn) {
            case FWD:
                chas->moveTo(0, 10, 5000);
                break;
            case TURN:
                chas->turnTo(10, 5, 5000);
                break;
        }
        chas.reset(); // Test this out!
     }
     inline void displayfwd() {
        switch (selector) {
            case 1:
                devControl->print(1, 1, "LatKp: %f", fwd->kP);
                break;
            case 2:
                devControl->print(1, 1, "LatKd: %f", fwd->kD);
                break;
            case 3:
                devControl->print(1, 1, "LatSmErr: %f", fwd->smallError);
                break;
            case 4:
                devControl->print(1, 1, "LatSmTOut: %f", fwd->smallErrorTimeout);
                break;
            case 5:
                devControl->print(1, 1, "LatLgErr: %f", fwd->largeError);
                break;
            case 6:
                devControl->print(1, 1, "LatLgTOut: %f", fwd->largeErrorTimeout);
                break;
            case 7:
                devControl->print(1, 1, "LatSlew: %f", fwd->slew);
                break;
        }
     }
     inline void displayTurn() {
        switch (selector) {
            case 1:
                devControl->print(1, 1, "TurnKp: %f", turn->kP);
                break;
            case 2:
                devControl->print(1, 1, "TurnKd: %f", turn->kD);
                break;
            case 3:
                devControl->print(1, 1, "TurnSmErr: %f", turn->smallError);
                break;
            case 4:
                devControl->print(1, 1, "TurnSmTOut: %f", turn->smallErrorTimeout);
                break;
            case 5:
                devControl->print(1, 1, "TurnLgErr: %f", turn->largeError);
                break;
            case 6:
                devControl->print(1, 1, "TurnLgTOut: %f", turn->largeErrorTimeout);
                break;
            case 7:
                devControl->print(1, 1, "TurnSlew: %f", turn->slew);
                break;
        }
     }
     inline double getResolution() {
        return increment;
     }
     inline void display() {
        //devControl->clear_line(1); 
        switch(fwdTurn) {
            case FWD:
                displayfwd();   
                break;
            case TURN:
                displayTurn();
                break;
        }
        //devControl->clear_line(2);
     }

     inline void outTurnHeading() {
        lemlib::Pose pose = chassis->getPose(); // get the current position of the robot
        std::printf("drive ->angleTurnTo(%f, 1000);", pose.theta);
     }

     inline void outMoveToPos() {
        lemlib::Pose pose = chassis->getPose(); // get the current position of the robot
        std::printf("drive ->moveTo(%f, %f, 1500);", pose.x, pose.y);
     }

     

     void main() {
        if (devControl->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) { devControl->clear(); }
        if (devControl->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) { selector--; }
        if (devControl->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) { selector++; }
        if (devControl->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) { decreaseIncrement(); }
        if (devControl ->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) { increaseIncrement(); }
        if (devControl->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) { switchFwdTurn(); }
        if (devControl->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) { outTurnHeading(); }
        if (devControl->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) { run(); }
        if (devControl->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) { restPosition(); }
        if (devControl->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) { outMoveToPos(); }
        if (devControl->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) { changeSetting(increment, fwdTurn); }
        if (devControl->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) { changeSetting(-increment, fwdTurn); }
        //devControl->print(2, 1, "RES: %f", getResolution());
        //pros::delay(50);
        //display();
    }


};