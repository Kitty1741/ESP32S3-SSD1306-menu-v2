# 这里定义了Keyboard类，按键扫描任务 和 特殊事件队列(长度1)
- 用户如果想复用这里的按键扫描，就需要知道Keyboard类的函数
- Keyboard类只有初始化创建的唯一实例，可通过引用Keyboard和引用kb调用
- 按键任务检测到特殊事件（长按，松手，按下...）会把这次的掩码发到队列里，方便动态调用

```cpp
// 用户可以用的函数（给懒得看||看不懂的人看的）
kb.getKey();                // 返回现在的按键掩码
kb.ifKeyEvent(KeyEvent);    // 参数填键值枚举，返回掩码对应事件是否发生
kb.getPressTime();          // 获取按键按下时间，单位 毫秒
kb.waitEvent();             // 一直等待事件发生直到世界毁灭
kb.waitEvent(ms);           // 一直等待事件发生直到{ms}之后

// 键盘类定义
class KeyboardClass{
    private:
        KeyEvent key = KEY_EVENT_NONE;      // 记录扫描到的按键事件掩码
        uint32_t pressTime = 0;             // 按键按下时间戳，单位 毫秒
        KeyboardClass();                    // 私有构造函数，禁止外部实例化

    public:
        
        uint32_t getPressTime();                        // 获取按键按下时间，单位 毫秒
        KeyEvent getKey();                              // 获取当前按键事件掩码
        KeyEvent waitEvent(uint32_t delay = portMAX_DELAY); // 等待按键队列事件，等到就返回按键
        bool ifKeyEvent(KeyEvent event);                // 判断是否发生了指定的按键事件

        friend KeyboardClass& initKeyboardClass();      // 初始化键盘实例
        friend void refreshKey(void* no_param);         // rtos更新按键函数
};

// 特殊事件队列
extern QueueHandle_t keyboardEventQueue;
```