#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#include <./0_config/config.h>
#include <./2_adapter/adapter.h>
#include <./3_core/core.h>

#include "core.h"
#include "core_config.h"

// 创建u8g2对象
#define _U8G2_CREATE U8G2_SSD1306_128X64_NONAME_F_HW_I2C
_U8G2_CREATE u8g2(                             
        /*rotation*/U8G2_R0,
        /*reset*/ U8X8_PIN_NONE ,
        /*SCL*/ SCL,                       
        /*SDA*/ SDA                      
);               
extern menu* currentMenu; // 3_core定义的当前菜单变量             

// 重置菜单显示设置
void resetU8g2Setting(){
    __DEBUG_4("resetU8g2Setting()\n")
    u8g2.enableUTF8Print();    // 启用UTF-8支持，用于显示中文
    u8g2.setFont(u8g2_font_ncenB12_tr);  // 设置英文字体
    u8g2.setFont(u8g2_font_wqy12_t_gb2312); // 设置中文字体
    u8g2.setFontPosTop();      // 设置字体绘制基准为顶部（默认为基线）
}

// 初始化U8g2库
void initU8g2Setting(){
    __DEBUG_4("initU8g2Setting()\n")
    u8g2.begin(); 
    resetU8g2Setting();
}

// 打印名字
void printNameBar(std::string name){
    __DEBUG_4("printNameBar()\n")
    u8g2.drawFrame(0, 0, 128, 16);
    u8g2.drawUTF8 (2, 4, name.c_str());
}

// 打印Item列表，后续添加动画
void printMenuItems(menu* menu){
    __DEBUG_4("printMenuItems()\n")
    uint32_t view;                   // 渲染开始位置
    uint32_t size = menu->size();

    //通过光标得出合适的屏幕位置
    if( size < 4 ){
        view = 0;
    }else{
        menu->cursor == 0         ? view = 0 :
        menu->cursor == size -2   ? view = menu->cursor -2 :
        menu->cursor == size -1   ? view = menu->cursor -3 :
        /*default*/view = menu->cursor -1;
    }

    // 打印选项和光标
    for(uint8_t i=0;i<4;i++){
        if( i < size )
        u8g2.drawUTF8 (                 // 选项
            4, 
            17 + 12*i, 
            menu->getItemName(view + i).c_str()
        );
        if( view + i == menu->cursor ){ // 光标
            u8g2.drawBox(0,16+12*i,2,12);
        }
    }
}

// 打印一整个菜单的函数
void printMenu(menu* menu){
    if(menu==nullptr||menu==NULL)return;
    else{
        printNameBar(menu->name);
        printMenuItems(menu);
    }
}