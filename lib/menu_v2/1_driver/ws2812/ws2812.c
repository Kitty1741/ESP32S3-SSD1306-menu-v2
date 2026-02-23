#include <Arduino.h>

#include "driver/rmt.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "ws2812.h"
#include "ws2812_config.h"

// WS2812时序参数（单位：纳秒）
#define WS2812_T0H_NS  400
#define WS2812_T0L_NS  850
#define WS2812_T1H_NS  800
#define WS2812_T1L_NS  450

// RMT时钟分频，80MHz APB时钟
#define RMT_CLK_DIV 8
#define RMT_TICK_NS (1000 / (80 / RMT_CLK_DIV))

// 计算RMT时序值
#define NS_TO_TICKS(ns) ((ns) / RMT_TICK_NS)

static rmt_channel_t rmt_channel = USING_RMT_CHANNEL; //ws2812_config.h
static int led_count = 0;
static uint8_t *led_buffer = NULL;

void ws2812_init(int pin, int count ) {
    if (led_buffer != NULL) {
        free(led_buffer);
    }
    
    led_count = count;
    led_buffer = (uint8_t *)malloc(count * 3);
    if (led_buffer == NULL) {
        return;
    }
    memset(led_buffer, 0, count * 3);
    
    // 配置RMT
    rmt_config_t config = {
        .rmt_mode = RMT_MODE_TX,
        .channel = rmt_channel,
        .gpio_num = pin,
        .clk_div = RMT_CLK_DIV,
        .mem_block_num = 1,
        .tx_config = {
            .carrier_freq_hz = 0,
            .carrier_level = RMT_CARRIER_LEVEL_LOW,
            .idle_level = RMT_IDLE_LEVEL_LOW,
            .carrier_duty_percent = 50,
            .carrier_en = false,
            .loop_en = false,
            .idle_output_en = true,
        }
    };
    
    rmt_config(&config);
    rmt_driver_install(rmt_channel, 0, 0);
}

void ws2812_set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    if (index < 0 || index >= led_count || led_buffer == NULL) {
        return;
    }
    
    // WS2812使用GRB顺序
    uint8_t *led = &led_buffer[index * 3];
    led[0] = g;
    led[1] = r;
    led[2] = b;
}

void ws2812_show(void) {
    if (led_buffer == NULL || led_count == 0) {
        return;
    }
    
    // 为每个位创建RMT项目
    size_t rmt_items_size = led_count * 3 * 8 * sizeof(rmt_item32_t);
    rmt_item32_t *rmt_items = (rmt_item32_t *)malloc(rmt_items_size);
    if (rmt_items == NULL) {
        return;
    }
    
    // 填充RMT项目
    rmt_item32_t *item = rmt_items;
    for (int i = 0; i < led_count * 3; i++) {
        uint8_t value = led_buffer[i];
        for (int bit = 7; bit >= 0; bit--) {
            if (value & (1 << bit)) {
                // 位为1: T1H高电平，T1L低电平
                item->level0 = 1;
                item->duration0 = NS_TO_TICKS(WS2812_T1H_NS);
                item->level1 = 0;
                item->duration1 = NS_TO_TICKS(WS2812_T1L_NS);
            } else {
                // 位为0: T0H高电平，T0L低电平
                item->level0 = 1;
                item->duration0 = NS_TO_TICKS(WS2812_T0H_NS);
                item->level1 = 0;
                item->duration1 = NS_TO_TICKS(WS2812_T0L_NS);
            }
            item++;
        }
    }
    
    // 发送数据
    rmt_write_items(rmt_channel, rmt_items, led_count * 3 * 8, true);
    rmt_wait_tx_done(rmt_channel, portMAX_DELAY);
    
    free(rmt_items);
}

void ws2812_clear(void) {
    if (led_buffer != NULL) {
        memset(led_buffer, 0, led_count * 3);
        ws2812_show();
    }
}

#if WS2812_TEST == 1
void ws2812_test(int pin, int led_count) {

    ws2812_init(pin, led_count);
    
    int r, g, b;
    for (int i = 0; i < 3 * 256; i++) {
        if (i < 256) {
            r = 255 - i;
            g = i;
            b = 0;
        } else if (i < 512) {
            r = 0;
            g = 255 - (i - 256);
            b = i - 256;
        } else {
            r = i - 512;
            g = 0;
            b = 255 - (i - 512);
        }
    
        ws2812_set_color(0, r, g, b);
        ws2812_show();
        delay(10);
    }


    ws2812_set_color(0, 255, 0, 0);ws2812_show();delay(500);
    ws2812_set_color(0, 64, 0, 0); ws2812_show();delay(500);
    ws2812_set_color(0, 0, 255, 0);ws2812_show();delay(500);
    ws2812_set_color(0, 0, 64, 0); ws2812_show();delay(500);
    ws2812_set_color(0, 0, 0, 255);ws2812_show();delay(500);
    ws2812_set_color(0, 0, 0, 64); ws2812_show();delay(500);

    ws2812_set_color(0,255,255,0  );ws2812_show();delay(500);
    ws2812_set_color(0,64 ,64 ,0  );ws2812_show();delay(500);
    ws2812_set_color(0,0  ,255,255);ws2812_show();delay(500);
    ws2812_set_color(0,0  ,64 ,64 );ws2812_show();delay(500);
    ws2812_set_color(0,255,0  ,255);ws2812_show();delay(500);
    ws2812_set_color(0,64 ,0  ,64 );ws2812_show();delay(500);

    ws2812_set_color(0,255,255,255);ws2812_show();delay(500);
    ws2812_set_color(0,64 ,64 ,64 );ws2812_show();delay(500);
    ws2812_set_color(0,16 ,16 ,16 );ws2812_show();delay(500);
    ws2812_set_color(0,0  ,0  ,0  );ws2812_show();delay(500);
}
#endif //WS2812_TEST