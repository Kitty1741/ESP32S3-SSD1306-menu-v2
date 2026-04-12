# 0_base
- 文档2026/4/12更新，文档可能更新不及时，请核对文档和代码时间

## 本文件夹含有以下内容
- macro/         dir         项目依赖的各种宏定义
  - get_time/    dir         获取时间函数宏定义（us/ms/s）和 FreeRTOS 延迟别名
  - lengthof()/  dir         获取数组长度的宏定义
  - f_debug/     dir         串口调试宏定义，支持多层级调试控制
  - pass/        dir         空宏定义（用于占位）
- base.h         file        用于打包这些功能