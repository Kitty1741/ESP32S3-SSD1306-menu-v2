#include <Arduino.h>
#include <U8g2lib.h>

#include <./0_config/config.h>
#include <./2_adapter/adapter.h>
#include <./3_core/core.h>

#include "core.h"
#include "core_config.h"

extern menu_t* currentMenu; // 3_core定义的当前菜单变量

// 打印菜单名字
void printMenuName(String name){
    u8g2_DrawButtonUTF8();
}