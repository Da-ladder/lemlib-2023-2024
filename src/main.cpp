#include "lemlib/api.hpp"
#include "main.h"
#include "autoPath.h"
#include "roborUtils.h"
#include "dev.h"
#include <cstdio>


pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller devControl(pros::E_CONTROLLER_PARTNER);

pros::Motor left_motor_A(16, pros::E_MOTOR_GEARSET_06, false); // port 1, blue gearbox, not reversed
pros::Motor left_motor_B(18, pros::E_MOTOR_GEARSET_06, true); // port 2, green gearbox, not reversed
pros::Motor left_motor_C(20, pros::E_MOTOR_GEARSET_06, true); // port 3, red gearbox, reversed
pros::Motor right_motor_A(11, pros::E_MOTOR_GEARSET_06, false); // port 4, red gearbox, reversed
pros::Motor right_motor_B(14, pros::E_MOTOR_GEARSET_06, false); // port 3, red gearbox, reversed
pros::Motor right_motor_C( 15, pros::E_MOTOR_GEARSET_06, true); // port 4, red gearbox, reversed
pros::Motor intake(17, pros::E_MOTOR_GEARSET_18, false);
pros::Motor cata(19,pros::E_MOTOR_GEARSET_36, false);
pros::Motor immigrant(0, pros::E_MOTOR_GEARSET_06, true); // Its taken over, hijacked

pros::ADIDigitalOut wings ('h', LOW);
pros::ADIDigitalOut elevation('f', LOW);
pros::ADIDigitalOut auxElevation('e', HIGH);
pros::ADIDigitalOut rightMatchLoad('d', LOW);
pros::ADIDigitalOut leftMatchLoad('c', LOW);

pros::ADIPotentiometer potentiometer ('g',pros::adi_potentiometer_type_e::E_ADI_POT_EDR);
pros::Distance cataTrigger(8);

pros::IMU inert(1);

pros::MotorGroup left_side_motors({left_motor_A, left_motor_B, left_motor_C});
pros::MotorGroup right_side_motors({right_motor_A, right_motor_B, right_motor_C});


// Sets up the auto drivetrain
lemlib::Drivetrain_t drivetrain {
	&left_side_motors, // left drivetrain motors
	&right_side_motors, // right drivetrain motors
	12.75, // track width
	3.25, // wheel diameter
	450 // wheel rpm
};

// Sets the pid for lateral control
lemlib::ChassisController_t lateralController {
    15, // kP
    17, // kD
    .1, // smallErrorRange
    100, // smallErrorTimeout
    2, // largeErrorRange
    400, // largeErrorTimeout
    40 // slew rate
};

// Sets the pid for turning control
lemlib::ChassisController_t angularController {
    3.5, // kP
    26, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};

// Tells lemlib what sensors to use
lemlib::OdomSensors_t sensors {
	nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
	nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inert // inertial sensor
};

// creates the lemlib chassis for auto
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);


// Sets up OverTemp notifications along with Controller push notifications
MotorUtils chassisThermo(50, &left_side_motors, &right_side_motors);
MotorUtils cataThermo(45, &cata);
MotorUtils intakeThermo(45, &intake);
Controller_Out controlOut(&master);
Monitor temps(&controlOut, &chassisThermo, &cataThermo, &intakeThermo);

// Sets up Automous path selector
AutoSelecter path(&potentiometer);
Routes roam(&chassis, &path, &intake, &cata);

// Sets up the PID tuner on the developer controller (second controller)
DevPidTune developerMode(&devControl, &lateralController, &angularController, &roam, &chassis, &drivetrain, &sensors);

// Sets up all piston uilities
PistonControl controlWing(&master, pros::E_CONTROLLER_DIGITAL_L2, &wings);
PistonControl controlElevation(&master, pros::E_CONTROLLER_DIGITAL_X, &elevation);
PistonControl controlLeftMatch(&master, pros::E_CONTROLLER_DIGITAL_LEFT, &leftMatchLoad);
PistonControl controlRightMatch(&master, pros::E_CONTROLLER_DIGITAL_RIGHT, &rightMatchLoad);
PistonControl auxControlElevate(&master, pros::E_CONTROLLER_DIGITAL_Y, &auxElevation);


CataControl controlCata(&master, pros::E_CONTROLLER_DIGITAL_A, &cata, 2280); //2200

void moniterStart(){
	while (true) {
		temps.checkTemps();
		pros::delay(500);
	}
}


// starts pistion 
void pistonUtils(){
	while (true) {
		controlWing.main();
		controlElevation.main();
		controlLeftMatch.main();
		controlRightMatch.main();
		auxControlElevate.main();
		pros::delay(50);
	}
}

void cataUtil() {
	while (true) {
		controlCata.main();
		pros::delay(10);
	}
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	chassis.calibrate();
	master.clear();
	chassisThermo.coast();
	pros::delay(150);
	devControl.clear();
	//pros::Task tempMonitor(moniterStart);
	pros::Task pistonControls(pistonUtils);
	pros::Task cat(cataUtil);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
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
void autonomous() {
	roam.autoRoute();
}

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
	bool cata_on = false;
	bool dev_mode = true;
	//autonomous();
	
	while (true) {
		lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // print the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // print the heading

		//Efficent+
		switch (path.checkPath()) {
			case AutoSelecter::MATCHLOAD:
				pros::lcd::print(3, "MATCHLOAD");
				break;
			case AutoSelecter::NOMATCHLOAD:
				pros::lcd::print(3, "NOMATCHLOAD");
				break;
			case AutoSelecter::SKILLS:
				pros::lcd::print(3, "SKILLS");
				break;
			default:
				pros::lcd::print(3, "None");
		}
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) { roam.autoRoute(); }

			
		
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) { controlOut.silence(); }
		else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) { controlOut.unsilence(); }

		//std::cout << "wwll well well" << std::endl; ???

		int fwd = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);
		int left = fwd + turn;
		int right = fwd - turn;



		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ 
			intake = 127;
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			intake = -127;
		} else {
			intake = 0;
		}

		left_side_motors = left;
		right_side_motors = right;
		
		
		if (dev_mode) {
			developerMode.main();
		}

		pros::delay(20);
	}
}
