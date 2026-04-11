#include <Arduino.h>
#include <menuv2.h>

menu mainMenu(
    "主菜单",{
    {"innerMenu",enterMenu(innerMenu)},
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
