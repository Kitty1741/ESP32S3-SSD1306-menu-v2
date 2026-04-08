#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <../lib/menu_v2/menuv2.h>

inline void getTimeTest(){
    __DEBUG_A("getTimeTest()\n")
    vTaskDelay(100);
    struct tm timeinfo;
    char str_1[50],str_2[50],str_3[50];
    KeyEventMask key = 0;
    WiFi.begin("SSID");
    configTime(8 * 3600/*bias*/, 0, "pool.ntp.org"); // 时区：UTC+8
    while(1){
        
        // 得到时间&字符串
        if (getLocalTime(&timeinfo)) { 
            strftime(str_1,sizeof(str_1),"%Y年%m月%d日",&timeinfo);
            strftime(str_2,sizeof(str_2),"%H:%M:%S",&timeinfo);
            sprintf (str_3,"Sys_t=%d",get_time_ms());
        }else{
            strcpy(str_1,"时间获取失败");
            str_2[0]='\0';
            str_3[0]='\0';
        }

        // 显示时间
        u8g2.clearBuffer();
        u8g2.drawUTF8(4,2,str_1);
        u8g2.drawUTF8X2(20,20,str_2);
        u8g2.drawUTF8(36,50,str_3);
        u8g2.sendBuffer();

        // 按键检测
        key=Keyboard.waitQueueEvent(200);
        if(key&(KEY_EVENT_B|KEY_EVENT_LEFT))return;
    }
}