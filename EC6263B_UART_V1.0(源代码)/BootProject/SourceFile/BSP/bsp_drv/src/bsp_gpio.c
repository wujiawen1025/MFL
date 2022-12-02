/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: bsp_gpio.c                                                                                                       
**
**    ��������: ͨ���������IO��                                                                                                        
**
**    ��    ˾��                                                                                                        
**
**    ��Ŀ���ƣ�                                                                                                        
**
**    ƽ̨��Ϣ��                                                                                                        
**
**    ��    �ߣ�LZH                                                                                                     
**
**    ����˵��:                                                                                                        
**
**    �޸ļ�¼:  
**
========================================================================================================================
========================================================================================================================
*/
/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "bsp_gpio.h"          
#include "CommonLib.h"



/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/
//#define  IO_OUTPUT_PUMP(v)                gpio_bit_write(GPIOD, GPIO_PIN_10, v)
#define  POWER_5V_SWITCH(v)               gpio_bit_write(GPIOE, GPIO_PIN_7, v)
#define  POWER_24V_SWITCH(v)              gpio_bit_write(GPIOE, GPIO_PIN_8, v)


//===================================================================================================
#define  IO_INTERRUPT_EN_VALID_COUNT              10     /*�����ж����� ����Ч״̬����ֵ ��������*/
#define  IO_INTERRUPT_DEAL_VALID_COUNT            25     /*�����жϴ��� ����Ч״̬����ֵ ��������*/


/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� :   IO���жϴ��� ��ز������ݽṹ                                                                                                       
************************************************************************************************************************
*/
typedef struct
{
  void (*pCB)(void);                /*�жϺ����ڵĻص�����*/
  
  uint8_t    HighValidStateCount;   /*�����жϴ��� �ĸߵ�ƽ��Ч״̬����ֵ*/
  uint8_t    LowValidStateCount;    /*�����ж����� �ĵ͵�ƽ��Ч״̬����ֵ*/

}IOInterruptHandle_t;


/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/
void BSP_IO_TimerTrigReadInputInit(void);

/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/

/*!<
 * USART0 remapping
 * 
 * [default]drv_gpio_remap_USART0_DEFAULT_PA9_10
 * 			| USART0_TX/PA9, USART0_RX/PA10 |
 * [-------]drv_gpio_remap_USART0_PB6_7
 * 			| USART0_TX/PB6, USART0_RX/PB7  |
 */
void drv_gpio_remap_USART0_DEFAULT_PA9_10(void){gpio_pin_remap_config(GPIO_USART0_REMAP, DISABLE);}
void drv_gpio_remap_USART0_PB6_7(void){gpio_pin_remap_config(GPIO_USART0_REMAP, ENABLE);}
/*!<
 * USART1 remapping
 * 
 * [default]drv_gpio_remap_USART1_DEFAULT_PA0_1_2_3_4
 * 			| USART1_CTS/PA0, USART1_RTS/PA1, USART1_TX/PA2, USART1_RX /PA3, USART1_CK/PA4 |
 * [-------]drv_gpio_remap_USART1_PD3_4_5_6_7
 * 			| USART1_CTS/PD3, USART1_RTS/PD4, USART1_TX/PD5, USART1_RX /PD6, USART1_CK/PD7 |
 */
void drv_gpio_remap_USART1_DEFAULT_PA0_1_2_3_4(void){gpio_pin_remap_config(GPIO_USART1_REMAP, DISABLE);}
void drv_gpio_remap_USART1_PD3_4_5_6_7(void){gpio_pin_remap_config(GPIO_USART1_REMAP, ENABLE);}
/*!<
 * USART2 remapping
 * 
 * [default]drv_gpio_remap_USART2_DEFAULT_PB10_11_12_13_14
 * 			| USART2_TX/PB10, USART2_RX /PB11, USART2_CK/PB12,USART2_CTS/PB13, USART2_RTS/PB14 |
 * [-------]drv_gpio_remap_USART2_PC10_11_12_PB13_14
 * 			| USART2_TX/PC10, USART2_RX /PC11, USART2_CK/PC12,USART2_CTS/PB13, USART2_RTS/PB14 |
 * [-------]drv_gpio_remap_USART2_PD8_9_10_11_12
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
* �������� : BSP_IO_Remap                                                                                                        
* �������� : ͨ��IO�� ������ӳ��                                                                                                        
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static __inline void BSP_IO_Remap(void)
{
  
  drv_gpio_remap_USART2_TX_PD8_RX_PD9();
  
//	drv_gpio_remap_TIMER0_PE7_8_9_10_11_12_13_14_15();
//	drv_gpio_remap_TIMER2_PC6_7_8_9();
//  drv_gpio_remap_TIMER3_PD12_13_14_15();
	
	
}

/*
************************************************************************************************************************
* �������� : BSP_IO_Init                                                                                                        
* �������� : ͨ��IO�� ��ʼ����                                                                                                        
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void  BSP_IO_Init (void)
{
  rcu_periph_clock_enable(RCU_GPIOA); //ʹ��GPIOAʱ��
  rcu_periph_clock_enable(RCU_GPIOB); //ʹ��GPIOBʱ��
  rcu_periph_clock_enable(RCU_GPIOC); //ʹ��GPIOCʱ��
  rcu_periph_clock_enable(RCU_GPIOD); //ʹ��GPIODʱ��
  rcu_periph_clock_enable(RCU_GPIOE); //ʹ��GPIOEʱ��
  rcu_periph_clock_enable(RCU_GPIOF); //ʹ��GPIOFʱ��
  rcu_periph_clock_enable(RCU_GPIOG); //ʹ��GPIOGʱ��

  rcu_periph_clock_enable(RCU_AF); /* ʹ��  */
  BSP_IO_Remap(); 

  /*J1--USART4,��J5���ô���,��ƽ��5оͨ�ſڴ�power��������,TX4-PC12,RX4-PD2*/
//  gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);               	/*UART4 TX*/
//  gpio_init(GPIOD, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_2);          	/*UART4 RX*/
//  gpio_init(GPIOD, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, GPIO_PIN_0);          					/*POWER*/ 
	
  /*J2--USART3,TX3-PC10,RX3-PC11*/
//  gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);               	/*UART3 TX*/
//  gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_11);         	/*UART3 RX*/
//	
  /*J3--����ɫ��,TM3_CH2-PD14,TM3_CH1-PD13,TM3_CH0-PD12*/
//  gpio_init(GPIOD, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_14);               	/*TM3_CH2-PD14*/
//  gpio_init(GPIOD, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);               	/*TM3_CH1-PD13*/
//  gpio_init(GPIOD, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);               	/*TM3_CH0-PD12*/
	
  /*J4--��д��,SWD_DIO-PA13,SWD_SCK-PA14*/
	
  /*J5--USART4,��J1���ô���,TX4-PC12,RX4-PD2*/

  /*J6--USART2,TX2-PD8,RX2-PD9*/
  gpio_init(GPIOD, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);                /*UART2 TX*/
  gpio_init(GPIOD, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_9);          /*UART2 RX*/

 
  //��ʼ������
//  gpio_init(GPIOE, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
//  gpio_init(GPIOE, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
//  
//  gpio_init(GPIOD, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
//  gpio_init(GPIOD, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_15);
  

  /*��ʼ�����ر��ⲿ��Դ�Ŀ���----------------------------------------------------*/ 

//  gpio_bit_set(GPIOE, GPIO_PIN_7);
//  gpio_bit_set(GPIOE, GPIO_PIN_8);
//  POWER_5V_SWITCH(1);                                     /*��5V ��Դ����*/
//  POWER_24V_SWITCH(1);                                    /*��24V��Դ����*/
  
//  IO_OUTPUT_PUMP(1);
//  
//  IO_OUTPUT_PUMP(0);


  /*������س�ʼ��----------------------------------------------------------------*/
//  BSP_IO_TimerTrigReadInputInit();         

}

/*
************************************************************************************************************************
* �������� : BSP_IO_SetOutput_CloseAll                                                                                                        
* �������� : ����IO���  ֮  �ر��������                                                                                    
* ������� : ��
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                
************************************************************************************************************************
*/
void BSP_IO_SetOutput_CloseAll(void)
{
//  BSP_IO_SetOutput_ERPPowerSw(OFF);                    /* �ر�����Դ */
//  BSP_IO_SetOutput_CalvesHeat(OFF);
//  BSP_IO_SetOutput_FeetSpikeCtrl(OFF, 0, 0);
//  BSP_IO_SetOutput_LegFlexSpikeCtrl(OFF, 0, 0);
//  BSP_IO_SetOutput_BackSpikeCtrl(OFF, 0, 0);
//  BSP_IO_SetOutput_ZeroSpikeCtrl(OFF, 0, 0);
//  BSP_IO_SetOutput_PumpGasCtrl(OFF, 0, 0);
}

/*
************************************************************************************************************************
* �������� : BSP_IO_SetOutput_LED                                                                                                        
* �������� :                                                                                      
* ������� : OnOff -- ȡֵ��ON  ��  
*                           OFF ��
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void BSP_IO_SetOutput_LED(uint8_t  OnOff)
{
//  IO_OUTPUT_LED0(OnOff);
//  IO_OUTPUT_LED1(!OnOff);
}

/*
************************************************************************************************************************
* �������� : BSP_IO_TimerTrigInputInit                                                                                                         
* �������� : IO ���� ��ʱ������ȡ����ĳ�ʼ��                                                                                                     
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void BSP_IO_TimerTrigReadInputInit(void)
{
  timer_parameter_struct timer_initpara;

  rcu_periph_clock_enable(RCU_TIMER6);                          //TIM6ʱ��ʹ�� 
  nvic_irq_enable(TIMER6_IRQn, 0, 1);

  timer_deinit(TIMER6);

  /* TIMER6 configuration */
  timer_initpara.prescaler         = 120-1;                     //��ʱ����Ƶ 120M/120=1Mhz�ļ���Ƶ��
  timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
  timer_initpara.counterdirection  = TIMER_COUNTER_UP;          //���ϼ���ģʽ
  timer_initpara.period            = 10000-1;                   //�Զ���װ��ֵ ��װ��ֵ10000�����Զ�ʱʱ��Ϊ10000/1M=10ms
  timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
  timer_initpara.repetitioncounter = 0;
  timer_init(TIMER6,&timer_initpara);                           //��ʼ����ʱ��1

  timer_interrupt_enable(TIMER6, TIMER_INT_UP);
  
  /* TIMER0 counter enable */
  timer_enable(TIMER6);
}

void TIMER6_IRQHandler(void)
{
  static uint8_t cc;
  
  if(timer_interrupt_flag_get(TIMER6,TIMER_INTF_UPIF) != RESET)
  {  
    timer_interrupt_flag_clear(TIMER6,TIMER_INTF_UPIF);
//    if(cc)
//    {
//      cc = 0;
//      gpio_bit_write(GPIOD, GPIO_PIN_15, 1);
//    }
//    else
//    {
//      cc = 1;
//      gpio_bit_write(GPIOD, GPIO_PIN_15, 0);
//    }
  }
}
