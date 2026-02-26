#ifndef __ADAPTER_H__
#define __ADAPTER_H__

#include "keyboard/keyboard.h"
#include "keyboard/keyboard_types.h"

extern QueueHandle_t keyboardEventQueue; // 事件队列句柄，按键释放/长按/双击(还没做)等事件会发送到这个队列

KeyboardClass& initKeyboardClass();     // 初始化键盘类实例
void initKeyboardEventQueue();          // 初始化按键事件队列
void initKeyboardTimer();               // 初始化键盘定时器

//该层初始化函数清单
#define INIT_LIST_2 \
    initKeyboardClass(); \
    initKeyboardTimer(); \
    initKeyboardEventQueue(); \

#endif // __ADAPTER_H__