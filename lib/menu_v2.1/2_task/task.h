#ifndef _2_TASK_H__
#define _2_TASK_H__

#include "2_task/keyboard/keyboard.h"
#include "2_task/menuDisplay/menuDisplay.h"

//该层初始化内容清单(init宏使用)
// 参数为根部菜单，用于初始化，类型为const menu&
#define INIT_LIST_2(mainMenu) \
    initKeyboardTask();         \
    initMenuDisplayTask(mainMenu);\

#endif