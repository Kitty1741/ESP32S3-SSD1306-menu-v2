详细引脚分配表
功能	引脚	说明

拓展引脚	GPIO17,18	全部引出至排针，可作ADC、数字IO等
拓展引脚	GPIO4–7  	全部引出至排针，可作ADC、数字IO等
I2C0 SDA	GPIO8	主屏幕数据线
I2C0 SCL	GPIO9	主屏幕时钟线
I2C1 SDA	GPIO15	第二组I2C数据线（传感器等）
I2C1 SCL	GPIO16	第二组I2C时钟线

SPI CS	GPIO10	片选（可自定义，也可多个CS）
SPI CLK	GPIO11	时钟
SPI MISO	GPIO12	主机输入
SPI MOSI	GPIO13	主机输出
SPI 备用/DC	GPIO14	如需控制屏幕数据/命令脚，可用此脚

按键1	GPIO35	上
按键2	GPIO36	下
按键3	GPIO37	左/取消
按键4	GPIO38	右/进入
按键5	GPIO39	功能键A
按键6	GPIO40	功能键B
按键7	GPIO41	功能键X
按键8	GPIO42	功能键Y
按键9	GPIO1	功能键+/引出备用
按键10	GPIO2	功能键-/引出备用
蜂鸣器	GPIO47	R-2R电路链接，用于输出叠加方波

闲置引脚
GPIO0	Strapping 引脚
GPIO3	Strapping 引脚
GPIO19	USB-JTAG 引脚
GPIO20	USB-JTAG 引脚
GPIO21	普通 GPIO，功能完整
GPIO43	U0TXD
GPIO44	U0RXD
GPIO45	Strapping 引脚
GPIO46	只能输入，Strapping 引脚
GPIO48	板载WS2812引脚，功能完整
建议：将这些闲置引脚全部引出至排针或测试点，方便未来扩展。若无需使用，在软件中保持未初始化即可（高阻态）。