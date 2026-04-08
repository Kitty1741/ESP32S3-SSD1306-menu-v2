#include <Arduino.h>

#include <./0_config/config.h>
#include <./3_core/core.h>
#include <./4_display/0_core/core.h>

#include "task.h"

TaskHandle_t displayTaskHandle = NULL;
menu currentMenu("",{}); // 要显示的菜单（副本防止空指针）

// 初始化显示任务，执行显示函数
// 由于u8g2只能单线程，所以显示任务设计如下
// 有一个队列，队列里面发的是显示相关函数，然后显示任务接受到后调用
// 这样就只有显示任务可以调用图形库
void initDisplayTask(){

    xTaskCreate(
        displayTask,
        "displayTask",
        8192,
        NULL,
        3,
        &displayTaskHandle
    );
}

// 显示函数
void displayTask(void*){
    initU8g2Setting(); // 初始化u8g2
    while(1){          
        if(xQueueReceive( 
            menuDisplayQueueHandle, 
            &currentMenu,
            portMAX_DELAY))// 接收到队列后显示
        {
            printMenu(&currentMenu);
        }
    }
}