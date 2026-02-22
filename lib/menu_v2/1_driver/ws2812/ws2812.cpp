/**
 * @file ws2812.cpp
 * @brief WS2812可寻址LED驱动实现文件
 */

#include "ws2812.h"
#include <Arduino.h>
#include <driver/rmt.h>

// C函数实现
bool driveWS2812(gpio_num_t pin, uint16_t ledCount, uint8_t r, uint8_t g, uint8_t b) {
    static rmt_channel_t currentChannel = RMT_CHANNEL_0;
    static bool initialized = false;
    
    // 如果未初始化，进行初始化
    if (!initialized) {
        rmt_config_t config = RMT_DEFAULT_CONFIG_TX(pin, currentChannel);
        config.clk_div = 2;  // 80MHz / 2 = 40MHz, 每个tick = 25ns
        
        esp_err_t err = rmt_config(&config);
        if (err != ESP_OK) {
            Serial.printf("RMT配置失败: %d\n", err);
            return false;
        }
        
        err = rmt_driver_install(currentChannel, 0, 0);
        if (err != ESP_OK) {
            Serial.printf("RMT驱动安装失败: %d\n", err);
            return false;
        }
        
        initialized = true;
        Serial.println("WS2812驱动初始化成功");
    }
    
    // 创建RMT数据项
    size_t rmtItemsSize = ledCount * 24;  // 每个LED 24位
    rmt_item32_t* rmtItems = new rmt_item32_t[rmtItemsSize];
    
    // 为每个LED生成RMT数据
    rmt_item32_t* currentItem = rmtItems;
    for (uint16_t i = 0; i < ledCount; i++) {
        // WS2812使用GRB顺序
        uint32_t color = (g << 16) | (r << 8) | b;
        
        for (int bit = 23; bit >= 0; bit--) {
            if (color & (1 << bit)) {
                // 逻辑1：T1H=800ns (32 ticks), T1L=450ns (18 ticks)
                // 注意：40MHz时钟下，每个tick=25ns
                currentItem->duration0 = 32;  // 800ns / 25ns = 32
                currentItem->level0 = 1;
                currentItem->duration1 = 18;  // 450ns / 25ns = 18
                currentItem->level1 = 0;
            } else {
                // 逻辑0：T0H=400ns (16 ticks), T0L=850ns (34 ticks)
                currentItem->duration0 = 16;  // 400ns / 25ns = 16
                currentItem->level0 = 1;
                currentItem->duration1 = 34;  // 850ns / 25ns = 34
                currentItem->level1 = 0;
            }
            currentItem++;
        }
    }
    
    // 发送数据
    esp_err_t err = rmt_write_items(currentChannel, rmtItems, rmtItemsSize, true);
    delete[] rmtItems;
    
    if (err != ESP_OK) {
        Serial.printf("RMT写入失败: %d\n", err);
        return false;
    }
    
    return true;
}

bool clearWS2812(gpio_num_t pin, uint16_t ledCount) {
    return driveWS2812(pin, ledCount, 0, 0, 0);
}

void rainbowWS2812(gpio_num_t pin, uint16_t ledCount, uint16_t durationMs) {
    Serial.println("开始彩虹效果演示...");
    
    unsigned long startTime = millis();
    unsigned long endTime = startTime + durationMs;
    
    while (millis() < endTime) {
        // 生成彩虹颜色
        uint8_t hue = (millis() * 256 / 2000) % 256;  // 每2秒循环一次
        
        uint8_t r, g, b;
        if (hue < 85) {
            r = hue * 3;
            g = 255 - hue * 3;
            b = 0;
        } else if (hue < 170) {
            hue -= 85;
            r = 255 - hue * 3;
            g = 0;
            b = hue * 3;
        } else {
            hue -= 170;
            r = 0;
            g = hue * 3;
            b = 255 - hue * 3;
        }
        
        if (!driveWS2812(pin, ledCount, r, g, b)) {
            Serial.println("彩虹效果发送失败");
            break;
        }
        
        delay(20);  // 控制刷新率
    }
    
    // 演示结束后清空LED
    clearWS2812(pin, ledCount);
    Serial.println("彩虹效果演示结束");
}