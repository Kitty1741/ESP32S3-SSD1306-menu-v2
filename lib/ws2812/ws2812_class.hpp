#ifndef __WS2812_HPP__
#define __WS2812_HPP__

#include <math.h>
#include "ws2812_config.h"

// C++类封装
#if ENABLE_CPP_CLASS == 1
class ws2812{
    private:
        int pin;
        int led_count;
    public:
        ws2812(int pin, int count);
        void set_color(int index, uint8_t r, uint8_t g, uint8_t b);
        void show();
        void clear();
        #if WS2812_TEST == 1
        void test();
#endif //WS2812_TEST
};
#endif // ENABLE_CPP_CLASS

#endif // __WS2812_HPP__