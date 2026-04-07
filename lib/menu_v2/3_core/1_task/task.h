#ifndef __CORE_TASK_H__
#define __CORE_TASK_H__

#include "../0_base/base.h"

// 菜单对按键的响应
void initMenuCore(const menu& mainMenu); // 初始化
void menuLoop(void* menuToRun); // 菜单循环
void menuLoop(menu menuToRun);  // 重载，用于在lambda表达式中用无名对象创建菜单并执行

// 对下一层声明的变量
extern QueueHandle_t menuDisplayQueueHandle;// 显示队列句柄，队列暂时设计发送menu类

#endif