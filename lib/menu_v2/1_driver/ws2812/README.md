# WS2812 库

ESP32 WS2812 LED 驱动（GRB颜色顺序）


## API

- `ws2812_init(pin, led_count)` - 初始化
- `ws2812_set_color(index, r, g, b)` - 设置颜色（GRB顺序）  
- `ws2812_show()` - 更新显示
- `ws2812_clear()` - 全部清除

## 配置

`ws2812_config.h`:
```c
#define WS2812_TEST 1        // 启用测试函数
#define ENABLE_CPP_CLASS 1   // 启用C++类
#define USING_RMT_CHANNEL 0  // RMT通道0-7
```

## 测试

```c
#if WS2812_TEST == 1
ws2812_test(18, 10);  // 颜色测试
#endif
```
