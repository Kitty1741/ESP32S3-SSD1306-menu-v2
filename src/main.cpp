#include <Arduino.h>
#include "../lib/menu_v2/1_driver/ws2812/ws2812.h"

// WS2812配置
#define WS2812_PIN GPIO_NUM_48  // 使用GPIO 48
#define LED_COUNT 1             // LED数量

void setup() {
    Serial.begin(115200);
    delay(1000);  // 等待串口初始化
    
    Serial.println("\n=== WS2812 LED驱动演示 ===");
    Serial.println("开发板: ESP32-S3");
    Serial.printf("WS2812引脚: GPIO %d\n", WS2812_PIN);
    Serial.printf("LED数量: %d\n", LED_COUNT);
    Serial.println("演示开始...\n");
}

void loop() {
    Serial.println("1. 显示红色");
    driveWS2812(WS2812_PIN, LED_COUNT, 255, 0, 0);
    delay(1000);
    
    Serial.println("2. 显示绿色");
    driveWS2812(WS2812_PIN, LED_COUNT, 0, 255, 0);
    delay(1000);
    
    Serial.println("3. 显示蓝色");
    driveWS2812(WS2812_PIN, LED_COUNT, 0, 0, 255);
    delay(1000);
    
    Serial.println("4. 显示白色");
    driveWS2812(WS2812_PIN, LED_COUNT, 255, 255, 255);
    delay(1000);
    
    Serial.println("5. 彩虹效果（5秒）");
    rainbowWS2812(WS2812_PIN, LED_COUNT, 5000);
    
    Serial.println("6. 清空LED");
    clearWS2812(WS2812_PIN, LED_COUNT);
    delay(1000);
    
    Serial.println("\n演示循环完成，重新开始...\n");
    delay(2000);
}
