/*
******************************************************************************* 
**    �ļ����ƣ�CommonLib.h 
**
**    ��������:
**
**    ��Ŀ���ƣ�
**
**    ƽ̨��Ϣ��
**
**    ��    �ߣ�Hzy
**
**    ��    ����V1.0
**
**    ����˵��:
**
**    �޸ļ�¼:  --------------------------------------------------------------
**               2015.08
**               ��� V1.0 �汾
******************************************************************************* 
*/ 

#ifndef COMMONLIB_C
#define COMMONLIB_C

#include <stdio.h>
#include <string.h>
#include "bsp.h"


/*���������������������������������
**	              ���ú궨�� 
���������������������������������*/

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
#ifndef  TAB_ISUM
#define  TAB_ISUM(tab)              (sizeof(tab)/sizeof(tab[0]))
#endif


/*ͨ�õĺ�----------------------------------------------------*/
#ifndef  MEM_IDLE
#define  MEM_IDLE                  0u           /*�ڴ���У������ͷ���*/          
#endif
#ifndef  MEM_USE
#define  MEM_USE                   1u           /*�ڴ�ʹ���У��������ͷ�*/
#endif


#ifndef  BEFORE
#define  BEFORE                    0u           /*ǰ*/
#endif
#ifndef  AFTER
#define  AFTER                     1u           /*��*/
#endif

//#ifndef  DISABLE
//#define  DISABLE                   0u           /*��ʹ��*/
//#endif
//#ifndef  ENABLE
//#define  ENABLE                    1u           /*ʹ��*/
//#endif

#ifndef  OFF
#define  OFF                       0u           /*��*/
#endif
#ifndef  ON
#define  ON                        1u           /*��*/
#endif

#ifndef  CLOSE
#define  CLOSE                     0u           /*��*/
#endif
#ifndef  OPEN
#define  OPEN                      1u           /*��*/
#endif

#ifndef  ERROR
#define  ERROR                     1u           /*����*/
#endif
#ifndef  CORRECT
#define  CORRECT                   0u           /*��ȷ*/
#endif

#ifndef  FALSE
#define  FALSE                     0u           /*��*/
#endif
#ifndef  TRUE
#define  TRUE                      1u           /*��*/
#endif

#ifndef  FAIL
#define  FAIL                      1u           /*ʧ��*/
#endif
#ifndef  SUCCESS
#define  SUCCESS                   0u           /*�ɹ�*/
#endif

#ifndef  FAULT
#define  FAULT                     1u           /*����*/
#endif
#ifndef  NORMAL
#define  NORMAL                    0u           /*����*/
#endif


#ifndef  ASCII_NULL
#define  ASCII_NULL                (int8_t)0    /*���ַ�*/
#endif


#ifndef  P_NULL
#define  P_NULL                    (void*)0     /*��ָ��*/
#endif
#ifndef  PNULL
#define  PNULL                     (void*)0     /*��ָ��*/
#endif
#ifndef  NULL
#define  NULL                      (void*)0     /*��ָ��*/
#endif
#ifndef  null
#define  null                      (void*)0     /*��ָ��*/
#endif


/*���������������������������������
**	              �����Ʊ�ʾ�궨��
** keil��֧��ֱ��ʹ�ö��������ݡ������ú궨����档
** ע�⣺�� ֻ�ܱ�ʾ��� 8 λ �Ķ��������ݡ���
���������������������������������*/
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


/*���������������������������������
**	                 �ٽ���������       
���������������������������������*/
void Critical_Enter(void);
void Critical_Exit(void);



/*���������������������������������
**	             Log ������Ϣ�ĸ������
���������������������������������*/
void  Log_OutPut(void);

//#define  LOG_LEVEL_OFF      0x00   /*��Ϣ�ȼ�   �ر�*/
//#define  LOG_LEVEL_INFO     0x01   /*��Ϣ�ȼ�   ��Ϣ���*/
//#define  LOG_LEVEL_DEBUG    0x02   /*��Ϣ�ȼ�   �������*/
//#define  LOG_LEVEL_ERROR    0x04   /*��Ϣ�ȼ�   �������*/

//#define  LOG_LEVEL     (LOG_LEVEL_DEBUG & LOG_LEVEL_INFO)	/*����Ҫʹ�õĵȼ�*/
//#define  LOG_INFO(x)   ((LOG_LEVEL & LOG_LEVEL_INFO)   ? Log_Output(x) : (void)0)
//#define  LOG_DEBUG(x)  ((LOG_LEVEL & LOG_LEVEL_DEBUG)  ? Log_Output(x) : (void)0)
//#define  LOG_ERROR(x)  ((LOG_LEVEL & LOG_LEVEL_ERROR)  ? Log_Output(x) : (void)0)

   
/*���������������������������������
**            
���������������������������������*/
uint8_t  HexToAscii(uint8_t hex);


/*���������������������������������
**             crc16���ֲ��
���������������������������������*/
uint16_t CRC16_Cal(uint8_t *pdata, uint32_t len, uint16_t crc); 
uint8_t  CRC16_Check(uint8_t *pdata, uint32_t len); 


/*���������������������������������
**               �ۼӺ�У��
���������������������������������*/
uint8_t CumulativeSum_Cal(uint8_t *pdata, uint32_t len); 
uint8_t CumulativeSum_Check(uint8_t *pdata, uint32_t len); 


/*���������������������������������
**               ��С���ֽ����ݷ�ת
** ˵������˸�ʽ -- �͵�ַ��Ÿ��ֽ����ݣ��ߵ�ַ��ŵ��ֽ����ݡ�
**       С�˸�ʽ -- �͵�ַ��ŵ��ֽ����ݣ��ߵ�ַ��Ÿ��ֽ����ݡ�      
���������������������������������*/
uint16_t Swap2Byte(uint16_t n);
uint32_t Swap4Byte(uint32_t n);


/*���������������������������������
**                �۰�����㷨
���������������������������������*/
#define  INDEX_NO_MATCH  0xFFFF

uint16_t BinarySearch(uint16_t  SearchID,  uint16_t TabNum, uint16_t (*pGetMatchID)(uint16_t index));


/*���������������������������������
**                 ��ͣ���� ����
���������������������������������*/
void PAUSE_ON(uint8_t *pOnOff, uint8_t ValidBit, void(*pPauseOn)());
void PAUSE_OFF(uint8_t *pOnOff, uint8_t ValidBit, void(*pPauseOff)());


#endif
