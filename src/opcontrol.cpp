#include "main.h"
#include "odomDebug/odomDebug.hpp"
auto chassis = ChassisControllerBuilder()
    .withMotors({4, 3}, {2, 1}) // pass motors to odomchassiscontroller builder
    .withGains(
         { 0.00345, 0.00002, 0.00009 }, // Distance controller gains
         { 0.0061, 0.00057, 0.000212 }, // Turn controller gains
         { 0.00022, 0.0001, 0.00003 }  // Angle controller gains
     )

    .withSensors({'E', 'F', true}, {'A', 'B', false}, {'C', 'D', true}) //pass sensors for left, right, middle
    .withDimensions(AbstractMotor::gearset::blue, {{2.75_in, 5.125_in, 4.3125_in, 2.75_in}, quadEncoderTPR}) //pass chassis dimensions. 2.75" tracking wheels, 4.25" distance and 4.375" b/w mid and middle wheel
    .withOdometry() // use the same scales as the chassis (above)
    .withLogger(std::make_shared<Logger>(
        TimeUtilFactory::createDefault().getTimer(),
        "/ser/sout", // Output to the PROS terminal
        Logger::LogLevel::debug // Show all feedback
    ))
    .withMaxVelocity(300) //cap velocity at 300 to reduce jerk and cut down on PID correction time
    .buildOdometry(); // build an odometry chassis
void setState(OdomDebug::state_t state) {
	// set your odometry position to these cartesian coordenates
	// to access the values, call `state.x`, `state.y`, and `state.theta`
	// to convert the QUnits to doubles, call
	// `state.x.convert(inch)` or `state.theta.convert(radian)`
	// you can use any length or angle unit
	// example commands:
	 state = chassis->getState();
	 //printf(str(state.x));
	 //odomSetPosition(state.x, state.y, state.theta);
	 //odomSetPosition(state.x.convert(inch), state.y.convert(inch), state.theta.convert(radian));
}

void resetSensors() {
	// reset sensors and reset odometry
	// example commands:
	 odomResetSensors();
	 odomSetPosition(0, 0, 0);
}

void opcontrol() {

	OdomDebug display(lv_scr_act(), LV_COLOR_ORANGE);
	display.setStateCallback(setState);
	display.setResetCallback(resetSensors);

	while(true) {

   	// set your odometry data here (position and sensor data)
   	// you can use QUnits for the x, y, and theta,
   	// or you can use doubles, in inches and radians
    // the last `middle` paramiter is optional, depending on your robot
     //display.setData({x, y, theta}, {left, right, middle});

    // display.setData({0, 0, 0}, {0, 0});
    // display.setData({0_in, 0_in, 0_deg}, {0, 0, 0});

    pros::delay(20);
  }

}
