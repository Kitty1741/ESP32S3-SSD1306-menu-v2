## 这里定义菜单项和菜单类
```cpp
class menuItem;   // 菜单项 
class menu;       // 菜单目录
```
```cpp
std::string menu::getItemName(uint32_t index) const;// 读指定选项名字
       void menu::runItem();                        // 执行光标对应选项的行为
   uint32_t menu::size() const;                     // 返回菜单长度                 
```