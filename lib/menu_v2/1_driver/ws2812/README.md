# WS2812 LED驱动库 for ESP32

这个库提供了使用ESP32微控制器驱动WS2812可寻址LED的功能，基于ESP32的RMT硬件外设确保纳秒级精确时序。

## 功能特性

- ✅ 使用ESP32 RMT硬件外设，时序精确到12.5ns
- ✅ 支持WS2812/WS2812B/NeoPixel等兼容LED
- ✅ 提供C函数接口（简单易用）
- ✅ 提供C++类接口（功能丰富）
- ✅ 支持GRB颜色顺序（WS2812标准）
- ✅ 内存安全：动态分配和自动释放
- ✅ 错误处理：所有操作都有返回值检查
- ✅ 多种效果：彩虹、呼吸灯、颜色渐变等

## 文件结构

```
ws2812/
├── README.md          # 本文档
├── ws2812.h           # 驱动头文件（C/C++接口）
├── ws2812.cpp         # C语言驱动函数实现
└── ws2812_driver.cpp  # C++ WS2812Driver类实现
```

## 快速开始

### 1. 包含头文件

```cpp
#include <lib/menu_v2/1_driver/ws2812/ws2812.h>
```

### 2. 使用C函数接口（简单）

```cpp
// 设置8个LED为红色
driveWS2812(GPIO_NUM_18, 8, 255, 0, 0);

// 清空所有LED
clearWS2812(GPIO_NUM_18, 8);

// 彩虹效果（5秒）
rainbowWS2812(GPIO_NUM_18, 8, 5000);
```

### 3. 使用C++类接口（高级）

```cpp
// 创建驱动对象
WS2812Driver ledStrip(GPIO_NUM_18, 16);

// 初始化
ledStrip.begin();

// 设置单个LED
ledStrip.setPixel(0, 255, 0, 0);  // 第一个LED红色
ledStrip.setPixel(1, 0, 255, 0);  // 第二个LED绿色

// 更新显示
ledStrip.show();

// 清空所有LED
ledStrip.clear();
ledStrip.show();

// 彩虹效果
ledStrip.rainbow(20);
```

## API参考

### C函数

#### `bool driveWS2812(gpio_num_t pin, uint16_t ledCount, uint8_t r, uint8_t g, uint8_t b)`
设置指定数量的LED为指定颜色。

**参数：**
- `pin`: GPIO引脚号（例如：`GPIO_NUM_18`）
- `ledCount`: LED数量
- `r`: 红色值 (0-255)
- `g`: 绿色值 (0-255)
- `b`: 蓝色值 (0-255)

**返回值：**
- `true`: 操作成功
- `false`: 操作失败

#### `bool clearWS2812(gpio_num_t pin, uint16_t ledCount)`
关闭所有LED。

#### `void rainbowWS2812(gpio_num_t pin, uint16_t ledCount, uint16_t durationMs)`
显示彩虹效果，持续指定毫秒数。

### C++类：WS2812Driver

#### 构造函数
```cpp
WS2812Driver(gpio_num_t pin, uint16_t ledCount, rmt_channel_t channel = RMT_CHANNEL_0)
```

#### 方法
- `bool begin()`: 初始化驱动，返回是否成功
- `void setPixel(uint16_t index, uint8_t r, uint8_t g, uint8_t b)`: 设置单个LED颜色
- `void fill(uint8_t r, uint8_t g, uint8_t b)`: 设置所有LED为相同颜色
- `void clear()`: 清空所有LED（关闭）
- `void show()`: 更新LED显示（发送数据到WS2812）
- `void rainbow(uint16_t wait = 10)`: 显示彩虹效果
- `static void hueToRGB(uint8_t hue, uint8_t* r, uint8_t* g, uint8_t* b)`: 色相转RGB（静态方法）

## 硬件连接

### 接线指南
1. **电源**：WS2812需要5V电源（不要使用ESP32的3.3V）
2. **信号线**：连接到ESP32的GPIO引脚（默认GPIO 18）
3. **接地**：确保ESP32和WS2812共地

### 电源注意事项
- 每个WS2812 LED全白时消耗约60mA
- 驱动多个LED时确保电源足够
- 建议使用独立5V电源，通过电平转换器连接信号线

## 技术细节

### 时序精度
使用ESP32的RMT（Remote Control）硬件外设，时钟频率40MHz，每个tick=25ns，确保符合WS2812协议要求：

- **逻辑0**：T0H = 400ns (16 ticks), T0L = 850ns (34 ticks)
- **逻辑1**：T1H = 800ns (32 ticks), T1L = 450ns (18 ticks)
- **复位码**：至少50us低电平（由RMT硬件自动生成）

### 颜色顺序
WS2812使用**GRB**颜色顺序（绿-红-蓝），库已自动处理转换。

### 内存使用
- 每个LED占用3字节内存（GRB各1字节）
- RMT数据项动态分配，使用后自动释放

## 示例程序

### 基本演示
```cpp
#include <Arduino.h>
#include <lib/menu_v2/1_driver/ws2812/ws2812.h>

#define WS2812_PIN GPIO_NUM_18
#define LED_COUNT 8

void setup() {
    Serial.begin(115200);
    
    // 红色
    driveWS2812(WS2812_PIN, LED_COUNT, 255, 0, 0);
    delay(1000);
    
    // 绿色
    driveWS2812(WS2812_PIN, LED_COUNT, 0, 255, 0);
    delay(1000);
    
    // 蓝色
    driveWS2812(WS2812_PIN, LED_COUNT, 0, 0, 255);
    delay(1000);
    
    // 清空
    clearWS2812(WS2812_PIN, LED_COUNT);
}

void loop() {
    // 彩虹效果循环
    rainbowWS2812(WS2812_PIN, LED_COUNT, 5000);
}
```

### 高级效果
```cpp
WS2812Driver leds(GPIO_NUM_18, 16);

void setup() {
    leds.begin();
    
    // 流水灯效果
    for(int i = 0; i < 16; i++) {
        leds.clear();
        leds.setPixel(i, 0, 0, 255);  // 蓝色
        leds.show();
        delay(100);
    }
    
    // 呼吸灯效果
    for(int brightness = 0; brightness <= 255; brightness += 5) {
        leds.fill(brightness, 0, 0);  // 红色呼吸
        leds.show();
        delay(10);
    }
}

void loop() {
    leds.rainbow(20);  // 彩虹效果
}
```

## 故障排除

### 常见问题

1. **LED不亮**
   - 检查5V电源连接
   - 检查接地是否共地
   - 检查信号线是否连接到正确的GPIO

2. **颜色错误**
   - WS2812使用GRB顺序，不是RGB
   - 确保代码中使用正确的颜色顺序

3. **部分LED不工作**
   - 检查电源是否足够
   - 检查LED之间的连接是否牢固

4. **编译错误**
   - 确保包含正确的头文件路径
   - 检查是否安装了必要的ESP32库

### 调试信息
库会在串口输出调试信息（波特率115200）：
- "WS2812驱动初始化成功"
- "RMT配置失败"
- "RMT驱动安装失败"
- "RMT写入失败"

## 许可证

MIT License - 可自由使用、修改和分发。

## 版本历史

- v1.0.0 (2026-02-22): 初始版本
  - 基于ESP32 RMT硬件驱动
  - 提供C和C++接口
  - 支持多种灯光效果
  - 完整的错误处理

## 贡献

欢迎提交Issue和Pull Request改进此库。