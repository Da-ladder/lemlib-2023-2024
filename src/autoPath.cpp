#include "autoPath.h"
#include "pros/rtos.hpp"
#include "roborUtils.h"
#include "main.h"


void Routes::matchload() {
    //drive->turnTo(10,10, 20000);
    drive ->moveTo(0, 10, 10000);
}

void Routes::nomatchload() {
    //Get first triball into goal
    *intake = 127;
    drive ->moveTo(0, 46, 2000);
    drive ->moveTo(0, 52, 400);
    pros::delay(250);
    *intake = 0;
    drive ->turnTo(-17.68, 47.81, 800);
    *intake = -127;
    //pros::delay(200);
    drive ->moveTo(-17.68, 47.81, 700);
    *intake = 0;

    
    //Get second triball into goal
    drive ->moveTo(-8.65, 49.88, 800);
    drive ->turnTo(0.06, 56.4, 1000);
    *intake = 127;
    drive ->moveTo(2, 56.4, 900); //0.06

    
    pros::delay(200);
    drive ->turnTo(-17.56, 43.63, 700); // 1100
    *intake = 0;

    drive ->moveTo(-5.78, 53.15, 800); //1100
    *intake = -127;
    pros::delay(200);
    *intake = 0;
    drive ->moveTo(-32.5, 48.07, 3000);
    


    //Get third triball into goal
    
    drive ->moveTo(-4.08, 52.66, 800);
    drive ->turnTo(3.05, 3.23, 1000);
    
    *intake = 127;
    drive ->moveTo(3.05, 3.23, 2000);
    manual_control(-100, -127);
    pros::delay(500);
    manual_control(0, 0);
    //*intake = 0;
    


    
    
}

void Routes::skills() {
    //score alliance triball
    drive ->moveTo(0, 58, 2000);
    drive ->turnTo(-9.73, 58, 700);
    *intake = -127;
    pros::delay(200);
    *intake = 0;
    drive ->moveTo(-9.73, 58, 600);
    
    // score barrier triball
    drive ->moveTo(2.69, 58, 600);
    drive ->turnTo(0, 100, 200); // FORCES TURN
    drive ->turnTo(16, 58, 1000);
    *intake = 127;
    drive ->moveTo(14, 58, 800);
    drive ->moveTo(15, 58, 200);
    drive ->turnTo(0, 100, 200); // FORCES TURN
    drive ->turnTo(-10.72, 58, 1000);
    *intake = -127;
    pros::delay(200);
    *intake = 0;
    drive ->moveTo(-15.72, 58, 1800); //-12.72

    // get matchload??
    drive ->moveTo(-5.29, 58, 1000);

    drive ->turnTo(-5.29, 100, 1200); // force turn?
    //drive ->turnTo(-5.29, 26.44, 1000); // TURN
    drive ->moveTo(-5.29, 26.44, 2000);




    

    drive ->turnTo(-14.2, 50, 600); // SHIT
    drive ->turnTo(-14.2, 26.44, 1000);
    drive ->moveTo(14.2, 26.44, 2000);

    wing ->set_value(true);
    //manual_control(-3, 0);
    pros::delay(100000);

    //drive ->turnTo(3.58, 52.24, 1000);
    //drive ->moveTo(3.58, 52.24, 2000);
    

    

    /*
    */




}


/*!
 * \brief Selects the route for auto using the Autoselector class pointer.
 * @param       weight    The weight of the chicken.
 * @param       sauce     The sauce for cooking. Could be a
 * @result      No return but runs autos
*/
void Routes::autoRoute() {
    if (path->checkPath() == AutoSelecter::MATCHLOAD) {
        matchload();
    } else if (path->checkPath() == AutoSelecter::NOMATCHLOAD) {
        nomatchload();
    } else if (path->checkPath() == AutoSelecter::SKILLS) {
        skills();
    } else {
        // Run nothing lol
    }
}