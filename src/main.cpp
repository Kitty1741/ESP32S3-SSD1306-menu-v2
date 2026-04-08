#include <Arduino.h>
#include <../lib/menu_v2/menuv2.h>
#include <../lib/ws2812/ws2812.h>

#include "test.cpp"

menu mainMenu(
    "主菜单",{
    {"子菜单1",newMenu(
        "子菜单1",{
        {"选项1"},
        {"选项2"},
        {"选项3"},
        {"选项4"},
        {"选项5"}
        }
        )},
    {"选项1"},
    {"时间",getTimeTest}
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
