这个文件夹提供了一些杂七杂八的宏
这些宏都是给用户用的
这里整合一下放在这
2026/4/12

```cpp
// menu_macro.h

/*  newMenu(menu)
    新建菜单并进入，该宏可作为选项的行为函数写在选项中
    该宏新建菜单的语法和menu的构造函数一样
    下面有示例
*/
#define newMenu(menu)
// 示例
// ↓这是个选项
    {"newMenu\"A\"",
        newMenu(// 执行时新建下面的菜单并进入
            "A",{
                {"option1",func},
            }
        )
    }

/*  newMenu(menu)
    进入已有菜单，该宏可作为选项的行为函数写在选项中
    下面有示例
*/
#define enterMenu(menu)
// 示例
menu SubMenu(...); // 已有菜单
// ↓这是个选项
    {"enterSubMenu",
        enterMenu(SubMenu) // 进入已有的SubMenu菜单
    }
```