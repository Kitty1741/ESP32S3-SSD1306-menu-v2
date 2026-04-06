#include <Arduino.h>

#include <0_config/config.h>
#include <2_adapter/adapter.h>
#include <3_core/0_base/base.h>

#include "task.h"

TaskHandle_t menuLoopTaskHandle = NULL; // 菜单任务句柄
menu* baseMenu    = nullptr;            // 根部菜单，用来检测是否在根部退出，防止rtos任务意外结束

menu* currentMenu = nullptr;            // 当前菜单指针，给显示任务看的

// 菜单初始化函数
// 注意：这个函数需要手动调用
void initMenuCore(void* mainMenu){
    __DEBUG_3("initMenuCore()\n")
    baseMenu = (menu*)mainMenu;
    currentMenu = baseMenu;
    xTaskCreate(
        menuLoop,           // 任务函数指针
        "menuLoop",         // 任务名称（调试用）
        8192,               // 任务栈大小（字节）
        mainMenu,           // 传递给任务的参数
        1,                  // 任务优先级
        &menuLoopTaskHandle // 任务句柄 (用于引用此任务)（TaskHandle_t值的地址）
    );
}

// 菜单循环函数,freertos任务
void menuLoop(void* menuToRun){
    __DEBUG_3("menuLoop()\n")
    currentMenu = (menu*)menuToRun;
    KeyEventMask key = 0;                   // 缓存按键事件用
    uint32_t& cursor = currentMenu->cursor;        // 菜单光标引用
    while(1){
        if( !xQueueReceive( keyboardEventQueue , &key , portMAX_DELAY ) ){ // 捕捉按键事件
            continue;    // 没捕捉到的处理
        } 
        if( key & KEY_EVENT_UP )   currentMenu->up();                   // 光标上移
        if( key & KEY_EVENT_DOWN ) currentMenu->down();                 // 光标下移
        if( key & (KEY_EVENT_LEFT | KEY_EVENT_B) ){                     // 返回
            if(currentMenu != baseMenu){ // 检测是否退无可退，防止任务意外结束
                break;
            }  
        } 
        if( key & (KEY_EVENT_RIGHT| KEY_EVENT_A) ){                     // 执行run()，执行完后重置当前菜单状态防止进子菜单后状态没改过来
            currentMenu->runItem();
            currentMenu = (menu*)menuToRun;    // 更新当前菜单状态
        }
        //if( key & KEY_EVENT_X )    {  } // 这几个不用
        //if( key & KEY_EVENT_Y )    {  } // 这几个不用
        //if( key & KEY_EVENT_F1 )   {  } // 这几个不用
        //if( key & KEY_EVENT_F2 )   {  } // 这几个不用
    }
}

// 重载，用于在lambda表达式中用无名对象创建菜单并执行
void menuLoop(menu menuToRun){
    menuLoop(&menuToRun);
}