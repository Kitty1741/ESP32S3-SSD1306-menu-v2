#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#include "config.h"
#include "0_base/base.h"
#include "1_modules/modules.h"
#include "2_task/keyboard/keyboard.h"

#include "menuDisplay.h"

extern QueueHandle_t keyboardEventQueue; // 键盘事件队列
TaskHandle_t menuDisplayTaskHandle = NULL; // 菜单显示任务句柄
const menu* mainMenuPtr;            // 根部菜单，用来检测是否在根部退出，防止rtos任务意外结束

// 初始化菜单显示任务
void initMenuDisplayTask(const menu& mainMenu){
    __DEBUG_2("initMenuDisplayTask()\n")
    mainMenuPtr = &mainMenu;

    // 确保任务优先级比loop高，这样显示不会轻易撞车
    uint8_t priority;
    TaskHandle_t loopTaskHandle = xTaskGetHandle("loopTask");
    if(loopTaskHandle != NULL){
        priority = uxTaskPriorityGet( loopTaskHandle ) +1; 
    } else priority=1;     // 依旧防空

    xTaskCreate(
        menuDisplayTask,
        "menuDisplayTask",
        8192,
        (void*)&mainMenu,
        priority,
        &menuDisplayTaskHandle
    );
}

// 菜单计算&显示任务
void menuDisplayTask(void* menuPtr){
    __DEBUG_2("menuDisplayTask()\n")
    menu& Menu = *(menu*)menuPtr;
    KeyEvent key = 0;                       // 缓存按键事件用
    uint32_t& cursor = Menu.cursor;         // 菜单光标引用

    while(1){
        // 按键响应
        if( xQueueReceive( keyboardEventQueue , &key , rtos_ms(0) ) ){ // 捕捉按键队列
            if( key & KEY_EVENT_UP )   Menu.up();                   // 光标上移
            if( key & KEY_EVENT_DOWN ) Menu.down();                 // 光标下移
            if( key & (KEY_EVENT_LEFT | KEY_EVENT_B) ){                 // 返回
                if(&Menu != mainMenuPtr)break; // 检测是否退无可退，防止任务意外结束
            } 
            if( key & (KEY_EVENT_RIGHT| KEY_EVENT_A) ){                 // 执行run()
                Menu.runItem();
            }
        }

        // 菜单打印
        printMenu(&Menu);
    }
}