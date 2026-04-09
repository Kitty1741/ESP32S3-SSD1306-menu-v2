#ifndef _1_DISPLAY_H__
#define _1_DISPLAY_H__

#include <string>
#include <U8g2lib.h>
#include "config.h"
#include "0_base/base.h"
#include "1_modules/menu/menu.h"

void initU8g2Setting(); // 初始化
void resetU8g2Setting();// 重置显示设置
void printNameBar(const std::string& name); // 打印菜单名字条
void printMenuItems(const menu& menu);// 打印菜单选项
void printMenu(menu* menu); // 打印一整个菜单

extern _U8G2_CREATE u8g2;

#endif