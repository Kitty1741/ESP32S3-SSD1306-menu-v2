## 这个文件夹提供菜单相关的类和函数

##### 包含：
 - 菜单/菜单项的类定义
 - 菜单的按键检测逻辑
 - 菜单的freeRTOS任务

##### 依赖关系
 - 依赖 0_config
 - 依赖 2_adapter
 - 被 4_display 依赖
 - 被 5_APIs 依赖
 - 对用户公开

##### 全局变量
```cpp
menu_t* currentMenu = nullptr;          // 当前菜单指针，给显示任务看的
```