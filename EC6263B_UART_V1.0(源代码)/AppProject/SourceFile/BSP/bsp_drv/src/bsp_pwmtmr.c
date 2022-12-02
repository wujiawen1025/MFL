/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: bsp_pwmtmr.c
**
**    ��������: pwm�����ʱ��
**
**    ��    ˾���ɷ�������
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
#include "bsp_pwmtmr.h"    


/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/
#define  PWM_CYCLE_COMMON            (500-1)              /* PWM���ڣ�ͨ�õ�   */

/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/



/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/

/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/

/*
************************************************************************************************************************
* �������� : BSP_PWMTmr_Init                                                                                                         
* �������� : PWM ��ʱ�� ��ʼ��                                                                                                        
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : ��
************************************************************************************************************************
*/
void BSP_PWMTmr_Init(void)
{
  timer_oc_parameter_struct timer_ocintpara;
  timer_parameter_struct timer_initpara;
//  timer_break_parameter_struct timer_breakpara;

  /*--- TIMER0 configuration------------------------------ */
  rcu_periph_clock_enable(RCU_TIMER0);                          //TIM2ʱ��ʹ�� 
  timer_deinit(TIMER0);

  timer_initpara.prescaler         = 10-1;                     	//��ʱ����Ƶ 108M/10=10800Khz�ļ���Ƶ��
  timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
  timer_initpara.counterdirection  = TIMER_COUNTER_UP;          //���ϼ���ģʽ
  timer_initpara.period            = PWM_CYCLE_COMMON;      		//�Զ���װ��ֵ ��װ��ֵ500������PWMƵ��Ϊ 10800Khz/500=21.6Khz
  timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
  timer_initpara.repetitioncounter = 0;
  timer_init(TIMER0,&timer_initpara);                           //��ʼ����ʱ��2

   /* CH2/CH2N,CH3/CH3N configuration in timing mode */
  timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
  timer_ocintpara.outputnstate = TIMER_CCXN_ENABLE;
  timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;        //�������:TIM����Ƚϼ��Ը�
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
  rcu_periph_clock_enable(RCU_TIMER1);                          //TIM2ʱ��ʹ�� 
  timer_deinit(TIMER1);

  timer_initpara.prescaler         = 10-1;                     	//��ʱ����Ƶ 108M/10=10800Khz�ļ���Ƶ��
  timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
  timer_initpara.counterdirection  = TIMER_COUNTER_UP;          //���ϼ���ģʽ
  timer_initpara.period            = PWM_CYCLE_COMMON;      		//�Զ���װ��ֵ ��װ��ֵ500������PWMƵ��Ϊ 10800Khz/500=21.6Khz
  timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
  timer_initpara.repetitioncounter = 0;
  timer_init(TIMER1,&timer_initpara);                           //��ʼ����ʱ��2

   /* CH3/CH3N configuration in timing mode */
  timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
  timer_ocintpara.outputnstate = TIMER_CCXN_ENABLE;
  timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;        //�������:TIM����Ƚϼ��Ը�
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
  rcu_periph_clock_enable(RCU_TIMER2);                          //TIM2ʱ��ʹ�� 
  timer_deinit(TIMER2);

  timer_initpara.prescaler         = 10-1;                     	//��ʱ����Ƶ 108M/10=10800Khz�ļ���Ƶ��
  timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
  timer_initpara.counterdirection  = TIMER_COUNTER_UP;          //���ϼ���ģʽ
  timer_initpara.period            = PWM_CYCLE_COMMON;      		//�Զ���װ��ֵ ��װ��ֵ500������PWMƵ��Ϊ 10800Khz/500=21.6Khz
  timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
  timer_initpara.repetitioncounter = 0;
  timer_init(TIMER2,&timer_initpara);                           //��ʼ����ʱ��2

   /* CH3/CH3N configuration in timing mode */
  timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
  timer_ocintpara.outputnstate = TIMER_CCXN_ENABLE;
  timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;        //�������:TIM����Ƚϼ��Ը�
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

#if 0   //ADCʹ����

  /*--- TIMER3 configuration------------------------------ */
  rcu_periph_clock_enable(RCU_TIMER3);                          //TIM3ʱ��ʹ�� 
  timer_deinit(TIMER3);

  timer_initpara.prescaler         = 10-1;                     	//��ʱ����Ƶ 108M/10=10800Khz�ļ���Ƶ��
  timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
  timer_initpara.counterdirection  = TIMER_COUNTER_UP;          //���ϼ���ģʽ
  timer_initpara.period            = PWM_CYCLE_COMMON;      		//�Զ���װ��ֵ ��װ��ֵ500������PWMƵ��Ϊ 10800Khz/500=21.6Khz
  timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
  timer_initpara.repetitioncounter = 0;
  timer_init(TIMER3,&timer_initpara);                           //��ʼ����ʱ��3

   /* CH0/CH0N,CH1/CH1N and CH2/CH2N configuration in timing mode */
  timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
  timer_ocintpara.outputnstate = TIMER_CCXN_ENABLE;
  timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;        //�������:TIM����Ƚϼ��Ը�
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
* �������� : BSP_PWMTmr_SetTapDuty                                                                                                         
* �������� : PWM ��ʱ�� �û�ͨ��ռ�ձȲ���ֵ�趨��װ���������ֵΪ521��ʱ��0%�����Ϊ0��ʱ�� 100%                                                                                                       
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : ʹ��FTM2ͨ��0
************************************************************************************************************************
*/
void BSP_PWMTmr_SetTapDuty(uint16_t Duty)
{
    if(Duty >= 500)   //521�ر�
        Duty = 0;
    else
        Duty = 500 - Duty;                                     /* ƥ��ɼܹ��������������Ĵ��� */
//    Duty = (Duty >>1); 
    if(Duty > PWM_CYCLE_COMMON)
    {
        Duty = PWM_CYCLE_COMMON;
    }
//    FTM_SetChannelValue(FTM2, FTM_CHANNEL_CHANNEL2, Duty);     /* ����CnV��ֵ */
//		timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_1,Duty);
}

/*
************************************************************************************************************************
* �������� : BSP_PWMTmr_SetKneadDuty                                                                                                         
* �������� : PWM ��ʱ�� ����ͨ��ռ�ձȲ���ֵ�趨��װ���������ֵΪ521��ʱ��0%�����Ϊ0��ʱ�� 100%                                                                                                       
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : PWM���ͨ��IRS2104оƬ������ʽMOS�ܣ����Է������ռ�ձ�>98%��ʱ�������ѹ��������Ӳ������H��ռ�ձ�����ܳ���95%
************************************************************************************************************************
*/
void BSP_PWMTmr_SetKneadDuty(uint16_t Duty)
{
    if(Duty >= 500)   //521�ر�,500���
        Duty = 0;
    else
        Duty = 500 - Duty;                                     /* ƥ��ɼܹ��������������Ĵ��� */

//    if(Duty > PWM_CYCLE_COMMON)    
//		{
//        Duty = PWM_CYCLE_COMMON;
//    }
		
    if(Duty > (PWM_CYCLE_COMMON*95/100)) //������95%
    {
        Duty = (PWM_CYCLE_COMMON*95/100);
    }
		
//    FTM_SetChannelValue(FTM2, FTM_CHANNEL_CHANNEL5, Duty);      /* ����CnV��ֵ */
//		timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_3,Duty);
}

/*
************************************************************************************************************************
* �������� : BSP_PWMTmr_SetKneadDuty2                                                                                                         
* �������� : PWM ��ʱ�� ����ͨ��ռ�ձȲ���ֵ�趨��װ���������ֵΪ521��ʱ��0%�����Ϊ0��ʱ�� 100%                                                                                                       
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : PWM���ͨ��IRS2104оƬ������ʽMOS�ܣ����Է������ռ�ձ�>98%��ʱ�������ѹ��������Ӳ������H��ռ�ձ�����ܳ���95%
************************************************************************************************************************
*/
void BSP_PWMTmr_SetKneadDuty2(uint16_t Duty)
{
    if(Duty >= 500)   //521�ر�,500���
        Duty = 0;
    else
        Duty = 500 - Duty;                                     /* ƥ��ɼܹ��������������Ĵ��� */

//    if(Duty > PWM_CYCLE_COMMON)
//    {
//        Duty = PWM_CYCLE_COMMON;
//    }
    if(Duty > (PWM_CYCLE_COMMON*95/100)) //������95%
    {
        Duty = (PWM_CYCLE_COMMON*95/100);
    }		
//    FTM_SetChannelValue(FTM2, FTM_CHANNEL_CHANNEL3, Duty);      /* ����CnV��ֵ */
//		timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_2,Duty);
}

/*
************************************************************************************************************************
* �������� : BSP_PWMTmr_SetRollDuty                                                                                                         
* �������� : PWM ��ʱ�� ����ͨ��ռ�ձȲ���ֵ�趨��װ���������ֵΪ521��ʱ��0%�����Ϊ0��ʱ�� 100%                                                                                                       
* ������� : 521~0֮��                                                                                                        
* ���ز��� : ��                                                                                                         
* ����˵�� : ʹ��FTM2ͨ��1
************************************************************************************************************************
*/
void BSP_PWMTmr_SetRollDuty(uint16_t Duty)
{	
	if(Duty >= 500)   //521�ر�
			Duty = 0;
	else
			Duty = 500 - Duty;                                         /* ƥ��ɼܹ��������������Ĵ��� */

//	Duty = (Duty >> 1); 
	if(Duty > PWM_CYCLE_COMMON)
	{
			Duty = PWM_CYCLE_COMMON;
	}
//	FTM_SetChannelValue(FTM1, FTM_CHANNEL_CHANNEL0, Duty);                /* ����CnV��ֵ */
//	timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_0,Duty);
}


/*
************************************************************************************************************************
* �������� : BSP_PWMTmr_SetFeetRollerDuty                                                                                                         
* �������� : ���ýŹ�����ռ�ձ� ��ʹ�ö�ʱ������PWM��                                                                                                     
* ������� : Duty Ҫ���õ�ռ�ձ�ֵ       
* ���ز��� : ��                                                                                                         
* ����˵�� : ��
************************************************************************************************************************
*/
void BSP_PWMTmr_SetFeetRollerDuty(uint16_t Duty)
{
	if(Duty >= 500)   //521�ر�
		Duty = 0;
	else
		Duty = 500 - Duty;                                         /* ƥ��ɼܹ��������������Ĵ��� */

//	Duty = (Duty >> 1); 
  
	if(Duty > PWM_CYCLE_COMMON)
  {
    Duty = PWM_CYCLE_COMMON;
  }

//  FTM_SetChannelValue(FTM0, FTM_CHANNEL_CHANNEL1, Duty);                /* ����CnV��ֵ */
	timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_1,Duty);
}



/*
************************************************************************************************************************
* �������� : BSP_PWMTmr_SetBLedDuty                                                                                                         
* �������� : ����BLed��ռ�ձ� ��ʹ�ö�ʱ������PWM��                                                                                                     
* ������� : Duty Ҫ���õ�ռ�ձ�ֵ       
* ���ز��� : ��                                                                                                         
* ����˵�� : ��
************************************************************************************************************************
*/
void BSP_PWMTmr_SetBLedDuty(uint16_t Duty)
{
  //Duty = (Duty << 1) + (Duty>>1); /*2.5 ����*/
	if(Duty >= 500)   //521�ر�
		Duty = 0;
	else
		Duty = 500 - Duty;                                         /* ƥ��ɼܹ��������������Ĵ��� */

//	Duty = (Duty >> 1); 
  
	if(Duty > PWM_CYCLE_COMMON)
	{
		Duty = PWM_CYCLE_COMMON;
	}
  
//	FTM_SetChannelValue(FTM0, FTM_CHANNEL_CHANNEL1, Duty);                /* ����CnV��ֵ */
	timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_2,Duty);
}

/*
************************************************************************************************************************
* �������� : BSP_PWMTmr_SetGLedDuty                                                                                                         
* �������� : ����GLed��ռ�ձ� ��ʹ�ö�ʱ������PWM��                                                                                                     
* ������� : Duty Ҫ���õ�ռ�ձ�ֵ       
* ���ز��� : ��                                                                                                         
* ����˵�� : ��
************************************************************************************************************************
*/
void BSP_PWMTmr_SetGLedDuty(uint16_t Duty)
{
  //Duty = (Duty << 1) + (Duty>>1); /*2.5 ����*/
	if(Duty >= 500)   //521�ر�
		Duty = 0;
	else
		Duty = 500 - Duty;                                         /* ƥ��ɼܹ��������������Ĵ��� */

//	Duty = (Duty >> 1); 
  
	if(Duty > PWM_CYCLE_COMMON)
	{
		Duty = PWM_CYCLE_COMMON;
	}

//	FTM_SetChannelValue(FTM2, FTM_CHANNEL_CHANNEL1, Duty);                /* ����CnV��ֵ */
	timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_3,Duty);

}

/*
************************************************************************************************************************
* �������� : BSP_PWMTmr_SetRLedDuty                                                                                                         
* �������� : ����RLed��ռ�ձ� ��ʹ�ö�ʱ������PWM��                                                                                                     
* ������� : Duty Ҫ���õ�ռ�ձ�ֵ       
* ���ز��� : ��                                                                                                         
* ����˵�� : ��
************************************************************************************************************************
*/
void BSP_PWMTmr_SetRLedDuty(uint16_t Duty)
{
  //Duty = (Duty << 1) + (Duty>>1); /*2.5 ����*/
	if(Duty >= 500)   //521�ر�
		Duty = 0;
	else
		Duty = 500 - Duty;                                         /* ƥ��ɼܹ��������������Ĵ��� */

//	Duty = (Duty >> 1); 
  
	if(Duty > PWM_CYCLE_COMMON)
	{
		Duty = PWM_CYCLE_COMMON;
	}

//	FTM_SetChannelValue(FTM2, FTM_CHANNEL_CHANNEL0, Duty);       /* ����CnV��ֵ */
	timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_3,Duty);
}



