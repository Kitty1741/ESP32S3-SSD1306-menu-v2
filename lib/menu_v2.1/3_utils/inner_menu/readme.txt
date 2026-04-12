这个文件夹是作者写的内置菜单，包含了一些小功能
可以当示例代码看，也可以直接拿去用
这个菜单的变量名是innerMenu，要想使用，直接在你的菜单项中使用宏包含即可，
像这样，不用extern
menu Menu(
    "name",{
        {"innerMenu",enterMenu(innerMenu)},
    }
)