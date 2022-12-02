/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: bsp_gpio.c                                                                                                       
**
**    功能描述: 通用输入输出IO口                                                                                                        
**
**    公    司：                                                                                                        
**
**    项目名称：                                                                                                        
**
**    平台信息：                                                                                                        
**
**    作    者：LZH                                                                                                     
**
**    其他说明:                                                                                                        
**
**    修改记录:  
**
========================================================================================================================
========================================================================================================================
*/
/*
========================================================================================================================
* 【文件包含】                                         【文件包含】                                          【文件包含】
========================================================================================================================
*/
#include "bsp_gpio.h"          
#include "CommonLib.h"
//#include "IO.h"



/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/




/*
========================================================================================================================
*【本地数据类型定义】                              【本地数据类型定义】                              【本地数据类型定义】
========================================================================================================================
*/
void BSP_IO_TimerTrigReadInputInit(void);

//static uint8_t ERPSwState;
/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/

/**
 *------------------------------------
 * PGIO / AFIO Pin Alter Function Remap
 *------------------------------------
 */
#define GPIO_USART2_DEFAULT_REMAP		((uint32_t)0x00140000U)		/*!< USART2 default remapping */
#define GPIO_USART2_NOP_REMAP			((uint32_t)0x00140020U)		/*!< USART2 nop remapping */
#define GPIO_TIMER0_DEFAULT_REMAP		((uint32_t)0x00160000U)		/*!< TIMER0 default remapping */
#define GPIO_TIMER0_NOP_REMAP			((uint32_t)0x00160080U)		/*!< TIMER0 nop remapping */
#define GPIO_TIMER1_DEFAULT_REMAP		((uint32_t)0x00180000U)		/*!< TIMER1 default remapping */
#define GPIO_TIMER2_DEFAULT_REMAP		((uint32_t)0x001A0000U)		/*!< TIMER2 default remapping */
#define GPIO_TIMER2_NOP_REMAP			((uint32_t)0x001A0400U)		/*!< TIMER2 nop remapping */
#define GPIO_SWJ_DEFAULT_REMAP			((uint32_t)0x00300000U)		/*!< SWJ default remapping */
#define GPIO_CTC_DEFAULT_REMAP			((uint32_t)0x801B0000U)		/*!< CTC default remapping */

/*!<
 * PB3/PB4/PA15 remapping
 * 
 * 芯片复位默认是JTAG-DP+SW-DP模式，此时PB3为JTDO/PB4为NJTRST/PA5为JTDI口
 * 因为板子用的是SWD模式，需要调整配置为JTAG-DP关闭，SW-DP开启。此时PB3/PB4/PA15为普通IO口。			
 * 			
 */
void drv_gpio_remap_PB3_PB4_PA15_TO_GPIO(void){gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP,ENABLE);}

/*!<
 * USART0 remapping
 * 
 * [default]drv_gpio_remap_USART0_TX_PA9_RX_PA10
 * 			| USART0_TX/PA9, USART0_RX/PA10 |
 * [-------]drv_gpio_remap_USART0_TX_PB6_RX_PB7
 * 			| USART0_TX/PB6, USART0_RX/PB7  |
 */
void drv_gpio_remap_USART0_TX_PA9_RX_PA10(void){gpio_pin_remap_config(GPIO_USART0_REMAP, DISABLE);}
void drv_gpio_remap_USART0_TX_PB6_RX_PB7(void){gpio_pin_remap_config(GPIO_USART0_REMAP, ENABLE);}
/*!<
 * USART1 remapping
 * 
 * [default]drv_gpio_remap_USART1_TX_PA2_RX_PA3
 * 			| USART1_CTS/PA0, USART1_RTS/PA1, USART1_TX/PA2, USART1_RX /PA3, USART1_CK/PA4 |
 * [-------]drv_gpio_remap_USART1_TX_PD5_RX_PD6
 * 			| USART1_CTS/PD3, USART1_RTS/PD4, USART1_TX/PD5, USART1_RX /PD6, USART1_CK/PD7 |
 */
void drv_gpio_remap_USART1_TX_PA2_RX_PA3(void){gpio_pin_remap_config(GPIO_USART1_REMAP, DISABLE);}
void drv_gpio_remap_USART1_TX_PD5_RX_PD6(void){gpio_pin_remap_config(GPIO_USART1_REMAP, ENABLE);}
/*!<
 * USART2 remapping
 * 
 * [default]drv_gpio_remap_USART2_TX_PB10_RX_PB11
 * 			| USART2_TX/PB10, USART2_RX /PB11, USART2_CK/PB12,USART2_CTS/PB13, USART2_RTS/PB14 |
 * [-------]drv_gpio_remap_USART2_TX_PC10_RX_PC11
 * 			| USART2_TX/PC10, USART2_RX /PC11, USART2_CK/PC12,USART2_CTS/PB13, USART2_RTS/PB14 |
 * [-------]drv_gpio_remap_USART2_TX_PD8_RX_PD9
 * 			| USART2_TX/PD8 , USART2_RX /PD9 , USART2_CK/PD10,USART2_CTS/PD11, USART2_RTS/PD12 |
 * [-------]drv_gpio_remap_USART2_NOP
 */
void drv_gpio_remap_USART2_TX_PB10_RX_PB11(void){gpio_pin_remap_config(GPIO_USART2_DEFAULT_REMAP, ENABLE);}
void drv_gpio_remap_USART2_TX_PC10_RX_PC11(void){gpio_pin_remap_config(GPIO_USART2_PARTIAL_REMAP, ENABLE);}
void drv_gpio_remap_USART2_TX_PD8_RX_PD9(void){gpio_pin_remap_config(GPIO_USART2_FULL_REMAP, ENABLE);}
/*!<
 * TIMER0 remapping
 * 
 * [default]drv_gpio_remap_TIMER0_DEFAULT_PA8_9_10_11_12_PB12_13_14_15
 * 			| TIMER0_ETI/PA12,TIMER0_CH0/PA8,TIMER0_CH1/PA9 ,TIMER0_CH2/PA10,TIMER0_CH3/PA11,TIMER0_BKIN/PB12,TIMER0_CH0_ON/PB13,TIMER0_CH1_ON/PB14,TIMER0_CH2_ON/PB15 |
 * [-------]drv_gpio_remap_TIMER0_PA6_7_8_9_10_11_12_PB0_1
 * 			| TIMER0_ETI/PA12,TIMER0_CH0/PA8,TIMER0_CH1/PA9 ,TIMER0_CH2/PA10,TIMER0_CH3/PA11,TIMER0_BKIN/PA6 ,TIMER0_CH0_ON/PA7 ,TIMER0_CH1_ON/PB0 ,TIMER0_CH2_ON/PB1  |
 * [-------]drv_gpio_remap_TIMER0_PE7_8_9_10_11_12_13_14_15
 * 			| TIMER0_ETI/PE7 ,TIMER0_CH0/PE9,TIMER0_CH1/PE11,TIMER0_CH2/PE13,TIMER0_CH3/PE14,TIMER0_BKIN/PE15,TIMER0_CH0_ON/PE8 ,TIMER0_CH1_ON/PE10,TIMER0_CH2_ON/PE12 |
 * [-------]drv_gpio_remap_TIMER0_NOP
 */
void drv_gpio_remap_TIMER0_DEFAULT_PA8_9_10_11_12_PB12_13_14_15(void){gpio_pin_remap_config(GPIO_TIMER0_DEFAULT_REMAP, ENABLE);}
void drv_gpio_remap_TIMER0_PA6_7_8_9_10_11_12_PB0_1(void){gpio_pin_remap_config(GPIO_TIMER0_PARTIAL_REMAP, ENABLE);}
void drv_gpio_remap_TIMER0_NOP(void){gpio_pin_remap_config(GPIO_TIMER0_NOP_REMAP, ENABLE);}
void drv_gpio_remap_TIMER0_PE7_8_9_10_11_12_13_14_15(void){gpio_pin_remap_config(GPIO_TIMER0_FULL_REMAP, ENABLE);}
/*!<
 * TIMER1 remapping
 * 
 * [default]drv_gpio_remap_TIMER1_DEFAULT_PA0_1_2_3
 * 			| TIMER1_CH0/TIMER1_ETI/PA0 ,TIMER1_CH1/PA1,TIMER1_CH2/PA2 ,TIMER1_CH3/PA3  |
 * [-------]drv_gpio_remap_TIMER1_PA2_3_15_PB3
 * 			| TIMER1_CH0/TIMER1_ETI/PA15,TIMER1_CH1/PB3,TIMER1_CH2/PA2 ,TIMER1_CH3/PA3  |
 * [-------]drv_gpio_remap_TIMER1_PA0_1_PB10_11
 * 			| TIMER1_CH0/TIMER1_ETI/PA0 ,TIMER1_CH1/PA1,TIMER1_CH2/PB10,TIMER1_CH3/PB11 |
 * [-------]drv_gpio_remap_TIMER1_PA15_PB3_10_11
 * 			| TIMER1_CH0/TIMER1_ETI/PA15,TIMER1_CH1/PB3,TIMER1_CH2/PB10,TIMER1_CH3/PB11 |
 */
void drv_gpio_remap_TIMER1_DEFAULT_PA0_1_2_3(void){gpio_pin_remap_config(GPIO_TIMER1_DEFAULT_REMAP, ENABLE);}
void drv_gpio_remap_TIMER1_PA2_3_15_PB3(void){gpio_pin_remap_config(GPIO_TIMER1_PARTIAL_REMAP0, ENABLE);}
void drv_gpio_remap_TIMER1_PA0_1_PB10_11(void){gpio_pin_remap_config(GPIO_TIMER1_PARTIAL_REMAP1, ENABLE);}
void drv_gpio_remap_TIMER1_PA15_PB3_10_11(void){gpio_pin_remap_config(GPIO_TIMER1_FULL_REMAP, ENABLE);}
/*!<
 * TIMER2 remapping
 * 
 * [default]drv_gpio_remap_TIMER2_DEFAULT_PA6_7_PB0_1
 * 			| TIMER2_CH0/PA6,TIMER2_CH1/PA7,TIMER2_CH2/PB0,TIMER2_CH3/PB1 |
 * [-------]drv_gpio_remap_TIMER2_PB0_1_4_5
 * 			| TIMER2_CH0/PB4,TIMER2_CH1/PB5,TIMER2_CH2/PB0,TIMER2_CH3/PB1 |
 * [-------]drv_gpio_remap_TIMER2_PC6_7_8_9
 * 			| TIMER2_CH0/PC6,TIMER2_CH1/PC7,TIMER2_CH2/PC8,TIMER2_CH3/PC9 |
 * [-------]drv_gpio_remap_TIMER2_NOP
 */
void drv_gpio_remap_TIMER2_DEFAULT_PA6_7_PB0_1(void){gpio_pin_remap_config(GPIO_TIMER2_DEFAULT_REMAP, ENABLE);}
void drv_gpio_remap_TIMER2_NOP(void){gpio_pin_remap_config(GPIO_TIMER2_NOP_REMAP, ENABLE);}
void drv_gpio_remap_TIMER2_PB0_1_4_5(void){gpio_pin_remap_config(GPIO_TIMER2_PARTIAL_REMAP, ENABLE);}
void drv_gpio_remap_TIMER2_PC6_7_8_9(void){gpio_pin_remap_config(GPIO_TIMER2_FULL_REMAP, ENABLE);}
/*!<
 * TIMER3 remapping
 * 
 * [default]drv_gpio_remap_TIMER3_DEFAULT_PB6_7_8_9
 * 			| TIMER3_CH0/PB6 ,TIMER3_CH1/PB7 ,TIMER3_CH2/PB8 ,TIMER3_CH3/PB9  |
 * [-------]drv_gpio_remap_TIMER3_PD12_13_14_15
 * 			| TIMER3_CH0/PD12,TIMER3_CH1/PD13,TIMER3_CH2/PD14,TIMER3_CH3/PD15 |
 */
void drv_gpio_remap_TIMER3_DEFAULT_PB6_7_8_9(void){gpio_pin_remap_config(GPIO_TIMER3_REMAP, DISABLE);}
void drv_gpio_remap_TIMER3_PD12_13_14_15(void){gpio_pin_remap_config(GPIO_TIMER3_REMAP, ENABLE);}

/*
************************************************************************************************************************
* 函数名称 : BSP_IO_Remap                                                                                                        
* 功能描述 : 通用IO口 引脚重映射                                                                                                        
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static __inline void BSP_IO_Remap(void)
{
	drv_gpio_remap_PB3_PB4_PA15_TO_GPIO(); /**/

  /*UART0==============================================================================*/
  drv_gpio_remap_USART0_TX_PA9_RX_PA10();                   
//  drv_gpio_remap_USART0_TX_PB6_RX_PB7
  
  /*UART1==============================================================================*/
  drv_gpio_remap_USART1_TX_PA2_RX_PA3();
//  drv_gpio_remap_USART1_TX_PD5_RX_PD6();
  
  /*UART2==============================================================================*/
  drv_gpio_remap_USART2_TX_PB10_RX_PB11();
//  drv_gpio_remap_USART2_TX_PC10_RX_PC11();
//  drv_gpio_remap_USART2_TX_PD8_RX_PD9();
  
//  drv_gpio_remap_TIMER0_PE7_8_9_10_11_12_13_14_15();
//  drv_gpio_remap_TIMER1_PA0_1_PB10_11();
//  drv_gpio_remap_TIMER2_PC6_7_8_9();
//  drv_gpio_remap_TIMER3_PD12_13_14_15();

}

/*
************************************************************************************************************************
* 函数名称 : BSP_IO_Init                                                                                                        
* 功能描述 : 通用IO口 初始化。                                                                                                        
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void  BSP_IO_Init (void)
{
  rcu_periph_clock_enable(RCU_GPIOA); //使能GPIOA时钟
  rcu_periph_clock_enable(RCU_GPIOB); //使能GPIOB时钟
  rcu_periph_clock_enable(RCU_GPIOC); //使能GPIOC时钟
  rcu_periph_clock_enable(RCU_GPIOD); //使能GPIOD时钟
  rcu_periph_clock_enable(RCU_GPIOE); //使能GPIOE时钟
  rcu_periph_clock_enable(RCU_GPIOF); //使能GPIOF时钟
  rcu_periph_clock_enable(RCU_GPIOG); //使能GPIOG时钟

  rcu_periph_clock_enable(RCU_AF);  /*!< alternate function clock */
  BSP_IO_Remap(); 

  gpio_init(GPIOA, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_9);               	/*UART0 TX*/
  gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);         	/*UART0 RX*/

  gpio_init(GPIOA, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_2);               	/*UART1 TX*/
  gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_3);          	/*UART1 RX*/
	
  gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_10);                /*UART2 TX*/
  gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);          /*UART2 RX*/

  gpio_init(GPIOC, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_10);                /*UART3 TX*/
  gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);          /*UART3 RX*/

  gpio_init(GPIOC, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_12);                /*UART4 TX*/
  gpio_init(GPIOD, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_2);          /*UART4 RX*/

  gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
  LED_IO_ON;
}





