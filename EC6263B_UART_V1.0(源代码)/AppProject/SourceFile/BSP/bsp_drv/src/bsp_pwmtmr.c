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
#define  PWM_CYCLE_COMMON            (500-1)              /* PWM周期：通用的   */

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
//  timer_break_parameter_struct timer_breakpara;

  /*--- TIMER0 configuration------------------------------ */
  rcu_periph_clock_enable(RCU_TIMER0);                          //TIM2时钟使能 
  timer_deinit(TIMER0);

  timer_initpara.prescaler         = 10-1;                     	//定时器分频 108M/10=10800Khz的计数频率
  timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
  timer_initpara.counterdirection  = TIMER_COUNTER_UP;          //向上计数模式
  timer_initpara.period            = PWM_CYCLE_COMMON;      		//自动重装载值 重装载值500，所以PWM频率为 10800Khz/500=21.6Khz
  timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
  timer_initpara.repetitioncounter = 0;
  timer_init(TIMER0,&timer_initpara);                           //初始化定时器2

   /* CH2/CH2N,CH3/CH3N configuration in timing mode */
  timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
  timer_ocintpara.outputnstate = TIMER_CCXN_ENABLE;
  timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;        //输出极性:TIM输出比较极性高
  timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
  timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
  timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
  
  timer_channel_output_config(TIMER0,TIMER_CH_0,&timer_ocintpara);
  timer_channel_output_config(TIMER0,TIMER_CH_1,&timer_ocintpara);
  timer_channel_output_config(TIMER0,TIMER_CH_2,&timer_ocintpara);
  timer_channel_output_config(TIMER0,TIMER_CH_3,&timer_ocintpara);

  timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_0,0);
  timer_channel_output_mode_config(TIMER0,TIMER_CH_0,TIMER_OC_MODE_PWM0);
  timer_channel_output_shadow_config(TIMER0,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);

	timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_1,0);
  timer_channel_output_mode_config(TIMER0,TIMER_CH_1,TIMER_OC_MODE_PWM0);
  timer_channel_output_shadow_config(TIMER0,TIMER_CH_1,TIMER_OC_SHADOW_DISABLE);

	timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_2,0);
  timer_channel_output_mode_config(TIMER0,TIMER_CH_2,TIMER_OC_MODE_PWM0);
  timer_channel_output_shadow_config(TIMER0,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);
 
	timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_3,0);
  timer_channel_output_mode_config(TIMER0,TIMER_CH_3,TIMER_OC_MODE_PWM0);
  timer_channel_output_shadow_config(TIMER0,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);

  /* TIMER0 primary output function enable */
  timer_primary_output_config(TIMER0,ENABLE);

  /* auto-reload preload enable */
  timer_auto_reload_shadow_enable(TIMER0);
  timer_enable(TIMER0);
#if 1	
  /*--- TIMER1 configuration------------------------------ */
  rcu_periph_clock_enable(RCU_TIMER1);                          //TIM2时钟使能 
  timer_deinit(TIMER1);

  timer_initpara.prescaler         = 10-1;                     	//定时器分频 108M/10=10800Khz的计数频率
  timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
  timer_initpara.counterdirection  = TIMER_COUNTER_UP;          //向上计数模式
  timer_initpara.period            = PWM_CYCLE_COMMON;      		//自动重装载值 重装载值500，所以PWM频率为 10800Khz/500=21.6Khz
  timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
  timer_initpara.repetitioncounter = 0;
  timer_init(TIMER1,&timer_initpara);                           //初始化定时器2

   /* CH3/CH3N configuration in timing mode */
  timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
  timer_ocintpara.outputnstate = TIMER_CCXN_ENABLE;
  timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;        //输出极性:TIM输出比较极性高
  timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
  timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
  timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

  timer_channel_output_config(TIMER1,TIMER_CH_2,&timer_ocintpara);
  timer_channel_output_config(TIMER1,TIMER_CH_3,&timer_ocintpara);

   timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_2,0);
  timer_channel_output_mode_config(TIMER1,TIMER_CH_2,TIMER_OC_MODE_PWM0);
  timer_channel_output_shadow_config(TIMER1,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);
  
  timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_3,0);
  timer_channel_output_mode_config(TIMER1,TIMER_CH_3,TIMER_OC_MODE_PWM0);
  timer_channel_output_shadow_config(TIMER1,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);

  /* TIMER2 primary output function enable */
  timer_primary_output_config(TIMER1,ENABLE);

  /* auto-reload preload enable */
  timer_auto_reload_shadow_enable(TIMER1);
  timer_enable(TIMER1);
#endif

#if 1	
  /*--- TIMER2 configuration------------------------------ */
  rcu_periph_clock_enable(RCU_TIMER2);                          //TIM2时钟使能 
  timer_deinit(TIMER2);

  timer_initpara.prescaler         = 10-1;                     	//定时器分频 108M/10=10800Khz的计数频率
  timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
  timer_initpara.counterdirection  = TIMER_COUNTER_UP;          //向上计数模式
  timer_initpara.period            = PWM_CYCLE_COMMON;      		//自动重装载值 重装载值500，所以PWM频率为 10800Khz/500=21.6Khz
  timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
  timer_initpara.repetitioncounter = 0;
  timer_init(TIMER2,&timer_initpara);                           //初始化定时器2

   /* CH3/CH3N configuration in timing mode */
  timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
  timer_ocintpara.outputnstate = TIMER_CCXN_ENABLE;
  timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;        //输出极性:TIM输出比较极性高
  timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
  timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
  timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
  
  timer_channel_output_config(TIMER2,TIMER_CH_3,&timer_ocintpara);

  timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_3,0);
  timer_channel_output_mode_config(TIMER2,TIMER_CH_3,TIMER_OC_MODE_PWM0);
  timer_channel_output_shadow_config(TIMER2,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);

  /* TIMER2 primary output function enable */
  timer_primary_output_config(TIMER2,ENABLE);

  /* auto-reload preload enable */
  timer_auto_reload_shadow_enable(TIMER2);
  timer_enable(TIMER2);
#endif

#if 0   //ADC使用了

  /*--- TIMER3 configuration------------------------------ */
  rcu_periph_clock_enable(RCU_TIMER3);                          //TIM3时钟使能 
  timer_deinit(TIMER3);

  timer_initpara.prescaler         = 10-1;                     	//定时器分频 108M/10=10800Khz的计数频率
  timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
  timer_initpara.counterdirection  = TIMER_COUNTER_UP;          //向上计数模式
  timer_initpara.period            = PWM_CYCLE_COMMON;      		//自动重装载值 重装载值500，所以PWM频率为 10800Khz/500=21.6Khz
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
  timer_channel_output_config(TIMER3,TIMER_CH_1,&timer_ocintpara);
  timer_channel_output_config(TIMER3,TIMER_CH_2,&timer_ocintpara);

  timer_channel_output_pulse_value_config(TIMER3,TIMER_CH_0,0);
  timer_channel_output_mode_config(TIMER3,TIMER_CH_0,TIMER_OC_MODE_PWM0);
  timer_channel_output_shadow_config(TIMER3,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);
  
  timer_channel_output_pulse_value_config(TIMER3,TIMER_CH_1,0);
  timer_channel_output_mode_config(TIMER3,TIMER_CH_1,TIMER_OC_MODE_PWM0);
  timer_channel_output_shadow_config(TIMER3,TIMER_CH_1,TIMER_OC_SHADOW_DISABLE);

  timer_channel_output_pulse_value_config(TIMER3,TIMER_CH_2,0);
  timer_channel_output_mode_config(TIMER3,TIMER_CH_2,TIMER_OC_MODE_PWM0);
  timer_channel_output_shadow_config(TIMER3,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);

  /* TIMER3 primary output function enable */
  timer_primary_output_config(TIMER3,ENABLE);

  /* auto-reload preload enable */
  timer_auto_reload_shadow_enable(TIMER3);
  timer_enable(TIMER3);


#endif

}

/*
************************************************************************************************************************
* 函数名称 : BSP_PWMTmr_SetTapDuty                                                                                                         
* 功能描述 : PWM 定时器 敲击通道占空比参数值设定封装，输入参数值为521的时候0%，输出为0的时候 100%                                                                                                       
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 使用FTM2通道0
************************************************************************************************************************
*/
void BSP_PWMTmr_SetTapDuty(uint16_t Duty)
{
    if(Duty >= 500)   //521关闭
        Duty = 0;
    else
        Duty = 500 - Duty;                                     /* 匹配旧架构动作表格参数做的处理 */
//    Duty = (Duty >>1); 
    if(Duty > PWM_CYCLE_COMMON)
    {
        Duty = PWM_CYCLE_COMMON;
    }
//    FTM_SetChannelValue(FTM2, FTM_CHANNEL_CHANNEL2, Duty);     /* 设置CnV的值 */
//		timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_1,Duty);
}

/*
************************************************************************************************************************
* 函数名称 : BSP_PWMTmr_SetKneadDuty                                                                                                         
* 功能描述 : PWM 定时器 揉捏通道占空比参数值设定封装，输入参数值为521的时候0%，输出为0的时候 100%                                                                                                       
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : PWM输出通过IRS2104芯片驱动桥式MOS管，测试发现输出占空比>98%的时候，输出电压不正常，硬件建议H桥占空比最大不能超过95%
************************************************************************************************************************
*/
void BSP_PWMTmr_SetKneadDuty(uint16_t Duty)
{
    if(Duty >= 500)   //521关闭,500最大
        Duty = 0;
    else
        Duty = 500 - Duty;                                     /* 匹配旧架构动作表格参数做的处理 */

//    if(Duty > PWM_CYCLE_COMMON)    
//		{
//        Duty = PWM_CYCLE_COMMON;
//    }
		
    if(Duty > (PWM_CYCLE_COMMON*95/100)) //限制在95%
    {
        Duty = (PWM_CYCLE_COMMON*95/100);
    }
		
//    FTM_SetChannelValue(FTM2, FTM_CHANNEL_CHANNEL5, Duty);      /* 设置CnV的值 */
//		timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_3,Duty);
}

/*
************************************************************************************************************************
* 函数名称 : BSP_PWMTmr_SetKneadDuty2                                                                                                         
* 功能描述 : PWM 定时器 揉捏通道占空比参数值设定封装，输入参数值为521的时候0%，输出为0的时候 100%                                                                                                       
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : PWM输出通过IRS2104芯片驱动桥式MOS管，测试发现输出占空比>98%的时候，输出电压不正常，硬件建议H桥占空比最大不能超过95%
************************************************************************************************************************
*/
void BSP_PWMTmr_SetKneadDuty2(uint16_t Duty)
{
    if(Duty >= 500)   //521关闭,500最大
        Duty = 0;
    else
        Duty = 500 - Duty;                                     /* 匹配旧架构动作表格参数做的处理 */

//    if(Duty > PWM_CYCLE_COMMON)
//    {
//        Duty = PWM_CYCLE_COMMON;
//    }
    if(Duty > (PWM_CYCLE_COMMON*95/100)) //限制在95%
    {
        Duty = (PWM_CYCLE_COMMON*95/100);
    }		
//    FTM_SetChannelValue(FTM2, FTM_CHANNEL_CHANNEL3, Duty);      /* 设置CnV的值 */
//		timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_2,Duty);
}

/*
************************************************************************************************************************
* 函数名称 : BSP_PWMTmr_SetRollDuty                                                                                                         
* 功能描述 : PWM 定时器 行走通道占空比参数值设定封装，输入参数值为521的时候0%，输出为0的时候 100%                                                                                                       
* 输入参数 : 521~0之间                                                                                                        
* 返回参数 : 无                                                                                                         
* 补充说明 : 使用FTM2通道1
************************************************************************************************************************
*/
void BSP_PWMTmr_SetRollDuty(uint16_t Duty)
{	
	if(Duty >= 500)   //521关闭
			Duty = 0;
	else
			Duty = 500 - Duty;                                         /* 匹配旧架构动作表格参数做的处理 */

//	Duty = (Duty >> 1); 
	if(Duty > PWM_CYCLE_COMMON)
	{
			Duty = PWM_CYCLE_COMMON;
	}
//	FTM_SetChannelValue(FTM1, FTM_CHANNEL_CHANNEL0, Duty);                /* 设置CnV的值 */
//	timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_0,Duty);
}


/*
************************************************************************************************************************
* 函数名称 : BSP_PWMTmr_SetFeetRollerDuty                                                                                                         
* 功能描述 : 设置脚滚马达的占空比 （使用定时器控制PWM）                                                                                                     
* 输入参数 : Duty 要设置的占空比值       
* 返回参数 : 无                                                                                                         
* 补充说明 : 无
************************************************************************************************************************
*/
void BSP_PWMTmr_SetFeetRollerDuty(uint16_t Duty)
{
	if(Duty >= 500)   //521关闭
		Duty = 0;
	else
		Duty = 500 - Duty;                                         /* 匹配旧架构动作表格参数做的处理 */

//	Duty = (Duty >> 1); 
  
	if(Duty > PWM_CYCLE_COMMON)
  {
    Duty = PWM_CYCLE_COMMON;
  }

//  FTM_SetChannelValue(FTM0, FTM_CHANNEL_CHANNEL1, Duty);                /* 设置CnV的值 */
	timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_1,Duty);
}



/*
************************************************************************************************************************
* 函数名称 : BSP_PWMTmr_SetBLedDuty                                                                                                         
* 功能描述 : 设置BLed的占空比 （使用定时器控制PWM）                                                                                                     
* 输入参数 : Duty 要设置的占空比值       
* 返回参数 : 无                                                                                                         
* 补充说明 : 无
************************************************************************************************************************
*/
void BSP_PWMTmr_SetBLedDuty(uint16_t Duty)
{
  //Duty = (Duty << 1) + (Duty>>1); /*2.5 倍。*/
	if(Duty >= 500)   //521关闭
		Duty = 0;
	else
		Duty = 500 - Duty;                                         /* 匹配旧架构动作表格参数做的处理 */

//	Duty = (Duty >> 1); 
  
	if(Duty > PWM_CYCLE_COMMON)
	{
		Duty = PWM_CYCLE_COMMON;
	}
  
//	FTM_SetChannelValue(FTM0, FTM_CHANNEL_CHANNEL1, Duty);                /* 设置CnV的值 */
	timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_2,Duty);
}

/*
************************************************************************************************************************
* 函数名称 : BSP_PWMTmr_SetGLedDuty                                                                                                         
* 功能描述 : 设置GLed的占空比 （使用定时器控制PWM）                                                                                                     
* 输入参数 : Duty 要设置的占空比值       
* 返回参数 : 无                                                                                                         
* 补充说明 : 无
************************************************************************************************************************
*/
void BSP_PWMTmr_SetGLedDuty(uint16_t Duty)
{
  //Duty = (Duty << 1) + (Duty>>1); /*2.5 倍。*/
	if(Duty >= 500)   //521关闭
		Duty = 0;
	else
		Duty = 500 - Duty;                                         /* 匹配旧架构动作表格参数做的处理 */

//	Duty = (Duty >> 1); 
  
	if(Duty > PWM_CYCLE_COMMON)
	{
		Duty = PWM_CYCLE_COMMON;
	}

//	FTM_SetChannelValue(FTM2, FTM_CHANNEL_CHANNEL1, Duty);                /* 设置CnV的值 */
	timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_3,Duty);

}

/*
************************************************************************************************************************
* 函数名称 : BSP_PWMTmr_SetRLedDuty                                                                                                         
* 功能描述 : 设置RLed的占空比 （使用定时器控制PWM）                                                                                                     
* 输入参数 : Duty 要设置的占空比值       
* 返回参数 : 无                                                                                                         
* 补充说明 : 无
************************************************************************************************************************
*/
void BSP_PWMTmr_SetRLedDuty(uint16_t Duty)
{
  //Duty = (Duty << 1) + (Duty>>1); /*2.5 倍。*/
	if(Duty >= 500)   //521关闭
		Duty = 0;
	else
		Duty = 500 - Duty;                                         /* 匹配旧架构动作表格参数做的处理 */

//	Duty = (Duty >> 1); 
  
	if(Duty > PWM_CYCLE_COMMON)
	{
		Duty = PWM_CYCLE_COMMON;
	}

//	FTM_SetChannelValue(FTM2, FTM_CHANNEL_CHANNEL0, Duty);       /* 设置CnV的值 */
	timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_3,Duty);
}



