#include <Arduino.h>

#include <0_config/config.h>
#include <2_adapter/adapter.h>
#include <3_core/0_base/base.h>

#include "task.h"

TaskHandle_t menuLoopTaskHandle = NULL; // 菜单任务句柄
QueueHandle_t menuDisplayQueueHandle = NULL;// 显示队列句柄
menu* _mainMenu = nullptr;            // 根部菜单，用来检测是否在根部退出，防止rtos任务意外结束


// 菜单初始化函数
// 注意：这个函数需要手动调用
void initMenuCore(const menu& mainMenu){
    __DEBUG_3("initMenuCore()\n")
    _mainMenu = (menu*)&mainMenu;
    menuDisplayQueueHandle = xQueueCreate( 
        2,
        sizeof(menu)
    );
    xTaskCreate(
        menuLoop,           // 任务函数指针
        "menuLoop",         // 任务名称（调试用）
        8192,               // 任务栈大小（字节）
        (void*)&mainMenu,           // 传递给任务的参数
        1,                  // 任务优先级
        &menuLoopTaskHandle // 任务句柄 (用于引用此任务)（TaskHandle_t值的地址）
    );
}

// 显示包发送函数，后续优化
bool sendDisplayData(menu* Menu){
    return xQueueSend(menuDisplayQueueHandle,Menu,0);
}

// 菜单循环函数,freertos任务
void menuLoop(void* menuToRun){
    __DEBUG_3("menuLoop()\n")
    menu* curMenu = (menu*)menuToRun;// 当前菜单指针，用于发送显示队列,cur->currentd
    KeyEventMask key = 0;                       // 缓存按键事件用
    uint32_t& cursor = curMenu->cursor;         // 菜单光标引用

    while(1){//                 -----------LOOP-----------
        if(!sendDisplayData(curMenu)){  // 显示刷新
            vTaskDelay(rtos_ms(50));    // 队列满的错误处理
            continue;
        }               
        if( xQueueReceive( keyboardEventQueue , &key , rtos_ms(50) ) ){ // 捕捉按键队列
            
            if( key & KEY_EVENT_UP )   curMenu->up();                   // 光标上移
            if( key & KEY_EVENT_DOWN ) curMenu->down();                 // 光标下移
            if( key & (KEY_EVENT_LEFT | KEY_EVENT_B) ){                 // 返回
                if(curMenu != _mainMenu)break; // 检测是否退无可退，防止任务意外结束
            } 
            if( key & (KEY_EVENT_RIGHT| KEY_EVENT_A) ){                 // 执行run()
                curMenu->runItem();
            }
        }
    }
}

// 重载，用于在lambda表达式中用无名对象创建菜单并执行
void menuLoop(menu menuToRun){
    menuLoop(&menuToRun);
}