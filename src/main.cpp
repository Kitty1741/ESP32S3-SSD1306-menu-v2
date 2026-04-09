#include <Arduino.h>
#include <menuv2.h>

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
    {"时间"}
    }
);

void setup(){
    Serial.begin(115200);
    __DEBUG_A("setup()\n")

    //test
    menuInit(mainMenu); //菜单系统初始化
}

void loop(){
    delay(1111);
}
