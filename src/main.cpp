#include <Arduino.h>
#include "menuv2.h"

// WS2812配置
#define WS2812_PIN GPIO_NUM_48  // 使用GPIO 48
#define LED_COUNT 1             // LED数量

void setup() {
    Serial.begin(115200);
    delay(1000);  // 等待串口初始化
}

void loop() {
    for(int16_t i = 0; i < 24; i++){
        double light = i/255.0;
        double real_light = light * light; // gamma校正
        uint8_t product = (uint8_t)(real_light*255);
        uint8_t remainder = (uint8_t)(real_light*255 - product);
        for(uint16_t j = 0;j<15;j++){ //PWM补充精度
            if(j < remainder*15 +1){
                driveWS2812(WS2812_PIN, LED_COUNT, product + 1, 0, 0); // 红色
            }else{
                driveWS2812(WS2812_PIN, LED_COUNT, product, 0, 0); // 红色
            }
            delay(1);
        }
    }
}
