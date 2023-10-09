#include "autoPath.h"
#include "peerPursuitRouts.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include "roborUtils.h"
#include "main.h"


void Routes::matchload() {
    PeerPursuit sup;
    //drive->turnTo(10,10, 20000);
    drive->followFromVector(&sup.route1, 2000, 3);
    //drive ->moveToKI(0, 10, 10000, 1, 4, 200);
    //drive ->angleTurnTo(30, 1000);    
}

void Routes::nomatchload() {
    //Get first triball into goal
    *intake = 127;
    drive ->moveTo(0, 46, 1200);
    drive ->moveTo(0, 52, 400);
    *intake = 0;
    drive ->turnTo(-17.68, 47.81, 800);
    *intake = -127;
    drive ->moveTo(-17.68, 47.81, 500); //700
    *intake = 0;

    
    //Get second triball into goal
    drive ->moveTo(-8.65, 49.88, 500);
    drive ->turnTo(0.06, 56.4, 700); //1000
    *intake = 127;
    drive ->moveTo(2, 56.4, 900); //900

    
    pros::delay(100); //0
    drive ->turnTo(-17.56, 43.63, 700); // 1100
    *intake = 0;

    drive ->moveTo(-5.78, 53.15, 600); //800
    *intake = -127;
    //pros::delay(200);
    //*intake = 0;
    drive ->moveTo(-32.5, 48.07, 800);
    


    //Get third triball into goal
    
    
    drive ->moveTo(-12.03, 49.09, 800);
    drive->angleTurnTo(102.89, 1200);

    //drive ->turnTo(0, 0, 300);
    //drive ->turnTo(5.38, 44.56, 1000); //???

    
    *intake = 127;
    drive ->moveTo(13.76, 41.25, 1000);
    drive ->moveTo(16, 40.81, 700);
    drive ->moveTo(-9.09, 47.56, 1000);

    drive->angleTurnTo(248.05, 800);
    *intake = -127;
    drive->moveToKI(-16.96, 46.08, 1000, 1, 10);
    *intake = 0;
    
    
    
    

    /*
    manual_control(-100, -127);
    pros::delay(500);
    manual_control(0, 0);
    //*intake = 0;
    */
    


    
    
}

void Routes::skills() {
    //Robot scor
    //score alliance triball
    double y = 54.4;
    drive ->moveTo(1, y, 2000);
    drive ->turnTo(-10, y, 700);
    *intake = -127;
    pros::delay(200);
    *intake = 0;
    drive ->moveTo(-10, y, 600); //shove into goal
    
    // score barrier triball
    drive ->moveTo(2.69, y, 600);
    drive->angleTurnTo(-268.16, 1200);
    
    *intake = 127;
    drive ->moveTo(17.17, 55, 1000);
    drive ->moveTo(15, 55, 800);
    drive ->turnTo(0, 100, 200); // FORCES TURN
    drive ->turnTo(-10.72, y, 1000);
    *intake = -127;
    pros::delay(200);
    *intake = 0;
    drive ->moveTo(-15.72, y, 1800); //-12.72

    // get matchload??
    
    drive ->moveTo(0.32, y, 1000);
    
    drive ->angleTurnTo(-177.83, 1200);
    drive ->moveTo(-1.53, 21.3, 2000, 85);
    




    
    drive ->angleTurnTo(-90.18, 1100);
    
    drive ->moveTo(14, 20.01, 2000, 80);
    pros::delay(100);
    rightWing ->set_value(true);
    manual_control(-60, -30);
    pros::delay(500);
    manual_control(-60, 0);
    pros::delay(500);
    manual_control(0, 0);
    
    

    //drive ->turnTo(3.58, 52.24, 1000);
    //drive ->moveTo(3.58, 52.24, 2000);
    

    

    /*
    */




}

void Routes::placehold1() {
    drive->moveTo(-0.95, 48.06, 1000);
    drive->moveTo(-0.88, 48.07, 800);
    drive->angleTurnTo(102.5, 800);
    *intake = -127;
    drive->moveTo(12.4, 44.73, 1000);
    *intake = 0;
    drive->moveTo(-17.33, 52.67, 1000, 80);
    //pros::delay(1000);
    
    
    drive->angleTurnTo(-25.86, 1000);

    drive->moveTo(6.03, 6.54, 3000, 60); // y: 4.54
    leftWing->set_value(true);
    drive->angleTurnTo(25.98, 1000, 1.5, 0, false, 80); //???
    pros::delay(700);
    drive->angleTurnTo(85.54, 1000, 1.5, 0, false, 70);
    leftWing->set_value(false);
    //rightWing->set_value(true);


    
    drive->moveTo(-11.05, 4.82, 1000);
    //rightWing->set_value(false);
    drive->angleTurnTo(99.5, 1000, 80);
    drive->moveTo(-37.84, 8.56, 1200, 70);
    pros::delay(1000);
    
    
}

void Routes::placehold2() {

}

void Routes::placehold3() {

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