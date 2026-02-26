#ifndef __KEYBOARD_TYPES_H__2
#define __KEYBOARD_TYPES_H__2

#include <math.h>

// 这个文件用于定义键盘事件类型的枚举和掩码

typedef enum {              // 定义按键事件枚举，每个事件对应一位掩码，发生时该位为1，否则为0
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

    KEY_EVENT_LONG_PRESS  = 1 << 10,      // 长按事件
    KEY_EVENT_LONG_LONG_PRESS = 1 << 11, // 超级长按事件
    KEY_EVENT_SHORT_PRESS = 1 << 12,    // 短按事件
    KEY_EVENT_UNPRESS = 1 << 13,       // 释放事件
    KEY_EVENT_DOUBLE_PRESS = 1 << 14, // 双击事件 // 还没做
    
} KeyEvent;
typedef uint16_t KeyEventMask; // 按键事件掩码

#endif // __KEYBOARD_TYPES_H__2