/*
******************************************************************************* 
**    文件名称：CommonLib.h 
**
**    功能描述:
**
**    项目名称：
**
**    平台信息：
**
**    作    者：Hzy
**
**    版    本：V1.0
**
**    其他说明:
**
**    修改记录:  --------------------------------------------------------------
**               2015.08
**               完成 V1.0 版本
******************************************************************************* 
*/ 

#ifndef COMMONLIB_C
#define COMMONLIB_C

#include <stdio.h>
#include <string.h>
#include "bsp.h"


/*︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻
**	              常用宏定义 
︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼*/

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


/*计算表格大小（表格包含的条目总数）--------------------------*/ 
#ifndef  TAB_NUM
#define  TAB_NUM(tab)              (sizeof(tab)/sizeof(tab[0]))
#endif
#ifndef  TAB_ISUM
#define  TAB_ISUM(tab)              (sizeof(tab)/sizeof(tab[0]))
#endif


/*通用的宏----------------------------------------------------*/
#ifndef  MEM_IDLE
#define  MEM_IDLE                  0u           /*内存空闲，可以释放了*/          
#endif
#ifndef  MEM_USE
#define  MEM_USE                   1u           /*内存使用中，还不能释放*/
#endif


#ifndef  BEFORE
#define  BEFORE                    0u           /*前*/
#endif
#ifndef  AFTER
#define  AFTER                     1u           /*后*/
#endif

//#ifndef  DISABLE
//#define  DISABLE                   0u           /*不使能*/
//#endif
//#ifndef  ENABLE
//#define  ENABLE                    1u           /*使能*/
//#endif

#ifndef  OFF
#define  OFF                       0u           /*关*/
#endif
#ifndef  ON
#define  ON                        1u           /*开*/
#endif

#ifndef  CLOSE
#define  CLOSE                     0u           /*关*/
#endif
#ifndef  OPEN
#define  OPEN                      1u           /*开*/
#endif

#ifndef  ERROR
#define  ERROR                     1u           /*错误*/
#endif
#ifndef  CORRECT
#define  CORRECT                   0u           /*正确*/
#endif

#ifndef  FALSE
#define  FALSE                     0u           /*假*/
#endif
#ifndef  TRUE
#define  TRUE                      1u           /*真*/
#endif

#ifndef  FAIL
#define  FAIL                      1u           /*失败*/
#endif
#ifndef  SUCCESS
#define  SUCCESS                   0u           /*成功*/
#endif

#ifndef  FAULT
#define  FAULT                     1u           /*故障*/
#endif
#ifndef  NORMAL
#define  NORMAL                    0u           /*正常*/
#endif


#ifndef  ASCII_NULL
#define  ASCII_NULL                (int8_t)0    /*空字符*/
#endif


#ifndef  P_NULL
#define  P_NULL                    (void*)0     /*空指针*/
#endif
#ifndef  PNULL
#define  PNULL                     (void*)0     /*空指针*/
#endif
#ifndef  NULL
#define  NULL                      (void*)0     /*空指针*/
#endif
#ifndef  null
#define  null                      (void*)0     /*空指针*/
#endif


/*︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻
**	              二进制表示宏定义
** keil不支持直接使用二进制数据。这里用宏定义代替。
** 注意：★ 只能表示最多 8 位 的二进制数据。★
︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼*/
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


/*︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻
**	                 临界区处理函数       
︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼*/
void Critical_Enter(void);
void Critical_Exit(void);



/*︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻
**	             Log 调试信息的跟踪输出
︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼*/
void  Log_OutPut(void);

//#define  LOG_LEVEL_OFF      0x00   /*信息等级   关闭*/
//#define  LOG_LEVEL_INFO     0x01   /*信息等级   信息输出*/
//#define  LOG_LEVEL_DEBUG    0x02   /*信息等级   调试输出*/
//#define  LOG_LEVEL_ERROR    0x04   /*信息等级   错误输出*/

//#define  LOG_LEVEL     (LOG_LEVEL_DEBUG & LOG_LEVEL_INFO)	/*定义要使用的等级*/
//#define  LOG_INFO(x)   ((LOG_LEVEL & LOG_LEVEL_INFO)   ? Log_Output(x) : (void)0)
//#define  LOG_DEBUG(x)  ((LOG_LEVEL & LOG_LEVEL_DEBUG)  ? Log_Output(x) : (void)0)
//#define  LOG_ERROR(x)  ((LOG_LEVEL & LOG_LEVEL_ERROR)  ? Log_Output(x) : (void)0)

   
/*︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻
**            
︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼*/
uint8_t  HexToAscii(uint8_t hex);


/*︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻
**             crc16半字查表法
︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼*/
uint16_t CRC16_Cal(uint8_t *pdata, uint32_t len, uint16_t crc); 
uint8_t  CRC16_Check(uint8_t *pdata, uint32_t len); 


/*︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻
**               累加和校验
︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼*/
uint8_t CumulativeSum_Cal(uint8_t *pdata, uint32_t len); 
uint8_t CumulativeSum_Check(uint8_t *pdata, uint32_t len); 


/*︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻
**               大小端字节数据反转
** 说明：大端格式 -- 低地址存放高字节数据，高地址存放低字节数据。
**       小端格式 -- 低地址存放低字节数据，高地址存放高字节数据。      
︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼*/
uint16_t Swap2Byte(uint16_t n);
uint32_t Swap4Byte(uint32_t n);


/*︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻
**                折半查找算法
︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼*/
#define  INDEX_NO_MATCH  0xFFFF

uint16_t BinarySearch(uint16_t  SearchID,  uint16_t TabNum, uint16_t (*pGetMatchID)(uint16_t index));


/*︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻︻
**                 暂停功能 处理
︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼︼*/
void PAUSE_ON(uint8_t *pOnOff, uint8_t ValidBit, void(*pPauseOn)());
void PAUSE_OFF(uint8_t *pOnOff, uint8_t ValidBit, void(*pPauseOff)());


#endif
