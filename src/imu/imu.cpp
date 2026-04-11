#include <Arduino.h>
#include <menuv2.h>
#include "SparkFun_BMI270_Arduino_Library.h"
#include "Example01_BasicReadingsI2C.ino"

void scanI2C(TwoWire &wire) {
    for (uint8_t address = 1; address < 127; address++) {
        wire.beginTransmission(address);
        uint8_t error = wire.endTransmission();
        if (error == 0) {
            Serial.print("\nDevice found at 0x");
            Serial.println(address, HEX);
        }
    }
}

void test(){
    Wire1.begin(16,15);
    scanI2C(Wire);
    Serial.print(", in Wire");
    scanI2C(Wire1);
    Serial.print(", in Wire1");
}

menu imuMenu(
    "惯性测量单元",{
        {"BasicReadingsI2C",run_imu},
        {"----------------"},
        {"test",test}
    }
);