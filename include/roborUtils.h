#pragma once
#include "api.h"
#include <functional>
#include <list>
#include <streambuf>
#include <string>
#include <type_traits>
#include <string>
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
 
//TEST

class Controller_Out {
  private:
   pros::Controller* out;
   const int DELAY = 50;


  public:
   Controller_Out(pros::Controller* output) {
    out = output;
  }
   static bool busy;
   static bool block;
   static int msg_sent;
   bool msg(int line, const char *MSG);
   bool vibrate(const char *pattern);
   inline void silence() {
    block = true;
   }
   inline void unsilence() {
    block = false;
   }
   inline bool checkSilence() {
    return block;
   }
};


class AutoSelecter {
  private:
   pros::Controller* keyboard;
   pros::ADIPotentiometer* selector;

  public:
   enum AutoPath {MATCHLOAD, NOMATCHLOAD, SKILLS, PLACEHOLD1, PLACEHOLD2, PLACEHOLD3, PLACEHOLD4, PLACEHOLD5, NONE};
   std::vector <AutoPath> listing = {
    MATCHLOAD,
    NOMATCHLOAD, 
    SKILLS, 
    PLACEHOLD1, 
    PLACEHOLD2, 
    PLACEHOLD3, 
    PLACEHOLD4, 
    PLACEHOLD5, 
    NONE
   };
   
   AutoSelecter (pros::ADIPotentiometer* sensor, pros::Controller* controller = nullptr) {
    keyboard = controller;
    selector = sensor;
   }
   AutoPath route;
   inline AutoPath checkPath() {
    int angle = (int) (selector->get_angle() / 20);
    if (angle >= 8) {
      return NONE;
    }
    route = listing[angle];
    return route;
   }
   
};


class MotorUtils {
  private:
   pros::MotorGroup* left_drive;
   pros::MotorGroup* right_drive;
   pros::Motor* motor;
  
  public:
   double temp_flag = 0;

   MotorUtils(double max_temp, pros::MotorGroup* left, pros::MotorGroup* right) {
    left_drive = left;
    right_drive = right;
    motor = nullptr;
    temp_flag = max_temp;
   }

   MotorUtils(double max_temp, pros::Motor* single_motor) {
    left_drive = nullptr;
    right_drive = nullptr;
    motor = single_motor;
    temp_flag = max_temp;
   }

   bool checkGroupTemps();
   bool checkMotorTemp();
   void hold();
   void coast();
};


class Monitor {
  private:
    Controller_Out* controller;
    MotorUtils* chassisThermo;
    MotorUtils* cataThermo;
    MotorUtils* intakeThermo;


  public:
   Monitor(Controller_Out* driver_control, MotorUtils* chassis, MotorUtils* cata, MotorUtils* intake) {
    controller = driver_control;
    chassisThermo = chassis;
    cataThermo = cata;
    intakeThermo = intake;
   }

   inline void checkTemps() {
    if (chassisThermo->checkGroupTemps() || cataThermo->checkMotorTemp() || intakeThermo->checkMotorTemp()) {
				controller->vibrate("-");
				controller->msg(1,"OverTemp: Down to Silence");
				if (controller->checkSilence()) {
					if (chassisThermo->checkGroupTemps()) { pros::lcd::print(5, "Chassis overtemp!"); }
					if (cataThermo->checkMotorTemp()) { pros::lcd::print(6, "Cata overtemp!"); }
					if (intakeThermo->checkMotorTemp()) { pros::lcd::print(7, "Intake overtemp!"); }
				} else { pros::lcd::clear_line(3); pros::lcd::clear_line(4); pros::lcd::clear_line(5); }
			}
   }


};


class PistonControl {
  private:
    pros::Controller* controller;
    pros::ADIDigitalOut* piston;
    pros::controller_digital_e_t button;
    int pistionState = 0;

  public:
    PistonControl(pros::Controller* control, pros::controller_digital_e_t digitalPress, pros::ADIDigitalOut* pistonbind) {
      controller = control;
      piston = pistonbind;
      button = digitalPress;
    }

    inline void setPistionState() {
      piston->set_value(pistionState);
    }

    inline void overrideState(int state) {
      pistionState = state;
      setPistionState();
    }

    inline void main() {
      if (controller->get_digital_new_press(button)) {
        if(pistionState == 1) {
          this->pistionState = 0;
        } else if (pistionState == 0) {
          this->pistionState = 1;
        }
        setPistionState();
      }
    }


};


class CataControl {
  private:
    pros::Controller* controller;
    double stopAmp;
    int OnOff = 0;
    pros::controller_digital_e_t button;
    pros::Motor* cata;
    PistonControl* elevate;
    PistonControl* matchLoadTouch;
    static int reqTurnOff;
  
  public:
    CataControl(pros::Controller* control, pros::controller_digital_e_t digitalPress, pros::Motor* cat, int stopCurrent, PistonControl* ele, PistonControl* match) {
      controller = control;
      stopAmp = stopCurrent;
      button = digitalPress;
      cata = cat;
      elevate = ele;
      matchLoadTouch = match;
    }
    void setCataState() {
      if (OnOff) {
        if (reqTurnOff == 1) {
          elevate->overrideState(1);
          matchLoadTouch->overrideState(1);
          reqTurnOff = 0;
        }
        *cata = 127;
      } else {
        if (reqTurnOff == 1) {
          if (cata->get_current_draw() > stopAmp) {
            *cata = 0;
            reqTurnOff = 0;
          }
          elevate->overrideState(0);
          matchLoadTouch->overrideState(0);
          
        }
        
      }
      /*else if (!OnOff && cata->get_current_draw() > 100) {
        elevate->overrideState(0);
        matchLoadTouch->overrideState(0);
        
      } */
    }

    void overRideCataState(bool state) {
      if (state) { reqTurnOff = 1; OnOff = 1;} else { reqTurnOff = 1; OnOff = 0;}
      setCataState();
    }

    void main() {
      if (controller->get_digital_new_press(button)) {
        if(OnOff == 1) {
          this->OnOff = 0;
          reqTurnOff = 1;
        } else if (OnOff == 0) {
          this->OnOff = 1;
          reqTurnOff = 1;
        }
      }
      setCataState();
    }
};
