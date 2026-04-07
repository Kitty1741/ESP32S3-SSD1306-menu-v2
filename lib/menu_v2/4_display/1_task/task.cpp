#include <Arduino.h>

#include <./0_config/config.h>
#include <./3_core/core.h>
#include <./4_display/0_core/core.h>

#include "task.h"

TaskHandle_t displayTaskHandle = NULL;
menu currentMenu("",{}); // 要显示的菜单（副本防止空指针）

// 初始化显示任务，执行显示函数
void initDisplayTask(){

    xTaskCreate(
        displayLoop,
        "displayLoop",
        8192,
        NULL,
        1,
        &displayTaskHandle
    );
}

// 显示函数
void displayLoop(void*){
    initU8g2Setting(); // 初始化u8g2
    while(1){          // 反复显示菜单
        if(xQueueReceive(
            menuDisplayQueueHandle,
            &currentMenu,
            portMAX_DELAY
        )){
            u8g2.clearBuffer();
            printMenu(&currentMenu);
            u8g2.sendBuffer();
        }
    }
}