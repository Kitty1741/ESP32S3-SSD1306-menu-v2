#ifndef __WS2812_H__
#define __WS2812_H__

#include <stdint.h>
#include "ws2812_config.h"

#ifdef __cplusplus
#include "ws2812.hpp"
extern "C" {
#endif

        /**
         * @brief 初始化 WS2812 驱动
         * @param pin GPIO引脚号
         * @param led_count LED数量
         */
        void ws2812_init(int pin, int led_count);

        /**
         * @brief 设置单个LED的颜色
         * @param index LED索引（从0开始）
         * @param r 红色值 (0-255)
         * @param g 绿色值 (0-255)
         * @param b 蓝色值 (0-255)
         */
        void ws2812_set_color(int index, uint8_t r, uint8_t g, uint8_t b);

        /**
         * @brief 更新所有LED显示
         */
        void ws2812_show(void);

        /**
         * @brief 清除所有LED（设置为黑色）
         */
        void ws2812_clear(void);


#if WS2812_TEST == 1
/**
 * @brief 测试LED显示功能
 */
void ws2812_test(int pin, int led_count);
#endif //WS2812_TEST


#ifdef __cplusplus
}
#endif

#endif // __WS2812_H__