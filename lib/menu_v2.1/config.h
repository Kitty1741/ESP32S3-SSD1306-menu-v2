#ifndef _CONFIG_H__
#define _CONFIG_H__

// 配置文件
// ----------------   0_base    ----------------


// ----------------  1_modules  ----------------
// keyboard
//键位配置
#define   GPIO_KEY_UP       35
#define   GPIO_KEY_LEFT     36
#define   GPIO_KEY_DOWN     37
#define   GPIO_KEY_RIGHT    38
#define   GPIO_KEY_X        39
#define   GPIO_KEY_A        40
#define   GPIO_KEY_Y        41
#define   GPIO_KEY_B        42
#define   GPIO_KEY_F1       1 
#define   GPIO_KEY_F2       2 
//按键检测
#define   KEYBOARD_SCAN_INTERVAL 20                   // 键盘扫描间隔，单位 毫秒
#define   KEYBOARD_LONG_PRESS_THRESHOLD  800          // 长按事件阈值，单位 毫秒
#define   KEYBOARD_LONG_LONG_PRESS_THRESHOLD 2000     // 超级长按事件阈值，单位 毫秒

// display
// u8g2构造函数选择
#define _U8G2_CREATE U8G2_SSD1306_128X64_NONAME_F_HW_I2C
#define _U8G2_SCL 9
#define _U8G2_SDA 8
// u8g2默认字体
#define _U8G2_ENG_FONT_X8  u8g2_font_ncen8_tr
#define _U8G2_ENG_FONT_X12 u8g2_font_ncenB12_tr
#define _U8G2_CN_FONT_X12  u8g2_font_wqy12_t_gb2312


// ----------------   2_task    ----------------


// ----------------   3_utils   ----------------

#endif