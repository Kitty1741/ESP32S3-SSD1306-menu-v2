#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <../lib/menu_v2/menuv2.h>

inline void getTimeTest(){
    struct tm timeinfo;
    char str_1[50],str_2[50],str_3[50];
    WiFi.begin("SSID");
    configTime(8 * 3600/*bias*/, 0, "pool.ntp.org"); // 时区：UTC+8
    while(1){
        
        // 得到时间&字符串
        if (getLocalTime(&timeinfo)) {
            strftime(str_1,sizeof(str_1),"%Y年%m月%d日",&timeinfo);
            strftime(str_2,sizeof(str_2),"%H:%M:%S",&timeinfo);
            //strcpy(str_3,"null");
        }else{
            str_1[0]='\0';
            strcpy(str_2,"时间获取失败");
            str_3[0]='\0';
        }

        // 显示时间
        u8g2.clearBuffer();
        u8g2.drawUTF8(4,2,str_1);
        u8g2.drawUTF8X2(20,20,str_2);
        //u8g2.drawUTF8(4,50,str_3);
        u8g2.sendBuffer();

        // 按键检测
        if(Keyboard.waitQueueEvent(3000)&(KEY_EVENT_B|KEY_EVENT_LEFT))return;
    }
}