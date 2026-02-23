#include "ws2812.h"
#include "ws2812.hpp"
#include "ws2812_config.h"

#if ENABLE_CPP_CLASS == 1
ws2812::ws2812(int pin, int count){
    this->pin = pin;
    this->led_count = count;
    ws2812_init(pin, count);
}
void ws2812::set_color(int index, uint8_t r, uint8_t g, uint8_t b){
    ws2812_set_color(index, r, g, b);
}
void ws2812::show(){
    ws2812_show();
}
void ws2812::clear(){
    ws2812_clear();
}   
#if WS2812_TEST == 1
void ws2812::test(){
    ws2812_test(this->pin, this->led_count);
}   
#endif //WS2812_TEST
#endif // ENABLE_CPP_CLASS