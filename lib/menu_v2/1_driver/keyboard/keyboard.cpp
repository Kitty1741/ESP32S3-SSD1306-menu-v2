// keyboard.cpp
#include <Arduino.h>

#include "../../0_config/config.h"

#include "keyboard_types.h"
#include "keyboard.h"
#include "keyboard_scan.h"

// 这个文件用于实现对外类函数和按键扫描逻辑

Keyboard keyboard; // 定义一个全局键盘对象


TaskHandle_t keyboardScanTaskHandle;  //任务句柄



//更新按键函数，定时扫描更新
//软件定时器版本
void refreshKey(void* no_param){
    while(1){
        __DEBUG_1("refreshKey()\n")

        //扫描获取按键
        keyboard.key = scanKeyValue();

        //更新按下时间
        if( keyboard.key ){ //如果有按键被按下
            keyboard.pressTime += keyboard.scanInterval;
        }else keyboard.pressTime = 0;

        vTaskDelay(keyboard.scanInterval / portTICK_PERIOD_MS); //延时
    }
}


void initKeyboardTimer(){  // 初始化键盘，启动定时器
    __DEBUG_1("initKeyboardTimer()\n")
    
    //使用软件定时器
    xTaskCreate(
        refreshKey,       // 任务函数指针
        "KeyboardScanTask", // 任务名称（调试用）
        4096,               // 任务栈大小（字节）
        NULL,           // 传递给任务的参数
        5,                   // 任务优先级
        &keyboardScanTaskHandle    // 任务句柄 (用于引用此任务)（TaskHandle_t值的地址）
    );
} 



//获取按键函数
KEY Keyboard::getKey(){
    __DEBUG_1("Keyboard::getKey()\n")
    return this -> key; //返回当前按键
}



//获取按键按下时间，单位 毫秒
uint32_t Keyboard::getPressTime(){
    __DEBUG_1("Keyboard::getPressTime()\n")
    return pressTime; 
}