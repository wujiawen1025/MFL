/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncMA_Vib.c 
**
**    功能描述:【振动】手动自动
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
static const uint16_t   VibCtrlOnOffTimeTab[][2] = 
{
  {100,  0},    /*长开*/

  {180,  60},
  {60,   50},
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
* 函数名称 : MChair_VibFuncReset_Feet                                                                                               
* 函数名称 : MChair_VibFuncReset_Calves                                                                                               
* 函数名称 : MChair_VibFuncReset_Seat                                                                                               
* 函数名称 : MChair_VibFuncReset_LumbarBack                                                                                               
* 功能描述 : 按摩椅 振动功能 复位                                                               
* 输入参数 : 无                                                                                
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_VibFuncReset_Feet(void)
{
  pMChair->FeetVibCtrlOnOffTime = 0;
  pMChair->FeetVibCtrlSw = OFF;
  Vib_SetFeetVibWorkState(FALSE);           /*停止工作*/ 
  Vib_FeetVibResetStep();                   /*复位步骤*/     
}

void MChair_VibFuncReset_Calves(void)
{
  pMChair->CalvesVibCtrlOnOffTime = 0;
  pMChair->CalvesVibCtrlSw = OFF;
  Vib_SetCalvesVibWorkState(FALSE);         /*停止工作*/  
  Vib_CalvesVibResetStep();                 /*复位步骤*/     
}

void MChair_VibFuncReset_Seat(void)
{
  pMChair->SeatVibCtrlOnOffTime = 0;
  pMChair->SeatVibCtrlSw = OFF;
  Vib_SetSeatVibWorkState(FALSE);           /*停止工作*/  
  Vib_SeatVibResetStep();                   /*复位步骤*/     
}

void MChair_VibFuncReset_LumbarBack(void)
{
  pMChair->LumbarBackVibCtrlOnOffTime = 0;
  pMChair->LumbarBackVibCtrlSw = OFF;
  Vib_SetLumbarBackVibWorkState(FALSE);     /*停止工作*/
  Vib_LumbarBackVibResetStep();             /*复位步骤*/     
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncSwitch_VibMA                                                                                               
* 功能描述 : 按摩椅 功能切换 之  【振动】手动自动                                                                   
* 输入参数 : SwitchMode -- 要切换模式
*            pFuncLogic -- 功能逻辑的描述                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_VibMA(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  VibAction_t VibActionCur;
  VibAction_t VibActionHis;

  VibActionCur.All = *pFuncLogic->pFuncCur;
  VibActionHis.All = *pFuncLogic->pFuncHis;

  if((VibActionCur.Bit.Feet != VibActionHis.Bit.Feet) || (CLOSE == SwitchMode))
  {
    MChair_VibFuncReset_Feet();
  }
  
  if((VibActionCur.Bit.Calves != VibActionHis.Bit.Calves) || (CLOSE == SwitchMode))
  {
    MChair_VibFuncReset_Calves();
  }
  
  if((VibActionCur.Bit.Seat != VibActionHis.Bit.Seat) || (CLOSE == SwitchMode))
  {
    MChair_VibFuncReset_Seat();
  }

  if((VibActionCur.Bit.LumbarBack != VibActionHis.Bit.LumbarBack) || (CLOSE == SwitchMode))
  {
    MChair_VibFuncReset_LumbarBack();
  }
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncExe_VibMA                                                                                               
* 功能描述 : 按摩椅 功能执行 之  【振动】手动自动                                                                   
* 输入参数 : ExePeriod  -- 执行周期
*            pFuncLogic -- 指向自身功能逻辑的指针。                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_VibMA(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  uint16_t OnTime;
  uint16_t OffTime;

  switch(pMChair->FuncMA_Vib.Bit.Feet)
  {
    case FMA_VIB_NONE:
    {
      pMChair->FeetVibCtrlSw = OFF;
    }break;

    case FMA_FEET_VIB_Mannual:         /*手动，则常开*/
    {
      pMChair->ComponentFuncState.Bit.FeetVib = FUNC_TYPE_MANNUALAUTO; /*功能状态：手动自动*/

      pMChair->FeetVibCtrlSw = ON;
    }break;

    case FMA_FEET_VIB_ByActionTab:    /*由表格内的值来控制，见ActionObjHandle_AccompanyFunc()函数*/
    {
      pMChair->ComponentFuncState.Bit.FeetVib = FUNC_TYPE_MANNUALAUTO; /*功能状态：手动自动*/
    }break;

    case FMA_FEET_VIB_ByTime_OnAlways:    /*由时间控制*/
    case FMA_FEET_VIB_ByTime_On180s_Off60s:
    case FMA_FEET_VIB_ByTime_On60s_Off50s:
    case FMA_FEET_VIB_ByTime_On300s_Off60s:
    {
      pMChair->ComponentFuncState.Bit.FeetVib = FUNC_TYPE_MANNUALAUTO; /*功能状态：手动自动*/

      pMChair->FeetVibCtrlOnOffTime += ExePeriod;
      OnTime  = VibCtrlOnOffTimeTab[pMChair->FuncMA_Vib.Bit.Feet - FMA_FEET_VIB_ByTime_OnAlways][0];
      OffTime = OnTime + VibCtrlOnOffTimeTab[pMChair->FuncMA_Vib.Bit.Feet - FMA_FEET_VIB_ByTime_OnAlways][1];
      if(pMChair->FeetVibCtrlOnOffTime/1000 < OnTime) 
      {
        pMChair->FeetVibCtrlSw = ON;
      }
      else if(pMChair->FeetVibCtrlOnOffTime/1000 < OffTime)
      {
        pMChair->FeetVibCtrlSw = OFF;
      }
      else
      {
        pMChair->FeetVibCtrlOnOffTime = 0;
      }

    }break;

    default:
    {
      pMChair->FuncMA_Vib.Bit.Feet = FMA_VIB_NONE;
    }break;
  }
  Vib_SetFeetVibWorkState((ON == pMChair->FeetVibCtrlSw) ? TRUE:FALSE);  

  /*-------------------------------------------------------------------------------------*/

}

