#include "main.h"
#include "autoPath.h"
#include "dev.h"

//*****************************************************************************************************************************
/** hehe
 * @brief initializes all motors, pistons, controllers, and sensors on the bot
 */
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller devControl(pros::E_CONTROLLER_PARTNER);

pros::Motor intake(5, pros::E_MOTOR_GEARSET_18, true);
pros::Motor cata(6, pros::E_MOTOR_GEARSET_36, false);
pros::Motor immigrant(0, pros::E_MOTOR_GEARSET_06,
                      true); // Its taken over, hijacked

pros::ADIDigitalOut leftWing('d', LOW);
pros::ADIDigitalOut primaryElevation('f', HIGH); // LINK
pros::ADIDigitalOut auxElevation('e', LOW);      // LINK
pros::ADIDigitalOut rightWing('h', LOW);
pros::ADIDigitalOut block('c', LOW);
pros::ADIDigitalOut matchloadWing('b', LOW);

// pros::ADIDigitalOut blocker('h', LOW);

pros::ADIPotentiometer
    potentiometer('g', pros::adi_potentiometer_type_e::E_ADI_POT_EDR);
pros::ADIPotentiometer fake('a', pros::adi_potentiometer_type_e::E_ADI_POT_EDR);

pros::IMU inert(1);

//*****************************************************************************************************************************

// Sets up drive using EZ lib for swing movements
Drive ezChassis{
    // Left Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    {-12, 13, 14}

    // Right Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    ,
    {-2, 3, 4}

    // IMU Port
    ,
    1

    // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
    //    (or tracking wheel diameter)
    ,
    3.25

    // Cartridge RPM
    //   (or tick per rotation if using tracking wheels)
    ,
    600

    // External Gear Ratio (MUST BE DECIMAL)
    //    (or gear ratio of tracking wheel)
    // eg. if your drive is 84:36 where the 36t is powered, your RATIO would
    // be 2.333.
    // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be
    // 0.6.
    ,
    2.333};

// swingCtrl swing(&ezChassis);

pros::Motor &left_motor_A = ezChassis.left_motors[0];
pros::Motor &left_motor_B = ezChassis.left_motors[1];
pros::Motor &left_motor_C = ezChassis.left_motors[2];
pros::Motor &right_motor_A = ezChassis.right_motors[0];
pros::Motor &right_motor_B = ezChassis.right_motors[1];
pros::Motor &right_motor_C = ezChassis.right_motors[2];

pros::MotorGroup left_side_motors({left_motor_A, left_motor_B, left_motor_C});
pros::MotorGroup right_side_motors({right_motor_A, right_motor_B,
                                    right_motor_C});

// Sets up the auto drivetrain
lemlib::Drivetrain_t drivetrain{
    &left_side_motors,  // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    12.75,              // track width
    3.25,               // wheel diameter
    450                 // wheel rpm
};

// Sets the pid for lateral control
lemlib::ChassisController_t lateralController{
    13.5,  // kP
    52,  // kD
    0,  // kI
    .1,  // smallErrorRange
    400, // smallErrorTimeout
    2,   // largeErrorRange
    500, // largeErrorTimeout
    40   // slew rate
};

// Sets the pid for turning control
lemlib::ChassisController_t angularController{
    4.3, // kP
    46,  // kD
    0,   // kI
    1,   // smallErrorRange
    100, // smallErrorTimeout
    3,   // largeErrorRange
    500, // largeErrorTimeout
    40   // slew rate
};

// Tells lemlib what sensors to use
lemlib::OdomSensors_t sensors{
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inert   // inertial sensor
};

// creates the lemlib chassis for auto
lemlib::Chassis chassis(drivetrain, lateralController, angularController,
                        sensors);

// Sets up OverTemp notifications along with Controller push notifications
/*
MotorUtils chassisThermo(50, &left_side_motors, &right_side_motors);
MotorUtils cataThermo(45, &cata);
MotorUtils intakeThermo(45, &intake);
Controller_Out controlOut(&master);
Monitor temps(&controlOut, &chassisThermo, &cataThermo, &intakeThermo);
*/

// Sets up all piston uilities
// PistonControl blocker(&master, pros::E_CONTROLLER_DIGITAL_L2, );
PistonControl blocker(&master, pros::E_CONTROLLER_DIGITAL_B, &block);
PistonControl matchContact(&master, pros::E_CONTROLLER_DIGITAL_Y,
                           &matchloadWing);
PistonControl controlLeftWing(&master, pros::E_CONTROLLER_DIGITAL_L2,
                              &leftWing);
PistonControl controlElevation(&devControl, pros::E_CONTROLLER_DIGITAL_L1,
                               &primaryElevation);
PistonControl controlRightWing(&master, pros::E_CONTROLLER_DIGITAL_L1,
                               &rightWing);
PistonControl auxControlElevate(&master, pros::E_CONTROLLER_DIGITAL_X,
                                &auxElevation);

// Sets up cata control using current to stop the motor at a designated angle
CataControl controlCata(&master, pros::E_CONTROLLER_DIGITAL_A, &cata, 2200, // 2100 ???
                        &auxControlElevate, &matchContact); // 2280

// Sets up Automous path selector
AutoSelecter path(&potentiometer);
Routes roam(&chassis, &path);

// Sets up the PID tuner on the developer controller (second controller)
DevPidTune developerMode(&devControl, &lateralController, &angularController,
                         &roam, &chassis, &drivetrain, &sensors);

// A function that loops forever to check motor temperatures (used by a thread)
void moniterStart() {
  while (true) {
    // temps.checkTemps();
    pros::delay(500);
  }
}

// starts pistions so that they can be toggled using a controller
// Loops forever and is used by a thread
void pistonUtils() {
  while (true) {
    controlLeftWing.main();
    blocker.main();
    matchContact.main();
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) &&
        master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
      auxControlElevate.overrideState(0);
      controlElevation.overrideState(0);
    }
    controlRightWing.main();
    auxControlElevate.main();
    pros::delay(50);
  }
}

// starts Cata utilities so the catapult can be controlled
void cataUtil() {
  while (true) {
    controlCata.main();
    pros::delay(10);
  }
}

void ptoEZChas(bool state) {
  ezChassis.pto_add({left_motor_B, left_motor_A});
  ezChassis.pto_add({left_motor_A, left_motor_B});
  ezChassis.pto_add({right_motor_A, right_motor_B});
  ezChassis.pto_add({right_motor_B, right_motor_A});
  ezChassis.pto_add({left_motor_C, right_motor_C});
  ezChassis.pto_add({right_motor_C, left_motor_C});
  left_motor_A.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  left_motor_B.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  left_motor_C.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  right_motor_A.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  right_motor_B.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  right_motor_C.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

/**
 * @brief Runs right when the program is started (threads and initialization
 * procedures are located here)
 */
void initialize() {
  pros::lcd::initialize();
  //chassis.calibrate();
  roam.initall();
  master.clear();
  // chassisThermo.coast();
  pros::delay(150);
  devControl.clear(); 
  // pros::Task tempMonitor(moniterStart); //idk if this slows down anything???
  pros::Task pistonControls(pistonUtils);
  pros::Task cat(cataUtil);
}

/**
 * @brief Runs when the field controller is in disabled mode. Don't run any
 * 		  physical items here.
 */
void disabled() {
  if ((roam.getAuto1() == 1) && (roam.getDriver1() == 1)) {
    auxControlElevate.overrideState(0);
    controlElevation.overrideState(0);
  }
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 * b 
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() { roam.updates(); roam.runv2(); }

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  std::vector<std::string> storagePoints{};

  bool dev_mode = true;
  int times = 0;
  // autonomous();
  // potentiometer.calibrate();
  // pros::delay(2000);

  while (true) {
    roam.updates();
    roam.lcdOutPath();
    lemlib::Pose pose =
        chassis.getPose(); // get the current position of the robot
    pros::lcd::print(0, "x: %f", pose.x);           // print the x position
    pros::lcd::print(1, "y: %f", pose.y);           // print the y position
    pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
    //pros::lcd::print(4, roam.returnPathTest());

    /*
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
    { controlOut.silence(); }

    else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
    { controlOut.unsilence(); }
    */

    // std::cout << "wwll well well" << std::endl; ???
    int maxLeft = 127;
    int maxRight = 127;

    int turn = -master.get_analog(ANALOG_LEFT_Y);
    int fwd = master.get_analog(ANALOG_RIGHT_X);
    int left = (-fwd - turn); //*0.9;
    int right = (-fwd + turn);
    // if (left > maxLeft) { left = maxLeft; }
    // if (right > maxRight) { right = maxRight; }
    // if (left < -maxLeft) { left = -maxLeft; }
    // if (right < -maxRight) { right = -maxRight; }

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      intake = 127;
      //left = (fwd + turn)/4;
      //right = (fwd - turn)/4;

    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      intake = -127;
    } else {
      intake = 0;
    }

    left_side_motors = left;
    right_side_motors = right;

    if(pros::competition::is_connected()) {
      roam.setDriver1(1);
    }


    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
      roam.updates(); 
      roam.runv2();
    }

    if (dev_mode) {
      developerMode.main();
      
      if (devControl.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        lemlib::Pose pos = chassis.getPose(); // get the current position of the robot
        std::printf("\"%f, %f, %f\", ", pos.x, pos.y, pos.theta);
        //std::printf("{%i, %i}, ", left, right);
        if (times == 4) {
          std::printf("\n");
          times = 0;
        }
        times++;
      }
      
      // std::printf("drive ->angleTurnTo(%f, 1000);", pose.theta);
    }
    pros::delay(50); // should be 20
  }
}
