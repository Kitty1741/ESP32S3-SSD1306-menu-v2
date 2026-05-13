#include <Arduino.h>
#include <config.h>
#include <0_base/base.h>

#include "keyboard.h"

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
keyEvent scanKeyboard(){
    __DEBUG_1("scanKeyboard()\n")
    keyEvent result = 0;
    
    // 单独操作离散IO
    if(digitalRead(GPIO_KEY_F1   ) == LOW) result |= KEY_EVENT_F1;
    if(digitalRead(GPIO_KEY_F2   ) == LOW) result |= KEY_EVENT_F2;
    if(digitalRead(GPIO_KEY_UP   ) == LOW) result |= KEY_EVENT_UP;
    if(digitalRead(GPIO_KEY_DOWN ) == LOW) result |= KEY_EVENT_DOWN;
    if(digitalRead(GPIO_KEY_LEFT ) == LOW) result |= KEY_EVENT_LEFT;
    if(digitalRead(GPIO_KEY_RIGHT) == LOW) result |= KEY_EVENT_RIGHT;
    if(digitalRead(GPIO_KEY_A    ) == LOW) result |= KEY_EVENT_A;
    if(digitalRead(GPIO_KEY_B    ) == LOW) result |= KEY_EVENT_B;
    if(digitalRead(GPIO_KEY_X    ) == LOW) result |= KEY_EVENT_X;
    if(digitalRead(GPIO_KEY_Y    ) == LOW) result |= KEY_EVENT_Y;

    return result;
}

//扫描函数，返回当前按键值
keyEvent scanKeyValue(){
    __DEBUG_1("scanKeyValue()\n")
    keyEvent result = scanKeyboard();
    return result;
}

