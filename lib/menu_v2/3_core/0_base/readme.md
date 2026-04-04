## 这里定义菜单项和菜单类
```cpp
class menuItem_t;   // 菜单项 
class menu_t;       // 菜单目录
```
```cpp
// 菜单项
menuItem_t::menuItem_t(string)// 构造函数，参数为名字
menuItem_t::~menuItem_t()// 析构函数
menuItem_t::getName()// 读名字,返回string
menuItem_t::changeName(string)// 改名
menuItem_t::run() // 执行该menuItem绑定的行为函数
bindRun(MENU_ITEM, FUNC) // 把参数2（表达式）作为参数1（菜单项）的run函数内容，返回值转换为uint32_t类型保存

// 菜单
menu_t::menu_t(String)  // 构造函数，参数为名字
menu_t::~menu_t()       // 析构函数
menu_t::getName()       // 读菜单名字
menu_t::changeName(String)// 改名
menu_t::getItemTable()  // 读所有选项，返回一个装着所有选项的vector容器
menu_t::getNameTable()  //读所有选项名字，返回一个装着所有名字的vector容器
menu_t::runItem()       // 执行光标对应选项的run函数
menu_t::size()          // 返回菜单选项数量
```