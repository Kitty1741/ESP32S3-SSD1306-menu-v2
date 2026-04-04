#include <Arduino.h>

#include <0_config/config.h>
#include <2_adapter/adapter.h>
#include <3_core/0_base/base.h>

#include "behaviors_config.h"
#include "behaviors.h"

TaskHandle_t menuLoopTaskHandle = NULL; // 菜单任务句柄
menu_t* currentMenu = nullptr;          // 当前菜单指针，给显示任务看的

// 菜单初始化函数
// 注意：这个函数需要手动调用
void initMenuSys(void* mainMenu){
    xTaskCreate(
        menuLoop,           // 任务函数指针
        "menuLoop",         // 任务名称（调试用）
        8192,               // 任务栈大小（字节）
        mainMenu,           // 传递给任务的参数
        1,                  // 任务优先级（1-24，与loop任务相同）
        &menuLoopTaskHandle // 任务句柄 (用于引用此任务)（TaskHandle_t值的地址）
    );
}

// 菜单任务循环，进入菜单调用这个函数，初始化菜单后作为freeRTOS任务启动
void menuLoop(void* currentMenu){
    currentMenu  = (menu_t*)currentMenu;    // 更新当前菜单状态
    menu_t* menu = (menu_t*)currentMenu;    // 指针类型转换
    KeyEventMask key = 0;                   // 缓存按键事件用
    uint32_t& cursor = menu->cursor;        // 菜单光标引用
    while(1){
        if( !xQueueReceive( keyboardEventQueue , &key , 200 ) ){ // 捕捉按键事件
            continue;    // 没捕捉到的处理
        } 
        if( key & KEY_EVENT_UP )   cursor = 0 ? cursor = menu->size() -1 : cursor--;    // 光标上移
        if( key & KEY_EVENT_DOWN ) cursor = menu->size() -1 ? cursor = 0 : cursor++;    // 光标下移
        if( key & KEY_EVENT_LEFT ) break;                                               // 左键返回
        if( key & KEY_EVENT_RIGHT ){menu->runItem();currentMenu = nullptr;}             // 执行选项并清除菜单指针
        if( key & KEY_EVENT_A )    {menu->runItem();currentMenu = nullptr;}             // 执行选项并清除菜单指针
        if( key & KEY_EVENT_B )    break;                                               // 返回
        //if( key & KEY_EVENT_X )    {  } // 这几个不用
        //if( key & KEY_EVENT_Y )    {  } // 这几个不用
        //if( key & KEY_EVENT_F1 )   {  } // 这几个不用
        //if( key & KEY_EVENT_F2 )   {  } // 这几个不用
    }
}