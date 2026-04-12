# 这里定义了独立键盘扫描函数和键值的枚举
- 后面代码的按键检测全部基于枚举，用户想用按键库也得用这里的枚举

### 枚举如下
```cpp
// 定义按键事件枚举，每个事件对应一位掩码，发生时该位为1，否则为0
// 这样定义不会像bool那样浪费内存，也可以有助于检测多个按键同时按下的情况
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
    KEY_EVENT_UNPRESS = 1 << 13,        // 释放事件
    KEY_EVENT_FIRSTPRESS = 1 << 14,    // 首次按下事件，在按键按下的第一帧发送
    KEY_EVENT_DOUBLE_PRESS = 1 << 15, // 双击事件 // 还没做

    KEY_EVENT_BACK  = KEY_EVENT_LEFT  | KEY_EVENT_B,    // 两个按键都能触发该事件
    KEY_EVENT_ENTER = KEY_EVENT_RIGHT | KEY_EVENT_A,
    
}KeyEventEnum;
typedef uint32_t KeyEvent; // 按键事件掩码
```