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

    
    public:
     Routes(Chassis* drivetrain, AutoSelecter* inpath) {
        drive = drivetrain;
        path = inpath;
        
     }
     void initDrive(lemlib::Chassis* drivetrain);
     void static matchload();
     void static nomatchload();
     void static skills();
     void autoRoute();
     void static placehold1();
     void static placehold2();
     void static placehold3();
     void static placehold4();
     void static placehold5();
     inline static void manual_control(double l, double r) {
      left_side_motors = l;
      right_side_motors = r;
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