#include <Arduino.h>
#include <menuv2.h>

menu mainMenu(
    "主菜单",{
    {"子菜单1",newMenu(
        "子菜单1",{
        {"选项1"},
        {"选项2"},
        {"子菜单2",newMenu(
            "子菜单2",{
            {"-"},
            {"-----"},
            {"---"},
            {"------------"},
            {"abcd"}
            }
        )},
        {"子菜单3",newMenu(
            "子菜单2",{
            {"a"},
            {"ab"},
            {"abc"},
            {"abcd"},
            {"abcde"},
            {"abcdef"},
            {"abcdefg"},
            {"abcdefgh"},
            {"abcdefghi"},
            {"abcdefghij"}
            }
        )},
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

    menuInit(mainMenu); //菜单系统初始化
}

void loop(){
    vTaskDelay(portMAX_DELAY);
}
