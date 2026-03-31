// base.cpp
#include <arduino.h>

#include <0_config/config.h>
#include <2_adapter/adapter.h>

#include "base.h"

menuItem_t::menuItem_t(String name="Noname"){

}    // 构造函数
menuItem_t::~menuItem_t(){

}      // 析构函数
void menuItem_t::setName(String name){

}     // 设置选项名称
int32_t menuItem_t::run(){
    return this->bind();
}