// keyboard_class.cpp
#include <Arduino.h>

#include "../../0_config/config.h"
#include "../../1_driver/driver.h"

#include "keyboard_timer.h"
#include "keyboard.h"

// 这个文件用于实现KeyboardClass类函数，创建唯一实例


// 工厂函数创建单个实例，不对外开放
KeyboardClass& initKeyboardClass(){
    static KeyboardClass Keyboard;
    return Keyboard;
}
KeyboardClass &Keyboard = initKeyboardClass(); // 定义一个全局键盘对象

KeyboardClass::KeyboardClass(){} // 私有构造函数，禁止外部实例化

//获取按键函数
KeyMask KeyboardClass::getKey(){
    __DEBUG_1("Keyboard::getKey()\n")
    return this -> key & 0x3ff; //返回当前按键 低十位
}

//获取按键按下时间，单位 毫秒
uint32_t KeyboardClass::getPressTime(){
    __DEBUG_1("Keyboard::getPressTime()\n")
    return pressTime; 
}

//返回当前按键事件掩码
KeyEventMask KeyboardClass::getKeyEvent(){
    __DEBUG_1("Keyboard::getKeyEvent()\n")
    return this -> key; 
}

//判断按键事件是否发生
bool KeyboardClass::ifKeyEvent(KeyEvent event){
    __DEBUG_1("Keyboard::ifKeyEvent()\n")
    return (this -> key & event) != 0;
}

// 从队列获取按键事件，阻塞
KeyEventMask KeyboardClass::waitQueueEvent(){
    KeyEventMask event;
    xQueueReceive(keyboardEventQueue,&event,portMAX_DELAY);
    return event;
}
