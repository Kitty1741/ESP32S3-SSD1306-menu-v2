// keyboard.cpp
#include <Arduino.h>

#include "../../0_config/config.h"
#include "../../1_driver/driver.h"

#include "keyboard_config.h"
#include "keyboard_timer.h"
#include "keyboard_types.h"
#include "keyboard.h"

// 这个文件用于实现按键定时器扫描逻辑和freertos信号发送

static StackType_t keyboardTaskStack[4096]; // 定义任务栈
static StaticTask_t keyboardTaskBuffer; // 定义任务控制块

QueueHandle_t keyboardEventQueue; // 定义一个队列句柄，用于发送按键事件
uint8_t keyboardEventQueueStorage[16 * sizeof(KeyEventMask)]; // 定义队列缓冲区
StaticQueue_t keyboardEventQueueBuffer; // 定义一个静态队列控制块



void initKeyboardEventQueue(){ // 初始化按键事件队列
    __DEBUG_1("initKeyboardEventQueue()\n")
    keyboardEventQueue = xQueueCreateStatic(
        16,                 // 队列长度
        sizeof(KeyEventMask), // 每个元素大小
        keyboardEventQueueStorage, // 队列缓冲区
        &keyboardEventQueueBuffer  // 队列控制块
    ); 
}



//更新按键事件函数(freertos任务)
void refreshKey(void* no_param){
    while(1){
        __DEBUG_1("refreshKey()\n")

        KeyEventMask lastKey = Keyboard.key & ~KEY_EVENT_UNPRESS;     // 上次是否有按键按下
        Keyboard.key = scanKeyValue();            //扫描获取按键

        // 检测长按和超长按
        if( Keyboard.key != KEY_NONE ){
            Keyboard.pressTime += KEYBOARD_SCAN_INTERVAL;   //按键按下时间增加
            if (Keyboard.pressTime <= KEYBOARD_LONG_PRESS_THRESHOLD) {
                Keyboard.key |= KEY_EVENT_SHORT_PRESS;
            } else if (Keyboard.pressTime <= KEYBOARD_LONG_LONG_PRESS_THRESHOLD) {
                Keyboard.key |= KEY_EVENT_LONG_PRESS;
            } else { 
                Keyboard.key |= KEY_EVENT_LONG_LONG_PRESS;
            }
        }else{
            Keyboard.pressTime = 0;
            if( lastKey ){ //如果上次有按键按下但这次没有，说明发生了释放事件，此时发送事件到队列
                Keyboard.key |= KEY_EVENT_UNPRESS;
                KeyEventMask event = Keyboard.key | lastKey;// 防止释放时不发送按键/长按信息
                xQueueSend(keyboardEventQueue, &event, 0); //发送事件到队列，缓冲区满直接丢
            }
        }

        vTaskDelay(KEYBOARD_SCAN_INTERVAL / portTICK_PERIOD_MS); //延时
    }
}

void initKeyboardTimer(){  // 初始化键盘，启动定时器
    __DEBUG_1("initKeyboardTimer()\n")
    
    //使用软件定时器
    xTaskCreateStatic(
        refreshKey,       // 任务函数指针
        "KeyboardScanTask", // 任务名称（调试用）
        4096,               // 任务栈大小（字节）
        NULL,           // 传递给任务的参数
        5,                   // 任务优先级
        keyboardTaskStack,   // 任务栈数组
        &keyboardTaskBuffer  // 任务控制块
    );
}

