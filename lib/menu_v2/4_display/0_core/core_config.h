#ifndef __CORE_CONFIG_H__
#define __CORE_CONFIG_H__

#include <U8g2lib.h>

// u8g2构造函数选择
#define _U8G2_CREATE U8G2_SSD1306_128X64_NONAME_F_HW_I2C
#define SCL 9
#define SDA 8

// 默认字体
#define _U8G2_ENG_FONT_X8  u8g2_font_ncen8_tr
#define _U8G2_ENG_FONT_X12 u8g2_font_ncenB12_tr
#define _U8G2_CN_FONT_X12  u8g2_font_wqy12_t_gb2312

#endif 