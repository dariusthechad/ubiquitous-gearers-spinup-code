#pragma once
#include "api.h"
#include "okapi/api.hpp"
#include "okapi/api/control/async/asyncMotionProfileController.hpp"
#include "pneumatics.hpp"
#include "ryanlib/api.hpp"

extern std::shared_ptr<okapi::ChassisController> drive;
extern okapi::Controller master;
extern okapi::Motor cata;
extern okapi::Motor intake;
extern std::shared_ptr<ryan::AsyncMotionProfiler> profiler;

#define TURN(angle) intake.moveRelative(0.000824653*angle,600)

