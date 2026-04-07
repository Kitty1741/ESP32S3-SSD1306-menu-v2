# 1 "C:\\Users\\admin\\AppData\\Local\\Temp\\tmpjeeg5jgz"
#include <Arduino.h>
# 1 "C:/Users/admin/Desktop/VScode/ESP32/C++/menu_v2/src/main.ino"
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
        {"选项3"}
        }
        )},
    {"选项1"},
    {"时间",getTimeTest}
    }
);
void setup();
void loop();
#line 21 "C:/Users/admin/Desktop/VScode/ESP32/C++/menu_v2/src/main.ino"
void setup(){
    Serial.begin(115200);
    __DEBUG_A("setup()\n")

    menuInit(mainMenu);
}

void loop(){
    vTaskDelay(portMAX_DELAY);
}