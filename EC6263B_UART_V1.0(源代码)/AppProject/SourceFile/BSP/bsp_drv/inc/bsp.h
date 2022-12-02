/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����:                                                                                                         
**
**    ��������:                                                                                                        
**
**    ��    ˾��                                                                                                        
**
**    ��Ŀ���ƣ�                                                                                                        
**
**    ƽ̨��Ϣ��                                                                                                        
**
**    ��    �ߣ�Hzy                                                                                                     
**
**    ����˵��:                                                                                                       
**
**    �޸ļ�¼:  
**
========================================================================================================================
========================================================================================================================
*/
#ifndef  _BSP_H_
#define  _BSP_H_

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
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
*��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿                                       ��ȫ�ֺ궨�塿
========================================================================================================================
*/
#define  BSP_DisInttrupt()         __set_PRIMASK(1)   /*���жϣ��ص����п����ε��쳣��ֻʣ��NMI��Ӳ fault������Ӧ��*/
#define  BSP_EnInttrupt()          __set_PRIMASK(0)   /*���ж�*/

#define  BSP_SystemReset()         NVIC_SystemReset() /*��λϵͳ*/ 


/*λ����------------------------------------------------------*/
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


/*�������С������������Ŀ������--------------------------*/ 
#ifndef  TAB_NUM
#define  TAB_NUM(tab)              (sizeof(tab)/sizeof(tab[0]))
#endif
#ifndef  TAB_ISUM                    /*tab item sum �����ľ����*/
#define  TAB_ISUM(tab)              (sizeof(tab)/sizeof(tab[0]))
#endif


/*ͨ�õĺ�----------------------------------------------------*/
//#ifndef  DISABLE
//#define  DISABLE                   0u                 /*��ʹ��*/ /*stm32�е�ͷ�ļ�����ص�ö�ٶ��壬�����ע�͵�*/
//#endif
//#ifndef  ENABLE
//#define  ENABLE                    1u                 /*ʹ��*/ /*stm32�е�ͷ�ļ�����ص�ö�ٶ��壬�����ע�͵�*/
//#endif

#ifndef  OFF
#define  OFF                       0u                 /*��*/
#endif
#ifndef  ON
#define  ON                        1u                 /*��*/
#endif

#ifndef  CLOSE
#define  CLOSE                     0u                 /*��*/
#endif
#ifndef  OPEN
#define  OPEN                      1u                 /*��*/
#endif

#ifndef  ERROR
#define  ERROR                     1u                 /*����*/
#endif
#ifndef  CORRECT
#define  CORRECT                   0u                 /*��ȷ*/
#endif

#ifndef  FALSE
#define  FALSE                     0u                 /*��*/
#endif
#ifndef  TRUE
#define  TRUE                      1u                 /*��*/
#endif

#ifndef  FAIL
#define  FAIL                      1u                 /*ʧ��*/
#endif
#ifndef  SUCCESS
#define  SUCCESS                   0u                 /*�ɹ�*/
#endif

#ifndef  FAULT
#define  FAULT                     1u                 /*����*/
#endif
#ifndef  NORMAL
#define  NORMAL                    0u                 /*����*/
#endif


#ifndef  ASCII_NULL
#define  ASCII_NULL                (int8_t)0          /*���ַ�*/
#endif


#ifndef  P_NULL
#define  P_NULL                    (void*)0           /*��ָ��*/
#endif
#ifndef  PNULL
#define  PNULL                     (void*)0           /*��ָ��*/
#endif
#ifndef  NULL
#define  NULL                      (void*)0           /*��ָ��*/
#endif
#ifndef  null
#define  null                      (void*)0           /*��ָ��*/
#endif

/*
===============================================================================
**	              �����Ʊ�ʾ�궨��
** keil��֧��ֱ��ʹ�ö��������ݡ������ú궨����档
** ע�⣺�� ֻ�ܱ�ʾ��� 8 λ �Ķ��������ݡ���
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
*��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿                              ��ȫ���������Ͷ��塿
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
*��ȫ��������                                          ��ȫ��������                                          ��ȫ��������
========================================================================================================================
*/
void  BSP_Init (void);

#endif                       
