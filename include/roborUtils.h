#pragma once
#include "main.h"
#include <streambuf>
#include <string>
#include <type_traits>
#include<string>


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
   enum AutoPath {MATCHLOAD, NOMATCHLOAD, SKILLS, NONE};
   AutoSelecter (pros::ADIPotentiometer* sensor, pros::Controller* controller = nullptr) {
    keyboard = controller;
    selector = sensor;
   }
   AutoPath route;
   inline AutoPath checkPath() {
    int angle = (int) (selector->get_angle() / 20);
    switch (angle) {
      case 1:
        route = MATCHLOAD;
        return route;
      case 2:
        route = NOMATCHLOAD;
        return route;
      case 3:
        route = SKILLS;
        return route;
      default:
        route = NONE;
        return route;
    }
   }
};


class MotorUtils {
  private:
   pros::MotorGroup* left_drive = nullptr;
   pros::MotorGroup* right_drive = nullptr;
   pros::Motor* motor = nullptr;
  
  public:
   double temp_flag = 0;

   MotorUtils(double max_temp, pros::MotorGroup* left = nullptr, pros::MotorGroup* right = nullptr, pros::Motor* single_motor = nullptr) {
    left_drive = left;
    right_drive = right;
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