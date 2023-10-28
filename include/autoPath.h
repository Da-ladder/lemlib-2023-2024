#pragma once
#include "peerPursuitRouts.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include "roborUtils.h"
#include "main.h"
#include "lemlib/api.hpp"
#include "roborUtils.h"
using namespace lemlib;


class Routes{
    private:
    Chassis* drive = nullptr;
    AutoSelecter* path = nullptr;
    pros::Motor* intake;
    CataControl* cata;
    pros::Motor_Group* left;
    pros::Motor_Group* right;
    pros::ADIDigitalOut* rightWing;
    pros::ADIDigitalOut* leftWing;
    pros::ADIDigitalOut* elvate;
    swingCtrl* ezchas;
    
    
    public:
     Routes(Chassis* drivetrain, AutoSelecter* inpath, pros::Motor* in, CataControl* cap, 
            pros::Motor_Group* drive_left, pros::Motor_Group* drive_right, pros::ADIDigitalOut* rwings, 
            pros::ADIDigitalOut* lwings, swingCtrl* ezchass, pros::ADIDigitalOut* elevate) {
        drive = drivetrain;
        path = inpath;
        intake = in;
        cata = cap;
        left = drive_left;
        right = drive_right;
        rightWing = rwings;
        leftWing = lwings;
        ezchas = ezchass;
        elvate = elevate;

        
     }
     void initDrive(lemlib::Chassis* drivetrain);
     void matchload();
     void nomatchload();
     void skills();
     void autoRoute();
     void placehold1();
     void placehold2();
     void placehold3();
     void placehold4();
     void placehold5();
     inline void manual_control(double l, double r) {
      *left = l;
      *right = r;
     }
    
    /*
     inline void initall() {
        void (*fp)(void) = &this->placehold1;
        AutoCreater devtest("sewiweo", (*fp));
     }
    */
     
};

struct paths{

    void placehold1() {
    

    }
    

};