#include <Arduino.h>
#include <menuv2.h>
#include <ws2812.h>

//test
#include <U8g2lib.h>
#include <Wire.h>

extern menu* currentMenu;
menu mainMenu(
    "mainMenu",{
    {"中文测试"},
    {"进入二级菜单",enterMenu(
        "test_2",{
        {"你已进入多级菜单"},
        {"祝你好运"},
        {"身体是革命的本钱"},
        {"原神牛逼"},
        {"进入三级菜单",enterMenu(
            "test_3",{
            {"浅网->深网->暗网"},
            {"第一章：斗罗大陆,异界唐三"},
            }
        )},
        {"永远别忘记自己在干什么"},
        }
    )},
    {"选项1"},
    {"选项2"},
    {"选项3"},
    {"选项4"},
    {"选项5"},
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
    printMenu(currentMenu);
    u8g2.sendBuffer();
}
