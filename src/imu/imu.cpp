#include <Arduino.h>
#include <menuv2.h>
#include "SparkFun_BMI270_Arduino_Library.h"
#include "Example01_BasicReadingsI2C.ino"

menu imuMenu(
    "惯性测量单元",{
        {"BasicReadingsI2C",run_imu},
        {"----------------"}
    }
);