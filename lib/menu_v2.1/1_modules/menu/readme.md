## 这里定义菜单项和菜单类
- 用户只用知道怎么用就行了，这里除了菜单要自己创建外，其他的函数几乎都由菜单内部任务搞定
- 想学可以看
```cpp
class menuItem;   // 菜单项 
class menu;       // 菜单目录
```
```cpp
std::string menu::getItemName(uint32_t index) const;// 读指定选项名字
       void menu::runItem();                        // 执行光标对应选项的行为
   uint32_t menu::size() const;                     // 返回菜单长度        
       void menu::up()                              // 光标上移
       void menu::down()                            // 光标下移         
```