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
#define  ADC_CH_NUM                     2         /*ADC ת��ͨ������*/

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
  uint8_t     FIFOPoint;
  uint16_t    FIFOBuf[ADC_CH_NUM][ADC_RESULT_FIFO_SIZE];
  uint16_t    ResultAvg[ADC_CH_NUM];
  uint32_t    ResultSum[ADC_CH_NUM];
}ADCResult_t;


/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/
/*static*/ ADCResult_t           ADCResult;
//static volatile uint8_t      ADCConversionFinish;       /* ת����ɱ�־ */
uint8_t ADCChannelMap[] = {ADC_Channel_5, ADC_Channel_4}; 


void BSP_ADC_TimerTrigInit(void);

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
  GPIO_InitTypeDef      GPIO_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  ADC_InitTypeDef       ADC_InitStructure;
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);                         //ʹ��GPIOAʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);                          //ʹ��ADC1ʱ��

  /* ��ʼ��ADC1ͨ��5 IO�� */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4;                                     //PA5 ͨ��5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;                                  //ģ������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;                             //����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);                                        //��ʼ��  
  
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                      //����ģʽ
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;  //���������׶�֮����ӳ�5��ʱ��
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;       //DMAʧ��
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;                   //Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure);                                     //��ʼ��
  
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                        //12λģʽ
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;                                 //��ɨ��ģʽ
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                           //�ر�����ת��
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;   //��ֹ������⣬ʹ���������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                        //�Ҷ���
  ADC_InitStructure.ADC_NbrOfConversion = 1;                                    //1��ת���ڹ��������� Ҳ����ֻת����������1 
  ADC_Init(ADC1, &ADC_InitStructure);                                           //ADC��ʼ��
          
  ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_480Cycles );  //ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_144Cycles );  //ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
 
  ADC_Cmd(ADC1, ENABLE);                                                        //����ADת����	
    
  BSP_ADC_TimerTrigInit();
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
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);              //ʹ��TIM3ʱ��
  
  TIM_TimeBaseInitStructure.TIM_Period = 3000-1;                   //�Զ���װ��ֵ ����3000��Ϊ300ms  
  TIM_TimeBaseInitStructure.TIM_Prescaler = 8400-1;                //��ʱ����Ƶ  ��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ��
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
  
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);               //��ʼ��TIM3
  
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                         //����ʱ��3�����ж�
  TIM_Cmd(TIM3,ENABLE);                                            //ʹ�ܶ�ʱ��3
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                  //��ʱ��3�ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;     //��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;            //�����ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*
************************************************************************************************************************
* �������� : BSP_ADC_Get                                                                                                         
* �������� :                                                                                         
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint16_t BSP_ADC_Get(uint8_t ch)   
{
   //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
  ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
  ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת����������	
   
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

  return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

/*
************************************************************************************************************************
* �������� : TIM3_IRQHandler                                                                                                         
* �������� : TIM3 ��ʱ�жϴ���ADC��������                                                                                        
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void TIM3_IRQHandler(void)
{
  uint8_t i;
  
  if( TIM_GetITStatus(TIM3,TIM_IT_Update) == SET )                             /* ����ж� */
  {
    /*ADC ����ֵ ���FIFO��ֵ�˲�*/
    for(i=0; i<ADC_CH_NUM; i++)
    {
      ADCResult.ResultSum[i] -= ADCResult.FIFOBuf[i][ADCResult.FIFOPoint];
      ADCResult.FIFOBuf[i][ADCResult.FIFOPoint] = BSP_ADC_Get(ADCChannelMap[i]); 
      ADCResult.ResultSum[i] += ADCResult.FIFOBuf[i][ADCResult.FIFOPoint];
      ADCResult.ResultAvg[i] = ADCResult.ResultSum[i] / ADC_RESULT_FIFO_SIZE;
    }
    
    ADCResult.FIFOPoint++;
    if(ADCResult.FIFOPoint > (ADC_RESULT_FIFO_SIZE-1))
    {
      ADCResult.FIFOPoint = 0;
    }
  }
  TIM_ClearITPendingBit(TIM3,TIM_IT_Update);                                      /* ����жϱ�־λ */
}

/*
************************************************************************************************************************
* �������� : ADC0_IRQHandler                                                                                                         
* �������� : ADC�жϴ���                                                                                        
* ������� : ��                                                                                                         
* ���ز��� : ��                                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
//void ADC_IRQHandler(void)
//{

//}

/*
************************************************************************************************************************
* �������� : BSP_ADC_GetFeetTemperatureAD                                                                                                         
* �������� : ��ȡ �㲿 �¶� ADC ����ֵ                                                                                     
* ������� : ��                                                                                                         
* ���ز��� : 8λ�ֱ��� �� ADC ֵ                                                                                                       
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t  BSP_ADC_GetFeetTemperatureAD(void)
{
  /*12λ�ֱ��� 4096��8λ�ֱ���256�� 4096/256 = 16*/ 
  return   (ADCResult.ResultAvg[0] >> 4);   
}


/*
************************************************************************************************************************
* �������� : BSP_ADC_GetBackLeftTemperatureAD                                                                                                         
* �������� : ��ȡ �� �¶� ADC ����ֵ                                                                                  
* ������� : ��                                                                                                         
* ���ز��� : 8λ�ֱ��� �� ADC ֵ                                                                                                       
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
//uint8_t  BSP_ADC_GetBackLeftTemperatureAD(void)
//{
//  /*12λ�ֱ��� 4096��8λ�ֱ���256�� 4096/256 = 16*/ 
//  return   (ADCResult.ResultAvg[2] >> 4);   
//}

/*
************************************************************************************************************************
* �������� : BSP_ADC_GetBackRightTemperatureAD                                                                                                         
* �������� : ��ȡ �ұ�  �¶� ADC ����ֵ                                                                                
* ������� : ��                                                                                                         
* ���ز��� : 8λ�ֱ��� �� ADC ֵ                                                                                                       
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
//uint8_t  BSP_ADC_GetBackRightTemperatureAD(void)
//{
//  /*12λ�ֱ��� 4096��8λ�ֱ���256�� 4096/256 = 16*/ 
//  return   (ADCResult.ResultAvg[1] >> 4);   
//}
