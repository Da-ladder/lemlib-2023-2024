/**
 * @file src/lemlib/chassis/chassis.cpp
 * @author LemLib Team
 * @brief definitions for the chassis class
 * @version 0.4.5
 * @date 2023-01-27
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <cmath>
#include <math.h>
#include <type_traits>
#include "pros/motors.hpp"
#include "pros/misc.hpp"
#include "lemlib/util.hpp"
#include "lemlib/pid.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/odom.hpp"
#include "pros/rtos.h"
#include "trackingWheel.hpp"

/**
 * @brief Construct a new Chassis
 *
 * @param drivetrain drivetrain to be used for the chassis
 * @param lateralSettings settings for the lateral controller
 * @param angularSetting settings for the angular controller
 * @param sensors sensors to be used for odometry
 */
lemlib::Chassis::Chassis(Drivetrain_t drivetrain, ChassisController_t lateralSettings,
                         ChassisController_t angularSettings, OdomSensors_t sensors) {
    this->drivetrain = drivetrain;
    this->lateralSettings = lateralSettings;
    this->angularSettings = angularSettings;
    this->odomSensors = sensors;
}

/**
 * @brief Calibrate the chassis sensors
 *
 */
void lemlib::Chassis::calibrate() {
    // calibrate the imu if it exists
    if (odomSensors.imu != nullptr) {
        odomSensors.imu->reset(true);
        // keep on calibrating until it calibrates successfully
        while (errno == PROS_ERR || errno == ENODEV || errno == ENXIO) {
            pros::c::controller_rumble(pros::E_CONTROLLER_MASTER, "---");
            odomSensors.imu->reset(true);
            pros::delay(10);
        }
    }
    // initialize odom
    if (odomSensors.vertical1 == nullptr)
        odomSensors.vertical1 = new lemlib::TrackingWheel(drivetrain.leftMotors, drivetrain.wheelDiameter,
                                                          -(drivetrain.trackWidth / 2), drivetrain.rpm);
    if (odomSensors.vertical2 == nullptr)
        odomSensors.vertical2 = new lemlib::TrackingWheel(drivetrain.rightMotors, drivetrain.wheelDiameter,
                                                          drivetrain.trackWidth / 2, drivetrain.rpm);
    odomSensors.vertical1->reset();
    odomSensors.vertical2->reset();
    if (odomSensors.horizontal1 != nullptr) odomSensors.horizontal1->reset();
    if (odomSensors.horizontal2 != nullptr) odomSensors.horizontal2->reset();
    lemlib::setSensors(odomSensors, drivetrain);
    lemlib::init();
    // rumble to controller to indicate success
    pros::c::controller_rumble(pros::E_CONTROLLER_MASTER, ".");
}

/**
 * @brief Set the Pose object
 *
 * @param x new x value
 * @param y new y value
 * @param theta new theta value
 * @param radians true if theta is in radians, false if not. False by default
 */
void lemlib::Chassis::setPose(double x, double y, double theta, bool radians) {
    lemlib::setPose(lemlib::Pose(x, y, theta), radians);
}

/**
 * @brief Set the pose of the chassis
 *
 * @param Pose the new pose
 * @param radians whether pose theta is in radians (true) or not (false). false by default
 */
void lemlib::Chassis::setPose(Pose pose, bool radians) { lemlib::setPose(pose, radians); }

/**
 * @brief Get the pose of the chassis
 *
 * @param radians whether theta should be in radians (true) or degrees (false). false by default
 * @return Pose
 */
lemlib::Pose lemlib::Chassis::getPose(bool radians) { return lemlib::getPose(radians); }

/**
 * @brief Turn the chassis so it is facing the target point
 *
 * The PID logging id is "angularPID"
 *
 * @param x x location
 * @param y y location
 * @param timeout longest time the robot can spend moving
 * @param reversed whether the robot should turn in the opposite direction. false by default
 * @param maxSpeed the maximum speed the robot can turn at. Default is 200
 * @param log whether the chassis should log the turnTo function. false by default
 */
void lemlib::Chassis::turnTo(float x, float y, int timeout, bool reversed, float maxSpeed, bool log) {
    Pose pose(0, 0);
    float targetTheta;
    float deltaX, deltaY, deltaTheta;
    float motorPower;
    std::uint8_t compState = pros::competition::get_status();

    // create a new PID controller
    FAPID pid = FAPID(0, 0, angularSettings.kP, 0, angularSettings.kD, "angularPID");
    pid.setExit(angularSettings.largeError, angularSettings.smallError, angularSettings.largeErrorTimeout,
                angularSettings.smallErrorTimeout, timeout);

    // main loop
    while (pros::competition::get_status() == compState && !pid.settled()) {
        // update variables
        pose = getPose();
        pose.theta = (reversed) ? fmod(pose.theta - 180, 360) : fmod(pose.theta, 360);
        deltaX = x - pose.x;
        deltaY = y - pose.y;
        targetTheta = fmod(radToDeg(M_PI_2 - atan2(deltaY, deltaX)), 360);

        // calculate deltaTheta
        deltaTheta = angleError(targetTheta, pose.theta);

        // calculate the speed
        motorPower = pid.update(0, deltaTheta, log);

        // cap the speed
        if (motorPower > maxSpeed) motorPower = maxSpeed;
        else if (motorPower < -maxSpeed) motorPower = -maxSpeed;

        // move the drivetrain
        drivetrain.leftMotors->move(-motorPower);
        drivetrain.rightMotors->move(motorPower);

        pros::delay(10);
    }

    // stop the drivetrain
    drivetrain.leftMotors->move(0);
    drivetrain.rightMotors->move(0);
}

/**
 * @brief Turn the chassis so it focuses on an angle
 *
 *
 * @param angle angle in degrees
 * @param timeout longest time the robot can spend moving
 * @param errorRange range that is acceptable for the robot to stop in
 * @param kI_dis range where KI kicks in
 * @param reversed whether the robot should turn in the opposite direction. false by default
 * @param maxSpeed the maximum speed the robot can turn at. Default is 200
 * @param log whether the chassis should log the turnTo function. false by default
 */
void lemlib::Chassis::angleTurnTo(float angle, int timeout, float errorRange, float kI_dis, bool reversed, float maxSpeed, bool log) {
    // Test function? PREREQ
    Pose pose(0, 0);
    float targetTheta;
    int accuracy = 0;
    float deltaX, deltaY, deltaTheta, prevError, prevOutput, totalError, error, deltaError, output;
    std::uint8_t compState = pros::competition::get_status();
    double startTime = pros::c::millis();
    double stopTime = startTime + timeout;

    // main loop with built in timeout and range along with when to call it quits for accuracy
    while (((pros::competition::get_status() == compState) && (pros::c::millis() >= stopTime)) || accuracy >= 20) {
        // update variables
        pose = getPose();
        pose.theta = (reversed) ? fmod(pose.theta - 180, 360) : fmod(pose.theta, 360);
        targetTheta = angle;

        // calculate deltaTheta
        deltaTheta = angleError(targetTheta, pose.theta);
        if (errorRange > std::fabs(deltaTheta)) { accuracy += 1; } else { accuracy = 0; }

        // calculate the speed
        error = 0 - deltaTheta;
        deltaError = error - prevError;
        output = angularSettings.kP * error + angularSettings.kD * deltaError;
        if (kI_dis < error) { output += angularSettings.kI * totalError; }
        prevOutput = output;
        prevError = error;

        // Finds sign of the error
        bool errorNegitive = error < 0;
        bool totalErrorNegitive = totalError < 0;

        // If the signs are opposite of each other, it will set totalError to zero
        if (!errorNegitive == totalErrorNegitive) {
            totalError = 0;
        }

        // cap the speed
        if (output > maxSpeed) output = maxSpeed;
        else if (output < -maxSpeed) output = -maxSpeed;

        // move the drivetrain
        drivetrain.leftMotors->move(-output);
        drivetrain.rightMotors->move(output);

        pros::delay(10);
    }

    // stop the drivetrain
    drivetrain.leftMotors->move(0);
    drivetrain.rightMotors->move(0);
}


/**
 * @brief Move the chassis towards the target
 *
 * The PID logging ids are "angularPID" and "lateralPID"
 *
 * @param x target x pos
 * @param y target y pos
 * @param timeout longest time the robot can spend moving
 * @param error will terminate the loop within error
 * @param kI_dis will use kI within the angle sepificied
 * @param maxSpeed the maximum speed the robot can move at
 */
void lemlib::Chassis::moveToKI(float x, float y, int timeout, float errorRange, float kI_dis, float maxSpeed) {
    // Test function? PREREQ WIP
    Pose pose(0, 0);
    float prevLateralPower = 0;
    float prevAngularPower = 0;
    bool close = false;
    double startTime = pros::c::millis();
    double stopTime = startTime + timeout;
    float totalError, prevLatError, prevLatOutput, deltaLatError, accuracy, lateralPower;
    std::uint8_t compState = pros::competition::get_status();

    // create a new PID controller
    FAPID angularPID(0, 0, angularSettings.kP, 0, angularSettings.kD, "angularPID");

    // main loop
    while (pros::competition::get_status() == compState && ((pros::c::millis() >= stopTime) || accuracy >= 20)) {
        // get the current position
        Pose pose = getPose();
        pose.theta = std::fmod(pose.theta, 360);

        // update error
        float deltaX = x - pose.x;
        float deltaY = y - pose.y;
        float targetTheta = fmod(radToDeg(M_PI_2 - atan2(deltaY, deltaX)), 360);
        float hypot = std::hypot(deltaX, deltaY);
        float diffTheta1 = angleError(pose.theta, targetTheta);
        float diffTheta2 = angleError(pose.theta, targetTheta + 180);
        float angularError = (std::fabs(diffTheta1) < std::fabs(diffTheta2)) ? diffTheta1 : diffTheta2;
        float lateralError = hypot * cos(degToRad(std::fabs(diffTheta1)));

        


        // checks for accuracy
        if (errorRange > std::fabs(lateralError)) { accuracy += 1; } else { accuracy = 0; }
        

        // calculate the speed
        deltaLatError = lateralError - prevLatError;
        lateralPower = lateralSettings.kP * lateralError + lateralSettings.kD * deltaLatError;
        if (kI_dis < lateralError) { lateralPower += lateralSettings.kI * totalError; }
        prevLatOutput = lateralPower;
        prevLatError = lateralError;
        

        // Finds sign of the error
        bool errorNegitive = lateralError < 0;
        bool totalErrorNegitive = totalError < 0;

        // If the signs are opposite of each other, it will set totalError to zero
        if (!errorNegitive == totalErrorNegitive) {
            totalError = 0;
        }

        // cap the speed
        if (lateralPower > maxSpeed) lateralPower = maxSpeed;
        else if (lateralPower < -maxSpeed) lateralPower = -maxSpeed;

        // limit acceleration
        if (!close) lateralPower = lemlib::slew(lateralPower, prevLateralPower, lateralSettings.slew);

        // if the robot is close to the target
        if (pose.distance(lemlib::Pose(x, y)) < 7.5) {
            close = true;
            maxSpeed = (std::fabs(prevLateralPower) < 30) ? 30 : std::fabs(prevLateralPower);
        }

        // ANGLE CORRECTION CALUCALTIONS
        float angularPower = -angularPID.update(angularError, 0, false);
        if (std::fabs(angularError) > 25) { angularPower = lemlib::slew(angularPower, prevAngularPower, angularSettings.slew); }
        if (close) angularPower = 0;
        prevLateralPower = lateralPower;
        prevAngularPower = angularPower;
        // END OF ANGLE CORRECTION CALUCALTIONS

        // Sets power to each side
        float leftPower = lateralPower + angularPower;
        float rightPower = lateralPower - angularPower;

        // ratio the speeds to respect the max speed
        float ratio = std::max(std::fabs(leftPower), std::fabs(rightPower)) / maxSpeed;
        if (ratio > 1) {
            leftPower /= ratio;
            rightPower /= ratio;
        }

        // move the motors
        drivetrain.leftMotors->move(leftPower);
        drivetrain.rightMotors->move(rightPower);

        pros::delay(10);
    }
}

/**
 * @brief Move the chassis towards the target point
 *
 *
 * @param x x location
 * @param y y location
 * @param timeout longest time the robot can spend moving
 * @param maxSpeed the maximum speed the robot can move at
 * @param reversed whether the robot should turn in the opposite direction. false by default
 * @param log whether the chassis should log the turnTo function. false by default
 */
void lemlib::Chassis::moveTo(float x, float y, int timeout, float maxSpeed, bool log) {
    
    Pose pose(0, 0);
    float prevLateralPower = 0;
    float prevAngularPower = 0;
    bool close = false;
    double start = pros::millis();
    std::uint8_t compState = pros::competition::get_status();

    // create a new PID controller
    FAPID lateralPID(0, 0, lateralSettings.kP, 0, lateralSettings.kD, "lateralPID");
    FAPID angularPID(0, 0, angularSettings.kP, 0, angularSettings.kD, "angularPID");
    lateralPID.setExit(lateralSettings.largeError, lateralSettings.smallError, lateralSettings.largeErrorTimeout,
                       lateralSettings.smallErrorTimeout, timeout);

    // main loop
    while (pros::competition::get_status() == compState && (!lateralPID.settled() || pros::millis() - start < 300)) {
        // get the current position
        Pose pose = getPose();
        pose.theta = std::fmod(pose.theta, 360);

        // update error
        float deltaX = x - pose.x;
        float deltaY = y - pose.y;
        float targetTheta = fmod(radToDeg(M_PI_2 - atan2(deltaY, deltaX)), 360);
        float hypot = std::hypot(deltaX, deltaY);
        float diffTheta1 = angleError(pose.theta, targetTheta);
        float diffTheta2 = angleError(pose.theta, targetTheta + 180);
        float angularError = (std::fabs(diffTheta1) < std::fabs(diffTheta2)) ? diffTheta1 : diffTheta2;
        float lateralError = hypot * cos(degToRad(std::fabs(diffTheta1)));

        // calculate speed
        float lateralPower = lateralPID.update(lateralError, 0, log);
        float angularPower = -angularPID.update(angularError, 0, log);

        // if the robot is close to the target
        if (pose.distance(lemlib::Pose(x, y)) < 7.5) {
            close = true;
            maxSpeed = (std::fabs(prevLateralPower) < 30) ? 30 : std::fabs(prevLateralPower);
        }

        // limit acceleration
        if (!close) lateralPower = lemlib::slew(lateralPower, prevLateralPower, lateralSettings.slew);
        if (std::fabs(angularError) > 25)
            angularPower = lemlib::slew(angularPower, prevAngularPower, angularSettings.slew);

        // cap the speed
        if (lateralPower > maxSpeed) lateralPower = maxSpeed;
        else if (lateralPower < -maxSpeed) lateralPower = -maxSpeed;
        if (close) angularPower = 0;

        prevLateralPower = lateralPower;
        prevAngularPower = angularPower;

        float leftPower = lateralPower + angularPower;
        float rightPower = lateralPower - angularPower;

        // ratio the speeds to respect the max speed
        float ratio = std::max(std::fabs(leftPower), std::fabs(rightPower)) / maxSpeed;
        if (ratio > 1) {
            leftPower /= ratio;
            rightPower /= ratio;
        }

        // move the motors
        drivetrain.leftMotors->move(leftPower);
        drivetrain.rightMotors->move(rightPower);

        pros::delay(10);
    }

    // stop the drivetrain
    drivetrain.leftMotors->move(0);
    drivetrain.rightMotors->move(0);
}
