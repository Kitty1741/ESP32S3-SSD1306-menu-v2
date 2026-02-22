#include <Arduino.h>
#include "../lib/menu_v2/1_driver/ws2812/ws2812.h"

// WS2812配置
#define WS2812_PIN GPIO_NUM_48  // 使用GPIO 48
#define LED_COUNT 1             // LED数量

void setup() {
    Serial.begin(115200);
    delay(1000);  // 等待串口初始化
}

void loop() {
    driveWS2812(WS2812_PIN, LED_COUNT, 1, 0, 0);
}
