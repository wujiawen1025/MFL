/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: bsp_adc.c
**
**    ��������: adc������
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
#include "bsp_adc.h"          


/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/
#define  ADC_RESULT_FIFO_SIZE           5         /*FIFO �˲� �����С*/
#define  ADC_CH_NUM                     6         /*ADC ת��ͨ������*/
#define ADC_PWM_FIFO_VAL	5	//PWM�˲���ֵ

/*������������ADCֵ*/
#define  TAPMOTOOVERC_LIMIT     			0x10	//ͬ�콡ȷ�ϣ�������ѹ����Ϊ0.2v
#define  KNEADMOTOOVERC_LIMIT     		0x10	//


/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* ���Ͷ��� : ADCת����� ��ز������ݽṹ                                                                                                        
************************************************************************************************************************
*/
typedef struct
{
  uint8_t     FIFOPoint[ADC_CH_NUM];
  uint16_t    FIFOBuf[ADC_CH_NUM][ADC_RESULT_FIFO_SIZE];
  uint16_t    ResultAvg[ADC_CH_NUM];
  uint32_t    ResultSum[ADC_CH_NUM];
}ADCResult_t;

/*OverCurrent ����������Ŀ*/
typedef  struct
{
    uint8_t	    ADCValue;
    uint8_t     OverCTime;
    struct
    {
    	unsigned char   OverCErrFlag    :	1;
    }StateBits;
}ADCOverCData_t; /*���İ�����Ҫ��������������Ŀ�ϵ�����*/

typedef  struct
{
    ADCOverCData_t KneadMotor;
    ADCOverCData_t TapMotor;
    //ADCOverCData_t PumpMotor;
    //ADCOverCData_t Heat;  
}ADCOverCUnit_t; /*���İ�����Ҫ������������Ŀ*/

/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/
/*static*/ ADCResult_t           ADCResult;
uint16_t adc_value[16]; //uint16_t��ֻȡADC0������

/*���²����ػ�����*/
#pragma arm section rwdata = "RAM_KEEP"
#pragma arm section zidata = "RAM_KEEP"
ADCOverCUnit_t OverCUnit;

#pragma arm section rwdata
#pragma arm section zidata


void BSP_ADC_TimerTrigInit(void);
void Init_dma_config(void);

/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/

/*
************************************************************************************************************************
* �������� : BSP_ADC_Init                                                                                                         
* �������� : ADC ���ܳ�ʼ��                                                                                                     
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : ADC���ܶ��Ǹ�����ӦIO��Ĭ�Ϲ��ܣ����Բ���ӳ��
*            ADC0_SE0 --> PTA0                                                                                                         
************************************************************************************************************************
*/
void BSP_ADC_Init(void)
{
  /* enable ADC0 clock */
  rcu_periph_clock_enable(RCU_ADC0);
  /* config ADC clock */
  rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV4);

	nvic_irq_enable(ADC0_1_IRQn, 0, 0);  	/**/

  /* ADC mode config */
  adc_mode_config(ADC_MODE_FREE); 			/*�����ڶ���ģʽ*/
  /* ADC special function config */
  adc_special_function_config(ADC0, ADC_SCAN_MODE, ENABLE);
  adc_special_function_config(ADC0, ADC_CONTINUOUS_MODE, DISABLE);  
  /* ADC data alignment config */
  adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);

	/* ADC channel length config */
	adc_channel_length_config(ADC0, ADC_REGULAR_CHANNEL, ADC_CH_NUM);	
	
	/* ADC regular channel config */
//	adc_regular_channel_config(ADC0, 0, ADC_CHANNEL_6, ADC_SAMPLETIME_55POINT5);
//	adc_regular_channel_config(ADC0, 1, ADC_CHANNEL_7, ADC_SAMPLETIME_55POINT5);
//	adc_regular_channel_config(ADC0, 2, ADC_CHANNEL_8, ADC_SAMPLETIME_55POINT5);
//	adc_regular_channel_config(ADC0, 3, ADC_CHANNEL_9, ADC_SAMPLETIME_55POINT5);
//	adc_regular_channel_config(ADC0, 4, ADC_CHANNEL_14, ADC_SAMPLETIME_55POINT5);
//	adc_regular_channel_config(ADC0, 5, ADC_CHANNEL_15, ADC_SAMPLETIME_55POINT5);

//  adc_regular_channel_config(ADC0, 0, ADC_CHANNEL_7, ADC_SAMPLETIME_55POINT5);
//	adc_regular_channel_config(ADC0, 1, ADC_CHANNEL_14, ADC_SAMPLETIME_55POINT5);

	adc_external_trigger_config(ADC0, ADC_REGULAR_CHANNEL, ENABLE);

  /* ADC trigger config */
//  adc_external_trigger_source_config(ADC0, ADC_INSERTED_CHANNEL, ADC0_1_EXTTRIG_INSERTED_T1_CH0); /*ע����*/
	adc_external_trigger_source_config(ADC0, ADC_REGULAR_CHANNEL, ADC0_1_EXTTRIG_REGULAR_T3_CH3); /*������*/

  /* ADC external trigger enable */
//  adc_external_trigger_config(ADC0, ADC_INSERTED_CHANNEL, ENABLE); /*ע����*/
	adc_external_trigger_config(ADC0, ADC_REGULAR_CHANNEL, ENABLE); /*������*/

  /* clear the ADC flag */
  adc_interrupt_flag_clear(ADC0, ADC_INT_FLAG_EOC);
//  adc_interrupt_flag_clear(ADC0, ADC_INT_FLAG_EOIC);
  /* enable ADC interrupt */
  adc_interrupt_enable(ADC0, ADC_INT_EOC);

	/* ADC DMA function enable */
	adc_dma_mode_enable(ADC0);
	
  /* enable ADC interface */
  adc_enable(ADC0);
//	delay_1ms(1);

  /* ADC calibration and reset calibration */
  adc_calibration_enable(ADC0);
  
  BSP_ADC_TimerTrigInit();
	Init_dma_config();
	
}

/*
************************************************************************************************************************
* �������� : BSP_ADC_TimerTrigInit                                                                                                         
* �������� : ADC ���� ��ʱ�����ĳ�ʼ��                                                                                                     
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void BSP_ADC_TimerTrigInit(void)
{
  timer_oc_parameter_struct timer_ocintpara;
  timer_parameter_struct timer_initpara;

  /* enable timer1 clock */
  rcu_periph_clock_enable(RCU_TIMER3);
  
  /* TIMER1 configuration */
  timer_initpara.prescaler         = 5400;   //��ʱ����Ƶ 108M/5400=20khz�ļ���Ƶ��
  timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
  timer_initpara.counterdirection  = TIMER_COUNTER_UP;
  timer_initpara.period            = 1300-1;  //1300/20k=0.065s=65ms
  timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
  timer_initpara.repetitioncounter = 0;
  timer_init(TIMER3,&timer_initpara);
  
  timer_channel_output_struct_para_init(&timer_ocintpara);

  /* CH0/CH1 configuration in PWM mode1 */
  timer_ocintpara.ocpolarity  = TIMER_OC_POLARITY_HIGH;
  timer_ocintpara.outputstate = TIMER_CCX_ENABLE;

//	timer_channel_output_config(TIMER1, TIMER_CH_0, &timer_ocintpara); /*��ע����*/
//  timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_0, 1000);
//  timer_channel_output_mode_config(TIMER1, TIMER_CH_0, TIMER_OC_MODE_PWM1);
//  timer_channel_output_shadow_config(TIMER1, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);

	timer_channel_output_config(TIMER3, TIMER_CH_3, &timer_ocintpara);	/*��������*/
  timer_channel_output_pulse_value_config(TIMER3, TIMER_CH_3, 1000);
  timer_channel_output_mode_config(TIMER3, TIMER_CH_1, TIMER_OC_MODE_PWM1);
  timer_channel_output_shadow_config(TIMER3, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

  timer_enable(TIMER3);
}

/************************************************
    ������: ADCʹ�� Timer1_Ch1 ������ʹ�� DMA���� �� ����ͨ��0-15
      ˵��: 
************************************************/
void Init_dma_config(void)
{
    dma_parameter_struct dma_data_parameter;
    
    rcu_periph_clock_enable(RCU_DMA0);
    /* ADC DMA_channel configuration */
    dma_deinit(DMA0, DMA_CH0);
    
    /* initialize DMA single data mode */
    dma_data_parameter.periph_addr = (uint32_t)(&ADC_RDATA(ADC0));
    dma_data_parameter.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_data_parameter.memory_addr = (uint32_t)(&adc_value);
    dma_data_parameter.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_data_parameter.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;
    dma_data_parameter.memory_width = DMA_MEMORY_WIDTH_16BIT;  
    dma_data_parameter.direction = DMA_PERIPHERAL_TO_MEMORY;
    dma_data_parameter.number = ADC_CH_NUM;//5;//16;/*����ʵ��ת����ͨ�����޸�*/
    dma_data_parameter.priority = DMA_PRIORITY_HIGH;
    dma_init(DMA0, DMA_CH0, &dma_data_parameter);

    dma_circulation_enable(DMA0, DMA_CH0);
  
    /* enable DMA channel */
    dma_channel_enable(DMA0, DMA_CH0);
}

extern uint16_t  giTapPWMBuffer,giKneadPWMBuffer;
//��GD32E230 ���Զ�ȡ��PWM���͵�ƽ������PWM��������MOS  ADֵ����й���
uint8_t ADC_Filtering_PWM(uint16_t adc_value, uint8_t mos)
{
	switch(mos)
	{
		case 1: 
//			if(giTapPWMBuffer != 521)
//			{
//				if(adc_value > ADC_PWM_FIFO_VAL)
//					return 1;
//				else
//					return 0;
//			}
			return 1;	
		case 4:
//			if(giKneadPWMBuffer != 521)
//			{
//				if(adc_value > ADC_PWM_FIFO_VAL)
//					return 1;
//				else
//					return 0;
//			}
			return 1;	
		default:
			return 1;
	}
}
/*
************************************************************************************************************************
* �������� : ADC0_IRQHandler                                                                                                         
* �������� : ADC�жϴ���                                                                                        
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : 130MSִ��һ��                                                                                                     
************************************************************************************************************************
*/
void ADC0_1_IRQHandler(void)
{
  uint8_t i;

//  static uint8_t ll;
//  if(ll)
//  {
////    gpio_bit_write(GPIOD, GPIO_PIN_15, 0);
//		gpio_bit_write(GPIOB, GPIO_PIN_7, RESET);
//    ll = 0;
//  }
//  else
//  {
////    gpio_bit_write(GPIOD, GPIO_PIN_15, 1);
//		gpio_bit_write(GPIOB, GPIO_PIN_7, SET);
//    ll = 1;
//  }
  
  /* clear the ADC flag */
//  adc_interrupt_flag_clear(ADC0, ADC_INT_FLAG_EOIC);
  adc_interrupt_flag_clear(ADC0, ADC_INT_FLAG_EOC);
  
  /*ADC ����ֵ ���FIFO��ֵ�˲�*/
//  for(i=0; i<ADC_CH_NUM; i++)
//  {
//    ADCResult.ResultSum[i] -= ADCResult.FIFOBuf[i][ADCResult.FIFOPoint];
//    ADCResult.FIFOBuf[i][ADCResult.FIFOPoint] = adc_value[i];//adc_inserted_data_read(ADC0, ADC_INSERTED_CHANNEL_0+i); 
//    ADCResult.ResultSum[i] += ADCResult.FIFOBuf[i][ADCResult.FIFOPoint];
//    ADCResult.ResultAvg[i] = ADCResult.ResultSum[i] / ADC_RESULT_FIFO_SIZE;
//  }
//  
//  ADCResult.FIFOPoint++;
//  if(ADCResult.FIFOPoint > (ADC_RESULT_FIFO_SIZE-1))
//  {
//    ADCResult.FIFOPoint = 0;
//  }
  for(i=0; i<ADC_CH_NUM; i++)
   {
       if(ADC_Filtering_PWM(adc_value[i],i))
      {
           ADCResult.ResultSum[i] -= ADCResult.FIFOBuf[i][ADCResult.FIFOPoint[i]];
      	   ADCResult.FIFOBuf[i][ADCResult.FIFOPoint[i]] = adc_value[i];//adc_inserted_data_read(ADC0, ADC_INSERTED_CHANNEL_0+i); 
     	   ADCResult.ResultSum[i] += ADCResult.FIFOBuf[i][ADCResult.FIFOPoint[i]];
     	   ADCResult.ResultAvg[i] = ADCResult.ResultSum[i] / ADC_RESULT_FIFO_SIZE;
     	   ADCResult.FIFOPoint[i]++;
	   if(ADCResult.FIFOPoint[i] > (ADC_RESULT_FIFO_SIZE-1))
	   {
	      ADCResult.FIFOPoint[i] = 0;
	   }
      }
   }
}


/*
************************************************************************************************************************
* �������� : BSP_ADC_GetTapMotoCurrentAD                                                                                                         
* �������� : ��ȡ �û������������ ADC ����ֵ                                                                                  
* ������� : ��                                                                                                         
* ���ز��� : 8λ�ֱ��� �� ADC ֵ                                                                                                       
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
//uint8_t  BSP_ADC_GetTapMotoCurrentAD(void)
//{
//	/*12λ�ֱ��� 4096��8λ�ֱ���256�� 4096/256 = 16*/ 
//	return   (ADCResult.ResultAvg[1] >> 4);   
//}

/*
************************************************************************************************************************
* �������� : BSP_ADC_GetKneadMotoCurrentAD                                                                                                         
* �������� : ��ȡ �û������������ ADC ����ֵ                                                                                  
* ������� : ��                                                                                                         
* ���ز��� : 8λ�ֱ��� �� ADC ֵ                                                                                                       
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
//uint8_t  BSP_ADC_GetKneadMotoCurrentAD(void)
//{
//	/*12λ�ֱ��� 4096��8λ�ֱ���256�� 4096/256 = 16*/ 
//	return   (ADCResult.ResultAvg[4] >> 4);   
//}


/*
************************************************************************************************************************
* �������� : ADCOverCTestUnit                                                                                                         
* �������� : ������������ж�                                                                                  
* ������� : ������ʵʱ����AD�������ݣ�����ֵ                                                                                                         
* ���ز��� : �����жϱ�־λ                                                                                                       
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t ADCOverCTestUnit(ADCOverCData_t* ADCUnit, uint8_t ADCRealTimeValue, uint8_t OverCLimit)
{
	ADCUnit->ADCValue = ADCRealTimeValue;
	if(ADCUnit->ADCValue > OverCLimit)
	{
		if(ADCUnit->OverCTime < 255)
			ADCUnit->OverCTime++;
		if(ADCUnit->OverCTime > 20)                     //20*50=1000ms  
		{
    		ADCUnit->StateBits.OverCErrFlag = 1;
		}
	}
	else
	{
		ADCUnit->OverCTime = 0;
		//ADCOverCUnit->StateBits.OverCErrFlag = 0;/*��Ҫ������ָ����ػ�������ʱ�ָ�*/
	}
	return ADCUnit->StateBits.OverCErrFlag;
}

void ADOverCTestProcess(void)
{//50ms�ж�һ��
	/*-----------------------??????-----------------------------------*/	
//    ADCOverCTestUnit(&OverCUnit.TapMotor,BSP_ADC_GetTapMotoCurrentAD(),TAPMOTOOVERC_LIMIT);
//    ADCOverCTestUnit(&OverCUnit.KneadMotor,BSP_ADC_GetKneadMotoCurrentAD(),KNEADMOTOOVERC_LIMIT);
	/*----------------------------------------------------------------------*/
}

/*
************************************************************************************************************************
* �������� : GetJ20_ADC0_7_TAP_OverCurFlag                                                                                                         
* �������� : ��ȡ �û���� ������־                                                                                
* ������� : ��                                                                                                         
* ���ز��� :                                                                                                       
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
//uint8_t  GetJ20_ADC0_7_TAP_OverCurFlag(void)
//{
//	if(OverCUnit.TapMotor.StateBits.OverCErrFlag > 0 )
//		return   1;   
//	else
//		return   0;   
//}

/*
************************************************************************************************************************
* �������� : GetJ20_ADC0_14_KNEAD_OverCurFlag                                                                                                         
* �������� : ��ȡ ������ ������־                                                                                
* ������� : ��                                                                                                         
* ���ز��� :                                                                                                       
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
//uint8_t  GetJ20_ADC0_14_KNEAD_OverCurFlag(void)
//{
//	if(OverCUnit.KneadMotor.StateBits.OverCErrFlag > 0 )
//		return   1;   
//	else
//		return   0;   
//}


