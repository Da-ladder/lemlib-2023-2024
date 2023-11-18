#include "autoPath.h"
#include "display/lv_draw/lv_draw_img.h"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include "roborUtils.h"

PeerPursuit pursuitPath;

std::vector<std::string> testering{"-0.000000, -0.000609, 0.005470",
                                   "-0.000001, -0.003941, 0.035421",
                                   "-0.000039, -0.028546, 0.103621",
                                   "-0.000329, -0.136581, 0.156949",
                                   "-0.001141, -0.404552, 0.194780",
                                   "-0.003044, -0.894530, 0.239705",
                                   "-0.006169, -1.642205, 0.230131",
                                   "-0.009980, -2.611398, 0.223247",
                                   "-0.015158, -3.702144, 0.314752",
                                   "-0.020757, -4.864759, 0.211024",
                                   "-0.024338, -6.066310, 0.151271",
                                   "-0.027314, -7.323015, 0.128383",
                                   "-0.030604, -8.577286, 0.160094",
                                   "-0.034727, -9.923304, 0.175226",
                                   "-0.037142, -11.313547, -0.023962",
                                   "-0.032441, -12.767032, -0.342922",
                                   "-0.016746, -14.354298, -0.835345",
                                   "0.017253, -15.983978, -1.555775",
                                   "0.073548, -17.649563, -2.253984",
                                   "0.148681, -19.239733, -3.163796",
                                   "0.245195, -20.765314, -4.107307",
                                   "0.364518, -22.225426, -5.316940",
                                   "0.513613, -23.628744, -6.856665",
                                   "0.697954, -24.976210, -8.779889",
                                   "0.927566, -26.301252, -10.916307",
                                   "1.198325, -27.559935, -13.491136",
                                   "1.507234, -28.708660, -16.792664",
                                   "1.840167, -29.694962, -20.511660",
                                   "2.232192, -30.653811, -23.817915",
                                   "2.665043, -31.571665, -26.625807",
                                   "3.149249, -32.495773, -28.490032",
                                   "3.689988, -33.466496, -29.667780",
                                   "4.258495, -34.440338, -31.003437",
                                   "4.834931, -35.365101, -33.062008",
                                   "5.432022, -36.241192, -35.461979",
                                   "6.027400, -37.043396, -37.647617",
                                   "6.692434, -37.878506, -39.370163",
                                   "7.337366, -38.647552, -40.596462",
                                   "7.983311, -39.382198, -42.051285",
                                   "8.673110, -40.126282, -43.637806",
                                   "9.414188, -40.881981, -45.213017",
                                   "10.205307, -41.646091, -46.798077",
                                   "11.049374, -42.417564, -48.373188",
                                   "11.951648, -43.194611, -50.211922",
                                   "12.880155, -43.939125, -52.361839",
                                   "13.848546, -44.656204, -54.607723",
                                   "14.849613, -45.336910, -56.956249",
                                   "15.855441, -45.961399, -59.467690",
                                   "16.872028, -46.530422, -62.072739",
                                   "17.904852, -47.048222, -64.687904",
                                   "18.998623, -47.535294, -67.308395",
                                   "20.049366, -47.945679, -70.092552",
                                   "21.111500, -48.298664, -73.108452",
                                   "22.232807, -48.607422, -76.036758",
                                   "23.322996, -48.852814, -78.533913",
                                   "24.440678, -49.058437, -80.554794",
                                   "25.655619, -49.247337, -81.892151",
                                   "27.072819, -49.433655, -83.039253",
                                   "28.520960, -49.602562, -83.700394",
                                   "29.402105, -49.692764, -84.457207",
                                   "29.242952, -49.678093, -84.823097",
                                   "29.038181, -49.659519, -84.835762",
                                   "29.015799, -49.657497, -84.884850",
                                   "29.009428, -49.656937, -84.942345",
                                   "29.007750, -49.656792, -84.957489",
                                   "29.000137, -49.656124, -85.026169",
                                   "28.961786, -49.652843, -85.142685",
                                   "28.928879, -49.650089, -85.286552",
                                   "endData"};

void Routes::matchload() {
  // score alliance triball
  double y = 54.4;
  intake = 127;
  chassis.moveTo(2.62, 53.65, 2000);
  intake = 0;
  chassis.angleTurnTo(-87.45, 1000);
  intake = -127;
  pros::delay(400);
  chassis.moveTo(-10.46, 54.37, 1000);
  chassis.moveTo(3.44, 54.10, 1000);
  chassis.angleTurnTo(83.75, 1000);
  intake = 127;
  chassis.moveTo(13.75, 55.51, 1000);
  intake = 0;
  chassis.angleTurnTo(266, 1000);
  intake = -127;
  pros::delay(300);
  chassis.moveTo(-13.52, 53.37, 1000); // x = -15
  // chassis.followFromVector(&pursuitPath.route1, 2000, 10, false, 60, 6);

  chassis.moveTo(-5.43, 53.9, 1000);
  chassis.angleTurnTo(355.49, 1000);

  chassis.moveTo(-5.92, 19.43, 3000, 80);

  chassis.angleTurnTo(-90.83, 1000);
  // chassis.moveTo(0, 18.88, 1000);

  chassis.moveTo(12.77, 18.88, 1000);
  controlRightWing.overrideState(1);
  intake = 0;

  manual_control(-40, 0);
  pros::delay(2000);
  manual_control(0, 0);
}

void Routes::nomatchload() {
  // Get first triball into goal
  //  RUSH all 3 triballs
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
  // pros::delay(600);

  manual_control(80, 0);
  pros::delay(450);
  manual_control(0, 0);
  manual_control(-22, 65);
  pros::delay(500);
  manual_control(15, -15); // equal before
  auxControlElevate.overrideState(1);
  pros::delay(200);
  manual_control(17, 17);
  pros::delay(400);
  manual_control(0, 0);

  // chassis.followFromVector(&pursuitPath.route1, 5000, 12);
  // chassis.followFromVector(&pursuitPath.skills, 800, 10, false, 40);

  chassis.angleTurnTo(-25.19, 700);
  manual_control(30, 30);
  pros::delay(200);
  manual_control(0, 0);
  chassis.angleTurnTo(-25.19, 800);

  controlCata.overRideCataState(true);
  pros::delay(27000); // 27 secs
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
}

void Routes::placehold1() {
  // STARTS with ALLIANCE TRIBALL and scores it in opp. goal and gets matchload
  // out touches the bar as well
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
  pros::delay(500);

  chassis.moveTo(-23.39, 28.31, 2000, 50);
  chassis.moveTo(-21.37, 26.46, 1000, 60);

  // controlLeftWing.overrideState(1);
}

void Routes::placehold2() {
  // ELIM AUTO MAX POINTS ie 3 triballs
  int outtakePower = -103;
  // ALLIANCE TRIBALL
  intake = 127;
  // pros::delay(500);
  chassis.moveTo(1.38, 40.01, 1100);
  intake = 0;
  chassis.angleTurnTo(91.66, 700);

  intake = -97;
  pros::delay(150);

  chassis.angleTurnTo(10.85, 700);

  // SECOND TRIBALL
  intake = 127;
  // chassis.moveTo(-3.22, 53.02, 900);
  chassis.moveTo(0.92, 52.23, 700);
  pros::delay(150);
  // intake = 0;
  chassis.angleTurnTo(99.88, 700);

  intake = outtakePower;
  pros::delay(150);
  intake = 0;
  chassis.angleTurnTo(251.06, 900);

  // THIRD TRIBALL
  intake = 127;
  chassis.moveTo(-10.47, 50.24, 600, 80); // 800
  pros::delay(170);
  chassis.moveTo(-2.39, 51.95, 700);
  // intake = 0;
  chassis.angleTurnTo(449.24, 800);
  intake = outtakePower;
  pros::delay(150);
  intake = 0;
  chassis.angleTurnTo(20.29, 800);

  intake = 127;
  chassis.moveTo(7.34, 65.36, 800); // 1000
  chassis.angleTurnTo(-67.19, 800);

  chassis.moveTo(-1.42, 67.55, 800);
  pros::delay(150);

  // ORGINAL
  chassis.moveTo(1.07, 66.45, 800);
  // intake = 0;
  chassis.angleTurnTo(463.62, 900);
  intake = outtakePower;
  pros::delay(150);
  intake = 0;
  chassis.moveTo(-2.93, 67.47, 700);
  chassis.angleTurnTo(641.35, 800);
  controlLeftWing.overrideState(1);
  controlRightWing.overrideState(1);
  chassis.moveTo(22.19, 58.29, 1500);

  // TEST
}

void Routes::placehold3() {
  // far side safe get center unsided triball
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
  // VERY SAFE AWP
  /*
  controlLeftWing.overrideState(1);
  chassis.moveTo(-0.053, -7.98, 1000);
  chassis.angleTurnTo(16.46, 1000);
  controlLeftWing.overrideState(0);
  chassis.angleTurnTo(-90.19, 1000);
  chassis.moveTo(-36.13, -8.38, 1000);
  chassis.angleTurnTo(-134.54, 1000);
  intake = 127;
  chassis.moveTo(-47.32, -18.95, 1000);
  pros::delay(150);
  chassis.angleTurnTo(-47.98, 1000);
  intake = -127;
  pros::delay(150);
  chassis.angleTurnTo(130.44, 1000);
  controlRightWing.overrideState(1);
  controlLeftWing.overrideState(1);
  chassis.moveTo(-62.52, -7.78, 1000);
  */
  // Comment on your code, Cody

  // Eva tries to code
  // chassis.moveTo(6, 70, 1000)

  matchContact.overrideState(1);
  intake = 127;
  chassis.moveTo(0.5, 50.98, 300, 110);
  matchContact.overrideState(0);
  chassis.moveTo(0.5, 50.98, 1200, 90);
  //pros::delay(100);
  /*
  manual_control(-127, -127);
  pros::delay(150);
  manual_control(0, 0);
  pros::delay(100);
  */
  
  //chassis.moveTo(-1.52, 46.32, 500);
  controlLeftWing.overrideState(1);
  chassis.angleTurnTo(-110.23, 500);
  chassis.moveTo(18.041, 52.51, 800);
  controlLeftWing.overrideState(0);
  chassis.angleTurnTo(-154.22, 700);
  chassis.moveTo(-0.11, 10.8, 900);
  chassis.angleTurnTo(-256.54, 700);
  intake = -127;
  pros::delay(150);
  chassis.angleTurnTo(-372.76, 600);

  controlRightWing.overrideState(1);
  chassis.angleTurnTo(410.04, 600);
  controlRightWing.overrideState(0);
  chassis.angleTurnTo(-444.13, 800);
  chassis.moveTo(16.37, 7.76, 700);
  chassis.angleTurnTo(-463.90, 600);

  
  

  /*
  controlLeftWing.overrideState(1);
  chassis.moveTo(14.71, 51.25, 700); //???
  
  controlLeftWing.overrideState(0); //???
  pros::delay(50);
  chassis.moveTo(14.71, 51.25, 400);

  chassis.angleTurnTo(-154.14, 300);

  chassis.moveTo(-9.32, 5.36, 500, 127);
  chassis.moveTo(-9.32, 5.36, 600, 50);

  // chassis.moveTo(-6.85, 6.39, 800, 127);
  // chassis.moveTo(-6.85, 6.39, 1000, 50); //????

  chassis.angleTurnTo(-261.32, 500);
  intake = -270;
  pros::delay(150);

  chassis.angleTurnTo(-379.48, 500);
  controlRightWing.overrideState(1);
  chassis.moveTo(-5.99, 1.06, 700); //1k
  chassis.angleTurnTo(-439.97, 400); //1k
  controlRightWing.overrideState(0);
  chassis.angleTurnTo(-429.03, 300); //???
  chassis.moveTo(7.20, -3.75, 700); //1k

  chassis.angleTurnTo(-462.52, 700);
  chassis.moveTo(32.32, 1.45, 800);

  // chassis.moveTo(30.55, -0.65, 1000);
  // chassis.moveTo(20.27, -2.46, 1000);

  // chassis.moveTo(30.55, 0.85, 1000);
  // blocker.overrideState(1);
  */

  /*
  chassis.angleTurnTo(-414.08, 1000);
  controlRightWing.overrideState(1);
  pros::delay(150);
  chassis.angleTurnTo(-447.41, 1000);
  */
}

int waiter = -1;
int onOffOps = 0;
PistonControl *realz = nullptr;

void pistonDelay(PistonControl *piston, int onOff, int wait) {
  realz = piston;
  onOffOps = onOff;
  waiter = wait;
}

void pistonWait() {
  while (true) {
    if (waiter != 0) {
      waiter--;
    } else if (waiter == 0) {
      realz->overrideState(onOffOps);
      waiter = -1;
    } else {
    }
    pros::delay(10);
  }
}

int intakeWaiter = -1;
int intakeOnOffOps = 0;
int intakeOnTime = 0;
int intakeSpeed = 0;

void intakeDelay(int speed, int onOff, int onTime, int wait) {
  intakeWaiter = wait;
  intakeOnOffOps = onOff;
  intakeOnTime = onTime;
  intakeSpeed = speed;
}

void intakeAsync() {
  while (true) {
    if (intakeWaiter != 0) {
      intakeWaiter--;
    } else if (intakeWaiter == 0) {
      intake = intakeSpeed;
      pros::delay(intakeOnTime);
      intakeWaiter = -1;
    } else {
    }
    pros::delay(10);
  }
}

void Routes::placehold5() {
  // 6 ball SAFE side
  pros::Task nameish(pistonWait);
  pros::Task nameish2(intakeAsync);

  intake = 127;
  chassis.moveTo(1.25, 51.77, 1300);
  //pros::delay(200);

  //chassis.moveTo(1.25, 49.77, 200);
  manual_control(-127, -127);
  pros::delay(100);
  manual_control(0, 0);
  chassis.angleTurnTo(107.77, 350); //700
  intake = -127;
  pros::delay(200);
  chassis.angleTurnTo(-43.63, 700); //700
  intake = 127;
  chassis.moveTo(-14.05, 60.85, 500); //900

  chassis.angleTurnTo(-15.35, 300); //300
  chassis.moveTo(-9.48, 39.88, 600); //800
  chassis.angleTurnTo(81.88, 400); //700
  intake = -127;
  pros::delay(200);
  chassis.angleTurnTo(-70.76, 600); //800
  intake = 127;
  chassis.moveTo(-24.6, 45.6, 600); //800
  chassis.followFromVector(&pursuitPath.autopt2, 1650, 8, true);
  chassis.moveTo(23.191, 42.94, 300); //400
  //pros::delay(200);

  chassis.angleTurnTo(-168.22, 400); //750
  chassis.moveTo(-5.84, 0.74, 1200, 110); //1.4k
  chassis.angleTurnTo(-272.89, 400); //800
  intake = -127;
  pros::delay(200);
  intake = 127;
  chassis.angleTurnTo(-84.74, 600); //800
  chassis.moveTo(-22.67, 2.51, 600); //800
  chassis.angleTurnTo(-427.64, 300); //500
  chassis.moveTo(-39.63, 9.42, 700); //800
  chassis.moveTo(-9.73, -1.99, 800); //1k
  chassis.angleTurnTo(-291.1, 500); //800
  intake = -127;
  pros::delay(200);
  chassis.angleTurnTo(-472.11, 500);
  controlRightWing.overrideState(1);
  chassis.followFromVector(&pursuitPath.autopt3, 1650, 8, true);
  pistonDelay(&controlRightWing, 0, 50);
  //chassis.moveTo(-1.46, 0.64, 800);
  //controlRightWing.overrideState(0);

  /*
  chassis.angleTurnTo(-244.05, 700);
  intake = -127;
  pros::delay(200);
  chassis.angleTurnTo(-158.23, 700);
  chassis.moveTo(-18.48, 4.13, 500);
  chassis.angleTurnTo(-73.94, 700);
  chassis.moveTo(-44.28, 10.75, 900);
  */
  //chassis.followFromVector(&pursuitPath.autopt3, 2050, 8);
  //chassis.angleTurnTo(-125.91, 700);
  

  /*
  chassis.followFromVector(&pursuitPath.autopt1v2, 1750, 10, true);
  pros::delay(200);
  
  chassis.angleTurnTo(-80.69, 700);
  */

  /*
  intake = -127;
  pros::delay(250);
  chassis.angleTurnTo(-68.26, 710);
  intake = 127;
  chassis.moveTo(-27.602, 43.15, 800);
  chassis.angleTurnTo(-107.37, 600);
  controlLeftWing.overrideState(1);
  chassis.followFromVector(&pursuitPath.autopt2, 1550, 10, true);
  //pros::delay(200);
  //chassis.followFromVector(&pursuitPath.autopt3, 1550, 10);
  chassis.angleTurnTo(-170.53, 800);
  chassis.moveTo(-9.27, 0.3, 1200);
  chassis.angleTurnTo(-268.51, 750);
  */
  

  
  


  /*
  chassis.followFromVector(&pursuitPath.autopt3, 1550, 10);
  intake = -127;
  pros::delay(250);
  chassis.angleTurnTo(-88.56, 800);
  intake = 127;
  chassis.moveTo(-27.07, 13.47, 1100);
  chassis.angleTurnTo(-74.98, 800);

  realz = &controlRightWing;
  onOffOps = 1;
  waiter = 50;

  chassis.followFromVector(&pursuitPath.autopt4, 2200, 10, true);
*/
  




  /*
  chassis.moveTo(-0.10, 50.2, 1000);
  pros::delay(200);
  chassis.moveTo(0.05, 43.57, 800);
  chassis.angleTurnTo(85.58, 600);
  intake = -127;
  pros::delay(200);
  chassis.angleTurnTo(-27.13, 600);
  intake = 127; 
  

  chassis.followFromVector(&pursuitPath.autopt2, 1000, 5, true);
  chassis.angleTurnTo(55.77, 1000);
  intake = -127;
  pros::delay(200);
  intake = 127;
  chassis.angleTurnTo(-80.35, 700);
  chassis.moveTo(-29.40, 46.64, 1000);
  pros::delay(200);
  chassis.followFromVector(&pursuitPath.autopt3, 1400, 5, true);
  chassis.angleTurnTo(-247.63, 700);
  intake = -127;
  pros::delay(200);
  chassis.angleTurnTo(-71.31, 800);
  controlRightWing.overrideState(1);
  chassis.moveTo(10, 47.09, 1000);
  */



  

  //chassis.followFromVector(&pursuitPath.autopt3, 1000, 5);



  //realz = &controlRightWing;
  // onOffOps = 1;
  // waiter = 30;
  


  //chassis.followFromVector(&pursuitPath.autopt2, 4000, 10, true); //WORKY
  //chassis.angleTurnTo(100, 1000);
  //manual_control(127,127);
  //pros::delay(200);


  /*
  for (int i = 0; i < pursuitPath.opse.size(); i++) {
  // Do something with vector[i]
    manual_control(pursuitPath.opse[i][0], pursuitPath.opse[i][1]);
    pros::delay(50);
  }
  */
  

  //pros::Task egs(pistonWait);


  // VERY VERY SAFE AWP
  // intake = 127;
  // pros::delay(200);

  // realz = &controlRightWing;
  // waiter = 30;
  // onOffOps = 1;
  //chassis.followFromVector(&testering, 3000, 15, true, 127, 15); hmm
  //controlLeftWing.overrideState(1); hmm
  // chassis.moveTo(7.307871, -35.735050, 200);
  // chassis.angleTurnTo(0, 600);

  // controlRightWing.overrideState(1);
  /*
  intake = 127;
  controlRightWing.overrideState(1);
  pros::delay(250);
  chassis.angleTurnTo(-37.03, 1000);
  controlRightWing.overrideState(0);
  intake = -127;
  pros::delay(200);
  chassis.moveTo(-3.26, 3.96, 800); //???

  chassis.angleTurnTo(-224.79, 1000);
  chassis.moveTo(-19.17, 21.96, 1000);
  chassis.angleTurnTo(162.34, 800);
  chassis.moveTo(-21.01, 48.52, 1000); //28.52

  chassis.moveTo(-20.04, 25.43, 1000); //28.52
  chassis.angleTurnTo(129.31, 1000);
  chassis.moveTo(-11.16, 15.83, 1000);
  chassis.angleTurnTo(-41.91, 1000);
  chassis.moveTo(0.49, 4.78, 1200, 80);
  blocker.overrideState(1);
  chassis.angleTurnTo(-88.72, 1000);
  chassis.angleTurnTo(-78.96, 800, 1.5, 0, false, 80);
  chassis.moveTo(29.10, -0.252, 2000, 80);
  */
}

/*!
 * \brief Selects the route for auto using the Autoselector class pointer.
 * @param       weight    The weight of the chicken.
 * @param       sauce     The sauce for cooking. Could be a
 * @result      No return but runs autos
 */
void Routes::autoRoute() {
  // void (*fp)(void) = &roam.placehold1();
  // AutoCreater devtest("sewiweo", (*fp));

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
