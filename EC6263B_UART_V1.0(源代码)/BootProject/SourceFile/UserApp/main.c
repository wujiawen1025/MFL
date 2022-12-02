/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: main.c 
**
**    ��������:
**
**    ��    ˾���ɷ�������
**
**    ��Ŀ���ƣ�
**
**    ƽ̨��Ϣ��
**
**    ��    �ߣ�Hzy
**
**    ����˵��:
**
**    �޸ļ�¼:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/


/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "System.h"
#include "bsp.h"

/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/
#define  WDT_EN               (!SYSTEM_DEBUGING)         /*���Ź�ʹ�ܿ��ơ� 1��ʹ��   0����ʹ��*/

#define  DEBUG_INFO_EN        0                          /*������Ϣ���ơ�   1��ʹ��   0����ʹ��*/

#define  DEBUG_BSP_EN         0                          /*ֱ�ӵ������Կ��Ƶײ�������·�� 1��ʹ��   0����ʹ�� */



/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/


/*
************************************************************************************************************************
* ���Ͷ��� :  ֱ�ӵ������Կ��Ƶײ�������·                                                                                                      
************************************************************************************************************************
*/
#if(DEBUG_BSP_EN)
typedef struct
{
  uint8_t         XOnOff;
  uint8_t         XDirection;              /* XMOTOR_DIRECTION_RIGHT  XMOTOR_DIRECTION_LEFT */
  uint16_t        XPWM;
  uint8_t         XPosition;
  
  uint8_t         YOnOff;
  uint8_t         YDirection;              /* YMOTOR_DIRECTION_UP  YMOTOR_DIRECTION_DOWN */
  uint16_t        YPWM;
  uint8_t         YPosition;
  
  uint8_t         ZOnOff;
  uint8_t         ZDirection;              /* ZMOTOR_DIRECTION_BACK    ZMOTOR_DIRECTION_FRONT */
  uint16_t        ZPWM;
  uint8_t         ZPosition;
  
  uint8_t         TCSOnOff;
  uint16_t        TCSDirection;
  uint8_t         TCSPWM;
  
  uint8_t         BackSpikeOnOff;
  uint8_t         BackSpikeDirection;      /* BACKSPIKE_DIRECTION_UP  BACKSPIKE_DIRECTION_DOWN */
  uint16_t        BackSpikePWM;
  uint8_t         BackSpikePosition;

  uint8_t         FeetSpikeOnOff;
  uint8_t         FeetSpikeDirection;      /* FEETSPIKE_DIRECTION_UP  FEETSPIKE_DIRECTION_DOWN */
  uint16_t        FeetSpikePWM;
  uint8_t         FeetSpikePosition;

  uint8_t         ZeroSpikeOnOff;
  uint8_t         ZeroSpikeDirection;      /*  */
  uint16_t        ZeroSpikePWM;
  uint8_t         ZeroSpikePosition;
 

  uint8_t         PumpSw;
  union
  {
    uint8_t    All;
    struct
    {
      uint8_t  b0     :1;
      uint8_t  b1     :1;
      uint8_t  b2     :1;
      uint8_t  b3     :1;
      uint8_t  b4     :1;
      uint8_t  b5     :1;
      uint8_t  b6     :1;
      uint8_t  b7     :1;
    }Bit;
  }GasPart1;
  union
  {
    uint8_t    All;
    struct
    {
      uint8_t  b0     :1;
      uint8_t  b1     :1;
      uint8_t  b2     :1;
      uint8_t  b3     :1;
      uint8_t  b4     :1;
      uint8_t  b5     :1;
      uint8_t  b6     :1;
      uint8_t  b7     :1;
    }Bit;
  }GasPart2;

}DebugBsp_t;
#endif   /*���� "if(DEBUG_BSP_EN)" */
   

/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/
#if(DEBUG_BSP_EN)
DebugBsp_t DebugBsp;
#endif   /*���� "if(DEBUG_BSP_EN)" */

/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/


#if(DEBUG_BSP_EN)


void TmrHandle(Ticker_t ExePeriod);

#define  COUNT_BUF_NUM   3
static Ticker_t TickCount[COUNT_BUF_NUM];

const ESF_TmrExeFunc_t  TmrExeFuncTab[] = 
{
  /*ִ�к���               ִ������(ms)       ʱ���������*/
  {TmrHandle,          100,            &TickCount[0]}
};

#define  TMR_EXE_FUNC_TAB_NUM     TAB_NUM(TmrExeFuncTab)


void TmrHandle(Ticker_t ExePeriod)
{
  static  Ticker_t t;
  static  uint16_t pwm = 0;

  t++;
  if(t < 2)
  {
    pwm = 0;
//    BSP_IO_SetOutput_BackSpikeCtrl(0, 0, pwm);
//    BSP_IO_SetOutput_FeetSpikeCtrl(0, 0, pwm);
  }
  else
  {
     t = 0;
  }
}

/*
************************************************************************************************************************
* �������� : main                                                                                                         
* �������� : ֱ�ӵ������Կ��Ƶײ�������·��������                                                                                               
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : �� DEBUG_BSP_EN ��Ϊ 0 ʱ��Ч��                                                                                                         
************************************************************************************************************************
*/ 
uint8_t test;
//uint8_t cc[] = "123";
int main(void)
{
  uint32_t i,k;
  uint8_t g_tipString[] =
    "Lpuart functional API interrupt example\r\nBoard receives characters then sends them out\r\nNow please input:\r\n";
  
  BSP_Init();                                           /* �弶֧�ְ���ʼ�� */ 
    BSP_WatchDog_Init();
  DebugBsp.XOnOff             = 0;
  DebugBsp.XDirection         = 0;             
  DebugBsp.XPWM               = 50;
  
  DebugBsp.YOnOff             = 0;
  DebugBsp.YDirection         = 0;             
  DebugBsp.YPWM               = 0;
  
  DebugBsp.ZOnOff             = 0;
  DebugBsp.ZDirection         = 0;             
  DebugBsp.ZPWM               = 0;
  
  DebugBsp.TCSOnOff           = 0;
  DebugBsp.TCSDirection       = 0;
  DebugBsp.TCSPWM             = 0;
  
  DebugBsp.BackSpikeOnOff     = 0;
  DebugBsp.BackSpikeDirection = 0;     
  DebugBsp.BackSpikePWM       = 0;

  DebugBsp.FeetSpikeOnOff     = 0;
  DebugBsp.FeetSpikeDirection = 0;     
  DebugBsp.FeetSpikePWM       = 0;

  DebugBsp.ZeroSpikeOnOff     = 0;
  DebugBsp.ZeroSpikeDirection = 0;     
  DebugBsp.ZeroSpikePWM       = 0;
  DebugBsp.PumpSw = 1;
                          
//  BSP_FLEXIO_UART_RegRxByteCB(BSP_UART_Port3, Uart_Test);    
  test=0;
  printf("Start\r\n");
  
  while(1)
  {
    BSP_WatchDog_Feed();
    /*���Ƿ��е�����ϢҪ���*/
    Log_OutPut();
    
//    ESF_TmrExeFuncScheduling(TmrExeFuncTab, TMR_EXE_FUNC_TAB_NUM);
    if(test==1)
    {
//      BSP_UART_TxData(BSP_UART_Port1, g_tipString, sizeof(g_tipString) / sizeof(g_tipString[0]));
      printf("123\r\n");
      test=0;
    }
    BSP_PWMTmr_SetOutput_LED(DebugBsp.XPWM);
//    gpio_bit_write(GPIOD, GPIO_PIN_12, 0);
    for(k=0;k<12000;k++)
    {
      ;
    }  
//    gpio_bit_write(GPIOD, GPIO_PIN_12, 1);

  }
}

#else

/*
************************************************************************************************************************
* �������� : main                                                                                                         
* �������� : Ӧ�ó���ʵ�ʵ�������                                                                                               
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
int main(void)
{
  System_Init();                                           /* ϵͳ��ʼ�� */ 
  
  #if(WDT_EN)
    BSP_WatchDog_Init();
  #endif
  
	GOTO_APP();
  while(1)
  {
    #if(WDT_EN)
      BSP_WatchDog_Feed();                                /* ι�� */
    #endif
    
    System_Handle();
  }
}

#endif   /*���� "if(DEBUG_BSP_EN)" */
