#include "roborUtils.h"


bool Controller_Out::busy = false;
bool Controller_Out::block = false;
int Controller_Out::msg_sent = 0;


bool Controller_Out::msg(int line, const char *MSG) {
    if (block) { return false; }
    if (busy) {
        return false;
    } else {
        busy = true;
        out ->print(line, 1, MSG);
        pros::delay(DELAY);
        busy = false;
    }
    return true;
}


bool Controller_Out::vibrate(const char *PATTERN) {
    if (block) { return false; }
    if (busy) {
        return false;
    } else {
        busy = true;
        out ->rumble(PATTERN);
        pros::delay(DELAY);
        busy = false;
    }
    return true;
}


bool MotorUtils::checkGroupTemps() {
    std::vector<double> right_temp = right_drive->get_temperatures();
    std::vector<double> left_temp = right_drive->get_temperatures();

    // This assumes that the left and right side have the same amount of motors
    unsigned int vecSize = right_temp.size();

    // Loops through the vectors (or lists) to check to see if any of them are at or above the temp_flag limit
    // If so, the function will return true and the user determines what to do next
    for(unsigned int motornum = 0; motornum < vecSize; motornum++) {
        if (right_temp[motornum] >= temp_flag || left_temp[motornum] >= temp_flag)
            return true;
    }

    // If none of the motors are over temp, the function will return false
    return false;
}


bool MotorUtils::checkMotorTemp() {
    // Checks a single motor to see if it is over temp
    // If so, it will return true
    if (motor->get_temperature() >= temp_flag) {
        return true;
    }

    // If the motor is not over temp, the function will return false
    return false;
}

void MotorUtils::hold() {
    if (right_drive == nullptr) {
        motor->set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
    } else {
        right_drive->set_brake_modes(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
        left_drive->set_brake_modes(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
    }
}

void MotorUtils::coast() {
    if (right_drive == nullptr) {
        motor->set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_COAST);
    } else {
        right_drive->set_brake_modes(pros::motor_brake_mode_e::E_MOTOR_BRAKE_COAST);
        left_drive->set_brake_modes(pros::motor_brake_mode_e::E_MOTOR_BRAKE_COAST);
    }
}