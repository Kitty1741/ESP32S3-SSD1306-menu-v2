#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#include "config.h"
#include "0_base/base.h"
#include "1_modules/menu/menu.h"

#include "display.h"



// 创建u8g2对象
#define _U8G2_CREATE U8G2_SSD1306_128X64_NONAME_F_HW_I2C
_U8G2_CREATE u8g2(                             
        /*rotation*/U8G2_R0,
        /*reset*/ U8X8_PIN_NONE,
        /*SCL*/ _U8G2_SCL,           
        /*SDA*/ _U8G2_SDA
);

// 重置菜单显示设置
void resetU8g2Setting(){
    __DEBUG_4("resetU8g2Setting()\n")
    u8g2.setClipWindow(0, 0, 128, 64); // 恢复全屏显示
    u8g2.enableUTF8Print();    // 启用UTF-8支持，用于显示中文
    u8g2.setDrawColor(2);        // xor显示
    u8g2.setFont(_U8G2_ENG_FONT_X12);  // 设置英文字体
    u8g2.setFont(_U8G2_CN_FONT_X12); // 设置中文字体
    u8g2.setFontPosTop();      // 设置字体绘制基准为顶部（默认为基线）
}

// 初始化U8g2库
void initU8g2Setting(){
    __DEBUG_1("initU8g2Setting()\n")
    u8g2.begin(); 
    resetU8g2Setting();
}



// 打印名字条
void printNameBar(const std::string& name){
    __DEBUG_1("printNameBar()\n")
    u8g2.drawFrame(0, 0, 128, 15);
    u8g2.drawUTF8 (2, 3, name.c_str());
}

static int32_t itemBias  = 0;                   // 用来计算选项整体显示偏移(向下为正),单位像素
static int32_t itemTargetBias = 0;              // 选项目标偏移量(向下为正),运行时不断二分趋近该值
const static uint8_t itemBeginCoor = 16;        // 选项渲染起始纵坐标(u8g2坐标系)，偏移以此为基准

static int8_t cursorBias = 0;                   // 光标相对初始屏幕位置的偏移(向下为正)
static int8_t cursorTargetBias = 0;             // 光标目标屏幕位置偏移量(向下为正)
const static uint8_t cursorBeginCoor = 16;      // 光标初始屏幕位置在选项1上

const static uint8_t itemHeight = 12;           // 选项高度，推荐12，不能小于12

// 打印Item列表，后续添加动画
void printMenuItems(const menu& menu){
    __DEBUG_1("printMenuItems()\n")
    
    // 处理光标和菜单的目标位置
    uint32_t size = menu.size();
    if(size < 4){                           // 短菜单固定选项位置
        itemTargetBias = 0;                                 // item无偏移
        cursorTargetBias = menu.cursor * itemHeight;        // 光标在位置1
    }
    else if(menu.cursor == 0){                  // 光标在第一个位置
        itemTargetBias = 0;                                 // item无偏移
        cursorTargetBias = 0;                               // 光标在位置1
    }else if(menu.cursor == size -2){           // 光标在倒数第二个位置
        itemTargetBias = -(menu.cursor -2) * itemHeight;    // item偏移到最后
        cursorTargetBias = 2 * itemHeight;                  // 光标在位置3
    }else if(menu.cursor == size -1){           // 光标在最后一个位置
        itemTargetBias = -(menu.cursor -3) * itemHeight;    // item偏移到最后
        cursorTargetBias = 3 * itemHeight;                  // 光标在位置4
    }else{                                      // 默认情况
        itemTargetBias = -(menu.cursor -1) * itemHeight;    // 列表位置随光标位置改变
        cursorTargetBias = 1 * itemHeight;                  // 光标在位置2
    }

    // 菜单和光标向目标位置逼近
    if(cursorTargetBias-cursorBias==1|cursorTargetBias-cursorBias==-1){cursorBias=cursorTargetBias;}
    cursorBias += (cursorTargetBias - cursorBias)/2;      // 实际偏移量计算
    if(itemTargetBias-itemBias==1|itemTargetBias-itemBias==-1){itemBias=itemTargetBias;}
    itemBias += (itemTargetBias - itemBias)/2;            // 实际偏移量计算

    // 打印
    for(uint8_t i=0;i<size;++i){    // 打印选项
        u8g2.drawUTF8(
            4,
            itemBeginCoor + itemBias + i*itemHeight,
            menu.itemTable[i].name.c_str()
        );
    }
    u8g2.drawBox(                   // 打印光标
        0,
        cursorBeginCoor + cursorBias -2,
        128,
        itemHeight +1/*这个打印需要宽一点来包住选项*/
    );
}

// 打印一整个菜单的函数
void printMenu(menu* Menu){
    __DEBUG_1("printMenu()\n")
    if(!Menu){return;}          // 防空指针
    u8g2.clearBuffer();
    u8g2.setClipWindow(0, 0, 128, 15); 
    printNameBar(Menu->name);
    u8g2.setClipWindow(0, 15, 128, 64); 
    printMenuItems(*Menu);
    u8g2.sendBuffer();
}