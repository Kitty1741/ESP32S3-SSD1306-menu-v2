#include <Arduino.h>

#include "../../0_config/config.h"

#include "keyboard_config.h"
#include "keyboard_types.h"
#include "keyboard_scan.h"

//这个文件提供键盘扫描函数

//初始化函数
void initKeyboard(){
    __DEBUG_1("initKeyboard()\n")
    
    pinMode(GPIO_KEY_UP, INPUT_PULLUP);
    pinMode(GPIO_KEY_DOWN, INPUT_PULLUP);
    pinMode(GPIO_KEY_LEFT, INPUT_PULLUP);
    pinMode(GPIO_KEY_RIGHT, INPUT_PULLUP);
    pinMode(GPIO_KEY_A, INPUT_PULLUP);
    pinMode(GPIO_KEY_B, INPUT_PULLUP);
    pinMode(GPIO_KEY_X, INPUT_PULLUP);
    pinMode(GPIO_KEY_Y, INPUT_PULLUP);
    pinMode(GPIO_KEY_F1, INPUT_PULLUP);
    pinMode(GPIO_KEY_F2, INPUT_PULLUP);
}

// 键盘扫描函数 
KEY scanKeyboard(){
    __DEBUG_1("scanKeyboard()\n")
    KEY returnValue;
    !digitalRead(GPIO_KEY_UP)     ? returnValue = KEY_UP    :
    !digitalRead(GPIO_KEY_DOWN)   ? returnValue = KEY_DOWN  :
    !digitalRead(GPIO_KEY_LEFT)   ? returnValue = KEY_LEFT  :
    !digitalRead(GPIO_KEY_RIGHT)  ? returnValue = KEY_RIGHT :
    !digitalRead(GPIO_KEY_A)      ? returnValue = KEY_A     :
    !digitalRead(GPIO_KEY_B)      ? returnValue = KEY_B     :
    !digitalRead(GPIO_KEY_X)      ? returnValue = KEY_X     :
    !digitalRead(GPIO_KEY_Y)      ? returnValue = KEY_Y     :
    !digitalRead(GPIO_KEY_F1)     ? returnValue = KEY_F1    :
    !digitalRead(GPIO_KEY_F2)     ? returnValue = KEY_F2    : 
    returnValue = KEY_NONE;
    return returnValue;
}


#if ENABLE_UART_SCAN == 1

// 串口检测函数 模拟键盘
KEY scanUART(){
    __DEBUG_1("scanUART()\n")

    if(Serial.available()){
        char c = Serial.read();
        switch (c)
        {
        case 'w':case 'W': // W 映射到 KEY_UP
            return KEY_UP;
        case 's':case 'S': // S 映射到 KEY_DOWN
            return KEY_DOWN;
        case 'a':case 'A': // A 映射到 KEY_LEFT
            return KEY_LEFT;
        case 'd':case 'D': // D 映射到 KEY_RIGHT
            return KEY_RIGHT;

        case 'k':case 'K': // K 映射到 KEY_A
            return KEY_A;
        case 'l':case 'L': // L 映射到 KEY_B
            return KEY_B;
        case 'j':case 'J': // J 映射到 KEY_X
            return KEY_X;
        case 'i':case 'I': // I 映射到 KEY_Y
            return KEY_Y;

        case '+':          // + 映射到 KEY_F1
            return KEY_F1;
        case '-':          // - 映射到 KEY_F2
            return KEY_F2;
        default:
            return KEY_NONE;
        }
    }
    return KEY_NONE;
}
#else 
#define scanUART() KEY_NONE //如果不启用串口扫描，定义一个空函数
#endif // ENABLE_UART_SCAN

//扫描函数，返回当前按键值
KEY scanKeyValue(){
    __DEBUG_1("scanKeyValue()\n")
    KEY returnValue = max(scanKeyboard(), scanUART());
    return returnValue;
}