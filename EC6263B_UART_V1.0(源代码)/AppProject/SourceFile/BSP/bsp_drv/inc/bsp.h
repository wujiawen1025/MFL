/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称:                                                                                                         
**
**    功能描述:                                                                                                        
**
**    公    司：                                                                                                        
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
#ifndef  _BSP_H_
#define  _BSP_H_

/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/

#include "gd32f30x_it.h" 
#include "bsp_Cfg.h"   
#include "bsp_gpio.h"          
#include "bsp_uart.h"          
#include "bsp_adc.h"          
//#include "bsp_pit.h"
#include "bsp_systicker.h"
#include "bsp_pwmtmr.h" 
//#include "bsp_iic.h"
#include "bsp_watchdog.h"          
#include "bsp_feep.h"          
#include "bsp_flash.h"          
//#include "bsp_pmc.h"   

/*
========================================================================================================================
*【全局宏定义】                                       【全局宏定义】                                       【全局宏定义】
========================================================================================================================
*/
#define  BSP_DisInttrupt()         __set_PRIMASK(1)   /*关中断，关掉所有可屏蔽的异常，只剩下NMI和硬 fault可以响应。*/
#define  BSP_EnInttrupt()          __set_PRIMASK(0)   /*开中断*/

#define  BSP_SystemReset()         NVIC_SystemReset() /*复位系统*/ 


/*位操作------------------------------------------------------*/
#ifndef  BIT_SET
#define  BIT_SET(reg, bit)         ((reg) |= (1u<<bit))   
#endif
#ifndef  BIT_CLR
#define  BIT_CLR(reg, bit)         ((reg) &= ~(1u<<bit))
#endif
#ifndef  BIT_TEST
#define  BIT_TEST(reg, bit)        ((reg) & (1u<<bit))
#endif
#ifndef  BIT_GET
#define  BIT_GET(reg, bit)         ((reg>>bit) & 0x01)
#endif


/*计算表格大小（表格包含的条目数量）--------------------------*/ 
#ifndef  TAB_NUM
#define  TAB_NUM(tab)              (sizeof(tab)/sizeof(tab[0]))
#endif
#ifndef  TAB_ISUM                    /*tab item sum 表格条木总数*/
#define  TAB_ISUM(tab)              (sizeof(tab)/sizeof(tab[0]))
#endif


/*通用的宏----------------------------------------------------*/
//#ifndef  DISABLE
//#define  DISABLE                   0u                 /*不使能*/ /*stm32中的头文件有相关的枚举定义，这里就注释掉*/
//#endif
//#ifndef  ENABLE
//#define  ENABLE                    1u                 /*使能*/ /*stm32中的头文件有相关的枚举定义，这里就注释掉*/
//#endif

#ifndef  OFF
#define  OFF                       0u                 /*关*/
#endif
#ifndef  ON
#define  ON                        1u                 /*开*/
#endif

#ifndef  CLOSE
#define  CLOSE                     0u                 /*关*/
#endif
#ifndef  OPEN
#define  OPEN                      1u                 /*开*/
#endif

#ifndef  ERROR
#define  ERROR                     1u                 /*错误*/
#endif
#ifndef  CORRECT
#define  CORRECT                   0u                 /*正确*/
#endif

#ifndef  FALSE
#define  FALSE                     0u                 /*假*/
#endif
#ifndef  TRUE
#define  TRUE                      1u                 /*真*/
#endif

#ifndef  FAIL
#define  FAIL                      1u                 /*失败*/
#endif
#ifndef  SUCCESS
#define  SUCCESS                   0u                 /*成功*/
#endif

#ifndef  FAULT
#define  FAULT                     1u                 /*故障*/
#endif
#ifndef  NORMAL
#define  NORMAL                    0u                 /*正常*/
#endif


#ifndef  ASCII_NULL
#define  ASCII_NULL                (int8_t)0          /*空字符*/
#endif


#ifndef  P_NULL
#define  P_NULL                    (void*)0           /*空指针*/
#endif
#ifndef  PNULL
#define  PNULL                     (void*)0           /*空指针*/
#endif
#ifndef  NULL
#define  NULL                      (void*)0           /*空指针*/
#endif
#ifndef  null
#define  null                      (void*)0           /*空指针*/
#endif

/*
===============================================================================
**	              二进制表示宏定义
** keil不支持直接使用二进制数据。这里用宏定义代替。
** 注意：★ 只能表示最多 8 位 的二进制数据。★
===============================================================================
*/
#ifndef LONG_TO_BIN
#define LONG_TO_BIN(n)                       \
                     (                       \
                       ((n >> 21) & 0x80) |  \
                       ((n >> 18) & 0x40) |  \
                       ((n >> 15) & 0x20) |  \
                       ((n >> 12) & 0x10) |  \
                       ((n >> 9)  & 0x08) |  \
                       ((n >> 6)  & 0x04) |  \
                       ((n >> 3)  & 0x02) |  \
                       ((n )      & 0x01)    \
                     )

#define BIN(n) LONG_TO_BIN(0x##n##l)
#define B(n)   BIN(n)
#define b(n)   BIN(n)
#endif

/*
========================================================================================================================
*【全局数据类型定义】                              【全局数据类型定义】                              【全局数据类型定义】
========================================================================================================================
*/
typedef union
{
  uint32_t HL;

  struct
  {
    uint16_t L;
    uint16_t H;
  }UHL;
}Union_Uint32Uint16_t;

typedef union
{
  int32_t HL;

  struct
  {
    int16_t L;
    int16_t H;
  }UHL;
}Union_Int32Int16_t;

typedef union 
{
    uint16_t HL;

  __packed struct 
  {
    uint8_t L;
    uint8_t H;
  }UHL;
}Union_Uint16Uint8_t;

typedef union 
{
    int16_t HL;

  __packed struct 
  {
    int8_t L;
    int8_t H;
  }UHL;
}Union_Int16Int8_t;

//typedef union
//{
//  uint8_t All;
//  struct
//  {
//    uint8_t        B0        :1;
//    uint8_t        B1        :1;
//    uint8_t        B2        :1;
//    uint8_t        B3        :1;
//    uint8_t        B4        :1;
//    uint8_t        B5        :1;
//    uint8_t        B6        :1;
//    uint8_t        B7        :1;
//  }Bit;

//}Union_Uint8Bit_t;

//typedef union
//{
//  uint16_t All;

//  struct
//  {
//    uint8_t        B0        :1;
//    uint8_t        B1        :1;
//    uint8_t        B2        :1;
//    uint8_t        B3        :1;
//    uint8_t        B4        :1;
//    uint8_t        B5        :1;
//    uint8_t        B6        :1;
//    uint8_t        B7        :1;

//    uint8_t        B8        :1;
//    uint8_t        B9        :1;
//    uint8_t        B10       :1;
//    uint8_t        B11       :1;
//    uint8_t        B12       :1;
//    uint8_t        B13       :1;
//    uint8_t        B14       :1;
//    uint8_t        B15       :1;
//  }Bit;

//}Union_Uint16Bit_t;


/*
========================================================================================================================
*【全局声明】                                          【全局声明】                                          【全局声明】
========================================================================================================================
*/
void  BSP_Init (void);

#endif                       
