#ifndef __LENGTHOF_H__
#define __LENGTHOF_H__

#include <Arduino.h>

//设置获取 数组长度 的宏
#define lengthof(ARRAY) sizeof(ARRAY)/sizeof(ARRAY[0])


#endif