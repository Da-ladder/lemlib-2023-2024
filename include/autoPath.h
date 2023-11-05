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
    std::vector<const char*> routeNames;
    std::list<void(*)> runRoutes;
    int indexToRun = 0;
  
  public:
    AutoCreater(const char *routeName, void routeCall()) { //
        //routeNames.push_back(std::string(routeName));
        routeNames.push_back(routeName);
        runRoutes.push_back(&routeCall);
    }

    inline void add(const char *routeName, void routeCall()) {
        //routeNames.push_back(std::string(routeName));
        routeNames.push_back(routeName);
        runRoutes.push_back(&routeCall);
    }

    inline void updatePath() {
        //this->indexToRun = potentiometer.get_value_calibrated()/100;
    }

    inline int getIndex() {
        return potentiometer.get_value_calibrated()/100;
    }

    inline void printPath() {
        pros::lcd::print(3, routeNames[indexToRun]);
    }

    inline const char* returnPathName() {
        //if (potentiometer.get_value_calibrated()/100 > 4) {
        //    return "NOPE";
        //}
        int value = potentiometer.get_value_calibrated()/100;
        if (value/100 >= 0 && value/100 < runRoutes.size()) {
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
        if (indexToRun >= 0 && indexToRun < runRoutes.size()) {
            auto it = runRoutes.begin(); // The iterator to use
            std::advance(it, indexToRun); // Move the iterator to the desired function
            (*it); // Calls the function
        } else {
            std::cout << "Index out of bounds." << std::endl;
        }
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
        void (*fp)(void) = &this->matchload;
        AutoCreater devtest("MatchloadA", (*fp));

        devtest.add("No Match LoadB", &this->nomatchload);
        devtest.add("Skill IssueC", &this->skills);
        devtest.add("idk what this is tbh 1", &this->placehold1);
        devtest.add("idk what this is tbh 2", &this->placehold2);
        devtest.add("idk what this is tbh 3", &this->placehold3);
        devtest.add("idk what this is tbh 4", &this->placehold4);
        devtest.add("idk what this is tbh 5", &this->placehold5);

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
    
     
};

