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
    
    
    public:
     Routes(Chassis* drivetrain, AutoSelecter* inpath, pros::Motor* in, pros::Motor* cap) {
        drive = drivetrain;
        path = inpath;
        intake = in;
        cata = cap;
     }
     void initDrive(lemlib::Chassis* drivetrain);
     void matchload();
     void nomatchload();
     void skills();
     void autoRoute();
     
};