/**
 * @file include/lemlib/chassis/chassis.hpp
 * @author LemLib Team
 * @brief Chassis class declarations
 * @version 0.4.5
 * @date 2023-01-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "pros/motors.hpp"
#include "pros/imu.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "lemlib/pose.hpp"

namespace lemlib {
/**
 * @brief Struct containing all the sensors used for odometry
 *
 * The sensors are stored in a struct so that they can be easily passed to the chassis class
 * The variables are pointers so that they can be set to nullptr if they are not used
 * Otherwise the chassis class would have to have a constructor for each possible combination of sensors
 *
 * @param vertical1 pointer to the first vertical tracking wheel
 * @param vertical2 pointer to the second vertical tracking wheel
 * @param horizontal1 pointer to the first horizontal tracking wheel
 * @param horizontal2 pointer to the second horizontal tracking wheel
 * @param imu pointer to the IMU
 */
typedef struct {
        TrackingWheel* vertical1;
        TrackingWheel* vertical2;
        TrackingWheel* horizontal1;
        TrackingWheel* horizontal2;
        pros::Imu* imu;
} OdomSensors_t;

/**
 * @brief Struct containing constants for a chassis controller
 *
 * The constants are stored in a struct so that they can be easily passed to the chassis class
 * Set a constant to 0 and it will be ignored
 *
 * @param kP proportional constant for the chassis controller
 * @param kD derivative constant for the chassis controller
 * @param smallError the error at which the chassis controller will switch to a slower control loop
 * @param smallErrorTimeout the time the chassis controller will wait before switching to a slower control loop
 * @param largeError the error at which the chassis controller will switch to a faster control loop
 * @param largeErrorTimeout the time the chassis controller will wait before switching to a faster control loop
 * @param slew the maximum acceleration of the chassis controller
 */
typedef struct {
        float kP;
        float kD;
        float kI; // Added for robor
        float smallError;
        float smallErrorTimeout;
        float largeError;
        float largeErrorTimeout;
        float slew;
} ChassisController_t;

/**
 * @brief Struct containing constants for a drivetrain
 *
 * The constants are stored in a struct so that they can be easily passed to the chassis class
 * Set a constant to 0 and it will be ignored
 *
 * @param leftMotors pointer to the left motors
 * @param rightMotors pointer to the right motors
 * @param trackWidth the track width of the robot
 * @param wheelDiameter the diameter of the wheels (2.75, 3.25, 4, 4.125)
 * @param rpm the rpm of the wheels
 */
typedef struct {
        pros::Motor_Group* leftMotors;
        pros::Motor_Group* rightMotors;
        float trackWidth;
        float wheelDiameter;
        float rpm;
} Drivetrain_t;

/**
 * @brief Chassis class
 *
 */
class Chassis {
    public:
        /**
         * @brief Construct a new Chassis
         *
         * @param drivetrain drivetrain to be used for the chassis
         * @param lateralSettings settings for the lateral controller
         * @param angularSettings settings for the angular controller
         * @param sensors sensors to be used for odometry
         */
        Chassis(Drivetrain_t drivetrain, ChassisController_t lateralSettings, ChassisController_t angularSettings,
                OdomSensors_t sensors);
        /**
         * @brief Calibrate the chassis sensors
         *
         */
        void calibrate();
        /**
         * @brief Set the pose of the chassis
         *
         * @param x new x value
         * @param y new y value
         * @param theta new theta value
         * @param radians true if theta is in radians, false if not. False by default
         */
        void setPose(double x, double y, double theta, bool radians = false);
        /**
         * @brief Set the pose of the chassis
         *
         * @param pose the new pose
         * @param radians whether pose theta is in radians (true) or not (false). false by default
         */
        void setPose(Pose pose, bool radians = false);
        /**
         * @brief Get the pose of the chassis
         *
         * @param radians whether theta should be in radians (true) or degrees (false). false by default
         * @return Pose
         */
        Pose getPose(bool radians = false);
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
        void turnTo(float x, float y, int timeout, bool reversed = false, float maxSpeed = 127, bool log = false);
        /**
         * @brief Move the chassis towards the target point
         *
         * The PID logging ids are "angularPID" and "lateralPID"
         *
         * @param x x location
         * @param y y location
         * @param timeout longest time the robot can spend moving
         * @param maxSpeed the maximum speed the robot can move at
         * @param log whether the chassis should log the turnTo function. false by default
         */
        void angleTurnTo(float angle, int timeout, float errorRange = 1.5, float kI_dis = 0, bool reversed = false, float maxSpeed = 127, bool log = false);
        /**
         * @brief Move the chassis towards the target point using angle
         *
         * The PID logging ids are "angularPID" and "lateralPID"
         *
         * @param angle what angle in degrees to turn to
         * @param timeout longest time the robot can spend moving
         * @param error will terminate the loop within error
         * @param kI_dis will use kI within the angle sepificied
         * @param reversed whether the robot should turn in the opposite direction
         * @param maxSpeed the maximum speed the robot can move at
         * @param log whether the chassis should log the turnTo function. false by default
         */

        void moveTo(float x, float y, int timeout, float maxSpeed = 200, bool log = false);
        
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
        void moveToKI(float x, float y, int timeout, float errorRange = 1, float kI_dis = 0, float maxSpeed = 127);
        /**
         * @brief Move the chassis along a path
         *
         * @param filePath file path to the path. No need to preface it with /usd/
         * @param timeout the maximum time the robot can spend moving
         * @param lookahead the lookahead distance. Units in inches. Larger values will make the robot move faster but
         * will follow the path less accurately
         * @param reverse whether the robot should follow the path in reverse. false by default
         * @param maxSpeed the maximum speed the robot can move at
         * @param log whether the chassis should log the path on a log file. false by default.
         */
        void follow(const char* filePath, int timeout, float lookahead, bool reverse = false, float maxSpeed = 127,
                    bool log = false);

        void followFromVector(std::vector<std::string>* pointList, int timeout, float lookahead, bool reverse = false, float maxSpeed = 127, int multix = 12, bool log = false);
    private:
        ChassisController_t lateralSettings;
        ChassisController_t angularSettings;
        Drivetrain_t drivetrain;
        OdomSensors_t odomSensors;
};
} // namespace lemlib
