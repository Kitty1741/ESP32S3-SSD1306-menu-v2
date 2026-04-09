#ifndef _1_KEYBOARD_H__
#define _1_KEYBOARD_H__

//该文件用于定义键盘输出的结构体

#include <math.h>

// 定义按键事件枚举，每个事件对应一位掩码，发生时该位为1，否则为0
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

    KEY_EVENT_LONG_PRESS  = 1 << 10,      // 长按事件
    KEY_EVENT_LONG_LONG_PRESS = 1 << 11, // 超级长按事件
    KEY_EVENT_SHORT_PRESS = 1 << 12,    // 短按事件
    KEY_EVENT_UNPRESS = 1 << 13,       // 释放事件
    KEY_EVENT_DOUBLE_PRESS = 1 << 14, // 双击事件 // 还没做
    
}KeyEventEnum;
typedef uint32_t KeyEvent; // 按键事件掩码


void initKeyboard(); //初始化函数
KeyEvent scanKeyValue(); // 键盘扫描函数 

#endif