### 这里定义菜单的交互函数和freeRTOS任务

```cpp
void initMenuSys(void* mainMenu); // 初始化freeRTOS任务（执行menuLoop(mainMenu)）
void menuLoop(void* menu); // 菜单循环

extern menu* currentMenu;          // 当前菜单指针，给显示任务看的
```