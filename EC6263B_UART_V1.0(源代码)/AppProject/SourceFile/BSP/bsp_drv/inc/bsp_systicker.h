/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: bsp_systicker.h 
**
**    功能描述:	系统滴答时钟定时器
**
**    公    司：蒙发利电子
**
**    项目名称：
**
**    平台信息：
**
**    作    者：Hzy
**
**    其他说明:	                                                                                                        
**
**    修改记录:  
**
========================================================================================================================
========================================================================================================================
*/
#ifndef  _BSP_SYSTICKER_H_
#define  _BSP_SYSTICKER_H_


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp.h"


/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
#ifndef BSP_CFG_SYS_TICKER_PERIOD
#define  BSP_CFG_SYS_TICKER_PERIOD          1                          /*系统ticker的周期时间，单位ms*/
#endif

#ifndef BSP_CFG_SYS_TICKER_MAX
#define  BSP_CFG_SYS_TICKER_MAX             0xFFFF                     /*系统ticker的的最大计数值，两字节最大0xFFFF*/
#endif


#define  SYS_TICKER_PERIOD                  BSP_CFG_SYS_TICKER_PERIOD  /*系统ticker的周期时间，单位ms*/
#define  SYS_TICKER_PER_SEC                 (1000/SYS_TICKER_PERIOD)   /*每秒ticker的次数*/

#define  TICKER_MAX                         BSP_CFG_SYS_TICKER_MAX    


/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 :                                                                                                       
************************************************************************************************************************
*/
#if (0xFFFF == TICKER_MAX)
typedef  uint16_t              Ticker_t;                
#elif (0xFF == TICKER_MAX)
typedef  uint8_t               Ticker_t;                 
#else 
typedef  uint32_t              Ticker_t;                 
#endif



/*
========================================================================================================================
*【全局声明】                                          【全局声明】                                          【全局声明】
========================================================================================================================
*/
void BSP_SysTicker_Init(void);
uint16_t BSP_SysTicker_GetCurUs(void);
Ticker_t BSP_SysTicker_GetCurTick(void);
Ticker_t BSP_SysTicker_CalLag(Ticker_t tick);


#endif                        /* End of module include.  */
