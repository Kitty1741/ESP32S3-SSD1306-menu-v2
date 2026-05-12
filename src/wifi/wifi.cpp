#include <Arduino.h>
#include <menuv2.h>
#include <wifiManager.h>
#include <WiFi.h>
#include <string.h>

#include "wifi.h"

WiFiManager wf;
menu wifiMenu(
    "WiFi",{
        {"当前网络",wifiStatus},
        {"AP配网",[](){wf.autoConnect("ESP32-S3-user1741");}},
        {"手动连接",setWifiManually},
    }
);

// 时钟
void wifiClock(){

}

// 查看当前网络状况
void wifiStatus(){
    newMenu(
        "测试",{
            {"A"},
        }
    );
}

// 手动连接网络
void setWifiManually(){

    std::vector<menuItem> wifiItems;    // 菜单选项列表，用于存储wifi选项
    int16_t wifiCount = 0;              // wifi数量
    String ssid;                        // 名字
    int32_t rssi;                       // 信号强度
    int32_t encryptionType;             // 加密类型 
    
    // 扫描WiFi网络
    u8g2.clearDisplay();
    u8g2.setFont(_U8G2_CN_FONT_X12);
    u8g2.drawUTF8(10, 20, "正在扫描WiFi...");
    u8g2.sendBuffer();
    wifiCount = WiFi.scanNetworks();
    if (wifiCount == 0) {
        u8g2.drawUTF8(10, 36, "未找到WiFi网络");
        u8g2.drawUTF8(10, 48, "2s后返回...");
        vTaskDelay(pdMS_TO_TICKS(2000));
        return;
    }
    
    // 创建WiFi列表菜单项
    for (int i = 0; i < wifiCount; i++) {
        ssid = WiFi.SSID(i);
        rssi = WiFi.RSSI(i);
        encryptionType = WiFi.encryptionType(i);
        
        wifiItems.push_back(
            menuItem(
                ssid.c_str(),
                [ssid,rssi,encryptionType](){
                    wifiConnectFunc(ssid.c_str(),rssi,encryptionType);}
            )
        );
    }
    
    // 创建WiFi选择菜单
    menu wifiSelectMenu("选择WiFi网络", wifiItems);
    
    // 使用menuLoop进入菜单
    menuLoop(wifiSelectMenu);
}

// 选中wifi后调用这个函数进入连接界面
void wifiConnectFunc(String ssid,int32_t rssi,int32_t encryptionType){

    char buffer[32];        // 用来缓存转换的数据，方便改动
    KeyEvent Key = 0;       // 用于存储键值

    // 显示信息
    u8g2.clearBuffer();
    u8g2.drawUTF8(4,2,ssid.c_str());            // 名字
    sprintf(buffer,"质量 -> %ddB",rssi);     // 信号强度
    u8g2.drawUTF8(4,16,buffer);
    sprintf(buffer,"加密类型 -> ");                // 加密类型
    switch(encryptionType){                     
        case WIFI_AUTH_OPEN:         strcat(buffer,"未加密");break;
        case WIFI_AUTH_WEP:          strcat(buffer,"WEP");break;
        case WIFI_AUTH_WPA_PSK:      strcat(buffer,"WPA");break;
        case WIFI_AUTH_WPA2_PSK:     strcat(buffer,"WPA2");break;
        case WIFI_AUTH_WPA_WPA2_PSK: strcat(buffer,"WPA/WPA2");break;
        case WIFI_AUTH_ENTERPRISE:   strcat(buffer,"WPA2企业版");break;
        case WIFI_AUTH_WPA3_PSK:     strcat(buffer,"WPA3");break;
        case WIFI_AUTH_WPA2_WPA3_PSK:strcat(buffer,"WPA2/WPA3");break;
        case WIFI_AUTH_WAPI_PSK:     strcat(buffer,"WAPI_PSK");break;
        case WIFI_AUTH_WPA3_ENT_192: strcat(buffer,"WPA3企业版");break;
        default:                     strcat(buffer,"错误");break;
    }   u8g2.drawUTF8(4,30,buffer);
    u8g2.drawUTF8(2,48,"A连接   B/LEFT返回");
    u8g2.sendBuffer();
    while(1){                                   // 按键检测
        Key = Keyboard.waitEvent(portMAX_DELAY);
        if(Key & KEY_EVENT_FIRSTPRESS){
            if(Key & KEY_EVENT_A)break;             // A确认连接
            if(Key & KEY_EVENT_BACK)return;         // B/LEFT返回
        }
    }

    // 输入密码
    String password = "";                       // 输入的密码
    char thisChar = '0';                         // 当前光标指向的密码

    if(encryptionType != WIFI_AUTH_OPEN)        // 只有加密了才会进入
    while(1){
        // 按键检测
        Key = Keyboard.waitEvent(portMAX_DELAY);
        if(Key & KEY_EVENT_FIRSTPRESS || Key & KEY_EVENT_LONG_PRESS){
            if(Key & KEY_EVENT_LONG_PRESS){vTaskDelay(pdMS_TO_TICKS(50));}
            if(Key & KEY_EVENT_LEFT) {thisChar <= 32 ? thisChar = 32 : thisChar --;}   // 左右键选择密码
            if(Key & KEY_EVENT_RIGHT){thisChar >= 126? thisChar = 126: thisChar ++;}
            if(Key & KEY_EVENT_X)password.remove(                 // X退格
                max((uint32_t)0,password.length() -1));
            if(Key & KEY_EVENT_Y)password += thisChar;      // 短按Y输入一位
            if(Key & KEY_EVENT_A)break;                     // 按A确认密码
            if(Key & KEY_EVENT_B)return;                    // B返回
        }

        // 显示
        u8g2.clearBuffer();
        u8g2.drawUTF8(4,2,"密码");
        u8g2.drawUTF8(30,2,password.c_str());                               // 密码
        u8g2.drawBox(30 + u8g2.getUTF8Width(password.c_str()), 2, 6, 14);   // 密码输入光标

        char buffer[2] = {0,'\0'};                  // 用于存储当前打印的字符的字符串
        for(int i=-4; i<=4; ++i ){                  // 打印密码选择部分
            buffer[0] = thisChar + i;
            u8g2.drawStr(12*i + u8g2.getDisplayWidth()/2,30,buffer);
        }u8g2.drawBox(u8g2.getDisplayWidth()/2 -3, 30, 12, 12);            // 密码选择光标

        u8g2.drawUTF8(4, 48, "A连接 X退格 Y输入");
        u8g2.sendBuffer();
    }
    
    // 连接，状态显示
    WiFi.begin(ssid,password);
    while(1){
        u8g2.clearBuffer();
        u8g2.drawUTF8(4,2,"WiFi连接中...");
        switch(WiFi.status()){
            case 0: u8g2.drawUTF8(4,16,"空闲");   break;
            case 1: u8g2.drawUTF8(4,16,"无SSID"); break;
            case 2: u8g2.drawUTF8(4,16,"扫描完成"); break;
            case 3: u8g2.drawUTF8(4,16,"连接成功"); break;
            case 4: u8g2.drawUTF8(4,16,"连接失败"); break;
            case 5: u8g2.drawUTF8(4,16,"连接丢失"); break;
            case 6: u8g2.drawUTF8(4,16,"已断开");   break;
            default:u8g2.drawUTF8(4,16,"未知状态"); break;
        }
        u8g2.sendBuffer();

        Key = Keyboard.waitEvent(500);
        if(Key & KEY_EVENT_FIRSTPRESS){
            if(Key & KEY_EVENT_BACK) {return;}   // 左右键选择密码
        }
    }
}