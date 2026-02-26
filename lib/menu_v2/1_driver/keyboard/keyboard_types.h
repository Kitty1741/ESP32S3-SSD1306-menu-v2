#ifndef __KEYBOARD_TYPES_H__
#define __KEYBOARD_TYPES_H__

//该文件用于定义键盘输出的结构体

#include <math.h>

//键盘输出的枚举，每个按键对应一个位，按下时该位为1，否则为0
typedef enum{
    KEY_NONE = 0,
    KEY_UP   = 1 << 0,
    KEY_DOWN = 1 << 1,
    KEY_LEFT = 1 << 2,
    KEY_RIGHT= 1 << 3,
    KEY_A    = 1 << 4,
    KEY_B    = 1 << 5,
    KEY_X    = 1 << 6,
    KEY_Y    = 1 << 7,
    KEY_F1   = 1 << 8,
    KEY_F2   = 1 << 9,
} KeyValue;
typedef uint16_t KeyMask; // 定义一个新的类型 KEY_MASK，表示按键掩码

#endif // __KEYBOARD_TYPES_H__