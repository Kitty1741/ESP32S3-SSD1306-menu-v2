// base_t.cpp
#include <arduino.h>
#include <string>

#include <0_config/config.h>

#include "base.h"

// 读指定选项名字
std::string menu::getItemName(uint32_t index) const{
    return this->itemTable[index].name;
}

// 执行光标对应选项的行为
void menu::runItem(){
    if(this->itemTable[this->cursor].run != nullptr)
    this->itemTable[this->cursor].run();
}     
// 返回菜单长度                    
uint32_t menu::size() const{
    return this->itemTable.size();
}      