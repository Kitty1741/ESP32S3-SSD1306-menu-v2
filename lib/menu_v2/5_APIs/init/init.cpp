#include "0_config/config.h"
#include "1_driver/driver.h"
#include "2_adapter/adapter.h"
#include "3_core/core.h"
#include "4_display/display.h"
#include "init.h"

void menuInit(){
    __DEBUG_A("menuInit()\n")

    //调用初始化函数清单
    INIT_LIST_0
    INIT_LIST_1
    INIT_LIST_2
    INIT_LIST_3
    INIT_LIST_4
}