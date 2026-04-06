#ifndef __CORE_H__2
#define __CORE_H__2

void initU8g2Setting(); // 初始化
void resetU8g2Setting();// 重置显示设置
void printNameBar(String name); // 打印菜单名字条
void printMenuItems(menu* menu);// 打印菜单选项

// u8g2对象
#include "core_config.h"
extern _U8G2_CREATE u8g2;

#endif