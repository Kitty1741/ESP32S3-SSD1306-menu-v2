#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "keyboard_config.h"
#include "keyboard_types.h"

//初始化函数
void initKeyboard();

// 键盘扫描函数 
KeyMask scanKeyValue();

#endif // __KEYBOARD_H__