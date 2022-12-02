/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: main.c 
**
**    功能描述:
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
**    修改记录:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/


/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "System.h"
#include "bsp.h"

/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/
#define  WDT_EN               (!SYSTEM_DEBUGING)         /*看门狗使能控制。 1：使能   0：不使能*/

#define  DEBUG_INFO_EN        0                          /*调试信息控制。   1：使能   0：不使能*/

#define  DEBUG_BSP_EN         0                          /*直接单独调试控制底层驱动电路。 1：使能   0：不使能 */



/*
========================================================================================================================
*【本地数据类型定义】                              【本地数据类型定义】                              【本地数据类型定义】
========================================================================================================================
*/


/*
************************************************************************************************************************
* 类型定义 :  直接单独调试控制底层驱动电路                                                                                                      
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
#endif   /*结束 "if(DEBUG_BSP_EN)" */
   

/*
========================================================================================================================
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                          【变量定义 & 各种声明】    
========================================================================================================================
*/
#if(DEBUG_BSP_EN)
DebugBsp_t DebugBsp;
#endif   /*结束 "if(DEBUG_BSP_EN)" */

/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/


#if(DEBUG_BSP_EN)


void TmrHandle(Ticker_t ExePeriod);

#define  COUNT_BUF_NUM   3
static Ticker_t TickCount[COUNT_BUF_NUM];

const ESF_TmrExeFunc_t  TmrExeFuncTab[] = 
{
  /*执行函数               执行周期(ms)       时间计数变量*/
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
* 函数名称 : main                                                                                                         
* 功能描述 : 直接单独调试控制底层驱动电路的主函数                                                                                               
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 宏 DEBUG_BSP_EN 不为 0 时有效。                                                                                                         
************************************************************************************************************************
*/ 
uint8_t test;
//uint8_t cc[] = "123";
int main(void)
{
  uint32_t i,k;
  uint8_t g_tipString[] =
    "Lpuart functional API interrupt example\r\nBoard receives characters then sends them out\r\nNow please input:\r\n";
  
  BSP_Init();                                           /* 板级支持包初始化 */ 
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
    /*看是否有调试信息要输出*/
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
* 函数名称 : main                                                                                                         
* 功能描述 : 应用程序实际的主函数                                                                                               
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
int main(void)
{
  System_Init();                                           /* 系统初始化 */ 
  
  #if(WDT_EN)
    BSP_WatchDog_Init();
  #endif
  
	GOTO_APP();
  while(1)
  {
    #if(WDT_EN)
      BSP_WatchDog_Feed();                                /* 喂狗 */
    #endif
    
    System_Handle();
  }
}

#endif   /*结束 "if(DEBUG_BSP_EN)" */
