# 基于ESP32的WS2812 库

ESP32 WS2812 LED 驱动（GRB颜色顺序）

## API

#### C
- `ws2812_init(pin, led_count)` - 初始化
- `ws2812_set_color(index, r, g, b)` - 设置颜色（GRB顺序）  
- `ws2812_show()` - 更新显示
- `ws2812_clear()` - 全部清除
- `ws2812_test(pin, led_count)` - 测试，需要启用

#### C++
- 见`ws2812_class.hpp` (需要启用)

## 配置

在`ws2812_config.h`中:
```c
#define WS2812_TEST        // 启用测试函数 （用于调试）（灯闪烁）
#define ENABLE_CPP_CLASS   // 启用编译C++类
#define USING_RMT_CHANNEL  // RMT通道0-3
``
