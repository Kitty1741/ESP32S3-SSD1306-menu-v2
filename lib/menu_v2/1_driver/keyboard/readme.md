 >>>>PLAN<<<<
这里有一个键盘驱动程序。
键盘会定时扫描，采集键值
也可以直接从串口发送数字来操作菜单 用于调试
可以用以下API调用键盘
```cpp
Keyboard.getKey();  //读取键盘，得到键值
Keyboard.getPressTime();  // 读取记录的按下时间
```

枚举定义如下
```cpp
enum KEY{
    KEY_NONE,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_A,
    KEY_B,
    KEY_X,
    KEY_Y,
    KEY_F1,
    KEY_F2
}KEY;
```

文件
keyboard_config.h   配置文件
keyboard.cpp        定义对外的函数/类
keyboard.h          声明对外函数/类
keyboard_scan.cpp   键盘扫描函数
keyboard_scan.h     声明键盘扫描函数
keyboard_types.h    声明键盘枚举
readme.md           说明文档

默认键位
按键1	GPIO35	上
按键2	GPIO36	下
按键3	GPIO37	左/取消
按键4	GPIO38	右/进入
按键5	GPIO39	功能键A
按键6	GPIO40	功能键B
按键7	GPIO41	功能键X
按键8	GPIO42	功能键Y
按键9	GPIO1   功能键+/引出备用
按键10	GPIO2	功能键-/引出备用