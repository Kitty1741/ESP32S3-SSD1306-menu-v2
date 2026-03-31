#include <Arduino.h>
#include <menuv2.h>
#include <ws2812.h>

//test
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1315_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE ,/*SCL*/9,/*SDA*/8);

void setup(){
    Serial.begin(115200);
    __DEBUG_A("Setup()\n")

    u8g2.begin();
    u8g2.enableUTF8Print();
    u8g2.setFontPosTop();      // 设置字体绘制基准为顶部（默认为基线）
    u8g2.setFont(u8g2_font_wqy12_t_gb2312);

    u8g2.clearBuffer();
    u8g2.drawUTF8(4,14,"Hello World!\n ");
    u8g2.sendBuffer();

    menuInit(); //菜单系统初始化
}

String str1;
KeyEventMask key;
char str[100];
void test(){

    key = Keyboard.waitQueueEvent(2000); //获取按键事件，至少每2000ms刷新一次
    // 输出对应事件名字
    u8g2.clearBuffer();
    sprintf(str, "%lums", get_time_ms());
    u8g2.drawButtonUTF8(12, 40, U8G2_BTN_SHADOW1|U8G2_BTN_BW2, 34,  2,  2, str );
    if( key & KEY_EVENT_LONG_PRESS ) u8g2.drawUTF8(4,2,"长按\n ");
    else if( key & KEY_EVENT_LONG_LONG_PRESS ) u8g2.drawUTF8(4,2,"超级长按\n ");
    else if( key & KEY_EVENT_SHORT_PRESS ) u8g2.drawUTF8(4,2,"短按\n ");
    if( key & KEY_EVENT_UNPRESS )u8g2.drawUTF8(80,2,"松开\n ");

    str1 = "";
    if( key == KEY_NONE )      str1 += "无按键按下";
    if( key & KEY_EVENT_UP )   str1 += "UP  ";
    if( key & KEY_EVENT_DOWN ) str1 += "DOWN  ";
    if( key & KEY_EVENT_LEFT ) str1 += "LEFT  ";
    if( key & KEY_EVENT_RIGHT )str1 += "RIGHT  ";
    if( key & KEY_EVENT_A )    str1 += "A  ";
    if( key & KEY_EVENT_B )    str1 += "B  ";
    if( key & KEY_EVENT_X )    str1 += "X  ";
    if( key & KEY_EVENT_Y )    str1 += "Y  ";
    if( key & KEY_EVENT_F1 )   str1 += "F1  ";
    if( key & KEY_EVENT_F2 )   str1 += "F2  ";
    u8g2.drawUTF8(4,14,str1.c_str());
    u8g2.sendBuffer();
}

void loop(){
    test();
}
