#include <Arduino.h>
#include <menuv2.h>

#include <U8g2lib.h>
#include <Wire.h>

menu mainMenu(
    "主菜单",{
        {"inner_menu",enterMenu(innerMenu)},
        {"WiFi",enterMenu(wifiMenu)},
        {"deep_sleep",[](){
            u8g2.clearDisplay();
            esp_sleep_enable_ext0_wakeup((gpio_num_t)GPIO_KEY_F1, 0);
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
    vTaskDelay(portMAX_DELAY);
}
