#include <Arduino.h>
#include <menuv2.h>
#include <ws2812.h>

//test
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE ,/*SCL*/9,/*SDA*/8);

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
    if( key == KEY_NONE ) u8g2.drawUTF8(4,14,"无按键按下\n ");//这里往下的纵坐标都是14.
    if( key & KEY_EVENT_UP ) u8g2.drawUTF8(4,14,"UP\n ");
    if( key & KEY_EVENT_DOWN ) u8g2.drawUTF8(4,14,"DOWN\n ");
    if( key & KEY_EVENT_LEFT ) u8g2.drawUTF8(4,14,"LEFT\n ");
    if( key & KEY_EVENT_RIGHT ) u8g2.drawUTF8(4,14,"RIGHT\n ");
    if( key & KEY_EVENT_A ) u8g2.drawUTF8(4,14,"A\n ");
    if( key & KEY_EVENT_B ) u8g2.drawUTF8(4,14,"B\n ");
    if( key & KEY_EVENT_X ) u8g2.drawUTF8(4,14,"X\n ");
    if( key & KEY_EVENT_Y ) u8g2.drawUTF8(4,14,"Y\n ");
    if( key & KEY_EVENT_F1 ) u8g2.drawUTF8(4,14,"F1\n ");
    if( key & KEY_EVENT_F2 ) u8g2.drawUTF8(4,14,"F2\n ");
    u8g2.sendBuffer();
}

void loop(){
    test();
}
