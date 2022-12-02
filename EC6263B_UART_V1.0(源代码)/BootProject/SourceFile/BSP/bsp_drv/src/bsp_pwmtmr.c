/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: bsp_pwmtmr.c
**
**    功能描述: pwm输出定时器
**
**    公    司：蒙发利电子
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
#include "bsp_pwmtmr.h"    


/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/
#define  PWM_CYCLE_COMMON            (250-1)              /* PWM周期：通用的   */

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
* 函数名称 : BSP_PWMTmr_Init                                                                                                         
* 功能描述 : PWM 定时器 初始化                                                                                                        
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 无
************************************************************************************************************************
*/
void BSP_PWMTmr_Init(void)
{
  timer_oc_parameter_struct timer_ocintpara;
  timer_parameter_struct timer_initpara;
  timer_break_parameter_struct timer_breakpara;

  rcu_periph_clock_enable(RCU_TIMER3);                          //TIM3时钟使能 

  timer_deinit(TIMER3);

  /* TIMER0 configuration */
  timer_initpara.prescaler         = 120-1;                     //定时器分频 120M/120=1Mhz的计数频率
  timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
  timer_initpara.counterdirection  = TIMER_COUNTER_UP;          //向上计数模式
  timer_initpara.period            = PWM_CYCLE_COMMON;          //自动重装载值 重装载值250，所以PWM频率为 1M/250=4Khz
  timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
  timer_initpara.repetitioncounter = 0;
  timer_init(TIMER3,&timer_initpara);                           //初始化定时器3

   /* CH0/CH0N,CH1/CH1N and CH2/CH2N configuration in timing mode */
  timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
  timer_ocintpara.outputnstate = TIMER_CCXN_ENABLE;
  timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;        //输出极性:TIM输出比较极性高
  timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
  timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
  timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
  
  timer_channel_output_config(TIMER3,TIMER_CH_0,&timer_ocintpara);

  timer_channel_output_pulse_value_config(TIMER3,TIMER_CH_0,0);
  timer_channel_output_mode_config(TIMER3,TIMER_CH_0,TIMER_OC_MODE_PWM0);
  timer_channel_output_shadow_config(TIMER3,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);

  /* TIMER0 primary output function enable */
  timer_primary_output_config(TIMER3,ENABLE);

  /* auto-reload preload enable */
  timer_auto_reload_shadow_enable(TIMER3);
  timer_enable(TIMER3);
}


/*
************************************************************************************************************************
* 函数名称 : BSP_PWMTmr_SetOutput_LED                                                                                                         
* 功能描述 : 设置LED呼吸灯的占空比 （使用定时器控制PWM）                                                                                                     
* 输入参数 : Duty 要设置的占空比值       
* 返回参数 : 无                                                                                                         
* 补充说明 : 无
************************************************************************************************************************
*/
void BSP_PWMTmr_SetOutput_LED(uint8_t Duty)
{
  if(0 == Duty)
  {
    Duty = 0;
  }
  else
  {
    Duty = (Duty>>1) + 50;          /*4959特殊处理*/
    Duty = (Duty << 1) + (Duty>>1); /*2.5 倍。*/
  }
  
  if(Duty > PWM_CYCLE_COMMON)
  {
    Duty = PWM_CYCLE_COMMON;
  }
  
  timer_channel_output_pulse_value_config(TIMER3,TIMER_CH_0,Duty);

}
