#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#include "config.h"
#include "0_base/base.h"
#include "1_modules/modules.h"
#include "2_task/keyboard/keyboard.h"

#include "menuDisplay.h"

uint32_t displayInterval = 1000/_DISPLAY_FPS; // 显示间隔，单位ms

extern QueueHandle_t keyboardEventQueue; // 键盘事件队列
TaskHandle_t menuDisplayTaskHandle = NULL; // 菜单显示任务句柄
static menu* mainMenuPtr;            // 根部菜单，用来检测是否在根部退出，防止rtos任务意外结束

// 初始化菜单显示任务
void initMenuDisplayTask(menu& mainMenu){
    __DEBUG_2("initMenuDisplayTask()\n")
    mainMenuPtr = &mainMenu;

    // 确保任务优先级比loop高，这样显示不会轻易撞车
    uint8_t priority;
    TaskHandle_t loopTaskHandle = xTaskGetHandle("loopTask");
    if(loopTaskHandle != NULL){
        priority = uxTaskPriorityGet( loopTaskHandle ) +1; 
    } else priority=1;     // 依旧防空

    xTaskCreate(
        menuDisplayTask,
        "menuDisplayTask",
        8192,
        mainMenuPtr,
        priority,
        &menuDisplayTaskHandle
    );
}

// 菜单计算&显示任务
void menuDisplayTask(void* menuPtr){
    __DEBUG_2("menuDisplayTask()\n")
    menu& Menu = *(menu*)menuPtr;
    KeyEvent key = 0;                       // 缓存按键事件用
    KeyEvent keyBuffer = 0;                 // 用来融合按键事件
    uint32_t& cursor = Menu.cursor;         // 菜单光标引用
    TickType_t lastWakeTime = 0;            // 上次任务唤醒时间，用于控制帧数
    TickType_t lastLPTime = xTaskGetTickCount(); // 上次响应长按改变菜单位置的时间，用于控制长按改变位置的速度,LP = longPress
    constexpr TickType_t LPInterval = pdMS_TO_TICKS(LONG_PRESS_ACT_INTERVAL); // 长按响应间隔，单位转换为每tick
    bool ifDraw = true;

    // 按键响应
    while(1){
        lastWakeTime = xTaskGetTickCount(); // 开始计时

        // 捕捉按键队列
        key = 0;
        while(xQueueReceive( keyboardEventQueue , &keyBuffer , 0 )){
            key |= keyBuffer;   // 由于按键实在多，一个个看不过来，所以干脆全融了
        }
        if(key & KEY_EVENT_LONG_PRESS ){// 如果是长按导致的
            if(lastLPTime + LPInterval > lastWakeTime){ // 如果时间间隔不够久就不响应
                goto KEY_ACT_END; 
            }else{                                      // 间隔够久就响应并刷新间隔
                lastLPTime = lastWakeTime;
            }
        }else if(!(key & KEY_EVENT_FIRST_PRESS)){          // 如果又不是长按又不是第一次按下就滚
            goto KEY_ACT_END;
        }
        
        // 能运行到这里代表输入的按键需要被执行
        // 执行后可能会改变显示，所以设计ifDraw的操作
        // 当前逻辑：每次按键后允许画，动画结束后不允许画，这样没有操作就不画了
        ifDraw = true;
        if( key & KEY_EVENT_UP )   {Menu.up();  }                // 光标上移
        if( key & KEY_EVENT_DOWN ) {Menu.down();}                 // 光标下移
        if( key & (KEY_EVENT_BACK) ){                 // 返回
            if(&Menu != mainMenuPtr)break; // 检测是否退无可退，防止任务意外结束
        } 
        if( key & (KEY_EVENT_ENTER) ){                 // 执行run()
            resetU8g2Setting(); // 初始化显示设置
            Menu.runItem();
            resetU8g2Setting(); // 防止有人改显示设置
        }
        KEY_ACT_END: // 按键响应结束位置，准备打印和延时

        // 菜单打印
        if(ifDraw)
            if(printMenu(&Menu)==true){ // 如果动画已经播放完了
                ifDraw = false; // 下次就不画了
            }else ifDraw = true;

        // 延时
        vTaskDelayUntil(&lastWakeTime,rtos_ms(displayInterval));
    }
}