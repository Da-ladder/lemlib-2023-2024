#include "lemlib/api.hpp"
#pragma once
#include "roborUtils.h"
using namespace lemlib;


class Routes{
    private:
    Chassis* drive = nullptr;
    AutoSelecter* path = nullptr;
    pros::Motor* intake;
    pros::Motor* cata;
    pros::Motor_Group* left;
    pros::Motor_Group* right;
    pros::ADIDigitalOut* wing;
    
    
    public:
     Routes(Chassis* drivetrain, AutoSelecter* inpath, pros::Motor* in, pros::Motor* cap, pros::Motor_Group* drive_left, pros::Motor_Group* drive_right, pros::ADIDigitalOut* wings) {
        drive = drivetrain;
        path = inpath;
        intake = in;
        cata = cap;
        left = drive_left;
        right = drive_right;
        wing = wings;
     }
     void initDrive(lemlib::Chassis* drivetrain);
     void matchload();
     void nomatchload();
     void skills();
     void autoRoute();
     inline void manual_control(double l, double r) {
      *left = l;
      *right = r;
     }
     
};