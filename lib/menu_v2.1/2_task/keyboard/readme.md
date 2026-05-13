# 这里定义了读取键盘的函数

### 基本用法
函数 `kb.getkey();` 将会返回一个KeyEvent(uint32_t)类型的`掩码`，通过解析这个掩码可以得到当前按键的按下信息
- 你可以将KeyEvent与 下列的枚举做`与运算(&)`来得到某个按键是否按下
- 需要注意的是：这个函数是 `非阻塞` 的，如果你不想自己写一些复杂的逻辑来防止重复触发，请看[高级用法](#高级用法)
```cpp
// menu_v2.1\1_modules\keyboard\keyboard.h中定义
typedef enum {              
    KEY_EVENT_NONE = 0,
    KEY_EVENT_UP   = 1 << 0,
    KEY_EVENT_DOWN = 1 << 1,
    KEY_EVENT_LEFT = 1 << 2,
    KEY_EVENT_RIGHT= 1 << 3,
    KEY_EVENT_A    = 1 << 4,
    KEY_EVENT_B    = 1 << 5,
    KEY_EVENT_X    = 1 << 6,
    KEY_EVENT_Y    = 1 << 7,
    KEY_EVENT_F1   = 1 << 8,
    KEY_EVENT_F2   = 1 << 9,

    KEY_EVENT_LONG_PRESS  = 1 << 10,       // 长按事件
    KEY_EVENT_LONG_LONG_PRESS = 1 << 11,  // 超级长按事件
    KEY_EVENT_SHORT_PRESS = 1 << 12,     // 短按事件
    KEY_EVENT_RELEASE = 1 << 13,        // 释放事件
    KEY_EVENT_FIRST_PRESS = 1 << 14,    // 首次按下事件，在按键按下的第一帧发送
    KEY_EVENT_DOUBLE_PRESS = 1 << 15, // 双击事件 // 还没做

    KEY_EVENT_BACK  = KEY_EVENT_LEFT  | KEY_EVENT_B,    // 两个按键都能触发该事件
    KEY_EVENT_ENTER = KEY_EVENT_RIGHT | KEY_EVENT_A,
}KeyEventEnum;
typedef uint32_t KeyEvent; // 按键事件掩码
```

函数 `kb.getPressTime()` 将会返回按下时间  (这个应该没啥好说的)

### 高级用法
- 注：这里的内容涉及FreeRTOS/u8g2，看之前你得先会一点这俩
为了用户可以方便的调用键值，可以不用写复杂的长按/上升下降沿触发逻辑，我们创建了这个队列
该队列长度为1，所以每个后来的数据都会替换掉前面的数据，不用担心取到陈年老数据(?)
```cpp
extern QueueHandle_t keyboardEventQueue;
```
我们的键盘轮询任务会自动判断`特殊标志位(1 << 10 及之后的所有位)`对应的事件是否发生，如果发生了，则会把这时的KeyEvent发送到这个队列
###### 也就是说，你可以通过 读取这个队列的信息 + 判断你想要的标志位 来快速判断动作/避免轮询
举个例子
```cpp
// 使用keyboardEventQueue非阻塞判断松手的测试
KeyEvent key = KEY_EVENT_NONE;
while(1){
    key = KEY_EVENT_NONE;
    xQueueReceive(
        keyboardEventQueue, // 这队列不用你自个extern
        &key, 1000           // 等待时可以阻塞，这里1000是为了刷新显示
    );
    if(!(key & KEY_EVENT_RELEASE)){  // 等到后检查是不是自己要的标志位，不是就下个循环再等
        u8g2.clearDisplay();  // 没等到松手就清屏
        continue;
    }
    // 运行到这里只能是松手了
    u8g2.clearBuffer();
    u8g2.drawUTF8X2(12, 4, "松手！");
    u8g2.sendBuffer();
    // 防止无法退出
    if(key & KEY_EVENT_BACK) return;
}
```
这段代码展示了利用这个队列，不用轮询判断松手的方法

20260513更新`waitEventUntil(event, ticks)`函数，可以用于替代上述代码接收队列的部分