#include <Arduino.h>
#include <menuv2.h>

#include "imu/imu.h"

menu mainMenu(
    "主菜单",{
    {"innerMenu",enterMenu(innerMenu)},
    {"imu",enterMenu(imuMenu)},
    }
);

void setup(){
    Serial.begin(115200);
    __DEBUG_A("setup()\n")

    menuInit(mainMenu); //菜单系统初始化
}

void loop(){
    vTaskDelay(portMAX_DELAY);
}
