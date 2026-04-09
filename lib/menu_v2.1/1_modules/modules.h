#ifndef _1_MODULES_H__
#define _1_MODULES_H__

#include "./keyboard/keyboard.h"
#include "./menu/menu.h"
#include "./display/display.h"

//该层初始化内容清单(init宏使用)
#define INIT_LIST_1 \
    initU8g2Setting();\
    initKeyboard();\

#endif