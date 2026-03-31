// base.cpp
#include <arduino.h>
#include <random>

#include <0_config/config.h>
#include <2_adapter/adapter.h>

#include "base.h"


// 菜单项
menuItem_t::menuItem_t(String name){
    this->name = name;
}    // 构造函数
menuItem_t::~menuItem_t(){}      // 析构函数

String menuItem_t::getName() const{
    return this->name;
}         // 读名字
void menuItem_t::changeName(String name){
    this->name = name;
}   // 改名
int32_t menuItem_t::run(){ // 菜单行为函数
    return this->bind();
}


// 菜单
menu_t::menu_t(String name){
    this->name = name;
}    // 构造函数
menu_t::~menu_t(){}      // 析构函数

String menu_t::getName(){
    return this->name;
}         // 读名字
void menu_t::changeName(String name){
    this->name = name;
}   // 改名

// 读选项数组
std::vector<menuItem_t> menu_t::getItemTable() const{
    return this->itemTable;
} 

// 读名字数组
std::vector<String> menu_t::getNameTable() const{
    uint32_t size = this->itemTable.size();     // 确认名字数组长度
    std::vector<String> nameTable;              // 初始化数组
    for(uint32_t i=0;i<size;i++){               // 遍历拷贝
        nameTable.push_back(this->itemTable[i].name);
    }
    return nameTable;
}

int32_t menu_t::runItem(){
    return this->itemTable[this->cursor].run();
}                         // 执行光标对应选项的行为