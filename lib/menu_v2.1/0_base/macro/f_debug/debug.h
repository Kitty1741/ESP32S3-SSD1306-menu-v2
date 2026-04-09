#ifndef __DEBUG_H__
#define __DEBUG_H__

//串口调试宏

//是否开启调试模式(串口发送调试信息)(1/0)
#define IF_DEBUG 1
#if( IF_DEBUG == 1 )

#define IF_DEBUG_0 0//允许调试不同层
#define IF_DEBUG_1 0
#define IF_DEBUG_2 0
#define IF_DEBUG_3 1
#define IF_DEBUG_A 1//another

#endif // IF_DEBUG



#if (IF_DEBUG_0 == 1)
#define __DEBUG_0(...) Serial.print(__VA_ARGS__);
#else
#define __DEBUG_0(...)
#endif

#if (IF_DEBUG_1 == 1)
#define __DEBUG_1(...) Serial.print(__VA_ARGS__);
#else
#define __DEBUG_1(...)
#endif

#if (IF_DEBUG_2 == 1)
#define __DEBUG_2(...) Serial.print(__VA_ARGS__);
#else
#define __DEBUG_2(...)
#endif

#if (IF_DEBUG_3 == 1)
#define __DEBUG_3(...) Serial.print(__VA_ARGS__);
#else
#define __DEBUG_3(...)
#endif

#if (IF_DEBUG_4 == 1)
#define __DEBUG_4(...) Serial.print(__VA_ARGS__);
#else
#define __DEBUG_4(...)
#endif

#if (IF_DEBUG_5 == 1)
#define __DEBUG_5(...) Serial.print(__VA_ARGS__);
#else
#define __DEBUG_5(...)
#endif

#if (IF_DEBUG_A == 1)
#define __DEBUG_A(...) Serial.print(__VA_ARGS__);
#else
#define __DEBUG_A(...)
#endif

#endif