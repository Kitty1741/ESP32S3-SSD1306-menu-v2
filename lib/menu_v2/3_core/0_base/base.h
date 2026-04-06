#ifndef __BASE_T_H__
#define __BASE_T_H__

#include <Arduino.h>
#include <string>
#include <vector>

/**
 * @brief menuItem类，包含了一个菜单项的名字和行为
 * @param name 在菜单中显示的名字
 * @param func 运行时调用的函数，类型为void()，支持lambda
 * 
 * @code
 * 示例代码:
 * menuItem item("item",displayHi); // 创建一个叫item，按下触发displayHi函数的菜单项
 * @endcode
*/
class menuItem{
public:
    std::string name;            // 显示名字
    std::function<void()> run;   // 行为函数，选中调用这个
    menuItem(const std::string& name, std::function<void()> func = nullptr)
        : name(name), run(func){}
};

/**
 * @brief menu类，管理一个菜单目录
 * @param name 运行时显示的名字
*/
class menu{
public:
    menu(const std::string& name,const std::vector<menuItem>& itemTable)
        :name(name),itemTable(itemTable){};           // 构造函数

    uint32_t cursor = 0;                    // 光标
    std::string name;                      // 菜单名字
    std::vector<menuItem> itemTable;      // 选项数组，存的选项对象
    
    uint32_t size() const;                              // 得到长度
    std::string getItemName(uint32_t index) const;      // 读指定选项名字
    void runItem();                                     // 执行光标对应选项的行为
    void up();                                          // 光标上移
    void down();                                        // 光标下移
    void insertItem(uint32_t index,menuItem item);      // 插入新选项到指定选项后
    void deleteItem(uint32_t index);                    // 删除选项
};

#include "base_macro.h" // 辅助工厂宏

#endif // __BASE_H__