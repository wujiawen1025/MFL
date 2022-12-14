/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: SysMode_VenderInspectAuto.c 
**
**    功能描述: 系统模式 之  厂家自检
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
#include "SysMode.h"


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


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : SysMode_InspectAuto_Timer                                                                                                         
* 功能描述 : 厂家自检 定时器 处理                                                                                        
* 输入参数 : ExePeriod -- 执行周期                                                                                     
* 返回参数 : 无                                                                
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_InspectAuto_Timer(Ticker_t ExePeriod)
{
  //static uint8_t CoreSpikePauseOnOff = OFF;

  if(pMChair->SysModeCur != SYS_MODE_INSPECTAUTO)
  {
    return;
  }

  /*开 滚&振  热&灯-----------------------------------------------*/
  Heat_SetLumbarBackHeatWorkState(TRUE);
  Roller_SetFeetRollerWorkState(TRUE);
  Roller_SetCalvesRollerWorkState(TRUE);
  Led_SetLogoWorkState(TRUE);  
  Led_SetProjectionWorkState(TRUE);  

  /*开敲击--------------------------------------------------------*/
  Core_SetTCSAction(CORE_ACTION_EXE_NONE, TAP);

  /*机芯 伸缩-----------------------------------------------*/
  pMChair->VenderInspect.CoreFlexTimeMs += ExePeriod;
  switch(pMChair->VenderInspect.CoreFlexStep)
  {
    case 0:
    {
      Core_SetZPosition(PZ_MAX);
      if(PZ_MAX == Core_GetZPosition())
      {
        pMChair->VenderInspect.CoreFlexStep++;
        pMChair->VenderInspect.CoreFlexTimeMs = 0;
      }
    }break;

    case 1:
    {
      Core_SetZPosition(PZ00);
      if(PZ00 == Core_GetZPosition())
      {
        pMChair->VenderInspect.CoreFlexTimeMs = 0;
        pMChair->VenderInspect.CoreFlexStep = 255;
      }
    }break;

    default: break;
  }

  /*机芯 揉捏-----------------------------------------------*/
  pMChair->VenderInspect.CoreKneadTimeMs += ExePeriod;
  switch(pMChair->VenderInspect.CoreKneadStep)
  {
    case 0:
    {
      Core_SetXPosition(PX00);
      if(PX00 == Core_GetXPosition())
      {
        pMChair->VenderInspect.CoreKneadTimeMs = 0;
        pMChair->VenderInspect.CoreKneadStep++;
      }
    }break;

    case 1:
    {
      Core_SetXPosition(PX02);
      if(PX02 == Core_GetXPosition())
      {
        pMChair->VenderInspect.CoreKneadTimeMs = 0;
        pMChair->VenderInspect.CoreKneadStep = 255;
      }
    }break;

    default:break;
  }

  /*机芯 推拿(滚动)-------------------------------------------------------*/
  pMChair->VenderInspect.CoreRollTimeMs += ExePeriod;
  switch(pMChair->VenderInspect.CoreRollStep)
  {
    case 0:
    {
      Core_SetYPosition(PY_MAX);
      if(PY_MAX == Core_GetYPosition())
      {
        pMChair->VenderInspect.CoreRollTimeMs = 0;
        pMChair->VenderInspect.CoreRollStep++;
      }
    }break;

    case 1:
    {
      Core_SetYPosition(PY00);
      if(PY00 == Core_GetYPosition())
      {
        pMChair->VenderInspect.CoreRollTimeMs = 0;
        pMChair->VenderInspect.CoreRollStep = 255;
      }

    }break;

    default: break;
  }

  /*靠背推杆--------------------------------------------------------*/
  pMChair->VenderInspect.BackSpikeTimeMs += ExePeriod;
  switch(pMChair->VenderInspect.BackSpikeStep)
  {
    case 0:
    {
      Spike_SetBackAngle(PBACK_MAX);
      if(PBACK_MAX == Spike_GetBackAngle())
      {
        pMChair->VenderInspect.BackSpikeTimeMs = 0;
        pMChair->VenderInspect.BackSpikeStep++;
      }
    }break;

    case 1:
    {
      Spike_SetBackAngle(PBACK00);
      if(PBACK00 == Spike_GetBackAngle())
      {
        pMChair->VenderInspect.BackSpikeTimeMs = 0;
        pMChair->VenderInspect.BackSpikeStep = 255;
      }
    }break;

    default: break;
  }

  /*小腿推杆--------------------------------------------------------*/
  pMChair->VenderInspect.FeetSpikeTimeMs += ExePeriod;
  switch(pMChair->VenderInspect.FeetSpikeStep)
  {
    case 0:
    {
      Spike_SetFeetAngle(PFEET_MAX);
      if(PFEET_MAX == Spike_GetFeetAngle())
      {
        pMChair->VenderInspect.FeetSpikeTimeMs = 0;
        if(0 == BSP_IO_GetVenderTestPin())      /*工装检测下*/
        {
          pMChair->VenderInspect.FeetSpikeStep = 3;
        }
        else 
        {
          pMChair->VenderInspect.FeetSpikeStep++;
        }          
      }
    }break;
    
    case 1:
    {
      Spike_SetLegFlexMove(SPIKE_MOVE_LEG_EXTEND);
      if((TRUE == LegFlexSpike_GetCSFlag().Bit.ReachExtendLimt) || (TRUE == LegFlexSpike_GetCSFlag().Bit.TouchGround))         //停止条件要加上触地
      {
        pMChair->VenderInspect.FeetSpikeTimeMs = 0;
        pMChair->VenderInspect.FeetSpikeStep++;
      }
    }break;
    
    case 2:
    {
      Spike_SetLegFlexMove(SPIKE_MOVE_LEG_SHORT);
      if((TRUE == LegFlexSpike_GetCSFlag().Bit.ReachShortenLimt) || (TRUE == LegFlexSpike_GetCSFlag().Bit.TouchFeet))
      {
        pMChair->VenderInspect.FeetSpikeTimeMs = 0;
        pMChair->VenderInspect.FeetSpikeStep++;
      }
    }break;

    case 3:
    {
      Spike_SetFeetAngle(PFEET00);
      if(PFEET00 == Spike_GetFeetAngle())
      {
        pMChair->VenderInspect.FeetSpikeTimeMs = 0;
        pMChair->VenderInspect.FeetSpikeStep = 255;
      }
    }break;

    default: break;
  }

  /*零重力推杆------------------------------------------------------*/


  /*气泵与气囊-------------------------------------------------------*/
  Gas_SetPumpSw(ON);
  Gas_AllCtrlEn();
  pMChair->CommonTimeSec++;
  switch(pMChair->CommonTimeSec>>1)
  {
    case 0: Gas_SetGasPart(B(11111111), B(11111111)); break; 
    default:
    {
      Gas_SetGasPart(B(00000000), B(00000000));  
      pMChair->CommonTimeSec = 0;
    }break;
  }
//  Gas_SetGasPart(B(11111111), B(11111111));  
//  pMChair->CommonTimeSec++;
//  switch(pMChair->CommonTimeSec>>2)
//  {
//    case 0: Gas_SetGasPart(B(00100000), B(00000000)); break; /*肩部*/
//    case 1: Gas_SetGasPart(B(00010000), B(00000000)); break; /*手部*/
//    case 2: Gas_SetGasPart(B(00001000), B(00000000)); break; /*坐部*/
//    case 3: Gas_SetGasPart(B(00000100), B(00000000)); break; /*腿背*/
//    case 4: Gas_SetGasPart(B(00000010), B(00000000)); break; /*腿两侧*/
//    case 5: Gas_SetGasPart(B(00000001), B(00000000)); break; /*脚两侧*/
//    default:
//    {
//      Gas_SetGasPart(B(00000000), B(00000000));  
//      pMChair->CommonTimeSec = 0;
//    }break;
//  }

  /*=================================================================*/
  if((255 == pMChair->VenderInspect.CoreFlexStep)  &&
     (255 == pMChair->VenderInspect.CoreKneadStep) &&
     (255 == pMChair->VenderInspect.CoreRollStep)  &&
     (255 == pMChair->VenderInspect.BackSpikeStep) &&
     (255 == pMChair->VenderInspect.FeetSpikeStep) )
  {
    Core_SetTCSAction(CORE_ACTION_EXE_NONE, TCS_ACTION_NONE);
    pMChair->CSFlag.Bit.VenderOpFinish = TRUE; /*厂家操作完成*/
  }
}

/*
************************************************************************************************************************
* 函数名称 : SysMode_InspectAuto_Init                                                                                                         
* 功能描述 : 系统模式 之 厂家自检 初始化                                                                                        
* 输入参数 : 无                                                                                     
* 返回参数 : 无                                                                
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_InspectAuto_Init(void)
{

}

/*
************************************************************************************************************************
* 函数名称 : SysMode_InspectAuto_Handle                                                                                                         
* 功能描述 : 系统模式 之 厂家自检 处理                                                                                        
* 输入参数 : 无                                                                                     
* 返回参数 : 无                                                                
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_InspectAuto_Handle(void)
{
  /*发生模式切换操作-----------------------------------------------------*/
  if(pMChair->SysModeHis != pMChair->SysModeCur)      
  {
    /*检测模式下，开启推杆的计数故障检测开关*/
    BackSpike_SetCountFaultCheckSw(ON);           
    FeetSpike_SetCountFaultCheckSw(ON);
    ZeroSpike_SetCountFaultCheckSw(ON);
    
    pMChair->SysModeHis = pMChair->SysModeCur; 
  }

  /*根据各个模式的不同，对键值处理相关变量赋值---------------------------*/
  SysMode_DefaultKeyValHandle();
}
