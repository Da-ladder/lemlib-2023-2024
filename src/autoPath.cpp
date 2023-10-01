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
    pros::delay(300);
    *intake = 0;
    drive ->turnTo(-17.68, 47.81, 800);
    *intake = -127;
    pros::delay(200);
    *intake = 0;
    drive ->moveTo(-17.68, 47.81, 700);

    
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
    drive ->moveTo(-20.5, 48.07, 1000);
    


    //Get third triball into goal
    
    drive ->moveTo(-4.08, 52.66, 800);
    drive ->turnTo(3.05, 3.23, 1000);
    
    *intake = 127;
    drive ->moveTo(3.05, 3.23, 2000);
    drive ->turnTo(5.01, -2.71, 400);
    drive ->moveTo(5.01, -2.71, 700);
    pros::delay(300);
    *intake = 0;
    
    
}

void Routes::skills() {
    //do something

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