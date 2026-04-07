#ifndef __BASE_MACRO_H__
#define __BASE_MACRO_H__

// 由于创建多级菜单的代码过于丑陋，所以我写了这个
/**
 * @brief 用lambda表达式中创建子菜单并执行的宏函数
 * @param name 字符串，填你想显示在顶部的字
 * @param __VA_ARGS__ std::vector<menuItem>类型数组，填你的选项-函数清单
 * 
*/
#define newMenu(name,...) nM_(name,__VA_ARGS__)
#define nM_(name,...)           \
[](){                           \
    menuLoop({                  \
        name,__VA_ARGS__        \
    });                         \
}                               \

/**
 * @brief 将已有菜单作为子菜单执行的宏函数
 * @param menu 变量名，填子菜单的变量名
*/
#define enterMenu(menu) eM_(menu)
#define eM_(menu)               \
[&](){                          \
    menuLoop(menu);             \
}                               \

#endif