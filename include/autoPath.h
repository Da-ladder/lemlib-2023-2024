#pragma once
#include "peerPursuitRouts.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include "roborUtils.h"
#include "main.h"
#include "lemlib/api.hpp"
#include "roborUtils.h"
#include <vector>
using namespace lemlib;

//hehe
class AutoCreater {
  private:
    //std::vector<std::string> routeNames = {};
    
    static std::vector<const char*> routeNames;
    //static std::vector<const char*> testnames;
    static std::vector<void (*)()> runRoutesv2;
    static std::list<void(*)> runRoutes;
    static int indexToRun;
    static int autoOver;
    static int driverON;
  
  public:
    AutoCreater(const char *routeName, void routeCall()) { //
        //routeNames.push_back(std::string(routeName));
        routeNames.push_back(routeName);
        runRoutesv2.push_back(routeCall);
    }

    inline static void setDriver(int num) {
        driverON = num;
    }
 
    inline void setAuto(int num) {
        autoOver = num;
    }

    inline int getDriver() {
        return driverON;
    }

    inline int getAuto() {
        return autoOver;
    }

    inline void add(const char *routeName, void routeCall()) {
        //routeNames.push_back(std::string(routeName));
        routeNames.push_back(routeName);
        runRoutesv2.push_back(routeCall);
    }

    inline void updatePath() {
        indexToRun = potentiometer.get_value_calibrated()/100;
    }

    inline int getIndex() {
        return potentiometer.get_value_calibrated()/100;
    }

    inline void printPath() {
        //int value = potentiometer.get_value_calibrated()/100;
        if (indexToRun >= 0 && indexToRun < routeNames.size()) {
            pros::lcd::print(3, routeNames[indexToRun]);
        } else {
            pros::lcd::print(3, "OUT OF BOUNDS || CURRENT VALUE:", indexToRun);
        }
        
    }

    inline const char* returnPathName() {
        int value = potentiometer.get_value_calibrated()/100;
        if (value >= 0 && value < routeNames.size()) {
            for (size_t i = 0; i < routeNames.size(); ++i) {
                const char* routeName = routeNames[i];
                if (i == value) {
                    return routeName;
                }
            // Now you can work with the 'routeName' value
            }
        } else {
            return "OUT OF BOUNDS";
        }
    }
    
    inline void run() {
        this->setAuto(1);
        runRoutesv2[indexToRun]();
    }
    
};

class Routes{
    private:
    Chassis* drive = nullptr;
    AutoSelecter* path = nullptr;
    AutoCreater* pathv2;

    
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
    
    
     inline void initall() {


        AutoCreater devtest("Matchload A", matchload);
        devtest.add("No Match Load B", &this->nomatchload);
        devtest.add("Skill Issue C", &this->skills);
        devtest.add("safe 6 ball", &this->placehold1);
        devtest.add("Driver Macro", &this->placehold2);
        devtest.add("Safe AWP", &this->placehold3);
        devtest.add("Flick ball over", &this->placehold4);
        devtest.add("6 Balls", &this->placehold5);

        pathv2 = &devtest;
     }

     inline void lcdOutPath() {
        pathv2->printPath();
     }
     inline const char* returnPathTest() {
         return pathv2->returnPathName();
     }

     inline int getNUM() {
        return pathv2->getIndex();
    }

     inline void runv2() {
        pathv2->run();
     }
     
     inline void updates() {
        pathv2->updatePath();
     }

     inline void setDriver1(int num) {
        pathv2->setDriver(num);
    }

    inline void setAuto1(int num) {
        pathv2->setAuto(num);
    }

    inline int getDriver1() {
        return pathv2->getDriver();
    }

    inline int getAuto1() {
        return pathv2->getAuto();
    }
    
     
};

