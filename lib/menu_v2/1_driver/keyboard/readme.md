 >>>>PLAN<<<<
这里有一个键盘驱动程序。
可以通过API扫描键盘，返回的是掩码


```cpp
//键盘输出的枚举，每个按键对应一个位，按下时该位为1，否则为0
typedef enum{
    KEY_NONE = 0,
    KEY_UP   = 1 << 0,
    KEY_DOWN = 1 << 1,
    KEY_LEFT = 1 << 2,
    KEY_RIGHT= 1 << 3,
    KEY_A    = 1 << 4,
    KEY_B    = 1 << 5,
    KEY_X    = 1 << 6,
    KEY_Y    = 1 << 7,
    KEY_F1   = 1 << 8,
    KEY_F2   = 1 << 9,
} KeyValue;
typedef uint16_t KeyMask; // 定义一个新的类型 KEY_MASK，表示按键掩码

// 键盘扫描函数 
KeyMask scanKeyValue();
```

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