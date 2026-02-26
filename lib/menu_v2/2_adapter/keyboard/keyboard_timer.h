#ifndef __KEYBOARD_TIMER_H__
#define __KEYBOARD_TIMER_H__

#include <freertos/queue.h>

extern QueueHandle_t keyboardEventQueue; // 事件队列句柄，按键释放/长按/双击(还没做)等事件会发送到这个队列

#endif // __KEYBOARD_TIMER_H__