#include <Arduino.h>
#include "menuv2.h"
#include "ws2812.h"

void setup() {
    Serial.begin(115200);
}

void loop() {
    ws2812 LED(48,1);
    LED.test(); // 更新显示
}