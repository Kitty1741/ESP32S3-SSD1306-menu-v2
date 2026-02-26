#include <Arduino.h>
#include <soc/gpio_reg.h>

#include "../../0_config/config.h"

#include "keyboard_config.h"
#include "keyboard_types.h"
#include "keyboard.h"

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
KeyMask scanKeyboard(){
    __DEBUG_1("scanKeyboard()\n")
    KeyMask result = 0;

    // 批量操作连续IO(直接读寄存器)
    uint32_t HighGPIO = ~REG_READ(GPIO_IN1_REG);  // GPIO 32-63
    result = (HighGPIO >> 3) & 0xFF; // 取 GPIO 35-42
    
    // 单独操作离散IO
    if(digitalRead(GPIO_KEY_F1) == LOW) result |= KEY_F1;
    if(digitalRead(GPIO_KEY_F2) == LOW) result |= KEY_F2;

    return result;
}


#if ENABLE_UART_SCAN == 1

// 串口检测函数 模拟键盘
KeyMask scanUART(){
    __DEBUG_1("scanUART()\n")

    KeyMask result = 0;

    if(Serial.available()){
        switch ( Serial.read() )
        {
        case 'w':case 'W': // W 映射到 KEY_UP
            result |= KEY_UP; break;
        case 's':case 'S': // S 映射到 KEY_DOWN
            result |= KEY_DOWN; break;
        case 'a':case 'A': // A 映射到 KEY_LEFT
            result |= KEY_LEFT; break;
        case 'd':case 'D': // D 映射到 KEY_RIGHT
            result |= KEY_RIGHT; break;

        case 'k':case 'K': // K 映射到 KEY_A
            result |= KEY_A; break;
        case 'l':case 'L': // L 映射到 KEY_B
            result |= KEY_B; break;
        case 'j':case 'J': // J 映射到 KEY_X
            result |= KEY_X; break;
        case 'i':case 'I': // I 映射到 KEY_Y
            result |= KEY_Y; break;

        case '+':          // + 映射到 KEY_F1
            result |= KEY_F1; break;
        case '-':          // - 映射到 KEY_F2
            result |= KEY_F2; break;
        }
    }
    return result;
}
#else 
#define scanUART() 0 //如果不启用串口扫描，定义一个空函数
#endif // ENABLE_UART_SCAN

//扫描函数，返回当前按键值
KeyMask scanKeyValue(){
    __DEBUG_1("scanKeyValue()\n")
    KeyMask result = scanKeyboard() | scanUART();
    return result;
}