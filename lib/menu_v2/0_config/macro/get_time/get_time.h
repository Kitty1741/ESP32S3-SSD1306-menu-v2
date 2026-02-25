#ifndef __GET_TIME_H__
#define __GET_TIME_H__

#include <Arduino.h>

//设置获取时间的函数别名，方便移植
#define get_time_us() esp_timer_get_time()      
#define get_time_ms() get_time_us()/1000 

#endif