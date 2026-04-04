## 这个文件夹提供将输入数据转化为逻辑的函数和类

##### 包含：
 - 独立键盘释放时发送信号
 - 定时检测键盘

##### 依赖关系
 - 依赖 0_config
 - 依赖 1_driver
 - 被 3_core 依赖
 - 被 5_APIs 依赖
 - 对用户公开

##### 全局变量
```cpp
QueueHandle_t keyboardEventQueue; // freeRTOS事件队列句柄，按键释放事件会发送到这个队列
```