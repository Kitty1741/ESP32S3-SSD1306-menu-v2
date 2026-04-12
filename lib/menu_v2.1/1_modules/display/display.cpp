#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#include "config.h"
#include "0_base/base.h"
#include "1_modules/menu/menu.h"

#include "display.h"



// 创建u8g2对象
_U8G2_CREATE u8g2(                             
        /*rotation*/U8G2_R0,
        /*reset*/ U8X8_PIN_NONE,
        /*SCL*/ _U8G2_SCL,           
        /*SDA*/ _U8G2_SDA
);

// 重置菜单显示设置
void resetU8g2Setting(){
    __DEBUG_4("resetU8g2Setting()\n")
    u8g2.setClipWindow(0, 0, u8g2.getDisplayWidth(), u8g2.getDisplayHeight()); // 恢复全屏显示
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

// 让now的值逐渐逼近目标值的函数，用于动画选项光标逼近实际位置，不支持无符号变量
// 返回值为真则代表已经approach到了target
template<typename T>
bool approachTarget(T& now,T target){

    T diff = target - now;  // 目标与当前值的差值
    if( std::abs(diff) <= 1){    // 如果只相差1，则直接赋相等，防止后面diff/2=0时now值不变
        now = target;
        return true;
    }
    now += diff/2;               // 否则用二分法逼近目标值
    return false;
}

// 官方的傻逼std::max和min没法用于两个不同类型的量，所以我自己写了一个
template<typename A,typename B>
int32_t min(A a,B b){
    if(a<b)return a;
    return b;
}
template<typename A,typename B>
int32_t max(A a,B b){
    if(a<b)return b;
    return a;
}

constexpr static uint32_t itemHeight = _DISPLAY_ITEM_HEIGHT;           // 选项高度，推荐13
constexpr static uint32_t titleHeight = _DISPLAY_TITLE_HEIGHT;         // 标题高度，推荐17
const static uint32_t maxItems =                                       // 最大同时出现选项数量
    (u8g2.getHeight() - titleHeight + itemHeight - 1) / itemHeight + 1;

static int32_t itemBias;                       // 用来计算选项整体显示偏移(向下为正),单位像素
static int32_t itemTargetBias;                  // 选项目标偏移量(向下为正),运行时不断二分趋近该值
const static uint32_t itemBeginCoor = titleHeight;      // 选项渲染起始纵坐标(u8g2坐标系)，偏移以此为基准

static int32_t cursorBias;                       // 光标相对初始屏幕位置的偏移(向下为正)
static int32_t cursorTargetBias;                 // 光标目标屏幕位置偏移量(向下为正)
static int32_t cursorWidth;                      // 光标宽度
static int32_t cursorTargetWidth;                // 光标目标宽度
const static uint32_t cursorBeginCoorY = titleHeight;   // 光标初始屏幕位置(在选项1上)
const static uint32_t cursorBeginCoorX = 0;             // 光标初始横坐标为0


// 打印Item列表，后续添加动画
// 返回值为真->光标和目标位置重合->显示任务可以休息了
bool printMenuItems(const menu& menu){
    
    __DEBUG_1("printMenuItems()\n")
    bool ifCompleteDraw = true;   // 返回值
    
    // 处理光标和菜单的目标位置
    uint32_t size = menu.size();
    cursorTargetWidth = u8g2.getUTF8Width(  // 计算光标宽度uint32_t size = menu.size();
        menu.itemTable[menu.cursor].name.c_str()) + 8;  
    itemTargetBias = -menu.cursor*itemHeight + (u8g2.getHeight() - titleHeight)/3;   // 默认起始位置在屏幕的上大约三分之一位置
    if(itemTargetBias >= 0||size < maxItems){                // 如果第一个显示的选项在起始位置下 或者选项很少
        itemTargetBias = 0;                                  // 就设置第一项对齐顶部
    }else if(itemTargetBias + size*itemHeight < u8g2.getHeight() - cursorBeginCoorY){ // 如果最后一个显示的选项后有空隙
        itemTargetBias = -size*itemHeight + (u8g2.getHeight() - cursorBeginCoorY) +1;    // 就把选项下放到没有空隙
    }
    cursorTargetBias = itemTargetBias + menu.cursor*itemHeight;

    // 菜单和光标向目标值逼近
    ifCompleteDraw &= approachTarget(itemBias  ,  itemTargetBias);
    ifCompleteDraw &= approachTarget(cursorBias,  cursorTargetBias);
    ifCompleteDraw &= approachTarget(cursorWidth, cursorTargetWidth);

    // 打印             
    for(uint32_t i=0;i<size;++i){    // 打印选项
        if(itemBeginCoor + itemBias + i*itemHeight < itemBeginCoor - itemHeight)continue;   // 跳过无效项
        if(itemBeginCoor + itemBias + i*itemHeight > itemBeginCoor + (maxItems-1)*itemHeight)continue; // 跳过无效项
        u8g2.drawUTF8(
            4,
            itemBeginCoor + itemBias + i*itemHeight,    // 每项的纵坐标
            menu.itemTable[i].name.c_str()
        );
    }
    u8g2.drawBox(                   // 打印光标
        cursorBeginCoorX,
        cursorBeginCoorY + cursorBias -2,
        cursorWidth,
        itemHeight +1/*这个打印需要宽一点来包住选项*/
    );
    return ifCompleteDraw;
}

// 打印名字条
void printNameBar(const std::string& name){
    __DEBUG_1("printNameBar()\n")
    u8g2.drawFrame(0, 0, u8g2.getWidth(), titleHeight -1);
    u8g2.drawUTF8 (2, 3, name.c_str());
}

// 打印一整个菜单的函数
// 返回值为真->光标和目标位置重合->显示任务可以休息了
bool printMenu(menu* Menu){
    __DEBUG_1("printMenu()\n")
    if(!Menu){return true;}          // 防空指针
    bool ifCompleteDraw;   // 返回值

    u8g2.clearBuffer();
    u8g2.setClipWindow(0, 0, u8g2.getWidth(), titleHeight -1); 
    printNameBar(Menu->name);
    u8g2.setClipWindow(0, titleHeight -1, u8g2.getWidth(), u8g2.getHeight()); 
    ifCompleteDraw = printMenuItems(*Menu);
    u8g2.sendBuffer();

    return ifCompleteDraw;
}