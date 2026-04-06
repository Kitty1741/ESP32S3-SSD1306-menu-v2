// base_t.cpp
#include <arduino.h>
#include <string>

#include <0_config/config.h>

#include "base.h"

// 读指定选项名字
std::string menu::getItemName(uint32_t index) const{
    __DEBUG_3("menu::getItemName()\n")
    return this->itemTable[index].name;
}

// 执行光标对应选项的行为
void menu::runItem(){
    __DEBUG_3("menu::runItem()\n")
    menuItem* item = &this->itemTable[this->cursor];
    if(item->run != nullptr)
    item->run();
}     
// 返回菜单长度                    
uint32_t menu::size() const{
    __DEBUG_3("menu::size()\n")
    return this->itemTable.size();
}      
void menu::up(){// 光标上移
    if(cursor!=0){
        cursor--;
    }else{
        cursor = this->size() -1;
    }
}
void menu::down(){// 光标下移
    if(cursor != this->size() -1){
        cursor++;
    }else{
        cursor = 0;
    }
}