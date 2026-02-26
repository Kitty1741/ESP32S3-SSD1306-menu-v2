键盘数据流如下

键盘驱动 -> 定时调用读取键值 -> 内部存储 -> 对外函数读取
              L如果读到"释放"标志 -> 发送到队列

所以键盘有两种用法
第一种就是典中典的轮询，没啥好说的
第二种是简单用法：等待直到收到队列信息，然后执行对应操作，阻塞线程但是逻辑简单


API
```cpp
//不用创建对象，直接调用的API如下
Keyboard.waitQueueEvent(); // 等待直到按键释放，然后返回键值
Keyboard.getKey(); //仅得到按键掩码  
Keyboard.getKeyEvent(); // 得到按键掩码和事件掩码
Keyboard.ifKeyEvent(KeyEvent event); // 返回bool，确认现在某按键是否按下
Keyboard.getPressTime();   // 获取按键按下时间，单位 毫秒



// 注：按键掩码定义如下，可以通过按位与转换为按键枚举
// 例：if(getKey() & KEY_EVENT_UP){ Serial.println("有人按了上键") }
// 等效于 if(ifKeyEvent(KEY_EVENT_UP)){...}
// 按键枚举
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

    KEY_EVENT_LONG_PRESS  = 1 << 10, // 长按事件
    KEY_EVENT_LONG_LONG_PRESS = 1 << 11, // 超级长按事件
    KEY_EVENT_SHORT_PRESS = 1 << 12, // 短按事件
    KEY_EVENT_DOUBLE_PRESS = 1 << 13, // 双击事件 // 还没做
    KEY_EVENT_TRIPLE_PRESS = 1 << 14, // 三连击事件  // 还没做
    KEY_EVENT_UNPRESS = 1 << 15 // 释放事件
} KeyEvent;
typedef uint16_t KeyEventMask; // 按键事件掩码

//键盘类定义
class KeyboardClass{
    private:
        KeyEventMask key = KEY_NONE;          // 记录扫描到的按键事件掩码
        uint32_t pressTime = 0;             // 按键按下时间戳，单位 毫秒
        uint64_t lastPressTime = 0;         // 上次按键事件时间戳，单位 毫秒
        KeyboardClass();                    // 私有构造函数，禁止外部实例化

    public:
        friend void test();                             // 测试函数，允许访问私有成员
        friend KeyboardClass& initKeyboardClass();      // 初始化键盘实例
        friend void refreshKey(void* no_param);         // 更新按键函数(定时器调用)
        KeyMask getKey();                               // 得到当前按键
        uint32_t getPressTime();                        // 获取按键按下时间，单位 毫秒

        KeyEventMask getKeyEvent();                     // 获取当前按键事件掩码
        bool ifKeyEvent(KeyEvent event);                // 根据掩码判断是否发生了指定的按键事件

        KeyEventMask waitQueueEvent();                  // 从队列获取按键事件，阻塞
};

extern KeyboardClass Keyboard;
```

当双击/长按/按键松开时，按键扫描函数会发送当时数据到freeRTOS队列
可以通过这个句柄调用队列
```cpp
QueueHandle_t keyboardEventQueue; // 事件队列句柄，按键释放/长按/双击(还没做)等事件会发送到这个队列
```
