#include "main.h"
using namespace okapi;
void doubleroller(){
    profiler->setTarget(1_in);
    profiler->waitUntilSettled();
    TURN(90);
    pros::delay(500);
    profiler->setTarget(-4_in);
    profiler->waitUntilSettled();
    profiler->setTarget(-135_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(5.6_tile);
    profiler->waitUntilSettled();
    profiler->setTarget(45_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(10_in);
    profiler->waitUntilSettled();
    TURN(90);
    pros::delay(1000);
}
void singleroller(){
    profiler->setTarget(3_in);
    profiler->waitUntilSettled();
    TURN(90);
    pros::delay(1000);
}