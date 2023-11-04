#include "autoPath.h"
#include "main.h"
#include "pros/rtos.hpp"

PeerPursuit pursuitPath;


void Routes::matchload() {
    //score alliance triball
    double y = 54.4;
    intake = 127;
    chassis. moveTo(2.62, 53.65, 2000);
    intake = 0;
    chassis.angleTurnTo(-87.45, 1000);
    intake = -127;
    pros::delay(400);
    chassis. moveTo(-10.46, 54.37, 1000);
    chassis. moveTo(3.44, 54.10, 1000);
    chassis.angleTurnTo(83.75, 1000);
    intake = 127;
    chassis. moveTo(13.75, 55.51, 1000);
    intake = 0;
    chassis.angleTurnTo(266, 1000);
    intake = -127;
    pros::delay(300);
    chassis.moveTo(-13.52, 53.37, 1000); // x = -15

    
    chassis.moveTo(-5.43, 53.9, 1000);
    chassis.angleTurnTo(355.49, 1000);
    
    chassis.moveTo(-5.92, 19.43, 3000, 80);
    
    
    chassis.angleTurnTo(-90.83, 1000);
    //chassis.moveTo(0, 18.88, 1000);
    
    

    chassis.moveTo(12.77, 18.88, 1000);
    controlRightWing.overrideState(1);
    intake = 0;
    

    manual_control(-40, 0);
    pros::delay(2000);
    manual_control(0, 0);
    
}

void Routes::nomatchload() {
    //Get first triball into goal
    // RUSH all 3 triballs
    intake = 127;
    chassis.moveTo(-0.92, 52.48, 2000);
    intake = 0;
    chassis.angleTurnTo(107.81, 1000);
    intake = -127;
    pros::delay(300);
    chassis.moveTo(16.22, 49.98, 1500);
    chassis.moveTo(4.52, 53.71, 1500);
    chassis.angleTurnTo(-55.38, 1000);
    
    intake = 127;
    chassis.moveTo(-14.38, 65.02, 1600, 100); //-6.13???
    pros::delay(400);
    intake = 0;
    chassis.angleTurnTo(106.49, 1000);
    intake = -127;
    chassis.moveTo(10, 54.47, 1000);
    chassis.moveTo(7.77, 57.75, 1000);
    chassis.angleTurnTo(18.7, 1000);

    chassis.moveTo(-3.7, 27.34, 3000, 70);
    chassis.angleTurnTo(110.59, 1000);
    chassis.moveTo(-27.28, 33.58, 3000, 70);
    controlLeftWing.overrideState(1);
    intake = 0;
    
    manual_control(5, -40);
    pros::delay(130000);
    
    

    
    
}

void Routes::skills() {
    /* Skills route
    ezchas->leftSwing(30, 127);
    pros::delay(700);
    ezchas->rightSwing(-20, 127); //-20
    */
    //pros::delay(600);
    
    manual_control(80, 0);
    pros::delay(450);
    manual_control(0, 0);
    manual_control(-22, 65);
    pros::delay(500);
    manual_control(15, -15); //equal before
    auxControlElevate.overrideState(1);
    pros::delay(200);
    manual_control(17, 17);
    pros::delay(200);
    manual_control(0, 0);
    
    //chassis.followFromVector(&pursuitPath.route1, 5000, 12);
    //chassis.followFromVector(&pursuitPath.skills, 800, 10, false, 40);
    chassis.angleTurnTo(-30, 600);
    manual_control(30, 30);
    pros::delay(200);
    manual_control(0, 0);

    controlCata.overRideCataState(true);
    pros::delay(35000); //27 secs
    controlCata.overRideCataState(false);
    auxControlElevate.overrideState(0);
    
    chassis.moveTo(3.37, 14.77, 700, 70);
    chassis.angleTurnTo(31.25, 800);
    chassis.moveTo(-4.47, 3.86, 900);
    chassis.angleTurnTo(1.32, 800);
    chassis.moveTo(-5.65, -71.66, 4000, 80);
    chassis.angleTurnTo(-89.16, 800);
    
    chassis.moveTo(16.3, -72.99, 1000, 80);
    chassis.angleTurnTo(-177.4, 1000);
    chassis.moveTo(18.12, -51.23, 1000);
    chassis.angleTurnTo(-88.15, 900);
    
    chassis.moveTo(56.41, -54.17, 1000);
    chassis.angleTurnTo(-0.9, 1000);
    controlLeftWing.overrideState(1);
    controlRightWing.overrideState(1);
    chassis.moveTo(58.02, -88.60, 1000);

    chassis.moveTo(58.02, -68.78, 1000);
    chassis.moveTo(58.02, -88.60, 1000);

    /*
    chassis.moveTo(-4.31, 4.26, 900, 70);
    chassis.angleTurnTo(2.3, 600);
    chassis.moveTo(-6.12, -70.02, 4000, 80);
    
    chassis.angleTurnTo(-100.58, 900);
    chassis.moveTo(16.94, -67.26, 900);
    */
    
    
    


    /*
    chassis.angleTurnTo(24.473568, 300);
    chassis.moveTo(-2.452747, -3.902936, 1000);
    chassis.angleTurnTo(1.912794, 400);
    chassis.moveTo(-3.720832, -66.550499, 1500);
    chassis.angleTurnTo(-31.219227, 700);
    leftWing->set_value(true);
    rightWing->set_value(true);
    chassis.moveTo(10.264065, -87.865616, 600);
    leftWing->set_value(false);
    rightWing->set_value(false);
    */

    /*
    chassis.moveTo(22.462017, -95.127281, 1000);
    chassis.moveTo(2.711529, -87.614944, 1000);
    chassis.angleTurnTo(-51.116760, 500);
    chassis.moveTo(25.554518, -99.227768, 200);
    manual_control(-127, -127);
    pros::delay(700);
    manual_control(127, 127);
    pros::delay(250);
    manual_control(-127, -127);
    pros::delay(700);
    manual_control(0, 0);
    */


    //chassis.moveTo(-2.346564, -76.252495, 1500);
    //chassis.angleTurnTo(-17.625759, 600);



    //chassis.followFromVector(&pursuitPath.skills, 20000, 12, true, 70);
    //leftWing->set_value(true);
    //rightWing->set_value(true);



    /*
    chassis.followFromVector(&pursuitPath.skillsPt2, 15000, 10, true, 80);
    leftWing->set_value(false);
    rightWing->set_value(false);
    chassis.moveTo(18.45, -93.39, 2000);
    chassis.moveTo(27.37, -92.86, 2000);
    */

    


}

void Routes::placehold1() {
    // STARTS with ALLIANCE TRIBALL and scores it in opp. goal and gets matchload out touches the bar as well
    chassis.moveTo(-0.74, -23.66, 1000);
    intake = 127;
    chassis.angleTurnTo(37.01, 800);
    intake = 0;

    // PUSH INTO GOAL
    
    chassis.moveTo(-7.98, -31.15, 1000); // ORGINAL POINT
    
    chassis.moveTo(-2.1, -23.54, 1000);
    
    
    chassis.angleTurnTo(-175.1, 1300);
    
    controlRightWing.overrideState(1);
    chassis.moveTo(-2.95, -5.81, 1000);
    controlRightWing.overrideState(0);

    chassis.moveTo(-0.93, 3.54, 1000);

    
    chassis.angleTurnTo(139.41, 800);
    blocker.overrideState(1);

    
    chassis.moveTo(-23.39, 28.31, 2000, 50);
    chassis.moveTo(-21.37, 26.46, 1000, 60);
    
    
    
    //controlLeftWing.overrideState(1); 
    
}

void Routes::placehold2() {
    // ELIM AUTO MAX POINTS ie 3 triballs
    int outtakePower = -103;

    //Gets first triball in
    /*
    intake = 127;
    chassis.moveTo(1.529109, 58.866264, 1200);
    chassis.angleTurnTo(106.086319, 800);
    intake = -127;
    pros::delay(300);
    chassis.moveTo(17.678692, 53.106972, 1200);

    //Gets second triball in 
    chassis.moveTo(8.417645, 56.126083, 1200);
    intake = 127;
    chassis.angleTurnTo(-67.989243, 870);
    
    chassis.moveTo(-10.052180, 66.153664, 1200);
    chassis.angleTurnTo(-245.428406, 800);
    intake = -127;
    pros::delay(300);
    chassis.moveTo(20.167933, 53.301449, 1400); //??

    
    //Gets third triball in
    chassis.moveTo(10.958176, 56.014328, 1200);
    intake = 127;
    chassis.angleTurnTo(253.14, 800);
    
    
    chassis.moveTo(-12.107163, 49.054832, 1300);
    chassis.moveTo(8.066624, 56.862743, 1200);
    intake = 0;
    chassis.angleTurnTo(464.019257, 600);
    intake = -127;
    pros::delay(300);
    chassis.moveTo(29.532024, 50.815063, 1200);
    intake = 0;
    */
    //ALLIANCE TRIBALL
    intake = 127;
    //pros::delay(500);
    
    
    chassis.moveTo(1.38, 40.01, 1100);
    intake = 0;
    chassis.angleTurnTo(75.08, 700);
    intake = -97;
    pros::delay(150);
    
    chassis.angleTurnTo(10.85, 700);
    
    
    // SECOND TRIBALL
    intake = 127;
    //chassis.moveTo(-3.22, 53.02, 900);
    chassis.moveTo(0.92, 52.23, 700);
    pros::delay(150);
    intake = 0;
    chassis.angleTurnTo(99.88, 700);
    intake = outtakePower;
    pros::delay(150);
    intake = 0;
    chassis.angleTurnTo(247.06, 900);
    
    
    // THIRD TRIBALL
    intake = 127;
    chassis.moveTo(-8.04, 50.88, 600, 80); //800
    pros::delay(150);
    intake = 0;
    
    chassis.moveTo(-2.39, 51.95, 700);
    chassis.angleTurnTo(449.24, 800);
    intake = outtakePower;
    pros::delay(150);
    intake = 0;
    chassis.angleTurnTo(20.29, 800);
    

    intake = 127;
    chassis.moveTo(7.34, 65.36, 800); //1000
    chassis.angleTurnTo(-67.19, 800);
    
    chassis.moveTo(0.48, 67.55, 800);
    pros::delay(150);
    intake = 0;
    

    
    

    // ORGINAL
    chassis.moveTo(1.07, 66.45, 800);
    chassis.angleTurnTo(463.62, 900);
    intake = outtakePower;
    pros::delay(150);
    intake = 0;
    chassis.moveTo(-2.93, 67.47, 700);
    chassis.angleTurnTo(641.35, 800);
    controlLeftWing.overrideState(1);
    controlRightWing.overrideState(1);
    chassis.moveTo(25, 63.12, 1200);
    
    
    
    
    
    

    

}

void Routes::placehold3() {
    //far side safe
    intake = 127;
    chassis.moveTo(-0.160420, 29.762564, 1000, 80);
    pros::delay(200);
    intake = 0;
    chassis.moveTo(-0.670581, 8.074307, 1000, 80);
    intake = 127;
    chassis.angleTurnTo(142.281921, 1000);
    intake = -127;
    pros::delay(200);
    chassis.angleTurnTo(-20.527496, 1000);
    controlRightWing.overrideState(1);
    chassis.moveTo(2.301120, -3.003214, 1000);
    chassis.angleTurnTo(-43.321899, 1000);
    chassis.moveTo(10.994921, -12.855775, 1000);
    controlRightWing.overrideState(0);
    chassis.moveTo(14.494976, -16.681007, 1000);
    chassis.angleTurnTo(-81.444534, 1000);
    chassis.moveTo(27.814409, -19.599689, 1000);
    chassis.moveTo(15.701077, -19.377268, 1000, 80);
    chassis.moveTo(27.838827, -19.613266, 1000);
    chassis.moveTo(20.55, -20, 1000);
    chassis.angleTurnTo(-40.26, 1000);
    chassis.moveTo(0.65, 3.48, 1000);
    chassis.angleTurnTo(-2.38, 1000);
    chassis.moveTo(-0.82, 31.43, 1000);
}

void Routes::placehold4() {

}

void Routes::placehold5() {

}


/*!
 * \brief Selects the route for auto using the Autoselector class pointer.
 * @param       weight    The weight of the chicken.
 * @param       sauce     The sauce for cooking. Could be a
 * @result      No return but runs autos
*/
void Routes::autoRoute() {
    //void (*fp)(void) = &roam.placehold1();
    //AutoCreater devtest("sewiweo", (*fp));

    switch (path->checkPath()) {
        case AutoSelecter::MATCHLOAD:
				matchload();
				break;
			case AutoSelecter::NOMATCHLOAD:
				nomatchload();
				break;
			case AutoSelecter::SKILLS:
				skills();
				break;
			case AutoSelecter::PLACEHOLD1:
				placehold1();
				break;
			case AutoSelecter::PLACEHOLD2:
				placehold2();
				break;
			case AutoSelecter::PLACEHOLD3:
				placehold3();
				break;
			case AutoSelecter::PLACEHOLD4:
				placehold4();
				break;
			case AutoSelecter::PLACEHOLD5:
				placehold5();
				break;
			default:
				pros::lcd::print(3, "None");
    
    }
}


