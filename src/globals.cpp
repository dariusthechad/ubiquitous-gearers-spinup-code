#include "main.h"
#include "okapi/impl/device/distanceSensor.hpp"

using namespace okapi;

okapi::Controller master;

okapi::Motor intake(9,true,AbstractMotor::gearset::blue,AbstractMotor::encoderUnits::rotations);
okapi::Motor cata(1,true,AbstractMotor::gearset::red,AbstractMotor::encoderUnits::degrees);

std::shared_ptr<ChassisController> drive =
ChassisControllerBuilder()
    .withMotors({-1,-2,3},{4,5,-6})
    .withDimensions(AbstractMotor::GearsetRatioPair(AbstractMotor::gearset::blue,84.0/36.0),{{4_in,12.3_in},imev5BlueTPR})
    .build();


ProfileConstraint drivelimits({1.367941937_mps, 8_mps2, 16_mps3});
std::shared_ptr<ryan::AsyncMotionProfiler> profiler = AsyncMotionProfilerBuilder()
  .withOutput(drive)
  .withProfiler(std::make_unique<SCurveMotionProfile>(drivelimits))
  .build();

