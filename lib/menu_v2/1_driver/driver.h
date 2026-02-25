#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "keyboard/keyboard.h"

//该层初始化函数清单
#define INIT_LIST_1 \
    initKeyboard(); \
    initKeyboardTimer();

#endif // __DRIVER_H__