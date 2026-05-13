#include "config.h"
#if ENABLE_WIFI_MENU

#include "1_modules/modules.h"
#include "wifi_items/wifi_items.h"
menu wifiMenu(
    "WiFi",{
        {"当前网络",wifiStatus},
        {"手动连接",setWifiManually},
    }
);

#endif