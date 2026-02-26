#include <Arduino.h>
#include <menuv2.h>
#include <ws2812.h>

void setup(){
    Serial.begin(115200);
    __DEBUG_A("Setup()\n")

    menuInit(); //菜单系统初始化
}

KeyEventMask key;
void test(){

    if(xQueueReceive(keyboardEventQueue,&key,portMAX_DELAY) == pdTRUE){
        __DEBUG_A("Received keyboard event: ")

        for (int i = 15; i >= 0; i--) { // 天才！
            __DEBUG_A((key & (1 << i)) ? '1' : '0');
        }
        __DEBUG_A("\n")
    }
    __DEBUG_A("Keyboard.getPressTime(): ")
    __DEBUG_A(Keyboard.getPressTime())
    __DEBUG_A("\n")
    // 输出对应事件名字
    if( key & KEY_EVENT_LONG_PRESS ) __DEBUG_A("长按\n ");
    if( key & KEY_EVENT_LONG_LONG_PRESS ) __DEBUG_A("超级长按\n ");
    if( key & KEY_EVENT_SHORT_PRESS ) __DEBUG_A("短按\n ");
    if( key & KEY_EVENT_UNPRESS ) __DEBUG_A("松开\n ");
}

void loop(){
    delay(400);
    test();
}
