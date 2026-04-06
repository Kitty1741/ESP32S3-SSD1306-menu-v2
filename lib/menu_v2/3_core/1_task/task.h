#ifndef __BEHAVIORS_H__
#define __BEHAVIORS_H__

#include "../0_base/base.h"

// 菜单对按键的响应
void initMenuCore(void* mainMenu); // 初始化
void menuLoop(void* menuToRun); // 菜单循环
void menuLoop(menu menuToRun);  // 重载，用于在lambda表达式中用无名对象创建菜单并执行
// 对下一层声明的变量
extern menu* currentMenu;          // 当前菜单指针，给显示任务看的

#endif