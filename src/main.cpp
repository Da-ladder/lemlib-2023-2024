#include "lemlib/api.hpp"
#include "main.h"
#include "autoPath.h"
#include "roborUtils.h"
#include "dev.h"
#include <cstdio>


pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller devControl(pros::E_CONTROLLER_PARTNER);

pros::Motor left_motor_A(16, pros::E_MOTOR_GEARSET_06, false); // port 16, blue, not reversed
pros::Motor left_motor_B(18, pros::E_MOTOR_GEARSET_06, true); // port 18, blue, reversed
pros::Motor left_motor_C(20, pros::E_MOTOR_GEARSET_06, true); // port 20, blue, reversed
pros::Motor right_motor_A(11, pros::E_MOTOR_GEARSET_06, false); // port 11, blue, not reversed
pros::Motor right_motor_B(14, pros::E_MOTOR_GEARSET_06, false); // port 14, blue, not reversed
pros::Motor right_motor_C( 15, pros::E_MOTOR_GEARSET_06, true); // port 15, blue, reversed
pros::Motor intake(17, pros::E_MOTOR_GEARSET_18, false);
pros::Motor cata(19,pros::E_MOTOR_GEARSET_36, false);
pros::Motor immigrant(0, pros::E_MOTOR_GEARSET_06, true); // Its taken over, hijacked

pros::ADIDigitalOut leftWing('d', LOW);
pros::ADIDigitalOut primaryElevation('f', HIGH); // LINK
pros::ADIDigitalOut auxElevation('e', LOW); // LINK
pros::ADIDigitalOut rightWing('h', LOW);

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
	10, //kI
    .1, // smallErrorRange
    400, // smallErrorTimeout
    2, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};

// Sets the pid for turning control
lemlib::ChassisController_t angularController {
    3.5, // kP
    26, // kD
	0, // kI
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
Routes roam(&chassis, &path, &intake, &cata, 
			&left_side_motors, &right_side_motors, &rightWing, &leftWing);

// Sets up the PID tuner on the developer controller (second controller)
DevPidTune developerMode(&devControl, &lateralController, &angularController, 
						 &roam, &chassis, &drivetrain, &sensors);

// Sets up all piston uilities
PistonControl controlLeftWing(&master, pros::E_CONTROLLER_DIGITAL_L2, &leftWing);
PistonControl controlElevation(&devControl, pros::E_CONTROLLER_DIGITAL_L1, &primaryElevation);
PistonControl controlRightWing(&master, pros::E_CONTROLLER_DIGITAL_L1, &rightWing);
PistonControl auxControlElevate(&master, pros::E_CONTROLLER_DIGITAL_X, &auxElevation);


CataControl controlCata(&master, pros::E_CONTROLLER_DIGITAL_A, &cata, 2100); //2280

void moniterStart(){
	while (true) {
		temps.checkTemps();
		pros::delay(500);
	}
}


// starts pistion 
void pistonUtils(){
	while (true) {
		controlLeftWing.main();
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && 
			master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
			controlElevation.overrideState(0);
			auxControlElevate.overrideState(1);
		}
		controlRightWing.main();
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
 * @brief 
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
			case AutoSelecter::PLACEHOLD1:
				pros::lcd::print(3, "PLACEHOLD1");
				break;
			case AutoSelecter::PLACEHOLD2:
				pros::lcd::print(3, "PLACEHOLD2");
				break;
			case AutoSelecter::PLACEHOLD3:
				pros::lcd::print(3, "PLACEHOLD3");
				break;
			case AutoSelecter::PLACEHOLD4:
				pros::lcd::print(3, "PLACEHOLD4");
				break;
			case AutoSelecter::PLACEHOLD5:
				pros::lcd::print(3, "PLACEHOLD5");
				break;
			default:
				pros::lcd::print(3, "None");
		}
		
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) { roam.autoRoute(); }

			
		
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) 
		{ controlOut.silence(); }

		else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) 
		{ controlOut.unsilence(); }

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
