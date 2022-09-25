#include "main.h"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QAngularSpeed.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/impl/device/controllerUtil.hpp"
using namespace okapi;
void turnroller(float angle){
float rotations = ((2.375*(angle/360.0))/4.0)/2.0;
intake.moveRelative(rotations,600);
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	//motionprofile->generatePath({{0_ft,0_ft,0_deg}},"sex");
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
	profiler->setTarget(-1_tile);
	profiler->waitUntilSettled();
	profiler->setTarget(360_deg);
	profiler->waitUntilSettled();
	profiler->setTarget(-1.1_tile);
	profiler->waitUntilSettled();
	TURN(90);
	pros::delay(1000);

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
	Pneumatics expansion('a');
	ControllerButton intakebutton(ControllerDigital::R1);
	ControllerButton outtakebutton(ControllerDigital::R2);
	ControllerButton expansionbutton(ControllerDigital::X);
	bool past30s = false;
	int startdriver = pros::millis();
	while(true){
		drive->getModel()->tank(master.getAnalog(ControllerAnalog::leftY),master.getAnalog(ControllerAnalog::rightY));
		if(((pros::millis()-startdriver)>75000)&&(past30s=false)){
			master.rumble("- - - ");
			past30s = true;
		}
		if(((pros::millis()-startdriver)>90000)&&(past30s=false)){
			master.rumble("-.-.-.");
			past30s = true;
		}
		if(intakebutton.isPressed()){
			intake.moveVoltage(12000);
		}
		else if(outtakebutton.isPressed()){
			intake.moveVoltage(-12000);
		}
		else{
			intake.moveVoltage(0);
		}
		if(expansionbutton.changedToPressed()){
			expansion.toggle();
		}
		pros::delay(10);
		
	}
}
