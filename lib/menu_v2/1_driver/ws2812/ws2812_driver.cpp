/**
 * @file ws2812_driver.cpp
 * @brief WS2812Driver类实现文件
 */

#include "ws2812.h"
#include <Arduino.h>
#include <driver/rmt.h>

// WS2812Driver类私有方法实现
void WS2812Driver::colorToRmtItem(uint8_t r, uint8_t g, uint8_t b, rmt_item32_t* items) {
    uint32_t color = (g << 16) | (r << 8) | b;  // WS2812使用GRB顺序
    
    for (int i = 23; i >= 0; i--) {
        if (color & (1 << i)) {
            // 逻辑1：T1H=800ns (64 ticks), T1L=450ns (36 ticks)
            items->duration0 = 64;
            items->level0 = 1;
            items->duration1 = 36;
            items->level1 = 0;
        } else {
            // 逻辑0：T0H=400ns (32 ticks), T0L=850ns (68 ticks)
            items->duration0 = 32;
            items->level0 = 1;
            items->duration1 = 68;
            items->level1 = 0;
        }
        items++;
    }
}

// WS2812Driver类公共方法实现
WS2812Driver::WS2812Driver(gpio_num_t pin, uint16_t ledCount, rmt_channel_t channel)
    : pin(pin), ledCount(ledCount), channel(channel) {
    pixelBuffer = new uint8_t[ledCount * 3];  // 每个LED 3字节 (GRB)
    rmtItemsSize = ledCount * 24;  // 每个LED 24位
    rmtItems = new rmt_item32_t[rmtItemsSize];
}

WS2812Driver::~WS2812Driver() {
    delete[] pixelBuffer;
    delete[] rmtItems;
    rmt_driver_uninstall(channel);
}

bool WS2812Driver::begin() {
    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(pin, channel);
    config.clk_div = 2;  // 80MHz / 2 = 40MHz，每个tick = 25ns
    
    esp_err_t err = rmt_config(&config);
    if (err != ESP_OK) {
        Serial.printf("RMT配置失败: %d\n", err);
        return false;
    }
    
    err = rmt_driver_install(channel, 0, 0);
    if (err != ESP_OK) {
        Serial.printf("RMT驱动安装失败: %d\n", err);
        return false;
    }
    
    // 清空LED缓冲区
    clear();
    return true;
}

void WS2812Driver::setPixel(uint16_t index, uint8_t r, uint8_t g, uint8_t b) {
    if (index >= ledCount) return;
    
    // WS2812使用GRB顺序
    pixelBuffer[index * 3] = g;
    pixelBuffer[index * 3 + 1] = r;
    pixelBuffer[index * 3 + 2] = b;
}

void WS2812Driver::fill(uint8_t r, uint8_t g, uint8_t b) {
    for (uint16_t i = 0; i < ledCount; i++) {
        setPixel(i, r, g, b);
    }
}

void WS2812Driver::clear() {
    fill(0, 0, 0);
}

void WS2812Driver::show() {
    // 将颜色数据转换为RMT数据项
    rmt_item32_t* currentItem = rmtItems;
    
    for (uint16_t i = 0; i < ledCount; i++) {
        uint8_t g = pixelBuffer[i * 3];
        uint8_t r = pixelBuffer[i * 3 + 1];
        uint8_t b = pixelBuffer[i * 3 + 2];
        colorToRmtItem(r, g, b, currentItem);
        currentItem += 24;
    }
    
    // 发送RMT数据
    esp_err_t err = rmt_write_items(channel, rmtItems, rmtItemsSize, true);
    if (err != ESP_OK) {
        Serial.printf("RMT写入失败: %d\n", err);
    }
    
    // WS2812需要至少50us的复位码（低电平）
    // rmt_write_items的wait_tx_done参数为true会等待传输完成
}

void WS2812Driver::rainbow(uint32_t wait) {
    for (uint16_t j = 0; j < 256; j++) {
        for (uint16_t i = 0; i < ledCount; i++) {
            // 生成彩虹颜色
            uint32_t pixelHue = (i * 256 / ledCount) + j;
            uint8_t r, g, b;
            hueToRGB(pixelHue, &r, &g, &b);
            setPixel(i, r, g, b);
        }
        show();
        delay(wait);
    }
}

// 静态方法实现（已经在头文件中声明为内联，这里不需要重复定义）