#include "config.h"
#if ENABLE_INNER_MENU

#include <Arduino.h>

#include "config.h"
#include "0_base/base.h"
#include "1_modules/modules.h"
#include "2_task/task.h"
#include "3_utils/init/init.h"
#include "3_utils/macro/macro.h"

#include "inner_items/inner_items.h"
#include "menu.h"

menu innerMenu(
    "内置菜单",{
        {"SpaceTrash",runSpaceTrash},
        {"LittleRookChess",runLittleRockChess},
    }
);

#endif