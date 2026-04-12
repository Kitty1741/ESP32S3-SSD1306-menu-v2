#ifndef _2_KEYBOARD_H__
#define _2_KEYBOARD_H__

#include <Math.h>
#include "0_base/base.h"
#include "1_modules/modules.h"

// 这个文件用于包装对外函数和键盘类定义

//键盘类定义
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

void initKeyboardTask();

extern QueueHandle_t keyboardEventQueue; // 特殊事件队列
extern KeyboardClass& Keyboard; // 声明一个唯一的全局键盘对象
extern KeyboardClass& kb;       // 认准官方缩写

#endif