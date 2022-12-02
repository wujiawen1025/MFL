/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: bsp_exti.c                                                                                                       
**
**    功能描述:                                                                                                
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
#include "bsp_exti.h"          



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


/*
========================================================================================================================
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                          【变量定义 & 各种声明】    
========================================================================================================================
*/


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/

/*
************************************************************************************************************************
* 函数名称 : BSP_EXTI_Init                                                                                                         
* 功能描述 : 外部中断初始化                                                                                                           
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void BSP_EXTI_Init(void)
{
  /* enable and set key EXTI interrupt to the lowest priority */
  nvic_irq_enable(EXTI0_IRQn, 2U, 0U);
  
  /* connect key EXTI line to key GPIO pin */
  gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOE, GPIO_PIN_SOURCE_0);

  /* configure key EXTI line */
  exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
  exti_interrupt_flag_clear(EXTI_0); 
}

/*
************************************************************************************************************************
* 函数名称 : EXTI0_IRQHandler                                                                                                         
* 功能描述 : 外部中断0中断服务函数                                                                                                         
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void EXTI0_IRQHandler(void)
{
  if (RESET != exti_interrupt_flag_get(EXTI_0)) 
  {
      exti_interrupt_flag_clear(EXTI_0);
  }
}
