/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: bsp_adc.c
**
**    功能描述: adc输入检测
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
#include "bsp_adc.h"          


/*
========================================================================================================================
*【本地宏定义】                                       【本地宏定义】                                       【本地宏定义】
========================================================================================================================
*/
#define  ADC_RESULT_FIFO_SIZE           5         /*FIFO 滤波 缓存大小*/
#define  ADC_CH_NUM                     2         /*ADC 转换通道数量*/

/*
========================================================================================================================
*【本地数据类型定义】                              【本地数据类型定义】                              【本地数据类型定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 类型定义 : ADC转换结果 相关操作数据结构                                                                                                        
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
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                          【变量定义 & 各种声明】    
========================================================================================================================
*/
/*static*/ ADCResult_t           ADCResult;
//static volatile uint8_t      ADCConversionFinish;       /* 转换完成标志 */
uint8_t ADCChannelMap[] = {ADC_Channel_5, ADC_Channel_4}; 


void BSP_ADC_TimerTrigInit(void);

/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/

/*
************************************************************************************************************************
* 函数名称 : BSP_ADC_Init                                                                                                         
* 功能描述 : ADC 功能初始化                                                                                                     
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : ADC功能都是各个相应IO的默认功能，可以不用映射
*            ADC0_SE0 --> PTA0                                                                                                         
************************************************************************************************************************
*/
void BSP_ADC_Init(void)
{
  GPIO_InitTypeDef      GPIO_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  ADC_InitTypeDef       ADC_InitStructure;
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);                         //使能GPIOA时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);                          //使能ADC1时钟

  /* 初始化ADC1通道5 IO口 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4;                                     //PA5 通道5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;                                  //模拟输入
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;                             //不带上下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);                                        //初始化  
  
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                      //独立模式
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;  //两个采样阶段之间的延迟5个时钟
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;       //DMA失能
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;                   //预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure);                                     //初始化
  
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;                        //12位模式
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;                                 //非扫描模式
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                           //关闭连续转换
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;   //禁止触发检测，使用软件触发
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                        //右对齐
  ADC_InitStructure.ADC_NbrOfConversion = 1;                                    //1个转换在规则序列中 也就是只转换规则序列1 
  ADC_Init(ADC1, &ADC_InitStructure);                                           //ADC初始化
          
  ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_480Cycles );  //ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_144Cycles );  //ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
 
  ADC_Cmd(ADC1, ENABLE);                                                        //开启AD转换器	
    
  BSP_ADC_TimerTrigInit();
}

/*
************************************************************************************************************************
* 函数名称 : BSP_ADC_TimerTrigInit                                                                                                         
* 功能描述 : ADC 功能 定时触发的初始化                                                                                                     
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void BSP_ADC_TimerTrigInit(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);              //使能TIM3时钟
  
  TIM_TimeBaseInitStructure.TIM_Period = 3000-1;                   //自动重装载值 计数3000次为300ms  
  TIM_TimeBaseInitStructure.TIM_Prescaler = 8400-1;                //定时器分频  定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
  
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);               //初始化TIM3
  
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                         //允许定时器3更新中断
  TIM_Cmd(TIM3,ENABLE);                                            //使能定时器3
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                  //定时器3中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;     //抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;            //子优先级3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*
************************************************************************************************************************
* 函数名称 : BSP_ADC_Get                                                                                                         
* 功能描述 :                                                                                         
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint16_t BSP_ADC_Get(uint8_t ch)   
{
   //设置指定ADC的规则组通道，一个序列，采样时间
  ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
  ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	
   
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

  return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

/*
************************************************************************************************************************
* 函数名称 : TIM3_IRQHandler                                                                                                         
* 功能描述 : TIM3 定时中断触发ADC采样处理                                                                                        
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void TIM3_IRQHandler(void)
{
  uint8_t i;
  
  if( TIM_GetITStatus(TIM3,TIM_IT_Update) == SET )                             /* 溢出中断 */
  {
    /*ADC 采样值 软件FIFO均值滤波*/
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
  TIM_ClearITPendingBit(TIM3,TIM_IT_Update);                                      /* 清除中断标志位 */
}

/*
************************************************************************************************************************
* 函数名称 : ADC0_IRQHandler                                                                                                         
* 功能描述 : ADC中断处理                                                                                        
* 输入参数 : 无                                                                                                         
* 返回参数 : 无                                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
//void ADC_IRQHandler(void)
//{

//}

/*
************************************************************************************************************************
* 函数名称 : BSP_ADC_GetFeetTemperatureAD                                                                                                         
* 功能描述 : 获取 足部 温度 ADC 采样值                                                                                     
* 输入参数 : 无                                                                                                         
* 返回参数 : 8位分辨率 的 ADC 值                                                                                                       
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t  BSP_ADC_GetFeetTemperatureAD(void)
{
  /*12位分辨率 4096，8位分辨率256， 4096/256 = 16*/ 
  return   (ADCResult.ResultAvg[0] >> 4);   
}


/*
************************************************************************************************************************
* 函数名称 : BSP_ADC_GetBackLeftTemperatureAD                                                                                                         
* 功能描述 : 获取 左背 温度 ADC 采样值                                                                                  
* 输入参数 : 无                                                                                                         
* 返回参数 : 8位分辨率 的 ADC 值                                                                                                       
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
//uint8_t  BSP_ADC_GetBackLeftTemperatureAD(void)
//{
//  /*12位分辨率 4096，8位分辨率256， 4096/256 = 16*/ 
//  return   (ADCResult.ResultAvg[2] >> 4);   
//}

/*
************************************************************************************************************************
* 函数名称 : BSP_ADC_GetBackRightTemperatureAD                                                                                                         
* 功能描述 : 获取 右背  温度 ADC 采样值                                                                                
* 输入参数 : 无                                                                                                         
* 返回参数 : 8位分辨率 的 ADC 值                                                                                                       
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
//uint8_t  BSP_ADC_GetBackRightTemperatureAD(void)
//{
//  /*12位分辨率 4096，8位分辨率256， 4096/256 = 16*/ 
//  return   (ADCResult.ResultAvg[1] >> 4);   
//}
