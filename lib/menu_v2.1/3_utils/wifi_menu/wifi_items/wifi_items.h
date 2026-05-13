#ifndef _3_WIFI_H__
#define _3_WIFI_H__

#include "config.h"
#if ENABLE_WIFI_MENU

#include <Arduino.h>
// wifi.cpp
void setWifiManually();
void wifiConnectFunc(String ssid,int32_t rssi,int32_t encryptionType);  // 连接wifi函数，选项lambda调用
void wifiClock();  // WiFi时钟功能
void wifiStatus(); // 查看当前网络状况



#endif
#endif
