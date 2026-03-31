#ifndef __BASE_H__
#define __BASE_H__

#include <Arduino.h>


/**
 * @brief 菜单项类
 * 
 * @note 绑定行为函数要通过宏 bindFuncToMenuItem 
 */
class menuItem_t{
private:
    String name;                        // 选项名称
    std::function<int32_t()> bind;      // 运行时调用函数

public:
    menuItem_t(String name="Noname");    // 构造函数
    ~menuItem_t();      // 析构函数

    void setName(String name);     // 设置选项名称
    int32_t run() ;       // 执行操作，返回返回值

    friend class menu_t; // 友元类--菜单类
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


#endif // __BASE_H__