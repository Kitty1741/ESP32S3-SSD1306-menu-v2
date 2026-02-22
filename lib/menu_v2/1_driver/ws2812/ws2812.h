/**
 * @file ws2812.h
 * @brief WS2812可寻址LED驱动头文件
 * 
 * 提供使用ESP32 RMT外设驱动WS2812 LED的函数和类接口
 */

#ifndef WS2812_H
#define WS2812_H

#include <driver/gpio.h>
#include <driver/rmt.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 简单的WS2812驱动函数
 * 
 * 使用ESP32的RMT外设驱动WS2812 LED
 * 
 * @param pin GPIO引脚号 (例如: GPIO_NUM_18)
 * @param ledCount LED数量
 * @param r 红色值 (0-255)
 * @param g 绿色值 (0-255)
 * @param b 蓝色值 (0-255)
 * 
 * @return true 成功, false 失败
 */
bool driveWS2812(gpio_num_t pin, uint16_t ledCount, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief 清空所有LED（关闭）
 * 
 * @param pin GPIO引脚号
 * @param ledCount LED数量
 * 
 * @return true 成功, false 失败
 */
bool clearWS2812(gpio_num_t pin, uint16_t ledCount);

/**
 * @brief 彩虹效果演示函数
 * 
 * @param pin GPIO引脚号
 * @param ledCount LED数量
 * @param durationMs 演示时长（毫秒，默认5000ms）
 */
void rainbowWS2812(gpio_num_t pin, uint16_t ledCount, uint32_t durationMs);

#ifdef __cplusplus
}
#endif

// C++类接口
#ifdef __cplusplus

/**
 * @brief WS2812驱动类
 * 
 * 使用ESP32的RMT外设驱动WS2812可寻址LED
 */
class WS2812Driver {
private:
    rmt_channel_t channel;
    gpio_num_t pin;
    uint16_t ledCount;
    uint8_t* pixelBuffer;
    rmt_item32_t* rmtItems;
    size_t rmtItemsSize;

    /**
     * @brief 将RGB颜色值转换为RMT数据项
     */
    void colorToRmtItem(uint8_t r, uint8_t g, uint8_t b, rmt_item32_t* items);

public:
    /**
     * @brief 构造函数
     * @param pin GPIO引脚号
     * @param ledCount LED数量
     * @param channel RMT通道（默认为RMT_CHANNEL_0）
     */
    WS2812Driver(gpio_num_t pin, uint16_t ledCount, rmt_channel_t channel = RMT_CHANNEL_0);
    
    /**
     * @brief 析构函数
     */
    ~WS2812Driver();
    
    /**
     * @brief 初始化WS2812驱动
     * @return true 初始化成功，false 初始化失败
     */
    bool begin();
    
    /**
     * @brief 设置单个LED颜色
     * @param index LED索引（从0开始）
     * @param r 红色值 (0-255)
     * @param g 绿色值 (0-255)
     * @param b 蓝色值 (0-255)
     */
    void setPixel(uint16_t index, uint8_t r, uint8_t g, uint8_t b);
    
    /**
     * @brief 设置所有LED为同一颜色
     * @param r 红色值 (0-255)
     * @param g 绿色值 (0-255)
     * @param b 蓝色值 (0-255)
     */
    void fill(uint8_t r, uint8_t g, uint8_t b);
    
    /**
     * @brief 清空所有LED（关闭）
     */
    void clear();
    
    /**
     * @brief 更新LED显示（发送数据到WS2812）
     */
    void show();
    
    /**
     * @brief 测试彩虹效果
     * @param wait 每个颜色之间的延迟（毫秒）
     */
    void rainbow(uint32_t wait = 10);
    
    /**
     * @brief 将色相转换为RGB颜色（静态公共方法）
     * @param hue 色相值 (0-255)
     * @param r 红色值输出指针
     * @param g 绿色值输出指针
     * @param b 蓝色值输出指针
     */
    static void hueToRGB(uint8_t hue, uint8_t* r, uint8_t* g, uint8_t* b);
};

#endif // __cplusplus

#endif // WS2812_H
