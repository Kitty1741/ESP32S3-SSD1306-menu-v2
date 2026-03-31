#ifndef __BASE_H__
#define __BASE_H__

#include <Arduino.h>
#include <vector>

/**
 * @brief 菜单项类
 * 
 * @note 绑定行为函数要通过宏 bindFuncToMenuItem 
 */
class menuItem_t{
private:
    std::function<int32_t()> bind;          // 运行时调用函数
    String name;                            // 选项名称

public:
    menuItem_t(String name="Noname");       // 构造函数
    ~menuItem_t();                          // 析构函数

    inline String getName() const;          // 读名字
    void changeName(String name);           // 改名
    int32_t run();                          // 执行操作，返回返回值

    friend class menu_t;                    // 友元类--菜单类
};


/**
 * @brief 将函数调用绑定到菜单项的宏
 * @param ITEM  menuItem_t 对象的指针/引用，填你要绑到的菜单项
 * @param FUNC_CALL 函数调用表达式或代码，填你要绑的函数
 * 
 * @warning 绑定的函数返回值为int32_t，否则会强制转换，不过你不调用返回值一般不会有事
 *          注意变量要塞就塞永久的指针，不要塞局部变量！变量被清除后调用会炸的！
 * 
 * @code
 * menuItem_t item("Add");                             // 创建菜单项
 * bindFuncToMenuItem(&item, add(3, 4));               // 绑定一个函数
 * item.run();      //=7                               // 绑定完后调用run=调用绑定函数（run在选中菜单时自动调用）
 * @endcode
 */
#define bindFuncToMenuItem(ITEM, FUNC_CALL) \
    do { \
        (ITEM)->bind = [ ]() -> int32_t { \
            return (int32_t)(FUNC_CALL); \
        }; \
    } while(0); // 确保执行一次，同时防止空绑定


// 菜单类，用于管理一个菜单目录
class menu_t{
private:
    String name;                        // 菜单名字
    std::vector<menuItem_t> itemTable;  // 选项数组，存的选项对象

public:
    menu_t(String name="Noname");       // 构造函数
    ~menu_t();                          // 析构函数

    inline String getName();                // 读名字
    void changeName(String name);           // 改名
    std::vector<menuItem_t> getItemTable() const; // 读选项数组
    std::vector<String> getNameTable() const;     // 读选项名字数组
    uint32_t cursor = 0;                    // 光标
    int32_t runItem();                      // 执行光标对应选项的行为
    void insertItem(menuItem_t item);       // 插入新选项到指定选项后
    void deleteItem(menuItem_t item);       // 删除选项
};

#endif // __BASE_H__