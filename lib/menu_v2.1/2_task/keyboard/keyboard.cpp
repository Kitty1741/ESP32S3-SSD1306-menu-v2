#include <Arduino.h>

#include "0_base/base.h"
#include "1_modules/modules.h"

#include "keyboard.h"

// rtos
static StackType_t keyboardTaskStack[4096]; // 定义任务栈
static StaticTask_t keyboardTaskBuffer; // 定义任务控制块

uint8_t keyboardEventQueueStorage[1 * sizeof(KeyEvent)]; // 定义队列缓冲区
StaticQueue_t keyboardEventQueueBuffer; // 定义一个静态队列控制块

// 定义一个队列句柄，用于发送按键事件
QueueHandle_t keyboardEventQueue = NULL;



//更新按键事件函数(freertos任务)
void refreshKey(void* no_param){
    while(1){
        __DEBUG_2("refreshKey()\n")

        KeyEvent lastKey = Keyboard.key & ~KEY_EVENT_UNPRESS;     // 上次是否有按键按下

        // 检测按键事件
        Keyboard.key = scanKeyValue();                      // 扫描获取按键
        if( Keyboard.key != KEY_EVENT_NONE ){
            Keyboard.pressTime += KEYBOARD_SCAN_INTERVAL;   //按键按下时间增加
            if (Keyboard.pressTime <= KEYBOARD_LONG_PRESS_THRESHOLD) {
                Keyboard.key |= KEY_EVENT_SHORT_PRESS;
            } else if (Keyboard.pressTime <= KEYBOARD_LONG_LONG_PRESS_THRESHOLD) {
                Keyboard.key |= KEY_EVENT_LONG_PRESS;
            } else { 
                Keyboard.key |= KEY_EVENT_LONG_PRESS;
                Keyboard.key |= KEY_EVENT_LONG_LONG_PRESS;
            }
            if( !lastKey ){              // 如果上次没按按键而这次按了，则是首次按下
                Keyboard.key |= KEY_EVENT_FIRSTPRESS;
            }
        }else{
            Keyboard.pressTime = 0;
            if( lastKey ){ //如果上次有按键按下但这次没有，说明发生了释放事件，此时发送事件到队列
                Keyboard.key |= KEY_EVENT_UNPRESS;
            }
        }

        if( Keyboard.key & ~0x03ff ){   // 特殊标志位但凡有动静就发
            xQueueSend(keyboardEventQueue, &Keyboard.key, portMAX_DELAY);
        }

        vTaskDelay(pdMS_TO_TICKS(KEYBOARD_SCAN_INTERVAL)); //延时
    }
}

void initKeyboardTask(){  // 初始化键盘循环检测任务
    __DEBUG_2("initKeyboardTask()\n")
    // 初始化按键队列
    keyboardEventQueue = xQueueCreateStatic(
        1,                 // 队列长度
        sizeof(KeyEvent), // 每个元素大小
        keyboardEventQueueStorage, // 队列缓冲区
        &keyboardEventQueueBuffer  // 队列控制块
    ); 
    // 初始化任务
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






















// class


// 工厂函数创建单个实例，不对外开放
KeyboardClass& initKeyboardClass(){
    static KeyboardClass Keyboard;
    return Keyboard;
}
KeyboardClass &Keyboard = initKeyboardClass(); // 定义一个全局键盘对象

KeyboardClass::KeyboardClass(){} // 私有构造函数，禁止外部实例化

//获取按键按下时间，单位 毫秒
uint32_t KeyboardClass::getPressTime(){
    __DEBUG_1("Keyboard::getPressTime()\n")
    return pressTime; 
}

//返回当前按键事件掩码
KeyEvent KeyboardClass::getKey(){
    __DEBUG_1("Keyboard::getKeyEvent()\n")
    return this -> key; 
}

//判断按键事件是否发生
bool KeyboardClass::ifKeyEvent(KeyEvent event){
    __DEBUG_1("Keyboard::ifKeyEvent()\n")
    return this->key & event == event;
}

// 从队列获取按键事件，阻塞
KeyEvent KeyboardClass::waitEvent( uint32_t delay ){
    KeyEvent event;
    xQueueReceive(keyboardEventQueue,&event,delay);
    return event;
}
