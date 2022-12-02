/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncMA_Roller.c 
**
**    功能描述:【滚轮】手动自动
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
static const uint16_t   FeetRollerCtrlOnOffTimeTab[][2] = 
{
  {100,  0},    /*长开*/
  {60,   60},
  {90,   90},
  {120,  120},
  {150,  150},
  {0,    100}   /*长关*/
};


static const uint16_t   CalvesRollerCtrlOnOffTimeTab[][2] = 
{
  {100,  0},    /*长开*/
  {60,   60},
  {90,   90},
  {120,  120},
  {150,  150},
  {0,    100}   /*长关*/
};

//static ActionTabStep_t GasFeetRollerStep;
static ActionTabStep_t GasCalvesRollerStep;


static const ActionTabAttr_t   GasRollerTab[] =
{
  { 
    0,                                                   /*动作ID   忽略动作ID*/
    (void*)FeetGasRollerTab,                             /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_ROLLER_NONE,                                     /*脚滚 伴随模式*/
    FMA_ROLLER_NONE,                                     /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  },
  
  { 
    0,                                                   /*动作ID   忽略动作ID*/
    (void*)CalvesGasRollerTab,                           /*动作表格*/
    0,                                                   /*开始步骤*/
    ACTION_TAB_STEP_NUM_MAX,                             /*结束步骤*/
    FMA_VIB_NONE,                                        /*脚振 伴随模式*/
    FMA_VIB_NONE,                                        /*腿振 伴随模式*/
    FMA_VIB_NONE,                                        /*座振 伴随模式*/
    FMA_VIB_NONE,                                        /*腰背振 伴随模式*/
    FMA_ROLLER_NONE,                                     /*脚滚 伴随模式*/
    FMA_ROLLER_NONE,                                     /*腿滚 伴随模式*/
    FMA_HEAT_NONE,                                       /*脚热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腿热 伴随模式*/
    FMA_HEAT_NONE,                                       /*座热 伴随模式*/
    FMA_HEAT_NONE,                                       /*腰背热 伴随模式*/
    FMA_LED_NONE                                         /*灯   伴随模式*/
  }
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
* 功能描述 : 按摩椅 滚轮功能 复位                                                               
* 输入参数 : 无                                                                                
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_RollerFuncReset_Feet(void)
{
    pMChair->FeetRollerCtrlOnOffTime = 0;
    pMChair->FeetRollerCtrlSw = OFF;
    Roller_SetFeetRollerWorkState(FALSE);                       /*停止工作*/
    Roller_FeetRollerResetStep();                               /*复位步骤*/
}

void MChair_RollerFuncReset_Calves(void)
{
    pMChair->CalvesRollerCtrlOnOffTime = 0;
    pMChair->CalvesRollerCtrlSw = OFF;
    Roller_SetCalvesRollerWorkState(FALSE);                     /*停止工作*/
    Roller_CalvesRollerResetStep();                             /*复位步骤*/
}

/*
************************************************************************************************************************
* 函数名称 : Roller_FeetGasCtrl                                                                                               
* 功能描述 : 脚滚充气控制                                                             
* 输入参数 : 无                                                                                
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void Roller_FeetGasCtrl(Ticker_t ExePeriod)
{
//  GasPart2_t   GasPart;
  
  if(TRUE == pMChair->CSFlag.Bit.GasCooperateSpikeRun)             /*充气配合推杆的动作*/
  {
    return;
  }  
  //Gas_SetPumpSw(ON);
  //Gas_FeetCtrlEnOnly();                                           /*脚部充气控制使能，执行脚滚所伴随的充气*/  

  /*方式1：从脚滚表格里获取充气控制，配合度较高，但充气强度不可控制--------------------------*/
//  GasPart2_t   GasPart;
//  GasPart.Bit.Ankle = Roller_GetFeetGas().Bit.Ankle;
//  GasPart.Bit.FeetSide = Roller_GetFeetGas().Bit.FeetSide;
//  Gas_SetGasPart(0, GasPart.All);
  
  /*方式2：直接伴随一个充气程序，配合度不高，充气强度可控制----------------------------------*/
  //MChair_TabHandle_GasAuto(ExePeriod, (ActionTabAttr_t *)&GasRollerTab[0], &GasFeetRollerStep);
}

/*
************************************************************************************************************************
* 函数名称 : Roller_CalvesGasCtrl                                                                                               
* 功能描述 : 腿滚充气控制                                                             
* 输入参数 : 无                                                                                
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void Roller_CalvesGasCtrl(Ticker_t ExePeriod)
{
  Gas_SetPumpSw(ON);
  Gas_CalvesCtrlEnOnly();                                     /*脚部充气控制使能，执行脚滚所伴随的充气*/  

  /*方式1：从脚滚表格里获取充气控制，配合度较高，但充气强度不可控制--------------------------*/
//  GasPart2_t   GasPart;
//  GasPart.Bit.Ankle = Roller_GetCalvesGas().Bit.Calves;
//  GasPart.Bit.FeetSide = Roller_GetCalvesGas().Bit.CalvesSide;
//  Gas_SetGasPart(0, GasPart.All);
  
  /*方式2：直接伴随一个充气程序，配合度不高，充气强度可控制----------------------------------*/
  MChair_TabHandle_GasAuto(ExePeriod, (ActionTabAttr_t *)&GasRollerTab[1], &GasCalvesRollerStep);
}
/*
************************************************************************************************************************
* 函数名称 : MChair_FuncSwitch_RollerMA                                                                                               
* 功能描述 : 按摩椅 功能切换 之  【滚轮】手动自动                                                                   
* 输入参数 : SwitchMode -- 要切换模式
*            pFuncLogic -- 功能逻辑的描述                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_RollerMA(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  RollerAction_t RollerActionCur;
  RollerAction_t RollerActionHis;


  RollerActionCur.All = *pFuncLogic->pFuncCur;
  RollerActionHis.All = *pFuncLogic->pFuncHis;
  if(RollerActionCur.Bit.Feet != RollerActionHis.Bit.Feet)      /*脚滚功能发生切换*/
  {
    MChair_RollerFuncReset_Feet();
    
    if(FUNC_TYPE_NONE == pMChair->ComponentFuncState.Bit.Gas)   /*无任何充气程序，则全部关闭*/
    {
      Gas_SetPumpSw(OFF);
      Gas_AllCtrlEn();                                          /*所有部位充气控制使能*/ 
      Gas_SetGasPart(0, 0);
    }
    else                                                        /*否则只关脚部充气，不关气泵*/
    {
      /*不同于旧架构，新架构中脚滚充气将覆盖其他充气程序对脚部充气的控制。
        关闭脚滚后，其他充气程序对脚部充气的控制将自动恢复。
        实现原理：在FuncLogicTab[] 表中，&MChair.FuncMA_Roller.All 放置在表格的后面，
                  由于整个架构是前后台顺序执行，因此靠后的赋值（脚滚对充气的赋值）将覆盖
                  靠前的赋值（其他充气程序对脚部充气的赋值）。 */
      Gas_FeetCtrlEnOnly();                                     /*脚部充气控制使能，执行脚滚所伴随的充气*/  
      Gas_SetGasPart(0, 0);
    }
  }
  
  if(RollerActionCur.Bit.Calves != RollerActionHis.Bit.Calves)  /*腿滚功能发生切换*/
  {
    MChair_RollerFuncReset_Calves();
    
    if(FUNC_TYPE_NONE == pMChair->ComponentFuncState.Bit.Gas)   /*无任何充气程序，则全部关闭*/
    {
      Gas_SetPumpSw(OFF);
      Gas_AllCtrlEn();                                          /*所有部位充气控制使能*/ 
      Gas_SetGasPart(0, 0);
    }
    else                                                        /*否则只关脚部充气，不关气泵*/
    {
      Gas_CalvesCtrlEnOnly();                                  /*腿部充气控制使能，执行腿滚所伴随的充气*/  
      Gas_SetGasPart(0, 0);
    }
  }  
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncExe_RollerMA                                                                                               
* 功能描述 : 按摩椅 功能执行 之  【滚轮】手动自动                                                                   
* 输入参数 : ExePeriod  -- 执行周期
*            pFuncLogic -- 指向自身功能逻辑的指针。                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_RollerMA(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  uint16_t OnTime;
  uint16_t OffTime;

  switch(pMChair->FuncMA_Roller.Bit.Feet)
  {
    case FMA_ROLLER_NONE:
    {
      pMChair->FeetRollerCtrlSw = OFF;
    }break;

    case FMA_FEET_ROLLER_Mannual:              /*手动*/
    {
      pMChair->ComponentFuncState.Bit.FeetRoller = FUNC_TYPE_MANNUALAUTO; /*脚滚功能状态：手动自动*/
      Roller_FeetGasCtrl(ExePeriod);           /*脚滚充气控制*/
      pMChair->FeetRollerCtrlSw = ON;          /*手动就常开*/

    }break;

    case FMA_FEET_ROLLER_ByActionTab:          /*由表格内的值来控制，见ActionObjHandle_AccompanyFunc()函数*/
    {
      pMChair->ComponentFuncState.Bit.FeetRoller = FUNC_TYPE_MANNUALAUTO; /*脚滚功能状态：手动自动*/
   }break;

    case FMA_FEET_ROLLER_ByTime_OnAlways:      /*由时间控制*/
    case FMA_FEET_ROLLER_ByTime_On60s_Off60s:
    case FMA_FEET_ROLLER_ByTime_On90s_Off90s:
    case FMA_FEET_ROLLER_ByTime_On120s_Off120s:
    case FMA_FEET_ROLLER_ByTime_On150s_Off120s:
    {
      pMChair->ComponentFuncState.Bit.FeetRoller = FUNC_TYPE_MANNUALAUTO; /*脚滚功能状态：手动自动*/

      pMChair->FeetRollerCtrlOnOffTime += ExePeriod;
      OnTime = FeetRollerCtrlOnOffTimeTab[pMChair->FuncMA_Roller.Bit.Feet - FMA_FEET_ROLLER_ByTime_OnAlways][0];
      OffTime = OnTime + FeetRollerCtrlOnOffTimeTab[pMChair->FuncMA_Roller.Bit.Feet - FMA_FEET_ROLLER_ByTime_OnAlways][1];
      if(pMChair->FeetRollerCtrlOnOffTime/1000 < OnTime) 
      {
        pMChair->FeetRollerCtrlSw = ON;
        Roller_FeetGasCtrl(ExePeriod);         /*脚滚充气控制*/
      }
      else if(pMChair->FeetRollerCtrlOnOffTime/1000 == OnTime) 
      {
        Gas_FeetCtrlEnOnly();                  /*脚部充气控制使能，执行脚滚所伴随的充气*/  
        Gas_SetGasPart(0, 0);                  /*进入关断之前，先关脚部充气*/
      }
      else if(pMChair->FeetRollerCtrlOnOffTime/1000 < OffTime)
      {
        pMChair->FeetRollerCtrlSw = OFF;
      }
      else
      {
        pMChair->FeetRollerCtrlOnOffTime = 0;
      }

    }break;

    default:
    {
      pMChair->FuncMA_Roller.Bit.Feet = FMA_ROLLER_NONE;
    }break;
  }
  Roller_SetFeetRollerWorkState((ON == pMChair->FeetRollerCtrlSw)   ? TRUE:FALSE); 


  //------------------------------------------------------------------------------------
  switch(pMChair->FuncMA_Roller.Bit.Calves)
  {
    case FMA_ROLLER_NONE:
    {
      pMChair->CalvesRollerCtrlSw = OFF;
    }break;

    case FMA_CALVES_ROLLER_Mannual:              /*手动*/
    {
      pMChair->ComponentFuncState.Bit.CalvesRoller = FUNC_TYPE_MANNUALAUTO; /*脚滚功能状态：手动自动*/
      Roller_CalvesGasCtrl(ExePeriod);           /*脚滚充气控制*/
      pMChair->CalvesRollerCtrlSw = ON;          /*手动就常开*/

    }break;

    case FMA_CALVES_ROLLER_ByActionTab:          /*由表格内的值来控制，见ActionObjHandle_AccompanyFunc()函数*/
    {
      pMChair->ComponentFuncState.Bit.CalvesRoller = FUNC_TYPE_MANNUALAUTO; /*脚滚功能状态：手动自动*/
   }break;

    case FMA_CALVES_ROLLER_ByTime_OnAlways:      /*由时间控制*/
    case FMA_CALVES_ROLLER_ByTime_On60s_Off60s:
    case FMA_CALVES_ROLLER_ByTime_On90s_Off90s:
    case FMA_CALVES_ROLLER_ByTime_On120s_Off120s:
    case FMA_CALVES_ROLLER_ByTime_On150s_Off120s:
    {
//      pMChair->ComponentFuncState.Bit.CalvesRoller = FUNC_TYPE_MANNUALAUTO; /*脚滚功能状态：手动自动*/

//      pMChair->CalvesRollerCtrlOnOffTime += ExePeriod;
//      OnTime = CalvesRollerCtrlOnOffTimeTab[pMChair->FuncMA_Roller.Bit.Calves - FMA_CALVES_ROLLER_ByTime_OnAlways][0];
//      OffTime = OnTime + CalvesRollerCtrlOnOffTimeTab[pMChair->FuncMA_Roller.Bit.Calves - FMA_CALVES_ROLLER_ByTime_OnAlways][1];
//      if(pMChair->CalvesRollerCtrlOnOffTime/1000 < OnTime) 
//      {
//        pMChair->CalvesRollerCtrlSw = ON;
//        Roller_CalvesGasCtrl(ExePeriod);         /*脚滚充气控制*/
//      }
//      else if(pMChair->CalvesRollerCtrlOnOffTime/1000 == OnTime) 
//      {
//        Gas_CalvesCtrlEnOnly();                  /*脚部充气控制使能，执行脚滚所伴随的充气*/  
//        Gas_SetGasPart(0, 0);                  /*进入关断之前，先关脚部充气*/
//      }
//      else if(pMChair->CalvesRollerCtrlOnOffTime/1000 < OffTime)
//      {
//        pMChair->CalvesRollerCtrlSw = OFF;
//      }
//      else
//      {
//        pMChair->CalvesRollerCtrlOnOffTime = 0;
//      }

      pMChair->ComponentFuncState.Bit.CalvesRoller = FUNC_TYPE_MANNUALAUTO; /*脚滚功能状态：手动自动*/

      pMChair->CalvesRollerCtrlOnOffTime += ExePeriod;
      OnTime = CalvesRollerCtrlOnOffTimeTab[pMChair->FuncMA_Roller.Bit.Calves - FMA_CALVES_ROLLER_ByTime_OnAlways][0];
      OffTime = OnTime + CalvesRollerCtrlOnOffTimeTab[pMChair->FuncMA_Roller.Bit.Calves - FMA_CALVES_ROLLER_ByTime_OnAlways][1];

      if(pMChair->CalvesRollerCtrlOnOffTime/1000 < OnTime)
      {
        pMChair->CalvesRollerCtrlSw = ON;
        Roller_CalvesGasCtrl(ExePeriod);         /*脚滚充气控制*/
      }
      else if(pMChair->CalvesRollerCtrlOnOffTime/1000 < OffTime) 
      {
        pMChair->CalvesRollerCtrlSw = OFF;
      }
      else
      {
        pMChair->CalvesRollerCtrlOnOffTime = 0;
      }
      
      if(pMChair->CalvesRollerCtrlOnOffTime == 0) 
      {
        Gas_CalvesCtrlEnOnly();                  /*脚部充气控制使能，执行脚滚所伴随的充气*/  
        Gas_SetGasPart(0, 0);                    /*进入关断之前，先关脚部充气*/
      }      
    }break;

    default:
    {
      pMChair->FuncMA_Roller.Bit.Calves = FMA_ROLLER_NONE;
    }break;
  }
  Roller_SetCalvesRollerWorkState((ON == pMChair->CalvesRollerCtrlSw) ? TRUE:FALSE);  
}
