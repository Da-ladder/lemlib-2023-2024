#include "autoPath.h"
#include "pros/rtos.hpp"
#include "roborUtils.h"
#include "main.h"


void Routes::matchload() {
    //drive->turnTo(10,10, 20000);
    drive ->moveTo(0, 10, 100000);
}

void Routes::nomatchload() {
    *intake = 127;
    drive ->moveTo(0, 50, 1200);
    pros::delay(400);
    *intake = 0;
    drive ->turnTo(-17.68, 47.81, 1200);
    drive ->moveTo(-17.68, 47.81, 1200);
    //pros::delay(200000);
    //do something
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