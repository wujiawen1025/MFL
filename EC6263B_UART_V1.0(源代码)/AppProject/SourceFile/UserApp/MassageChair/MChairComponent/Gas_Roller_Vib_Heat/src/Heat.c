/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: Heat.c                                                                                                         
**
**    功能描述: 加热驱动
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
#include "Heat.h"
#include "ESF.h"


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
static Heat_t   Heat;
Heat_t   *pHeat = &Heat;

/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/


/*
************************************************************************************************************************
* 函数名称 : Heat_GetLumbarBackLeftTemperature                                                                                                         
* 函数名称 : Heat_GetLumbarBackRightTemperature                                                                                                         
* 功能描述 : 获取温度                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 左按摩头温度                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
int8_t Heat_GetLumbarBackLeftTemperature(void)
{
  return pHeat->SetQry0x41.MassageHeadTemp1;
}

int8_t Heat_GetLumbarBackRightTemperature(void)
{
  return pHeat->SetQry0x41.MassageHeadTemp2;
}



/*
************************************************************************************************************************
* 函数名称 : Heat_SetFeetHeatFunc      
* 函数名称 : Heat_SetCalvesHeatFunc      
* 函数名称 : Heat_SetSeatHeatFunc      
* 函数名称 : Heat_SetLumbarBackHeatFunc      
* 功能描述 : 设置加热的工作与不工作                                                                                     
* 输入参数 : TrueFalse -- TRUE  工作
*                         FALSE 不工作                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Heat_SetFeetHeatWorkState(uint8_t TrueFalse)
{
  #if(1==HEAT_FEET_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pHeat->CSFlag.Bit.FeetWork = TrueFalse;
  #endif
}

void Heat_SetCalvesHeatWorkState(uint8_t TrueFalse)
{
  #if(1==HEAT_CALVES_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pHeat->CSFlag.Bit.CalvesWork = TrueFalse;
  #endif
}

void Heat_SetSeatHeatWorkState(uint8_t TrueFalse)
{
  #if(1==HEAT_SEAT_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pHeat->CSFlag.Bit.SeatWork = TrueFalse;
  #endif
}

void Heat_SetLumbarBackHeatWorkState(uint8_t TrueFalse)
{
  #if(1==HEAT_LUMBARBACK_EN)
  if((TrueFalse != TRUE) && (TrueFalse != FALSE))
  {
    TrueFalse = FALSE;
  }
  pHeat->CSFlag.Bit.LumbarBackWork = TrueFalse;
  #endif
}


/*
************************************************************************************************************************
* 函数名称 : Heat_FeetHeatPauseOn                                                                                                         
* 函数名称 : Heat_CalvesHeatPauseOn                                                                                                         
* 函数名称 : Heat_SeatHeatPauseOn                                                                                                         
* 函数名称 : Heat_LumbarBackHeatPauseOn                                                                                                         
* 功能描述 : 暂停加热功能                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Heat_FeetHeatPauseOn(void)
{
  #if(1==HEAT_FEET_EN)
  if(pHeat->CSFlag.Bit.FeetPause < 0x1F)
  {
    pHeat->CSFlag.Bit.FeetPause++;
  }
  #endif
}

void Heat_CalvesHeatPauseOn(void)
{
  #if(1==HEAT_CALVES_EN)
  if(pHeat->CSFlag.Bit.CalvesPause < 0x1F)
  {
    pHeat->CSFlag.Bit.CalvesPause++;
  }
  #endif
}

void Heat_SeatHeatPauseOn(void)
{
  #if(1==HEAT_SEAT_EN)
  if(pHeat->CSFlag.Bit.SeatPause < 0x1F)
  {
    pHeat->CSFlag.Bit.SeatPause++;
  }
  #endif
}

void Heat_LumbarBackHeatPauseOn(void)
{
  #if(1==HEAT_LUMBARBACK_EN)
  if(pHeat->CSFlag.Bit.LumbarBackPause < 0x1F)
  {
    pHeat->CSFlag.Bit.LumbarBackPause++;
  }
  #endif
}

/*
************************************************************************************************************************
* 函数名称 : Heat_FeetHeatPauseOff                                                                                                         
* 函数名称 : Heat_CalvesHeatPauseOff                                                                                                         
* 函数名称 : Heat_SeatHeatPauseOff                                                                                                         
* 函数名称 : Heat_LumbarBackHeatPauseOff                                                                                                         
* 功能描述 : 解除暂停加热功能                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Heat_FeetHeatPauseOff(void)
{
  #if(1==HEAT_FEET_EN)
  if(pHeat->CSFlag.Bit.FeetPause > 0)
  {
    pHeat->CSFlag.Bit.FeetPause--;
  }
  #endif
}

void Heat_CalvesHeatPauseOff(void)
{
  #if(1==HEAT_CALVES_EN)
  if(pHeat->CSFlag.Bit.CalvesPause > 0)
  {
    pHeat->CSFlag.Bit.CalvesPause--;
  }
  #endif
}

void Heat_SeatHeatPauseOff(void)
{
  #if(1==HEAT_SEAT_EN)
  if(pHeat->CSFlag.Bit.SeatPause > 0)
  {
    pHeat->CSFlag.Bit.SeatPause--;
  }
  #endif
}

void Heat_LumbarBackHeatPauseOff(void)
{
  #if(1==HEAT_LUMBARBACK_EN)
  if(pHeat->CSFlag.Bit.LumbarBackPause > 0)
  {
    pHeat->CSFlag.Bit.LumbarBackPause--;
  }
  #endif
}


/*
************************************************************************************************************************
* 函数名称 : Heat_FeetHeatHandle                                                                                                         
* 函数名称 : Heat_CalvesHeatHandle                                                                                                         
* 函数名称 : Heat_SeatHeatHandle                                                                                                         
* 函数名称 : Heat_LumbarBackHeatHandle                                                                                                         
* 函数名称 : Heat_AllPartsHandle                                                                                                         
* 功能描述 : 各部位加热加热处理                                                                                     
* 输入参数 : ExePeriod -- 函数的执行周期                                                                                    
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Heat_FeetHeatHandle(Ticker_t ExePeriod)
{
  #if(1==HEAT_FEET_EN)
  do
  {
    if(pHeat->CSFlag.Bit.FeetPause > 0)
    {
      pHeat->CSFlag.Bit.FeetRun = OFF;
      break;
    }

    if(TRUE == pHeat->CSFlag.Bit.FeetWork) /*工作*/
    {
      pHeat->CSFlag.Bit.FeetRun = ON;
    }
    else  /*不使能*/
    {
      pHeat->CSFlag.Bit.FeetRun = OFF;
    }

  }while(0);

  //BSP_IO_SetOutput_FeetHeatCtrl(pHeat->CSFlag.Bit.FeetRun);
  #endif
}

void Heat_CalvesHeatHandle(Ticker_t ExePeriod)
{
  #if(1==HEAT_CALVES_EN)
  do
  {
    if(pHeat->CSFlag.Bit.CalvesPause > 0)
    {
      pHeat->CSFlag.Bit.CalvesRun = OFF;
      break;
    }

    if(TRUE == pHeat->CSFlag.Bit.CalvesWork) /*工作*/
    {
      pHeat->CSFlag.Bit.CalvesRun = ON;
    }
    else  /*不使能*/
    {
      pHeat->CSFlag.Bit.CalvesRun = OFF;
    }

  }while(0);

  BSP_IO_SetOutput_CalvesHeat(pHeat->CSFlag.Bit.CalvesRun);
//  pHeat->SetQry0x4E.Byte0.Bit.CalvesWork = pHeat->CSFlag.Bit.LumbarBackWork;
//  pHeat->SetQry0x4E.Byte0.Bit.CalvesPause = (pHeat->CSFlag.Bit.LumbarBackPause > 0) ? 1:0;
  #endif
}

void Heat_SeatHeatHandle(Ticker_t ExePeriod)
{
  #if(1==HEAT_SEAT_EN)
  do
  {
    if(pHeat->CSFlag.Bit.SeatPause > 0)
    {
      pHeat->CSFlag.Bit.SeatRun = OFF;
      break;
    }

    if(TRUE == pHeat->CSFlag.Bit.SeatWork) /*工作*/
    {
      pHeat->CSFlag.Bit.SeatRun = ON;
    }
    else  /*不使能*/
    {
      pHeat->CSFlag.Bit.SeatRun = OFF;
    }

  }while(0);

  //BSP_IO_SetOutput_SeatHeatCtrl(pHeat->CSFlag.Bit.SeatRun);

  #endif
}

void Heat_LumbarBackHeatHandle(Ticker_t ExePeriod)
{
  #if(1==HEAT_LUMBARBACK_EN)
  do
  {
    if(pHeat->CSFlag.Bit.LumbarBackPause > 0)
    {
      pHeat->CSFlag.Bit.LumbarBackRun = OFF;
      break;
    }

    if(TRUE == pHeat->CSFlag.Bit.LumbarBackWork) /*工作*/
    {
      pHeat->CSFlag.Bit.LumbarBackRun = ON;
    }
    else  /*不使能*/
    {
      pHeat->CSFlag.Bit.LumbarBackRun = OFF;
    }

  }while(0);
  //BSP_IO_SetOutput_LumbarBackHeat(pHeat->CSFlag.Bit.LumbarBackRun);
  pHeat->SetQry0x41.Byte0.Bit.MassageHeadHeatWork = pHeat->CSFlag.Bit.LumbarBackWork;

  #endif
}


void Heat_AllPartsHandle(Ticker_t ExePeriod)                                                                                                         
{
  Heat_FeetHeatHandle(ExePeriod);
  Heat_CalvesHeatHandle(ExePeriod);  
  Heat_SeatHeatHandle(ExePeriod);
  Heat_LumbarBackHeatHandle(ExePeriod);
}


/*
========================================================================================================================
*         加热功能函数表                           加热功能函数表                           加热功能函数表
========================================================================================================================
*/
#define  HEAT_TICK_COUNT_BUF_NUM   1
static Ticker_t Heat_TickCount[HEAT_TICK_COUNT_BUF_NUM];
static const ESF_TmrExeFunc_t  Heat_TmrExeFuncTab[] = 
{
  /*   执行函数              执行周期(ms)     时间计数变量*/
  {Heat_AllPartsHandle,         200,          &Heat_TickCount[0]}  
};

#define  HEAT_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(Heat_TmrExeFuncTab)

/*
************************************************************************************************************************
* 函数名称 : Heat_Handle                                                                                                         
* 功能描述 : 加热处理                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Heat_Handle(void)
{
  /*调度功能函数表------------------------------------------------*/
  ESF_TmrExeFuncScheduling(Heat_TmrExeFuncTab, HEAT_TMR_EXE_FUNC_TAB_NUM);
}

/*
************************************************************************************************************************
* 函数名称 : Heat_Init                                                                                                         
* 功能描述 : 加热初始化                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 返回 可操作加热功能 的结构体 的指针                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
Heat_t*  Heat_Init(void)
{
  /*初始化相关数据------------------------------------------*/
  memset(pHeat, 0, sizeof(Heat_t)); /*清零所有数据*/

  /*检测 Heat_TmrExeFuncTab 功能函数表排列是否正确------------------------*/
  ESF_TmrExeFuncTabCheck(Heat_TmrExeFuncTab, HEAT_TMR_EXE_FUNC_TAB_NUM, HEAT_TICK_COUNT_BUF_NUM);

  return pHeat;
}

/*
************************************************************************************************************************
* 函数名称 : Heat_GetCSFlag                                                                                                         
* 功能描述 : 获得 控制 与 状态 标识                                                                                     
* 输入参数 : 无                                                                                      
* 返回参数 : 控制与状态标识 的结构体                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
HeatCSFlag_t Heat_GetCSFlag(void)
{
  return pHeat->CSFlag;
}

/*
************************************************************************************************************************
* 函数名称 : Heat_CDPDataObjRx_0x41                                                                                      
* 功能描述 : 0x41 按摩头加热控制(中心板<-->机芯板）：应用于 中心板和机芯板单独布板的系统，且机芯板实现成一个独立的逻辑模块。
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象中数据的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t Heat_CDPDataObjRx_0x41(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  /*更新数据到中心板-------------------------------------------------------------*/
  memcpy((uint8_t *)&pHeat->SetQry0x41, &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);
  pHeat->CSFlag.Bit.LumbarBackRun  = pHeat->SetQry0x41.Byte0.Bit.MassageHeadHeatRun;
  pHeat->CSFlag.Bit.LumbarBackThyristorShortFault  = pHeat->SetQry0x41.Byte3.Bit.MassageHeadThyristorShortFault;
  pHeat->CSFlag.Bit.LumbarBackThermistorShortFault  = pHeat->SetQry0x41.Byte3.Bit.MassageHeadThermistorShortFault;
  pHeat->CSFlag.Bit.LumbarBackThermistorOpenFault  = pHeat->SetQry0x41.Byte3.Bit.MassageHeadThermistorOpenFault;
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* 函数名称 : Heat_CDPDataObjTx_0x41                                                                                      
* 功能描述 : 0x41 按摩头加热控制(中心板<-->机芯板）：应用于 中心板和机芯板单独布板的系统，且机芯板实现成一个独立的逻辑模块。
* 输入参数 : 无
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t* Heat_CDPDataObjTx_0x41(void)
{
  pHeat->SetQry0x41.Byte0.Bit.MassageHeadHeatPause = (pHeat->CSFlag.Bit.LumbarBackPause > 0) ? TRUE : FALSE;

  pHeat->SetQry0x41.DataLen = sizeof(pHeat->SetQry0x41);  
  pHeat->SetQry0x41.DataID = 0x41;  

  return (uint8_t *)&pHeat->SetQry0x41;
}
