#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "keyboard/keyboard.h"
#include "keyboard/keyboard_types.h"

//初始化函数
void initKeyboard();

//该层初始化函数清单
#define INIT_LIST_1 \
    initKeyboard(); \

#endif // __DRIVER_H__