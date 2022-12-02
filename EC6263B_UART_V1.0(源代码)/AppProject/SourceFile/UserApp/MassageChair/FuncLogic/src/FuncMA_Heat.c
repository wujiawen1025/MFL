/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncMA_Heat.c 
**
**    功能描述:【加热】手动自动
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
#include "FuncLogic.h"
#include "FuncTab.h"
#include "MChair.h"


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
*【变量定义 & 各种声明】                          【变量定义 & 各种声明】                         【变量定义 & 各种声明】    
========================================================================================================================
*/
static const uint16_t   HeatCtrlOnOffTimeTab[][2] = 
{
  {100,  0},    /*长开*/

  {180,  60},
  {120,  180},
  {300,  60},

  {0,    100}   /*长关*/
};

/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : MChair_HeatFuncReset_Feet                                                                                               
* 函数名称 : MChair_HeatFuncReset_Calves                                                                                               
* 函数名称 : MChair_HeatFuncReset_Seat                                                                                               
* 函数名称 : MChair_HeatFuncReset_LumbarBack                                                                                               
* 功能描述 : 按摩椅 加热功能 复位                                                               
* 输入参数 : 无                                                                                
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_HeatFuncReset_Feet(void)
{
  pMChair->FeetHeatCtrlOnOffTime = 0;
  pMChair->FeetHeatCtrlSw = OFF;
  Heat_SetFeetHeatWorkState(FALSE);  
}

void MChair_HeatFuncReset_Calves(void)
{
  pMChair->CalvesHeatCtrlOnOffTime = 0;
  pMChair->CalvesHeatCtrlSw = OFF;
  Heat_SetCalvesHeatWorkState(FALSE);  
}

void MChair_HeatFuncReset_Seat(void)
{
  pMChair->SeatHeatCtrlOnOffTime = 0;
  pMChair->SeatHeatCtrlSw = OFF;
  Heat_SetSeatHeatWorkState(FALSE);  
}

void MChair_HeatFuncReset_LumbarBack(void)
{
  pMChair->LumbarBackHeatCtrlOnOffTime = 0;
  pMChair->LumbarBackHeatCtrlSw = OFF;
  Heat_SetLumbarBackHeatWorkState(FALSE);  
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncSwitch_HeatMA                                                                                               
* 功能描述 : 按摩椅 功能切换 之  【加热】手动自动                                                                   
* 输入参数 : SwitchMode -- 要切换模式
*            pFuncLogic -- 功能逻辑的描述                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_HeatMA(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  HeatAction_t   HeatActionCur;
  HeatAction_t   HeatActionHis;

  HeatActionCur.All = *pFuncLogic->pFuncCur;
  HeatActionHis.All = *pFuncLogic->pFuncHis;
  
  if((HeatActionCur.Bit.Feet != HeatActionHis.Bit.Feet) || (CLOSE == SwitchMode)) 
  {
    MChair_HeatFuncReset_Feet();
  }
  
  if((HeatActionCur.Bit.Calves != HeatActionHis.Bit.Calves) || (CLOSE == SwitchMode)) 
  {
    MChair_HeatFuncReset_Calves();
  }
  
  if((HeatActionCur.Bit.Seat != HeatActionHis.Bit.Seat) || (CLOSE == SwitchMode)) 
  {
    MChair_HeatFuncReset_Seat();
  }

  if((HeatActionCur.Bit.LumbarBack != HeatActionHis.Bit.LumbarBack) || (CLOSE == SwitchMode))
  {
    MChair_HeatFuncReset_LumbarBack();
  }
}
/*
************************************************************************************************************************
* 函数名称 : MChair_FuncExe_HeatMA                                                                                               
* 功能描述 : 按摩椅 功能执行 之  【加热】手动自动                                                                   
* 输入参数 : ExePeriod  -- 执行周期
*            pFuncLogic -- 指向自身功能逻辑的指针。                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_HeatMA(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  uint16_t OnTime;
  uint16_t OffTime;


  switch(pMChair->FuncMA_Heat.Bit.Calves)
  {
    case FMA_HEAT_NONE:
    {
      pMChair->CalvesHeatCtrlSw = OFF;
    }break;

    case FMA_CALVES_HEAT_Mannual:         /*手动，则常开*/
    {
      pMChair->ComponentFuncState.Bit.CalvesHeat = FUNC_TYPE_MANNUALAUTO; /*功能状态：手动自动*/

      pMChair->CalvesHeatCtrlSw = ON;
    }break;

    case FMA_CALVES_HEAT_ByActionTab:    /*由表格内的值来控制，见ActionObjHandle_AccompanyFunc()函数*/
    {
      pMChair->ComponentFuncState.Bit.CalvesHeat = FUNC_TYPE_MANNUALAUTO; /*功能状态：手动自动*/
    }break;

    case FMA_CALVES_HEAT_ByTime_OnAlways:    /*由时间控制*/
    case FMA_CALVES_HEAT_ByTime_On180s_Off60s:
    case FMA_CALVES_HEAT_ByTime_On120s_Off180s:
    case FMA_CALVES_HEAT_ByTime_On300s_Off60s:
    {
      pMChair->ComponentFuncState.Bit.CalvesHeat = FUNC_TYPE_MANNUALAUTO; /*功能状态：手动自动*/

      pMChair->CalvesHeatCtrlOnOffTime += ExePeriod;
      OnTime  = HeatCtrlOnOffTimeTab[pMChair->FuncMA_Heat.Bit.Calves - FMA_CALVES_HEAT_ByTime_OnAlways][0];
      OffTime = OnTime + HeatCtrlOnOffTimeTab[pMChair->FuncMA_Heat.Bit.Calves - FMA_CALVES_HEAT_ByTime_OnAlways][1];
      if(pMChair->CalvesHeatCtrlOnOffTime/1000 < OnTime) 
      {
        pMChair->CalvesHeatCtrlSw = ON;
      }
      else if(pMChair->CalvesHeatCtrlOnOffTime/1000 < OffTime)
      {
        pMChair->CalvesHeatCtrlSw = OFF;
      }
      else
      {
        pMChair->CalvesHeatCtrlOnOffTime = 0;
      }
    }break;

    default:
    {
      pMChair->FuncMA_Heat.Bit.Calves = FMA_HEAT_NONE;
    }break;
  }
  Heat_SetCalvesHeatWorkState((ON == pMChair->CalvesHeatCtrlSw) ? TRUE:FALSE);  

  
  /*--------------------------------------------------------------------------------------------------*/
  if(pMChair->FuncMA_Heat.Bit.Feet != FMA_HEAT_NONE)
  {
    pMChair->ComponentFuncState.Bit.FeetHeat = FUNC_TYPE_MANNUALAUTO; /*功能状态：手动自动*/
    Heat_SetFeetHeatWorkState(TRUE);  
  }
  else
  {
    Heat_SetFeetHeatWorkState(FALSE);  
  }

  /*--------------------------------------------------------------------------------------------------*/
//  if(pMChair->FuncMA_Heat.Bit.Calves != FMA_HEAT_NONE)
//  {
//    pMChair->ComponentFuncState.Bit.CalvesHeat = FUNC_TYPE_MANNUALAUTO; /*功能状态：手动自动*/

//    Heat_SetCalvesHeatWorkState(TRUE);  
//  }
//  else
//  {
//    Heat_SetCalvesHeatWorkState(FALSE);  
//  }
  
  /*--------------------------------------------------------------------------------------------------*/
  if(pMChair->FuncMA_Heat.Bit.LumbarBack != FMA_HEAT_NONE)
  {
    pMChair->ComponentFuncState.Bit.LumbarBackHeat = FUNC_TYPE_MANNUALAUTO; /*功能状态：手动自动*/
    pMChair->LumbarBackHeatCtrlSw = ON;
  }
  else
  {
    pMChair->LumbarBackHeatCtrlSw = OFF;
  }
  Heat_SetLumbarBackHeatWorkState((ON == pMChair->LumbarBackHeatCtrlSw) ? TRUE:FALSE);  
}

