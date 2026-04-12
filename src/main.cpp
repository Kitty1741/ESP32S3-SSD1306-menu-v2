#include <Arduino.h>
#include <menuv2.h>

#include <U8g2lib.h>
#include <Wire.h>

void test(){
    u8g2.clearDisplay();
    u8g2.drawUTF8X2(2,2,"世界你好");
    u8g2.sendBuffer();
    while(1){
        if(Keyboard.getKey()==KEY_EVENT_A)return;
    }
}

menu mainMenu(
    "主菜单",{
        {"inner_menu",enterMenu(innerMenu)},
        {"子菜单",newMenu(
            "子菜单",{
                {"1--"},
                {"2------"},
                {"3----------"},
                {"4------"},
                {"5--"},
                {"6------"},
                {"7----------"},
                {"8------"},
                {"9--"},
                {"10-----"},
                {"11---------"},
                {"12-----"},
                {"13-"},
                {"14-----"},
                {"15---------"},
                {"16-----"},
            }
        )},
        {"poweroff",[](){
            u8g2.clearDisplay();
            esp_deep_sleep_start();
        }},
    }
);



void setup(){
    Serial.begin(115200);
    __DEBUG_A("setup()")

    menuInit(mainMenu);
}

void loop(){
    delay(999999);
}
