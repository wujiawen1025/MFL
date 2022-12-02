/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncMannual_Core.c 
**
**    功能描述:【机芯】手动功能
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
static  CoreXYZMannualArrt_t CoreXYZMannualAttr;      /*手动动作的相关管理属性*/
static  uint8_t  XYZRollForTCS;                       /*给TCS动作伴随的推拿(滚动)*/

static  uint8_t  VenderTest3DFlex;                    /*厂家测试3D伸缩*/
/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : MChair_CoreMannualVenderTest3DSwSet                                                                                               
* 功能描述 : 按摩椅 设置手动程序厂家拷机3D伸缩                                                                          
* 输入参数 : Sw -- 非0则表示开启3D自动伸缩                                                                                    
* 返回参数 : 无                                                                                           
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_CoreMannualVenderTest3DSwSet(uint8_t Sw)
{
  VenderTest3DFlex = Sw; 
}


/*
************************************************************************************************************************
* 函数名称 : MChair_GetCoreMannualWidthMax                                                                                               
* 功能描述 : 按摩椅 获得机芯手动程序 时宽度最大值                                                                                
* 输入参数 : 无                                                                                      
* 返回参数 : 手动程序下，可调节的最大宽度。
*            特殊值：PKEEP -- 宽度不可调节                                                                                               
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
uint8_t MChair_GetFuncCoreMannualWidthMax(void)
{
  return CoreXYZMannualAttr.XMax; 
}

/*
************************************************************************************************************************
* 函数名称 : MChair_GetCoreMannualFlexLevelMax                                                                                               
* 功能描述 : 按摩椅 获得机芯手动程序 时伸缩度最大值                                                                                
* 输入参数 : 无                                                                                      
* 返回参数 : 手动程序下，可调节的最大伸缩度。
*            特殊值：PKEEP -- 伸缩度不可调节                                                                                               
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
uint8_t MChair_GetFuncCoreMannualFlexLevelMax(void)
{
  return CoreXYZMannualAttr.ZMax; 
}

/*
************************************************************************************************************************
* 函数名称 : MChair_GetFuncCoreMannualXYZSpeedMax                                                                                               
* 功能描述 : 按摩椅 获得机芯手动程序 时XYZ手法速度最大值                                                                              
* 输入参数 : 无                                                                                      
* 返回参数 : 手动程序下，可调节的最大速度。
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
uint8_t MChair_GetFuncCoreMannualXYZSpeedMax(void)
{
  return CoreXYZMannualAttr.SpeedMax; 
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncSwitch_CoreMannual                                                                                               
* 功能描述 : 按摩椅 功能切换 之  【机芯】手动                                                                                
* 输入参数 : SwitchMode -- 切换模式，取值：OPEN打开， 
*                                          CLOSE关闭 
*            pFuncLogic -- 指向自身功能逻辑的指针。                                                                                      
* 返回参数 : 无                                                                                               
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_CoreMannual(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  CoreAction_t  HisAction;

  if(OPEN == SwitchMode)
  {
    HisAction.All = *pFuncLogic->pFuncHis;

    if(pMChair->FuncMannual_Core.Bit.XYZ.All != HisAction.Bit.XYZ.All )
    {
      if(XYZ_NONE == pMChair->FuncMannual_Core.Bit.XYZ.All) 
      {
        if(pMChair->FuncMannual_Core.Bit.TCS.All > 0)                 /*XYZ无动作，但TCS有动作*/
        {
          XYZRollForTCS = ROLL;                                       /*则要 开启TCS伴随的推拿(滚动)*/
        }
      }
      else
      {
        XYZRollForTCS = XYZ_ACTION_NONE;                              /*XYZ有动作 关闭TCS伴随的推拿(滚动)*/
        if(ROLL == pMChair->FuncMannual_Core.Bit.XYZ.All)   
        {
          pMChair->FuncMannual_Core.Bit.TCS.All = TCS_ACTION_NONE;    /*XYZ手动推拿(滚动)要关闭敲击*/
          if(CORE_ROLL_RANGE_SPOT == Core_GetRollRange())             /*推拿时，要关闭定点*/
          {
            Core_SetRollRange(CORE_ROLL_RANGE_WHOLE);
          }
        }
      }

      pMChair->MannualCoreXYZActionSpeed = 3;                         /*切换XYZ动作，则默认推荐速度*/
      pMChair->MannualCoreWidth = 0;                                  /*切换XYZ动作，则默认推荐宽度*/
    }
    else if(pMChair->FuncMannual_Core.Bit.TCS.All != HisAction.Bit.TCS.All )
    {
      if(pMChair->FuncMannual_Core.Bit.TCS.All > 0)
      {
        if(ROLL == pMChair->FuncMannual_Core.Bit.XYZ.All)       
        {
          pMChair->FuncMannual_Core.Bit.XYZ.All = XYZ_ACTION_NONE;    /*手动敲击要关闭手动推拿(滚动)*/
        }
        if(XYZ_ACTION_NONE == pMChair->FuncMannual_Core.Bit.XYZ.All) 
        {
          XYZRollForTCS = ROLL;                                       /*开启伴随的推拿(滚动)*/
        }  
      }
      else
      {
        XYZRollForTCS = XYZ_ACTION_NONE;
      }      
    }

    if(ROLL == XYZRollForTCS)
    {
      Core_GetXYZMannualManageAttr(XYZRollForTCS, &CoreXYZMannualAttr);
    }
    else
    {
      Core_GetXYZMannualManageAttr(pMChair->FuncMannual_Core.Bit.XYZ.All, &CoreXYZMannualAttr);
    }  
    
    /*动作切换时，同时修正调节量的极限值*/
    if(pMChair->MannualCoreWidth > CoreXYZMannualAttr.XMax)
    {
      pMChair->MannualCoreWidth = CoreXYZMannualAttr.XMax; 
    }
    
    if(CoreXYZMannualAttr.ZPrePosition != PKEEP)
    {
      pMChair->MannualCoreFlexLevel = CoreXYZMannualAttr.ZPrePosition; 
    }
    if(pMChair->MannualCoreFlexLevel > CoreXYZMannualAttr.ZMax)
    {
      pMChair->MannualCoreFlexLevel = CoreXYZMannualAttr.ZMax; 
    }
    
    if(pMChair->MannualCoreXYZActionSpeed > CoreXYZMannualAttr.SpeedMax)
    {
      pMChair->MannualCoreXYZActionSpeed = CoreXYZMannualAttr.SpeedMax; 
    }
  }
  else// if(CLOSE == SwitchMode)
  {
    pMChair->MannualCoreWidth          = PXWIDE;     /*手动程序下  机芯宽度*/
    pMChair->MannualCoreFlexLevel      = 2;          /*手动程序下  机芯伸缩度*/
    pMChair->MannualCoreTCSActionSpeed = 3;          /*手动程序下  TCS动作手法速度*/
    pMChair->MannualCoreXYZActionSpeed = 3;          /*手动程序下  XYZ动作手法速度*/
 
    Core_SetXYZPosition(PXWIDE, PYTOP, PZBACK); 
    Core_SetAction(CORE_ACTION_EXE_NONE, XYZ_ACTION_NONE, TCS_ACTION_NONE); 

    /*-----------------------------------------------------------*/
    VenderTest3DFlex = 0;
  }
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncExe_CoreMannual                                                                                               
* 功能描述 : 按摩椅 功能执行 之  【机芯】手动                                                                                
* 输入参数 : ExePeriod  -- 执行周期
*            pFuncLogic -- 指向自身功能逻辑的指针。                                                                                      
* 返回参数 : 无                                                                                               
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_CoreMannual(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  static  Ticker_t  Period;

  pMChair->ComponentFuncState.Bit.Core = FUNC_TYPE_MANNUAL;            /*机芯功能状态：手动*/

  if((TRUE  == CoreXYZMannualAttr.ExeOp.Bit.PreBackScan) &&            /*该XYZ动作需要先执行背部检测*/
     (FALSE == pMChair->StateBodyScan.Bit.Finish)       )              /*人体扫描未完成*/
  {
    return;
  }

  /*更新用户的调节值*/
  Core_SetTCSActionSpeed(pMChair->MannualCoreTCSActionSpeed);
  Core_SetXYZActionSpeed(pMChair->MannualCoreXYZActionSpeed);

  Core_SetXPosition(pMChair->MannualCoreWidth); 
  
  if(VenderTest3DFlex)    /*厂家机芯手动程序拷机时，对3D伸缩的处理*/
  {
    Period += ExePeriod;
    if(Period < 6000)
    {
      pMChair->MannualCoreFlexLevel = 0;
    }
    else if(Period < 12000)
    {
      pMChair->MannualCoreFlexLevel = 5;
    }
    else
    {
      Period = 0;
    }
    
    if(Core_GetYPosition() <= 9)
    {
      pMChair->MannualCoreFlexLevel = (pMChair->MannualCoreFlexLevel>4) ? 4 : pMChair->MannualCoreFlexLevel;
    }
    else if(Core_GetYPosition() <= 22)
    {
      pMChair->MannualCoreFlexLevel = (pMChair->MannualCoreFlexLevel>3) ? 3 : pMChair->MannualCoreFlexLevel;
    }
    else 
    {
      pMChair->MannualCoreFlexLevel = (pMChair->MannualCoreFlexLevel>2) ? 2 : pMChair->MannualCoreFlexLevel;
    }      
  }
  Core_SetZPosition(pMChair->MannualCoreFlexLevel); 

  /*执行动作*/
  if(ROLL == XYZRollForTCS)
  {
    Core_SetAction(CORE_ACTION_EXE_MANNNUAL, XYZRollForTCS, pMChair->FuncMannual_Core.Bit.TCS.All); 
  }
  else
  {
    Core_SetAction(CORE_ACTION_EXE_MANNNUAL, pMChair->FuncMannual_Core.Bit.XYZ.All, pMChair->FuncMannual_Core.Bit.TCS.All); 
  }  
}
