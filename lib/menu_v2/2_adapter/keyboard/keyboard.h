#ifndef __KEYBOARD_H__2
#define __KEYBOARD_H__2

#include <Math.h>
#include "../../1_driver/driver.h"
#include "keyboard_types.h"


// 这个文件用于包装对外函数和键盘类定义

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

extern KeyboardClass& Keyboard; // 声明一个唯一的全局键盘对象

#endif // __KEYBOARD_H__2