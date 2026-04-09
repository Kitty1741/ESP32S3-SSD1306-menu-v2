#include "0_base/base.h"
#include "1_modules/modules.h"
#include "2_task/task.h"
#include "init.h"

void menuInit(const menu& mainMenu){
    __DEBUG_3("menuInit()\n")

    //执行初始化清单
    INIT_LIST_0
    INIT_LIST_1
    INIT_LIST_2(mainMenu)

    //test
    //initMenuCore(mainMenu);
}