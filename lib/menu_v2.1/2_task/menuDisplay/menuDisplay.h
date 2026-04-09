#ifndef _MENUDISPLAY_H__
#define _MENUDISPLAY_H__

#include "1_modules/modules.h"

void initMenuDisplayTask(const menu& mainMenu); // 初始化显示任务
void menuDisplayTask(void* menuPtr);            // rtos显示任务
void menuLoop(menu Menu);                       // lambda进入新菜单
// 对下一层声明的变量
extern QueueHandle_t menuDisplayQueueHandle;// 显示队列句柄，队列暂时设计发送menu类

#endif