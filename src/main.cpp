#include <Arduino.h>
#include <menuv2.h>
#include <ws2812.h>

//test
#include <U8g2lib.h>
#include <Wire.h>

menu mainMenu(
    "mainMenu",{
        {"test"},
        {"setup",setup},
        {"中文测试"},
    }
);

void setup(){
    Serial.begin(115200);
    __DEBUG_A("Setup()\n")

    menuInit(); //菜单系统初始化
    initMenuCore(&mainMenu);
}

void loop(){
    u8g2.clearBuffer();
    printNameBar("test//中文测试");
    printMenuItems(&mainMenu);
    u8g2.sendBuffer();
}
