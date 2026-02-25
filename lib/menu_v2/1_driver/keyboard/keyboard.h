#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <Math.h>
#include "keyboard_types.h"


// 这个文件用于包装对外函数和键盘类定义

//键盘类定义
class Keyboard{
    private:
        KEY key = KEY_NONE;                 // 记录扫描到的按键
        uint32_t pressTime = 0;             // 按键按下时间戳，单位 毫秒
        const uint8_t scanInterval = 20;    // 扫描间隔，单位 毫秒

    public:
        friend void refreshKey(void* no_param);        // 更新按键函数(定时器调用)
        KEY getKey();            // 得到当前按键
        uint32_t getPressTime(); // 获取按键按下时间，单位 毫秒
};

extern Keyboard keyboard; // 声明一个全局键盘对象

//初始化函数
void initKeyboardTimer();
void initKeyboard();

#endif // __KEYBOARD_H__