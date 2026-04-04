#ifndef __BEHAVIORS_H__
#define __BEHAVIORS_H__

// 菜单对按键的响应
void initMenuSys(void* mainMenu); // 初始化
void menuLoop(void* menu); // 菜单循环

// 对下一层声明的变量
extern menu_t* currentMenu;          // 当前菜单指针，给显示任务看的

#endif