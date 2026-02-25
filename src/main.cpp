#include <Arduino.h>
#include <menuv2.h>
#include <ws2812.h>

void setup(){
    Serial.begin(115200);
    __DEBUG_A("Setup()\n")

    menuInit(); //菜单系统初始化
}

void loop(){
    __DEBUG_A("loop()\n")
    delay(1000);
} 