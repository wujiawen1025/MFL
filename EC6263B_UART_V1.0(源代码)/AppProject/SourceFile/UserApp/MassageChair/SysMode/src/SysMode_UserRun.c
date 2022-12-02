/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: SysMode_UserRun.c 
**
**    功能描述: 系统模式  之  用户运行
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
#pragma  diag_suppress 177            /*屏蔽mdk中，函数声明但没被引用的告警*/

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
extern uint8_t StandBy_Key_SpikeBackUp(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeBackDown(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeFeetUp(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeFeetDown(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeBackUpFeetDown(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeBackDownFeetUp(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeZeroGravity(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeLegExtend(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeLegShorten(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeULegExtend(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeULegShorten(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeZeroGravity1(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeZeroGravity2(uint8_t *pData);
extern uint8_t StandBy_Key_SpikeHomeReset(uint8_t *pData);

/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_NoKeyPress                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_NoKeyPress(uint8_t *pData)
{
  /*长按按键的释放处理---------------------------------------------*/
  Core_SetMoveAdjustRoll(CORE_MOVE_ADJUST_NONE);                /*机芯上下调节 的长按释放*/
  
  #if (SHOULDER_ADJUST_KEY_L == SHOULDER_ADJUST_KEY_LSMODE)     /*肩部调节长按的释放*/
  BodyScan_UserAdjustShoulder(SHOULDER_ADJUST_NONE, SHOULDER_ADJUST_KEY_LSMODE);
  #endif

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)                   /*推杆为长按*/
  pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;    /*靠背推杆 的长按释放*/
  pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;    /*小腿推杆 的长按释放*/
  #endif

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_Power                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_Power(uint8_t *pData)
{
  return SysMode_Standby_Enter(SYS_MODE_USERRUN, TRUE);    /*关机，复位推杆角度*/
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_Pause                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_Pause(uint8_t *pData)
{
//  if(TRUE == pMChair->CSFlag.Bit.UserMassageTimeOut)
//  {
//    return FAIL;  /*按摩定时到后，不响应暂停操作*/
//  }
  
  if(FALSE == pMChair->CSFlag.Bit.Pause)
  {
    pMChair->CSFlag.Bit.Pause = TRUE;
  }
  else
  {
    pMChair->CSFlag.Bit.Pause = FALSE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_TimerAdd                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_TimerAdd(uint8_t *pData)
{
  if(TRUE == pMChair->CSFlag.Bit.UserMassageTimeOut)
  {
    return FAIL; /*超时后，时间不可调*/
  }

  pMChair->UserMassageTimeDelayOnSec = 0;
  pMChair->UserMassageTimeSec = 0;

  pMChair->UserMassageTimeMin += (5 - (pMChair->UserMassageTimeMin%5));
  if(pMChair->UserMassageTimeMin > 30)
  {
    pMChair->UserMassageTimeMin = 30;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_TimerDec                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_TimerDec(uint8_t *pData)
{
  if(TRUE == pMChair->CSFlag.Bit.UserMassageTimeOut)
  {
    return FAIL; /*超时后，时间不可调*/
  }

  if(pMChair->UserMassageTimeMin < 5)
  {
    return FAIL;
  }

  pMChair->UserMassageTimeDelayOnSec = 0;
  pMChair->UserMassageTimeSec = 0;

  if((pMChair->UserMassageTimeMin%5) == 0)
  {
    pMChair->UserMassageTimeMin -= 5;
  }
  else
  {
    pMChair->UserMassageTimeMin -= (pMChair->UserMassageTimeMin%5);
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_Timer                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_Timer(uint8_t *pData)
{
  if((SYS_MODE_TESTAGE == pMChair->SysModeCur)    || 
     (SYS_MODE_TESTNOTIMER == pMChair->SysModeCur))
  {
    MChair_CoreMannualVenderTest3DSwSet(1);       /*厂家拷机下自动伸缩触发（一定要先开手动程序，才能触发）*/
    if(pMChair->UserMassageTimeMin == 20)         /*时间为20的时候按下才开启小腿伸缩拷机测试开关*/
    {
      pMChair->CSFlag.Bit.LegFlexTestSw = TRUE;
    }
  }
  
  /*-------------------------------------------------------------------*/
  if(TRUE == pMChair->CSFlag.Bit.UserMassageTimeOut)
  {
    return FAIL; /*超时后，时间不可调*/
  }

  pMChair->UserMassageTimeDelayOnSec = 0;
  pMChair->UserMassageTimeSec = 0;

  if(pMChair->UserMassageTimeMin >= 30)
  {
    pMChair->UserMassageTimeMin = 5;
  }
  else
  {
    pMChair->UserMassageTimeMin += (5 - (pMChair->UserMassageTimeMin%5));
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_BodyCheckOk                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_BodyCheckOk(uint8_t *pData)
{
  return BodyScan_UserAdjustShoulder(SHOULDER_ADJUST_FINISH, SHOULDER_ADJUST_KEY_LSMODE);
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_BodyReCheck                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_BodyReCheck(uint8_t *pData)
{
  return BodyScan_ShoulderReCheck();
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_BluetoothSwitch                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_BluetoothSwitch(uint8_t *pData)
{
  pMChair->CSFlag.Bit.BluetoothSwitch = !pMChair->CSFlag.Bit.BluetoothSwitch;

  BSP_IO_SetOutput_BluetoothSwitch(pMChair->CSFlag.Bit.BluetoothSwitch);
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SpikeBackUp                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeBackUp      StandBy_Key_SpikeBackUp
//static uint8_t UserRun_Key_SpikeBackUp(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SpikeBackDown                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeBackDown      StandBy_Key_SpikeBackDown
//static uint8_t UserRun_Key_SpikeBackDown(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SpikeFeetUp                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeFeetUp      StandBy_Key_SpikeFeetUp
//static uint8_t UserRun_Key_SpikeFeetUp(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SpikeFeetDown                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeFeetDown      StandBy_Key_SpikeFeetDown
//static uint8_t UserRun_Key_SpikeFeetDown(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SpikeBackUpFeetDown                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeBackUpFeetDown      StandBy_Key_SpikeBackUpFeetDown
//static uint8_t UserRun_Key_SpikeBackUpFeetDown(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SpikeBackDownFeetUp                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeBackDownFeetUp      StandBy_Key_SpikeBackDownFeetUp
//static uint8_t UserRun_Key_SpikeBackDownFeetUp(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SpikeLegExtend                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeLegExtend      StandBy_Key_SpikeLegExtend
//static uint8_t UserRun_Key_SpikeLegExtend(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SpikeLegShorten                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeLegShorten      StandBy_Key_SpikeLegShorten
//static uint8_t UserRun_Key_SpikeFeetShorten(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SpikeULegExtend                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeULegExtend      StandBy_Key_SpikeULegExtend
//static uint8_t UserRun_Key_SpikeULegExtend(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SpikeULegShorten                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeULegShorten      StandBy_Key_SpikeULegShorten
//static uint8_t UserRun_Key_SpikeULegShorten(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SpikeZeroGravity1                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeZeroGravity1      StandBy_Key_SpikeZeroGravity1
//static uint8_t UserRun_Key_SpikeZeroGravity1(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SpikeZeroGravity2                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeZeroGravity2      StandBy_Key_SpikeZeroGravity2
//static uint8_t UserRun_Key_SpikeZeroGravity2(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SpikeZeroGravity                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeZeroGravity      StandBy_Key_SpikeZeroGravity
//static uint8_t UserRun_Key_SpikeZeroGravity(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SpikeHomeReset                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
#define  UserRun_Key_SpikeHomeReset      StandBy_Key_SpikeHomeReset
//static uint8_t UserRun_Key_SpikeHomeReset(uint8_t *pData)
//{
//}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreXYZSpeedAdd                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreXYZSpeedAdd(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，不调节速度*/
  }

  if((pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL) ||    /*电机没工作在手动程序下*/
     (0 == pMChair->StateCoreAction.Bit.XYZ.All))                      /*电机没工作在XYZ程序下*/
  {
    return FAIL; 
  }
  
  if(ROLL == pMChair->FuncMannual_Core.Bit.XYZ.All)
  {
    return FAIL;      /*推拿不能调节速度*/
  }

  if(pMChair->MannualCoreXYZActionSpeed < MChair_GetFuncCoreMannualXYZSpeedMax())
  {
    pMChair->MannualCoreXYZActionSpeed++;   
    return SUCCESS;
  }
  
  return FAIL; 
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreXYZSpeedDec                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreXYZSpeedDec(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，不调节速度*/
  }

  if((pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL) ||    /*电机没工作在手动程序下*/
     (0 == pMChair->StateCoreAction.Bit.XYZ.All))                      /*电机没工作在XYZ程序下*/
  {
    return FAIL; 
  }
  
  if(ROLL == pMChair->FuncMannual_Core.Bit.XYZ.All)
  {
    return FAIL;      /*推拿不能调节速度*/
  }

  if(pMChair->MannualCoreXYZActionSpeed > XYZ_ACTION_SPEED_MIN)
  {
    pMChair->MannualCoreXYZActionSpeed--;   
    return SUCCESS;
  }

  return FAIL;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreXYZSpeed                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 该功能叫揉捏力度，推拿时不能调节                                                                                               
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreXYZSpeed(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，不调节速度*/
  }

  if((pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL) ||    /*电机没工作在手动程序下*/
     (0 == pMChair->StateCoreAction.Bit.XYZ.All))                      /*电机没工作在XYZ程序下*/
  {
    return FAIL; 
  }

  
  if(MChair_GetFuncCoreMannualXYZSpeedMax() == XYZ_ACTION_SPEED_MIN)
  {
    return FAIL;      /*只有一档速度，不可调*/
  }
  
  if(TRUE == pMChair->StateCoreAction.Bit.XYZ.Bit.RollRun)
  {
    return FAIL;      /*推拿不能调节速度*/
  }
  pMChair->MannualCoreXYZActionSpeed++;   
  if(pMChair->MannualCoreXYZActionSpeed > MChair_GetFuncCoreMannualXYZSpeedMax())
  {
    pMChair->MannualCoreXYZActionSpeed = XYZ_ACTION_SPEED_MIN;
  }  

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreTCSSpeedAdd                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreTCSSpeedAdd(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，不调节速度*/
  }
  
  if((pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL) ||    /*电机没工作在手动程序下*/
     (pMChair->MannualCoreTCSActionSpeed >= TCS_SPEED_MAX))                      
  {
    return FAIL; 
  }
  
  if(0 == pMChair->StateCoreAction.Bit.TCS.All)                    /*电机没工作在TCS程序下*/
  {
    return FAIL; 
  }
  
  pMChair->MannualCoreTCSActionSpeed++;
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreTCSSpeedDec                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreTCSSpeedDec(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，不调节速度*/
  }

  if((pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL) ||    /*电机没工作在手动程序下*/
     (pMChair->MannualCoreTCSActionSpeed <= TCS_SPEED_MIN))                      
  {
    return FAIL; 
  }
  
  if(0 == pMChair->StateCoreAction.Bit.TCS.All)                    /*电机没工作在TCS程序下*/
  {
    return FAIL; 
  }

  pMChair->MannualCoreTCSActionSpeed--;
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreTCSSpeed                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreTCSSpeed(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，不调节速度*/
  }

  if((pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL) ||    /*电机没工作在手动程序下*/
     (0 == pMChair->StateCoreAction.Bit.TCS.All))                      /*电机没工作在TCS程序下*/
  {
    return FAIL; 
  }

  pMChair->MannualCoreTCSActionSpeed++;   /*机芯手动程序的速度设置*/
  if(pMChair->MannualCoreTCSActionSpeed > TCS_SPEED_MAX)
  {
    pMChair->MannualCoreTCSActionSpeed = TCS_SPEED_MIN;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreWidthAdd                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreWidthAdd(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，不调节*/
  }

  if(pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL)
  {
    return FAIL; /*机芯手动程序，才能调节宽度*/
  }
 
  if(PKEEP == MChair_GetFuncCoreMannualWidthMax())
  {
    return FAIL; /*宽度不允许调节*/
  }

  if(pMChair->MannualCoreWidth < MChair_GetFuncCoreMannualWidthMax())
  {
    pMChair->MannualCoreWidth++;
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreWidthDec                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreWidthDec(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，不调节*/
  }

  if(pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL)
  {
    return FAIL; /*机芯手动程序，才能调节宽度*/
  }
 
  if(PKEEP == MChair_GetFuncCoreMannualWidthMax())
  {
    return FAIL; /*宽度不允许调节*/
  }

  if(pMChair->MannualCoreWidth > PX_MIN)
  {
    pMChair->MannualCoreWidth--;
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreWidth                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreWidth(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，不调节*/
  }

  if(pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL)
  {
    return FAIL; /*机芯手动程序，才能调节宽度*/
  }
 
  if(PKEEP == MChair_GetFuncCoreMannualWidthMax())
  {
    return FAIL; /*宽度不允许调节*/
  }

  pMChair->MannualCoreWidth += 2;
  if(pMChair->MannualCoreWidth > MChair_GetFuncCoreMannualWidthMax())
  {
    pMChair->MannualCoreWidth = PX_MIN;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreMannualUp                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreMannualUp(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run) /*正在检测肩部位置*/ 
  {
    if(TRUE == pMChair->StateBodyScan.Bit.ShoulderAdjustEn)    /*肩部检测时的用户肩位置调节*/
    {
      return BodyScan_UserAdjustShoulder(SHOULDER_ADJUST_UP, SHOULDER_ADJUST_KEY_LSMODE);
    }
    else
    {
      return FAIL;
    }
  }
  else
  {
    if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core) /*机芯手动*/
    {
      if(CORE_MOVE_ADJUST_ROLL_UP == Core_GetMoveAdjustRoll())
      {
        return FAIL;
      }
      else
      {
        return Core_SetMoveAdjustRoll(CORE_MOVE_ADJUST_ROLL_UP);
      }
    }
    else if(FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core) /*机芯自动时，调节肩部位置(体型)*/
    {
      //return BodyScan_UserAdjustShoulder(SHOULDER_ADJUST_UP);
      return FAIL;
    }
    else
    {
      return FAIL;
    }
  }
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreMannualDown                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreMannualDown(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run) /*正在检测肩部位置*/ 
  {
    if(TRUE == pMChair->StateBodyScan.Bit.ShoulderAdjustEn)    /*肩部检测时的用户肩位置调节*/
    {
      return BodyScan_UserAdjustShoulder(SHOULDER_ADJUST_DOWN, SHOULDER_ADJUST_KEY_LSMODE);
    }
    else
    {
      return FAIL;
    }
  }
  else
  {
    if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core) /*机芯手动*/
    {
      if(CORE_MOVE_ADJUST_ROLL_DOWN == Core_GetMoveAdjustRoll())
      {
        return FAIL;
      }
      else
      {
        return Core_SetMoveAdjustRoll(CORE_MOVE_ADJUST_ROLL_DOWN);
      }
    }
    else if(FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core) /*机芯自动时，调节肩部位置(体型)*/
    {
      //return BodyScan_UserAdjustShoulder(SHOULDER_ADJUST_DOWN);
      return FAIL;
    }
    else
    {
      return FAIL;
    }
  }
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreMannualFront                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreMannualFront(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，不调节*/
  }

  if(TRUE == pMChair->CSFlag.Bit.ZeroGravityAngleRun) 
  {
    return FAIL; /*零重力角度调节中,则该设置无效*/
  }

  if(FA_COREGASSPIKE_Thai == pMChair->FuncAuto_CoreGasSpike)
  {
    return FAIL; /*该程序不调节*/
  }
  
  if(FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core) /*机芯自动*/
  {
    if(pMChair->AutoCoreFlexLevelAdjust < 8)
    {
      pMChair->AutoCoreFlexLevelAdjust++;
      return SUCCESS;
    }
    else
    {
      return FAIL;
    }
  }
  else if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core) /*机芯手动*/
  {
    if(PKEEP == MChair_GetFuncCoreMannualFlexLevelMax())
    {
      return FAIL; /*不允许调节*/
    }

    if(pMChair->MannualCoreFlexLevel < MChair_GetFuncCoreMannualFlexLevelMax())
    {
      pMChair->MannualCoreFlexLevel++;
      return SUCCESS;
    }
    else
    {
      return FAIL;
    }
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreMannualBack                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreMannualBack(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，不调节*/
  }

  if(TRUE == pMChair->CSFlag.Bit.ZeroGravityAngleRun) 
  {
    return FAIL; /*零重力角度调节中,则该设置无效*/
  }

  if(FA_COREGASSPIKE_Thai == pMChair->FuncAuto_CoreGasSpike)
  {
    return FAIL; /*该程序不调节*/
  }

  if(FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core) /*机芯自动*/
  {
    if(pMChair->AutoCoreFlexLevelAdjust > 1)
    {
      pMChair->AutoCoreFlexLevelAdjust--;
      return SUCCESS;
    }
    else
    {
      return FAIL;
    }
  }
  else if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core) /*机芯手动*/
  {
    if(PKEEP == MChair_GetFuncCoreMannualFlexLevelMax())
    {
      return FAIL; /*不允许调节*/
    }

    if(pMChair->MannualCoreFlexLevel > 0)
    {
      pMChair->MannualCoreFlexLevel--;
      return SUCCESS;
    }
    else
    {
      return FAIL;
    }
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreFlexLevel                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreFlexLevel(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，不调节*/
  }

  if(TRUE == pMChair->CSFlag.Bit.ZeroGravityAngleRun) 
  {
    return FAIL; /*零重力角度调节中,则该设置无效*/
  }

  if(FA_COREGASSPIKE_Thai == pMChair->FuncAuto_CoreGasSpike)
  {
    return FAIL; /*该程序不调节*/
  }

  if(FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Core) /*机芯自动*/
  {
    if(pMChair->AutoCoreFlexLevelAdjust < 8)
    {
      pMChair->AutoCoreFlexLevelAdjust++;
    }
    else
    {
      pMChair->AutoCoreFlexLevelAdjust = 1;
    }
    return SUCCESS;
  }
  else if(FUNC_TYPE_MANNUAL == pMChair->ComponentFuncState.Bit.Core) /*机芯手动*/
  {
    if(PKEEP == MChair_GetFuncCoreMannualFlexLevelMax())
    {
      return FAIL; /*不允许调节*/
    }

    if(pMChair->MannualCoreFlexLevel < MChair_GetFuncCoreMannualFlexLevelMax())
    {
      pMChair->MannualCoreFlexLevel++;
    }
    else
    {
      pMChair->MannualCoreFlexLevel = 0;
    }
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreSpot                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreSpot(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，无效*/
  }

  if(pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL)
  {
    return FAIL; /*机芯手动程序，才能调节*/
  }

  if(Core_GetRollRange() != CORE_ROLL_RANGE_SPOT)
  {
    return Core_SetRollRange(CORE_ROLL_RANGE_SPOT);
  }
  else 
  {
    if( SUCCESS == Core_SetRollRange(CORE_ROLL_RANGE_WHOLE) )
    {
      return SUCCESS;
    }
    else
    {
      return Core_SetRollRange(CORE_ROLL_RANGE_PART);
    }
  }
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CorePart                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CorePart(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，无效*/
  }

  if(pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL)
  {
    return FAIL; /*机芯手动程序，才能调节*/
  }

  if(Core_GetRollRange() != CORE_ROLL_RANGE_PART)
  {
    return Core_SetRollRange(CORE_ROLL_RANGE_PART);
  }
  else 
  {
    if( SUCCESS == Core_SetRollRange(CORE_ROLL_RANGE_WHOLE) )
    {
      return SUCCESS;
    }
    else
    {
      return Core_SetRollRange(CORE_ROLL_RANGE_SPOT);
    }
  }
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreWhole                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreWhole(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，无效*/
  }

  if(pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL)
  {
    return FAIL; /*机芯手动程序，才能调节*/
  }

  if(Core_GetRollRange() != CORE_ROLL_RANGE_WHOLE)
  {
    return Core_SetRollRange(CORE_ROLL_RANGE_WHOLE);
  }
  return FAIL;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreSpotPartWhole                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreSpotPartWhole(uint8_t *pData)
{
  if(ON == pMChair->StateBodyScan.Bit.Run)
  {
    return FAIL; /*背部扫描时，无效*/
  }

  if(pMChair->ComponentFuncState.Bit.Core != FUNC_TYPE_MANNUAL)
  {
    return FAIL; /*机芯手动程序，才能调节*/
  }

  if(CORE_ROLL_RANGE_WHOLE == Core_GetRollRange())
  {
    if(FAIL == Core_SetRollRange(CORE_ROLL_RANGE_SPOT))
    {
      return Core_SetRollRange(CORE_ROLL_RANGE_PART);
    }
    else
    {
      return SUCCESS;
    }
  }
  else if(CORE_ROLL_RANGE_SPOT == Core_GetRollRange())
  {
    return Core_SetRollRange(CORE_ROLL_RANGE_PART);
  }
  else 
  {
    return Core_SetRollRange(CORE_ROLL_RANGE_WHOLE);
  }
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreRoll                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreRoll(uint8_t *pData)
{
  if(pMChair->FuncMannual_Core.Bit.XYZ.All != ROLL) 
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = ROLL;
  }
  else
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreKnead                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreKnead(uint8_t *pData)
{
  if((pMChair->FuncMannual_Core.Bit.XYZ.All != KNIN)  && 
     (pMChair->FuncMannual_Core.Bit.XYZ.All != KNOUT) ) 
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = KNIN;
  }
  else if(KNIN == pMChair->FuncMannual_Core.Bit.XYZ.All)
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = KNOUT;
  }
  else
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreTap                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreTap(uint8_t *pData)
{
  if((pMChair->FuncMannual_Core.Bit.XYZ.All == SWEDISH1)  || 
     (pMChair->FuncMannual_Core.Bit.XYZ.All == SWEDISH2) )
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  
  if((pMChair->FuncMannual_Core.Bit.TCS.All != LTAP) && 
     (pMChair->FuncMannual_Core.Bit.TCS.All != TAP)  ) 
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = LTAP;
  }
  else if(LTAP == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = TAP;
  }
  else
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CORE_ACTION_NONE;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreShiatsu                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreShiatsu(uint8_t *pData)
{
  if((pMChair->FuncMannual_Core.Bit.XYZ.All == SWEDISH1)  || 
     (pMChair->FuncMannual_Core.Bit.XYZ.All == SWEDISH2) )
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  
  if((pMChair->FuncMannual_Core.Bit.TCS.All != SHIA1)  && 
     (pMChair->FuncMannual_Core.Bit.TCS.All != SHIA2) ) 
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = SHIA1;
  }
  else if(SHIA1 == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = SHIA2;
  }
  else
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CORE_ACTION_NONE;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreClap                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreClap(uint8_t *pData)
{
  if((pMChair->FuncMannual_Core.Bit.XYZ.All == SWEDISH1)  || 
     (pMChair->FuncMannual_Core.Bit.XYZ.All == SWEDISH2) )
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  
  if((pMChair->FuncMannual_Core.Bit.TCS.All !=CLAP1)  && 
     (pMChair->FuncMannual_Core.Bit.TCS.All != CLAP2) ) 
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CLAP1;
  }
  else if(CLAP1 == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CLAP2;
  }
  else
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CORE_ACTION_NONE;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreMannualAction                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreMannualAction(uint8_t *pData)
{
  if(CORE_ACTION_NONE == pMChair->FuncMannual_Core.All) 
  {
    pMChair->MannualCoreXYZActionSpeed = 3;   
    pMChair->FuncMannual_Core.Bit.XYZ.All = KNIN;
    pMChair->FuncMannual_Core.Bit.TCS.All = CORE_ACTION_NONE;
  }
  else if((KNOUT == pMChair->FuncMannual_Core.Bit.XYZ.All) ||
          (KNIN  == pMChair->FuncMannual_Core.Bit.XYZ.All) )
  {
    pMChair->MannualCoreTCSActionSpeed = 3;   
    pMChair->FuncMannual_Core.Bit.TCS.All = LTAP;
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  else if((TAP  == pMChair->FuncMannual_Core.Bit.TCS.All) ||
          (LTAP == pMChair->FuncMannual_Core.Bit.TCS.All) )
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = SHIA1;
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  else if((SHIA2 == pMChair->FuncMannual_Core.Bit.TCS.All) ||
          (SHIA1 == pMChair->FuncMannual_Core.Bit.TCS.All) )
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CLAP1;
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  else if((CLAP1 == pMChair->FuncMannual_Core.Bit.TCS.All) ||
          (CLAP2 == pMChair->FuncMannual_Core.Bit.TCS.All) )
  {
    pMChair->MannualCoreXYZActionSpeed = 3;   
    pMChair->FuncMannual_Core.Bit.XYZ.All = ROLL;
    pMChair->FuncMannual_Core.Bit.TCS.All = CORE_ACTION_NONE;
  }
  else
  {
    pMChair->FuncMannual_Core.All = CORE_ACTION_NONE;
  }    

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreMannualMode                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreMannualMode(uint8_t *pData)
{
  if(KNIN  == pMChair->FuncMannual_Core.Bit.XYZ.All) 
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = KNOUT;
  }
  else if(KNOUT  == pMChair->FuncMannual_Core.Bit.XYZ.All) 
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = KNIN;
  }
  else if(TAP  == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = LTAP;
  }
  else if(LTAP  == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = TAP;
  }
  else if(SHIA1  == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = SHIA2;
  }
  else if(SHIA2  == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = SHIA1;
  }
  else if(CLAP1  == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CLAP2;
  }
  else if(CLAP2  == pMChair->FuncMannual_Core.Bit.TCS.All)
  {
    pMChair->FuncMannual_Core.Bit.TCS.All = CLAP1;
  }
  else
  {
    return FAIL;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreMannualSpeed                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreMannualSpeed(uint8_t *pData)
{
  if((KNOUT == pMChair->FuncMannual_Core.Bit.XYZ.All) ||
     (KNIN  == pMChair->FuncMannual_Core.Bit.XYZ.All) )
  {
    return UserRun_Key_CoreXYZSpeed(pData);
  }
  else
  {
    return  UserRun_Key_CoreTCSSpeed(pData);
  }
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreXYZAction                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreXYZAction(uint8_t *pData)
{
  if(pMChair->FuncMannual_Core.Bit.XYZ.All != pData[0]) 
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = pData[0];
  }
  else
  {
    pMChair->FuncMannual_Core.Bit.XYZ.All = CORE_ACTION_NONE;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_CoreTCSAction                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_CoreTCSAction(uint8_t *pData)
{
  return FAIL;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasIntensityAdd                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_GasIntensityAdd(uint8_t *pData)
{
  if((pMChair->ComponentFuncState.Bit.Gas != FUNC_TYPE_MANNUAL) &&  /*无充气功能*/
     (pMChair->ComponentFuncState.Bit.Gas != FUNC_TYPE_AUTO)    )
  {
    if((FMA_ROLLER_NONE == pMChair->FuncMA_Roller.Bit.Calves)            || /*无脚滚*/
       (FMA_FEET_ROLLER_ByActionTab == pMChair->FuncMA_Roller.Bit.Calves))  /*不是由表格控制开关的脚滚*/
    {
      return FAIL;
    }
  }

  if(pMChair->GasIntensity >= 5)
  {
    return FAIL;
  }
  
  pMChair->GasIntensity++;
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasIntensityDec                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_GasIntensityDec(uint8_t *pData)
{
  if((pMChair->ComponentFuncState.Bit.Gas != FUNC_TYPE_MANNUAL) &&  /*无充气功能*/
     (pMChair->ComponentFuncState.Bit.Gas != FUNC_TYPE_AUTO)    )
  {
    if((FMA_ROLLER_NONE == pMChair->FuncMA_Roller.Bit.Calves)            || /*无脚滚*/
       (FMA_FEET_ROLLER_ByActionTab == pMChair->FuncMA_Roller.Bit.Calves))  /*不是由表格控制开关的脚滚*/
    {
      return FAIL;
    }
  }

  if(pMChair->GasIntensity <= 1)
  {
    return FAIL;
  }
  
  pMChair->GasIntensity--;
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasIntensity                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_GasIntensity(uint8_t *pData)
{
  if((pMChair->ComponentFuncState.Bit.Gas != FUNC_TYPE_MANNUAL) &&  /*无充气功能*/
     (pMChair->ComponentFuncState.Bit.Gas != FUNC_TYPE_AUTO)    )
  {
    if((FMA_ROLLER_NONE == pMChair->FuncMA_Roller.Bit.Calves)            || /*无脚滚*/
       (FMA_FEET_ROLLER_ByActionTab == pMChair->FuncMA_Roller.Bit.Calves))  /*不是由表格控制开关的脚滚*/
    {
      return FAIL;
    }
  }
  
  pMChair->GasIntensity++;   
  if(pMChair->GasIntensity > 5)
  {
    pMChair->GasIntensity = 1;
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasHead                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasHead(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.Head != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.Head = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.Head = FM_GAS_HEAD;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasShoulder                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasShoulder(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.Shoulder != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.Shoulder = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.Shoulder = FM_GAS_SHOULDER;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasArms                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasArms(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.Arms != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.Arms = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.Arms = FM_GAS_ARMS;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasLumbar                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasLumbar(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.Lumbar != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.Lumbar = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.Lumbar = FM_GAS_LUMBAR;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasSeat                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasSeat(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.Seat != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.Seat = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.Seat = FM_GAS_SEAT;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasLumbarSeat                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasLumbarSeat(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.LumbarSeat != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.LumbarSeat = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.LumbarSeat = FM_GAS_LUMBARSEAT;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasCalves                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasCalves(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.Calves != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.Calves = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.Calves = FM_GAS_CALVES;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasFeet                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasFeet(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.Feet != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.Feet = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.Feet = FM_GAS_CALVESFEET;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasCalvesFeet                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_GasCalvesFeet(uint8_t *pData)
{
  if(pMChair->FuncMannual_Gas.Bit.CalvesFeet != FM_GAS_NONE)
  {
    pMChair->FuncMannual_Gas.Bit.CalvesFeet = FM_GAS_NONE;
  }
  else
  {
    pMChair->FuncMannual_Gas.Bit.CalvesFeet = FM_GAS_CALVESFEET;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasFullGas                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_GasFullGas(uint8_t *pData)
{
  if(pMChair->FuncAuto_Gas != FA_GAS_FullGas)
  {
    pMChair->FuncAuto_Gas = FA_GAS_FullGas;
  }
  else
  {
    pMChair->FuncAuto_Gas = FA_GAS_NONE;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasQuickGas                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_GasQuickGas(uint8_t *pData)
{
  if(pMChair->FuncAuto_Gas != FA_GAS_QuickGas)
  {
    pMChair->FuncAuto_Gas = FA_GAS_QuickGas;
  }
  else
  {
    pMChair->FuncAuto_Gas = FA_GAS_NONE;
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_GasPartSelcet                                                                                                        
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_GasPartSelcet(uint8_t *pData)
{
  if(FM_GAS_NONE == pMChair->FuncMannual_Gas.All)
  {
    pMChair->FuncMannual_Gas.All = FM_GAS_NONE;
    pMChair->FuncMannual_Gas.Bit.CalvesFeet = FM_GAS_CALVESFEET;
  }
  else if(FM_GAS_CALVESFEET == pMChair->FuncMannual_Gas.Bit.CalvesFeet)
  {
    pMChair->FuncMannual_Gas.All = FM_GAS_NONE;
    pMChair->FuncMannual_Gas.Bit.Seat = FM_GAS_SEAT;
  }
  else if(FM_GAS_SEAT == pMChair->FuncMannual_Gas.Bit.Seat)
  {
    pMChair->FuncMannual_Gas.All = FM_GAS_NONE;
    pMChair->FuncMannual_Gas.Bit.Arms = FM_GAS_ARMS;
  }
  else if(FM_GAS_ARMS == pMChair->FuncMannual_Gas.Bit.Arms)
  {
    pMChair->FuncMannual_Gas.All = FM_GAS_NONE;
    pMChair->FuncMannual_Gas.Bit.Shoulder = FM_GAS_SHOULDER;
  }
  else
  {
    pMChair->FuncMannual_Gas.All = FM_GAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_VibLumbarBack                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_VibLumbarBack(uint8_t *pData)
{
  if(Core_GetYPosition() < PY15)        /*上半身，不允许机芯振动*/
  {
    return FAIL;
  }
  
  /*振动处于伴随状态--------------------------------------*/
  if((pMChair->FuncMA_Vib.Bit.LumbarBack != FMA_VIB_NONE) && 
     (pMChair->FuncMA_Vib.Bit.LumbarBack != FMA_LUMBARBACK_VIB_Mannual))
  {
    if(ON == pMChair->LumbarBackVibCtrlSw) /*伴随状态下的振动正在运行*/
    {
      pMChair->FuncMA_Vib.Bit.LumbarBack = FMA_VIB_NONE; /*关闭振动*/
    }
    else /*伴随状态下的振动处于停止阶段*/
    {
      pMChair->FuncMA_Vib.Bit.LumbarBack = FMA_SEAT_VIB_Mannual; /*振动常开*/
    }
  }
  /*振动被用户单独操作------------------------------------*/
  else
  {
    if(pMChair->FuncMA_Vib.Bit.LumbarBack != FMA_VIB_NONE)
    {
      pMChair->FuncMA_Vib.Bit.LumbarBack = FMA_VIB_NONE;
    }
    else
    {
      pMChair->FuncMA_Vib.Bit.LumbarBack = FMA_LUMBARBACK_VIB_Mannual;
    }
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_VibSeat                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_VibSeat(uint8_t *pData)
{
  /*振动处于伴随状态--------------------------------------*/
  if((pMChair->FuncMA_Vib.Bit.Seat != FMA_VIB_NONE) && 
     (pMChair->FuncMA_Vib.Bit.Seat != FMA_SEAT_VIB_Mannual))
  {
    if(ON == pMChair->SeatVibCtrlSw) /*伴随状态下的振动正在运行*/
    {
      pMChair->FuncMA_Vib.Bit.Seat = FMA_VIB_NONE; /*关闭振动*/
    }
    else /*伴随状态下的振动处于停止阶段*/
    {
      pMChair->FuncMA_Vib.Bit.Seat = FMA_SEAT_VIB_Mannual; /*振动常开*/
    }
  }
  /*振动被用户单独操作------------------------------------*/
  else
  {
    if(pMChair->FuncMA_Vib.Bit.Seat != FMA_VIB_NONE)
    {
      pMChair->FuncMA_Vib.Bit.Seat = FMA_VIB_NONE;
    }
    else
    {
      pMChair->FuncMA_Vib.Bit.Seat = FMA_SEAT_VIB_Mannual;
    }
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_VibCalves                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_VibCalves(uint8_t *pData)
{
  /*振动处于伴随状态--------------------------------------*/
  if((pMChair->FuncMA_Vib.Bit.Calves != FMA_VIB_NONE) && 
     (pMChair->FuncMA_Vib.Bit.Calves != FMA_CALVES_VIB_Mannual))
  {
    if(ON == pMChair->CalvesVibCtrlSw) /*伴随状态下的振动正在运行*/
    {
      pMChair->FuncMA_Vib.Bit.Calves = FMA_VIB_NONE; /*关闭振动*/
    }
    else /*伴随状态下的振动处于停止阶段*/
    {
      pMChair->FuncMA_Vib.Bit.Calves = FMA_CALVES_VIB_Mannual; /*振动常开*/
    }
  }
  /*振动被用户单独操作------------------------------------*/
  else
  {
    if(pMChair->FuncMA_Vib.Bit.Calves != FMA_VIB_NONE)
    {
      pMChair->FuncMA_Vib.Bit.Calves = FMA_VIB_NONE;
    }
    else
    {
      pMChair->FuncMA_Vib.Bit.Calves = FMA_CALVES_VIB_Mannual;
    }
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_VibFeet                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_VibFeet(uint8_t *pData)
{
  /*振动处于伴随状态--------------------------------------*/
  if((pMChair->FuncMA_Vib.Bit.Feet != FMA_VIB_NONE) && 
     (pMChair->FuncMA_Vib.Bit.Feet != FMA_FEET_VIB_Mannual))
  {
    if(ON == pMChair->FeetVibCtrlSw) /*伴随状态下的振动正在运行*/
    {
      pMChair->FuncMA_Vib.Bit.Feet = FMA_VIB_NONE; /*关闭振动*/
    }
    else /*伴随状态下的振动处于停止阶段*/
    {
      pMChair->FuncMA_Vib.Bit.Feet = FMA_FEET_VIB_Mannual; /*振动常开*/
    }
  }
  /*振动被用户单独操作------------------------------------*/
  else
  {
    if(pMChair->FuncMA_Vib.Bit.Feet != FMA_VIB_NONE)
    {
      pMChair->FuncMA_Vib.Bit.Feet = FMA_VIB_NONE;
    }
    else
    {
      pMChair->FuncMA_Vib.Bit.Feet = FMA_FEET_VIB_Mannual;
    }
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_HeatLumbarBack                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_HeatLumbarBack(uint8_t *pData)
{
  /*处于伴随状态--------------------------------------*/
  if((pMChair->FuncMA_Heat.Bit.LumbarBack != FMA_HEAT_NONE) && 
     (pMChair->FuncMA_Heat.Bit.LumbarBack != FMA_LUMBARBACK_HEAT_Mannual))
  {
    if(ON == pMChair->LumbarBackHeatCtrlSw) /*伴随状态下的正在运行*/
    {
      pMChair->FuncMA_Heat.Bit.LumbarBack = FMA_HEAT_NONE; /*关闭*/
    }
    else /*伴随状态下的处于停止阶段*/
    {
      pMChair->FuncMA_Heat.Bit.LumbarBack = FMA_LUMBARBACK_HEAT_Mannual; /*常开*/
    }
  }
  /*被用户单独操作------------------------------------*/
  else
  {
    if(TRUE == pMChair->CSFlag.Bit.LumbarBackHeatMannualOpDisable)
    {
      return FAIL; /*靠背加热手动无效*/
    }
    
    if(pMChair->FuncMA_Heat.Bit.LumbarBack != FMA_HEAT_NONE)
    {
      pMChair->FuncMA_Heat.Bit.LumbarBack = FMA_HEAT_NONE;
    }
    else
    {
      pMChair->FuncMA_Heat.Bit.LumbarBack = FMA_LUMBARBACK_HEAT_Mannual;
    }
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_HeatSeat                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_HeatSeat(uint8_t *pData)
{
  /*处于伴随状态--------------------------------------*/
  if((pMChair->FuncMA_Heat.Bit.Seat != FMA_HEAT_NONE) && 
     (pMChair->FuncMA_Heat.Bit.Seat != FMA_SEAT_HEAT_Mannual))
  {
    if(ON == pMChair->SeatHeatCtrlSw) /*伴随状态下的正在运行*/
    {
      pMChair->FuncMA_Heat.Bit.Seat = FMA_HEAT_NONE; /*关闭*/
    }
    else /*伴随状态下的处于停止阶段*/
    {
      pMChair->FuncMA_Heat.Bit.Seat = FMA_SEAT_HEAT_Mannual; /*常开*/
    }
  }
  /*被用户单独操作------------------------------------*/
  else
  {
    if(TRUE == pMChair->CSFlag.Bit.SeatHeatMannualOpDisable)
    {
      return FAIL; /*加热手动无效*/
    }
    if(pMChair->FuncMA_Heat.Bit.Seat != FMA_HEAT_NONE)
    {
      pMChair->FuncMA_Heat.Bit.Seat = FMA_HEAT_NONE;
    }
    else
    {
      pMChair->FuncMA_Heat.Bit.Seat = FMA_SEAT_HEAT_Mannual;
    }
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_HeatCalves                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_HeatCalves(uint8_t *pData)
{
  /*处于伴随状态--------------------------------------*/
  if((pMChair->FuncMA_Heat.Bit.Calves != FMA_HEAT_NONE) && 
     (pMChair->FuncMA_Heat.Bit.Calves != FMA_CALVES_HEAT_Mannual))
  {
    if(ON == pMChair->CalvesHeatCtrlSw) /*伴随状态下的正在运行*/
    {
      pMChair->FuncMA_Heat.Bit.Calves = FMA_HEAT_NONE; /*关闭*/
    }
    else /*伴随状态下的处于停止阶段*/
    {
      pMChair->FuncMA_Heat.Bit.Calves = FMA_CALVES_HEAT_Mannual; /*常开*/
    }
  }
  /*被用户单独操作------------------------------------*/
  else
  {
    if(TRUE == pMChair->CSFlag.Bit.CalvesHeatMannualOpDisable)
    {
      return FAIL; /*加热手动无效*/
    }
    if(pMChair->FuncMA_Heat.Bit.Calves != FMA_HEAT_NONE)
    {
      pMChair->FuncMA_Heat.Bit.Calves = FMA_HEAT_NONE;
    }
    else
    {
      pMChair->FuncMA_Heat.Bit.Calves = FMA_CALVES_HEAT_Mannual;
    }
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_HeatFeet                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t  UserRun_Key_HeatFeet(uint8_t *pData)
{
  /*处于伴随状态--------------------------------------*/
  if((pMChair->FuncMA_Heat.Bit.Feet != FMA_HEAT_NONE) && 
     (pMChair->FuncMA_Heat.Bit.Feet != FMA_CALVES_HEAT_Mannual))
  {
    if(ON == pMChair->FeetHeatCtrlSw) /*伴随状态下的正在运行*/
    {
      pMChair->FuncMA_Heat.Bit.Feet = FMA_HEAT_NONE; /*关闭*/
    }
    else /*伴随状态下的处于停止阶段*/
    {
      pMChair->FuncMA_Heat.Bit.Feet = FMA_CALVES_HEAT_Mannual; /*常开*/
    }
  }
  /*被用户单独操作------------------------------------*/
  else
  {
    if(TRUE == pMChair->CSFlag.Bit.FeetHeatMannualOpDisable)
    {
      return FAIL; /*脚部加热手动无效*/
    }
    if(pMChair->FuncMA_Heat.Bit.Feet != FMA_HEAT_NONE)
    {
      pMChair->FuncMA_Heat.Bit.Feet = FMA_HEAT_NONE;
    }
    else
    {
      pMChair->FuncMA_Heat.Bit.Feet = FMA_CALVES_HEAT_Mannual;
    }
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_RollerCalves                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_RollerCalves(uint8_t *pData)
{
  /*处于伴随状态--------------------------------------*/
  if((pMChair->FuncMA_Roller.Bit.Calves != FMA_ROLLER_NONE) && 
     (pMChair->FuncMA_Roller.Bit.Calves != FMA_CALVES_ROLLER_Mannual))
  {
    if(ON == pMChair->CalvesRollerCtrlSw) /*伴随状态下的正在运行*/
    {
      pMChair->FuncMA_Roller.Bit.Calves = FMA_ROLLER_NONE; /*关闭*/
    }
    else /*伴随状态下的处于停止阶段*/
    {
      pMChair->FuncMA_Roller.Bit.Calves = FMA_CALVES_ROLLER_Mannual; /*常开*/
    }
  }
  /*被用户单独操作------------------------------------*/
  else
  {
    if(pMChair->FuncMA_Roller.Bit.Calves != FMA_ROLLER_NONE)
    {
      pMChair->FuncMA_Roller.Bit.Calves = FMA_ROLLER_NONE;
    }
    else
    {
      pMChair->FuncMA_Roller.Bit.Calves = FMA_CALVES_ROLLER_Mannual;
    }
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_RollerFeet                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_RollerFeet(uint8_t *pData)
{
  /*处于伴随状态--------------------------------------*/
  if((pMChair->FuncMA_Roller.Bit.Feet != FMA_ROLLER_NONE) && 
     (pMChair->FuncMA_Roller.Bit.Feet != FMA_FEET_ROLLER_Mannual))
  {
    if(ON == pMChair->FeetRollerCtrlSw) /*伴随状态下的正在运行*/
    {
      pMChair->FuncMA_Roller.Bit.Feet = FMA_ROLLER_NONE; /*关闭*/
    }
    else /*伴随状态下的处于停止阶段*/
    {
      pMChair->FuncMA_Roller.Bit.Feet = FMA_FEET_ROLLER_Mannual; /*常开*/
    }
  }
  /*被用户单独操作------------------------------------*/
  else
  {
    if(pMChair->FuncMA_Roller.Bit.Feet != FMA_ROLLER_NONE)
    {
      pMChair->FuncMA_Roller.Bit.Feet = FMA_ROLLER_NONE;
    }
    else
    {
      pMChair->FuncMA_Roller.Bit.Feet = FMA_FEET_ROLLER_Mannual;
    }
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_SleepLed                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_SleepLed(uint8_t *pData)
{
  if(pMChair->FuncMA_Led.Bit.Logo != FMA_PROJECTION_LED_Mannual)   /*投影灯*/
  {
    pMChair->FuncMA_Led.Bit.Logo = FMA_PROJECTION_LED_Mannual;
  }
  else
  {
    pMChair->FuncMA_Led.Bit.Logo = FMA_LED_NONE;      
  }
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoQuick                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoQuick(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Quick)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_Quick;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoRelax                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoRelax(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Relax)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_Relax;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 2;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoMoveSleep                                                                                                        
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoMoveSleep(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_MoveSleep)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_MoveSleep;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 1;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoStretch                                                                                                        
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoStretch(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Stretch)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_Stretch;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoScraping                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoScraping(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Scraping)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_Scraping;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoShiatsu                                                                                                        
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoShiatsu(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Shiatsu)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_Shiatsu;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoLady                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoLady(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Lady)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_Lady;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 2;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoMan                                                                                                        
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoMan(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_Man)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_Man;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoShoulderRelax                                                                                                       
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoShoulderRelax(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_ShoulderRelax)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_ShoulderRelax;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 2;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoShoulderRecovery                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoShoulderRecovery(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_ShoulderRecovery)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_ShoulderRecovery;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoShoulderTuina                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoShoulderTuina(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_ShoulderTuina)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_ShoulderTuina;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoShoulderShiatsu                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoShoulderShiatsu(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_ShoulderShiatsu)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_ShoulderShiatsu;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoLumbarButtockRelax                                                                                                        
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoLumbarButtockRelax(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_LumbarButtockRelax)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_LumbarButtockRelax;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 2;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoLumbarButtockRecovery                                                                                                     
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoLumbarButtockRecovery(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_LumbarButtockRecovery)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_LumbarButtockRecovery;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoLumbarButtockPress                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoLumbarButtockPress(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_LumbarButtockPress)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_LumbarButtockPress;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoLumbarKidneyCare                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoLumbarKidneyCare(uint8_t *pData)
{
  if(pMChair->FuncAuto_CoreGas != FA_COREGAS_LumbarKidneyCare)
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_LumbarKidneyCare;
    pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
    pMChair->GasIntensity = 3;
    pMChair->UserMassageTimeMin = 15;
    pMChair->UserMassageTimeSec = 0;
  }
  else
  {
    pMChair->FuncAuto_CoreGas = FA_COREGAS_NONE;
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_AutoGridCombo                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_AutoGridCombo(uint8_t *pData)
{
  uint8_t Result;

//  Result = GridComboAuto_UpdateComboSelectBit(&pData[1]);
//  if(SUCCESS == Result)
//  {
//    if(FA_GRIDCOMBO_ON == pMChair->FuncAuto_GridCombo)
//    {
//      pMChair->AutoCoreFlexLevelAdjust = CORE_AUTO_PZLEVEL_REF;    /*自动程序下  机芯按摩强度*/
//      pMChair->UserMassageTimeMin = 15;
//      pMChair->UserMassageTimeSec = 0;
//    }
//  }

  return Result;
}


/*
************************************************************************************************************************
* 函数名称 : UserRun_EnterSysModeVender                                                                                                         
* 功能描述 : 进入厂家模                                                                                    
* 输入参数 : pData         -- 键值所附带的命令数据 
*            SysModeVender -- 要进入的厂家模式
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_EnterSysModeVender(uint8_t *pData, uint8_t SysModeVender)
{
  /*注：由于类平板靠中心板供电，ERP关闭后，类平板就无法操作了。
        因此无法在待机模式下操作类平板进入厂家模式，只能在开机后操作类平板进入厂家模式。
        增加SysModeVender这个变量，记录要进入的厂家模式。开机状态下，按下相应的厂家模式按键，
        将先进入待机模式，然后待机模式的代码将根据SysModeVender变量的值，再转入到相应的厂家模式。*/
  if(pMChair->SysModeCur != SYS_MODE_USERRUN)
  {
    return FAIL;/*只能在用户运行模式下，操作类平板进入厂家模式*/
  }

  pMChair->SysModeCur    = SYS_MODE_STANDBY;    /*先进入待机模式*/
  pMChair->SysModeVender = SysModeVender;       /*再从待机模式转入到厂家模式*/
  pMChair->SysModeHis    = SYS_MODE_USERRUN;  

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_InspectAuto                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_InspectAuto(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_INSPECTAUTO);
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_InspectManual                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_InspectManual(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_INSPECTMANUAL);
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_PackingAngle                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_PackingAngle(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_PACKING);
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_InspectOther1                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_InspectOther1(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_INSPECTOTHER1);
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_InspectOther2                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_InspectOther2(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_INSPECTOTHER2);
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_TestNoTimer                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_TestNoTimer(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_TESTNOTIMER);
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_TestAge                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_TestAge(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_TESTAGE);
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_Key_TestSpike                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t UserRun_Key_TestSpike(uint8_t *pData)
{
  return UserRun_EnterSysModeVender(pData, SYS_MODE_TESTSPIKE);
}


/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/

static const SysMode_KeyLogicTabItem_t UserRun_KeyLogicTab[] = 
{
  /*附加操作：

    键值执行前：bit7 -- 1：ERP主电源关闭，则键值执行前，要重新开启。    
                        0：ERP主电源关闭，则键值执行前，不需要重新开启。    
    键值执行前：bit6 -- 1：暂停开启，仍可执行键值。  
                        0：暂停开启，则键值不执行。
    键值执行前：bit5 -- 1：不管背光状态，直接执行键值
                        0：手控器背光若关闭，则要先开启，且本次键值无效。

    键值执行后：                                                   */

  {KEYVAL_NoPress,                  B(01100000),    UserRun_Key_NoKeyPress},

  /* 开关机、暂停、调时间 等--------------------------------------------------------*/
  {KEYVAL_Power,                    B(01100000),    UserRun_Key_Power},
  {KEYVAL_Pause,                    B(01000000),    UserRun_Key_Pause},
//  {KEYVAL_TimerAdd,                 B(00000000),    UserRun_Key_TimerAdd},
//  {KEYVAL_TimerDec,                 B(00000000),    UserRun_Key_TimerDec},
  {KEYVAL_Timer,                    B(00000000),    UserRun_Key_Timer},
  {KEYVAL_BodyCheckOk,              B(00000000),    UserRun_Key_BodyCheckOk},
//  {KEYVAL_BodyReCheck,              B(00000000),    UserRun_Key_BodyReCheck},

  {KEYVAL_BluetoothSwitch,          B(00000000),    UserRun_Key_BluetoothSwitch},
  /*推杆相关------------------------------------------------------------------------*/
//  {KEYVAL_SpikeBackUp,              B(10000000),    UserRun_Key_SpikeBackUp},
//  {KEYVAL_SpikeBackDown,            B(10000000),    UserRun_Key_SpikeBackDown},
  {KEYVAL_SpikeFeetUp,              B(10000000),    UserRun_Key_SpikeFeetUp},
  {KEYVAL_SpikeFeetDown,            B(10000000),    UserRun_Key_SpikeFeetDown},
  {KEYVAL_SpikeBackUpFeetDown,      B(10000000),    UserRun_Key_SpikeBackUpFeetDown},
  {KEYVAL_SpikeBackDownFeetUp,      B(10000000),    UserRun_Key_SpikeBackDownFeetUp},
  {KEYVAL_SpikeLegExtend,           B(10000000),    UserRun_Key_SpikeLegExtend},
  {KEYVAL_SpikeLegShorten,          B(10000000),    UserRun_Key_SpikeLegShorten},
  {KEYVAL_SpikeZeroGravity1,        B(10000000),    UserRun_Key_SpikeZeroGravity1},
//  {KEYVAL_SpikeZeroGravity2,        B(10000000),    UserRun_Key_SpikeZeroGravity2},
  {KEYVAL_SpikeZeroGravity,         B(10000000),    UserRun_Key_SpikeZeroGravity},
  {KEYVAL_SpikeHomeReset,           B(10000000),    UserRun_Key_SpikeHomeReset},
//  {KEYVAL_SpikeHomeReset,           B(10000000),    UserRun_Key_SpikeBackUpFeetDown},
//  {KEYVAL_SpikeULegExtend,          B(10000000),    UserRun_Key_SpikeULegExtend},
//  {KEYVAL_SpikeULegShorten,         B(10000000),    UserRun_Key_SpikeULegShorten},
  
  /*机芯手动 及其辅助变量  相关-----------------------------------------------------*/
  {KEYVAL_CoreXYZSpeedAdd,          B(00000000),    UserRun_Key_CoreXYZSpeedAdd},
  {KEYVAL_CoreXYZSpeedDec,          B(00000000),    UserRun_Key_CoreXYZSpeedDec},
  {KEYVAL_CoreXYZSpeed,             B(00000000),    UserRun_Key_CoreXYZSpeed},
  {KEYVAL_CoreTCSSpeedAdd,          B(00000000),    UserRun_Key_CoreTCSSpeedAdd},
  {KEYVAL_CoreTCSSpeedDec,          B(00000000),    UserRun_Key_CoreTCSSpeedDec},
  {KEYVAL_CoreTCSSpeed,             B(00000000),    UserRun_Key_CoreTCSSpeed},
  {KEYVAL_CoreWidthAdd,             B(00000000),    UserRun_Key_CoreWidthAdd},
  {KEYVAL_CoreWidthDec,             B(00000000),    UserRun_Key_CoreWidthDec},
  {KEYVAL_CoreWidth,                B(00000000),    UserRun_Key_CoreWidth},
  {KEYVAL_CoreMannualUp,            B(00000000),    UserRun_Key_CoreMannualUp},
  {KEYVAL_CoreMannualDown,          B(00000000),    UserRun_Key_CoreMannualDown},
  {KEYVAL_CoreMannualFront,         B(00000000),    UserRun_Key_CoreMannualFront},
  {KEYVAL_CoreMannualBack,          B(00000000),    UserRun_Key_CoreMannualBack},
  {KEYVAL_CoreFlexLevel,            B(00000000),    UserRun_Key_CoreFlexLevel},
  {KEYVAL_CoreSpot,                 B(00000000),    UserRun_Key_CoreSpot},
  {KEYVAL_CorePart,                 B(00000000),    UserRun_Key_CorePart},
//  {KEYVAL_CoreWhole,                B(00000000),    UserRun_Key_CoreWhole},
//  {KEYVAL_CoreSpotPartWhole,        B(00000000),    UserRun_Key_CoreSpotPartWhole},
  {KEYVAL_CoreRoll,                 B(00000000),    UserRun_Key_CoreRoll},
  {KEYVAL_CoreKnead,                B(00000000),    UserRun_Key_CoreKnead},
  {KEYVAL_CoreTap,                  B(00000000),    UserRun_Key_CoreTap},
  {KEYVAL_CoreClap,                 B(00000000),    UserRun_Key_CoreClap},
  {KEYVAL_CoreShiatsu,              B(00000000),    UserRun_Key_CoreShiatsu},
//  {KEYVAL_CoreMannualAction,        B(00000000),    UserRun_Key_CoreMannualAction},
//  {KEYVAL_CoreMannualMode,          B(00000000),    UserRun_Key_CoreMannualMode},
//  {KEYVAL_CoreMannualSpeed,         B(00000000),    UserRun_Key_CoreMannualSpeed},
  
  {KEYVAL_XYZAction,                B(00000000),    UserRun_Key_CoreXYZAction},
//  {KEYVAL_TCSAction,                B(00000000),    UserRun_Key_CoreTCSAction},
  
  /*充气 及 辅助变量  相关------------------------------------------------------*/
  {KEYVAL_GasIntensityAdd,          B(00000000),    UserRun_Key_GasIntensityAdd},
  {KEYVAL_GasIntensityDec,          B(00000000),    UserRun_Key_GasIntensityDec},
  {KEYVAL_GasIntensity,             B(00000000),    UserRun_Key_GasIntensity},
//  {KEYVAL_GasHead,                  B(00000000),    UserRun_Key_GasHead},
  {KEYVAL_GasShoulder,              B(00000000),    UserRun_Key_GasShoulder},
  {KEYVAL_GasArms,                  B(00000000),    UserRun_Key_GasArms},
//  {KEYVAL_GasLumbar,                B(00000000),    UserRun_Key_GasLumbar},
//  {KEYVAL_GasSeat,                  B(00000000),    UserRun_Key_GasSeat},
  {KEYVAL_GasLumbarSeat,            B(00000000),    UserRun_Key_GasLumbarSeat},
  {KEYVAL_GasCalves,                B(00000000),    UserRun_Key_GasCalves},
//  {KEYVAL_GasFeet,                  B(00000000),    UserRun_Key_GasFeet},
//  {KEYVAL_GasCalvesFeet,            B(00000000),    UserRun_Key_GasCalvesFeet},
  {KEYVAL_AutoFullGas,              B(00000000),    UserRun_Key_GasFullGas},
  {KEYVAL_GasPartSelcet,            B(00000000),    UserRun_Key_GasPartSelcet},
  {KEYVAL_AutoQuickGas,             B(00000000),    UserRun_Key_GasQuickGas},

  /*滚轮、加热 、振动、灯 等其他功能相关--------------------------------------------*/
//  {KEYVAL_VibLumbarBack,            B(00000000),    UserRun_Key_VibLumbarBack},
//  {KEYVAL_VibSeat,                  B(00000000),    UserRun_Key_VibSeat},
//  {KEYVAL_VibCalves,                B(00000000),    UserRun_Key_VibCalves},
//  {KEYVAL_VibFeet,                  B(00000000),    UserRun_Key_VibFeet},
//  {KEYVAL_HeatLevelAdd,             B(00000000),    NULL},
//  {KEYVAL_HeatLevelDec,             B(00000000),    NULL},
//  {KEYVAL_HeatLevel,                B(00000000),    NULL},
  {KEYVAL_HeatLumbarBack,           B(00000000),    UserRun_Key_HeatLumbarBack},
  {KEYVAL_HeatSeat,                 B(00000000),    UserRun_Key_HeatLumbarBack/*UserRun_Key_HeatSeat*/},
//  {KEYVAL_HeatCalves,               B(00000000),    UserRun_Key_HeatCalves},
//  {KEYVAL_HeatFeet,                 B(00000000),    UserRun_Key_HeatFeet},
  {KEYVAL_RollerCalves,             B(00000000),    UserRun_Key_RollerCalves},
  {KEYVAL_RollerFeet,               B(00000000),    UserRun_Key_RollerFeet},
  {KEYVAL_SleepLed,                 B(00000000),    UserRun_Key_SleepLed},

  /*自动程序相关 -------------------------------------------------------------------*/
  {KEYVAL_AutoQuick,                B(00000000),    UserRun_Key_AutoQuick},
  {KEYVAL_AutoRelax,                B(00000000),    UserRun_Key_AutoRelax},
  {KEYVAL_AutoMoveSleep,            B(00000000),    UserRun_Key_AutoMoveSleep},
  {KEYVAL_AutoStretch,              B(00000000),    UserRun_Key_AutoStretch},
  {KEYVAL_AutoScraping,             B(00000000),    UserRun_Key_AutoScraping},
  {KEYVAL_AutoShiatsu,              B(00000000),    UserRun_Key_AutoShiatsu},
  {KEYVAL_AutoLady,                 B(00000000),    UserRun_Key_AutoLady},
  {KEYVAL_AutoMan,                  B(00000000),    UserRun_Key_AutoMan},
  {KEYVAL_AutoShoulderRelax,        B(00000000),    UserRun_Key_AutoShoulderRelax},
  {KEYVAL_AutoShoulderRecovery,     B(00000000),    UserRun_Key_AutoShoulderRecovery},
  {KEYVAL_AutoShoulderTuina,        B(00000000),    UserRun_Key_AutoShoulderTuina},
  {KEYVAL_AutoShoulderShiatsu,      B(00000000),    UserRun_Key_AutoShoulderShiatsu},
  {KEYVAL_AutoLumbarButtockRelax,   B(00000000),    UserRun_Key_AutoLumbarButtockRelax},
  {KEYVAL_AutoLumbarButtockRecovery,B(00000000),    UserRun_Key_AutoLumbarButtockRecovery},
  {KEYVAL_AutoLumbarButtockPress,   B(00000000),    UserRun_Key_AutoLumbarButtockPress},
  {KEYVAL_AutoLumbarKidneyCare,     B(00000000),    UserRun_Key_AutoLumbarKidneyCare},
  
  {KEYVAL_AutoGridCombo,            B(00000000),    UserRun_Key_AutoGridCombo},

  /*厂家模式的切换------------------------------------------------------------------*/
  {KEYVAL_InspectAuto,              B(00000000),    UserRun_Key_InspectAuto},           /*系统模式：厂家自检*/
  {KEYVAL_InspectManual,            B(00000000),    UserRun_Key_InspectManual},         /*系统模式：厂家手检*/
  {KEYVAL_PackingAngle,             B(00000000),    UserRun_Key_PackingAngle},          /*系统模式：厂家包装*/
  {KEYVAL_InspectOther1,            B(00000000),    UserRun_Key_InspectOther1},         /*系统模式：系统模式：其他厂家检测 1*/
  {KEYVAL_InspectOther2,            B(00000000),    UserRun_Key_InspectOther2},         /*系统模式：系统模式：其他厂家检测 2*/
  {KEYVAL_TestNoTimer,              B(00000000),    UserRun_Key_TestNoTimer},           /*系统模式：厂家考机 之 无定时测试模式*/
  {KEYVAL_TestSpike,                B(00000000),    UserRun_Key_TestSpike},             /*系统模式：厂家考机 之 推杆*/
  {KEYVAL_TestAge,                  B(00000000),    UserRun_Key_TestAge},               /*系统模式：厂家考机 之 寿命 动一小时，停15分钟*/

  /*--------------------------------------------------------------------------------*/
  {KEYVAL_MAX,                      B(00000000),    NULL}
};


#define USERRUN_KEY_TAB_NUM  TAB_NUM(UserRun_KeyLogicTab)

static uint16_t UserRun_GetKeyValID(uint16_t index)
{
  if(index > (USERRUN_KEY_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return UserRun_KeyLogicTab[index].KeyValID;
}

/*
************************************************************************************************************************
* 函数名称 : UserRun_KeyValAdditonOp                                                                                                         
* 功能描述 : 键值执行前后的附加操作                                                                                    
* 输入参数 : Index       -- 键值在表格里的索引
*            BeforeAfter -- BEFORE：键值执行前执行附加操作
*                           AFTER：键值执行后执行附加操作   
*            CurExeState -- 当前执行状态。 SUCCESS 成功   FAIL 失败 
* 返回参数 : SUCCESS -- 可执行后续键值操作。
*            FAIL    -- 不可执行后续键值操作。                                                            
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t UserRun_KeyValAdditonOp(uint8_t Index, uint8_t BeforeAfter, uint8_t CurExeState)
{
  uint8_t ret;


  ret = SUCCESS;                                                /*先假设成功*/
  
  /*键值执行前的附加操作------------------------------------------------------*/
  if(BEFORE == BeforeAfter) 
  {
    /*键值执行前：bit7 -- 1：ERP主电源关闭，则键值执行前，要重新开启。    
                          0：ERP主电源关闭，则键值执行前，不需要重新开启。 */   
    if(UserRun_KeyLogicTab[Index].AdditonOp & B(10000000))
    {
      if(OFF == pMChair->ERPPowerSw)                            /*主电源若关闭，则重新开启*/
      {
        pMChair->ERPPowerSw = ON;                               /*开启主电源*/
        pMChair->ERPPowerOnTimeMs = 0;
      }
      pMChair->ERPPowerOffWaitTimeMs = 0;
    }

    /*键值执行前：bit6 -- 1：暂停开启，仍可执行键值。  
                          0：暂停开启，则键值不执行。*/
    if(0 == (UserRun_KeyLogicTab[Index].AdditonOp & B(01000000))) 
    {
      if(TRUE == pMChair->CSFlag.Bit.Pause)
      {
        ret = FAIL;                                             /*暂停开启，则不执行键值处理*/
      }
    }

    /*键值执行前：bit5 -- 1：不管背光状态，直接执行键值
                          0：手控器背光若关闭，则要先开启，且本次键值无效。*/
    if(0 == (UserRun_KeyLogicTab[Index].AdditonOp & B(00100000))) 
    {
      if(0 == pMChair->LcdBackLightTLMs)                        /*背光时长已经用完*/
      {
        ret = FAIL;                                             /*背光若关闭，则不执行键值处理*/
        pMChair->LcdBackLightTLMs = 60000;                      /*要开背光后，下次键值才有效*/
      }
    }
  }
  
  /*键值执行后的附加操作----------------------------------------------------*/
  else
  {
    if((SUCCESS == CurExeState) &&                               /*键值成功执行*/
       (UserRun_KeyLogicTab[Index].KeyValID != KEYVAL_NoPress))  /*有按键按下*/
    {
      pMChair->PromptToneTLMs = 300;                             /*键值成功执行，则开提示音*/
      pMChair->LcdBackLightTLMs = 60000;                         /*开背光*/
    }
  }

  return ret;
}


/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
/*
************************************************************************************************************************
* 函数名称 : SysMode_UserRun_Timer                                                                                                         
* 功能描述 : 用户运行 相关定时处理                                                                                    
* 输入参数 : ExePeriod -- 执行周期                                                                         
* 返回参数 : 无                                                               
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_UserRun_Timer(Ticker_t ExePeriod)
{
  if(TRUE == pMChair->CSFlag.Bit.TabTryRun)
  {
    return;  /*表格体验时，不执行任何定时功能，直接返回*/
  }
  
  /*=======================================================================*/
  /*系统模式：厂家考机 之 无定时测试模式, 做温升拷机用---------------------*/
  if(SYS_MODE_TESTNOTIMER == pMChair->SysModeCur)
  {
    Core_SetZMBackProtectDisableSw(ON);       /*拷机时，关闭机芯的3D退档保护功能*/
    return;                                   /*不执行任何定时功能，直接返回*/
  }

  /*=======================================================================*/
  /*系统模式：厂家考机 之 寿命， 动一小时，停15分钟------------------------*/
  else if(SYS_MODE_TESTAGE == pMChair->SysModeCur)
  {
    Core_SetZMBackProtectDisableSw(ON);       /*拷机时，关闭机芯的3D退档保护功能*/
    
    pMChair->CommonTimeSec++;

    if(pMChair->CommonTimeSec > (3600+900)) 
    {
      pMChair->CommonTimeSec = 0;             /*1h+15min 后重新计时*/
      pMChair->CSFlag.Bit.Pause = FALSE;
    }
    else if(pMChair->CommonTimeSec > 3600)
    {
      pMChair->CSFlag.Bit.Pause = TRUE;       /*1h 后，暂停15min*/
    }
    
    if(pMChair->CSFlag.Bit.LegFlexTestSw == TRUE)
    {
      pMChair->CommonTimeSec1++;
      if(pMChair->CommonTimeSec1 <= 60)               
      {
        Spike_SetLegFlexAngle(PLEGFLEX_MAX);          /*伸缩推杆缩到最长*/
      }
      else if(pMChair->CommonTimeSec1 <= 120)               
      {
        Spike_SetLegFlexAngle(PLEGFLEX_MIN);          /*伸缩推杆缩到最短*/
      } 
      else
      {
        pMChair->CommonTimeSec1 = 0;
      }      
    }
  }

  /*=======================================================================*/
  /*用户运行模式：  按摩计时-----------------------------------------------*/
  else if(SYS_MODE_USERRUN == pMChair->SysModeCur)
  {
    if((pMChair->ComponentFuncState.Bit.Core           != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.Gas            != FUNC_TYPE_NONE) ||
       //(pMChair->ComponentFuncState.Bit.Spike        != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.FeetVib        != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.CalvesVib      != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.SeatVib        != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.LumbarBackVib  != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.FeetRoller     != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.CalvesRoller   != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.FeetHeat       != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.CalvesHeat     != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.SeatHeat       != FUNC_TYPE_NONE) ||
       (pMChair->ComponentFuncState.Bit.LumbarBackHeat != FUNC_TYPE_NONE) )
       //(pMChair->ComponentFuncState.Bit.Led            != FUNC_TYPE_NONE) )
    {
      if(TRUE == pMChair->CSFlag.Bit.UserMassageTimeOut)           /*发生定时到*/
      {
        /* 定时到后，会调用MChair_FuncLogic_ClearAllFunc()先清零按摩功能，
         * 120s内按摩椅仍处于用户运行模式下，用户可操作按键重新打开按摩功能。
         * 此时，应该重新初始化定时的时间。由于开启带默认时间的功能会对UserMassageTimeMin先赋值。
         * 因此，这里判断UserMassageTimeMin为0时，即用户再次开启了不带默认时间的功能时，才对UserMassageTimeMin赋值。*/
        if(0 == pMChair->UserMassageTimeMin)
        {
          pMChair->UserMassageTimeMin = MASSAGETIME_MIN_DEFAULT;   /*按摩时间 分*/
          pMChair->UserMassageTimeSec = 0;                         /*按摩时间 秒*/
        }
        pMChair->UserMassageTimeDelayOnSec = 0;                    /*按摩定时器延时启动的秒数*/
        pMChair->CSFlag.Bit.UserMassageTimeOut = FALSE;            /*按摩定时 时间到 清零*/
      }

      pMChair->UserMassageIdleTimeSec = 0;                         /*有功能，则按摩空闲时间清零*/
      pMChair->CSFlag.Bit.UserMassageTimeRun = ON;                 /*有功能 则开始按摩计时*/
    }
    else
    {
//      if(pMChair->UserMassageIdleTimeSec < 180)
//      {
//        pMChair->UserMassageIdleTimeSec++;                         /*无按摩功能开启，累计按摩空闲时间*/
//      }
//      else
//      {
//        /*180s内没开启相关按摩功能，则以当前的推杆角度（用户可能手动调节了），自动关机*/
//        SysMode_Standby_Enter(SYS_MODE_USERRUN, FALSE);            /*关机，保持当前推杆角度*/
//      }
    }

    /*倒计时------------------------------------------------------------------*/
    if(pMChair->UserMassageTimeDelayOnSec < 10)
    {
      pMChair->UserMassageTimeDelayOnSec++;
    }

    if((OFF == pMChair->CSFlag.Bit.UserMassageTimeRun)                 || /*定时未开启，有按摩相关功能时，才开启*/
       (pMChair->UserMassageTimeDelayOnSec <= MASSAGETIME_DELAYON_SEC) || /*定时延时启动时间 未到*/
       (TRUE == pMChair->CSFlag.Bit.Pause)                             || /*系统暂停时，不计时*/
       (TRUE == pMChair->StateBodyScan.Bit.Run)                        )  /*背部扫描时，不计时*/
    {
      return; 
    }

    if(pMChair->UserMassageTimeSec > 0)
    {
      pMChair->UserMassageTimeSec--;
    }
    else
    {
      if(pMChair->UserMassageTimeMin > 0)
      {
        pMChair->UserMassageTimeSec = 59;
        pMChair->UserMassageTimeMin--;
      }
      else
      {
        pMChair->CSFlag.Bit.UserMassageTimeOut = TRUE;     /*设置定时到标识*/
        pMChair->CSFlag.Bit.UserMassageTimeRun = OFF;      /*关定时器运行*/
        MChair_FuncLogic_ClearAllFunc();                   /*清零所有按摩功能*/
        pMChair->UserMassageIdleTimeSec = 60;              /*定时到后，还有180-60=120s的等待用户继续操作的时间*/ 
        //SysMode_Standby_Enter(SYS_MODE_USERRUN, FALSE);  /*定时到后关机，保持当前推杆角度*/
        /*定时到后不关机，保持当前推杆角度*/
        Spike_SetLegFlexAngle(PLEGFLEX_MIN);               /*伸缩推杆缩到最短*/
        Spike_SetULegFlexAngle(PULEGFLEX_MAX);             /*上小腿伸到最长*/
        Spike_SetAngle(PKEEP, PKEEP, PKEEP);               /*停止推杆*/
      }
    }

    /*时间剩1分钟时，提示音10s*/
    if((0== pMChair->UserMassageTimeMin)  &&
       (pMChair->UserMassageTimeSec > 50)  && 
       (pMChair->UserMassageTimeSec <= 59))
    {
      pMChair->PromptToneTLMs = 300;                             
    }

    //    if(pMChair->UserMassageTimeSec < 60)
//    {
//      pMChair->UserMassageTimeSec++;
//    }
//    else
//    {
//      if(pMChair->UserMassageTimeMin > 1)
//      {
//        pMChair->UserMassageTimeSec = 0;
//        pMChair->UserMassageTimeMin--;
//      }
//      else
//      {
//        pMChair->UserMassageTimeMin = 0;                   /*定时到，时间清零*/
//        pMChair->CSFlag.Bit.UserMassageTimeOut = TRUE;     /*设置定时到标识*/
//        pMChair->CSFlag.Bit.UserMassageTimeRun = OFF;      /*关定时器运行*/
//        MChair_FuncLogic_ClearAllFunc();                   /*清零所有按摩功能*/

//        pMChair->UserMassageIdleTimeSec = 60;              /*定时到后，还有180-60=120s的等待用户继续操作的时间*/ 
//        //SysMode_Standby_Enter(SYS_MODE_USERRUN, FALSE);  /*定时到后关机，保持当前推杆角度*/
//      }
//    }

//    /*时间剩1分钟时，提示音10s*/
//    if((1== pMChair->UserMassageTimeMin)  &&
//       (pMChair->UserMassageTimeSec > 0)  && 
//       (pMChair->UserMassageTimeSec <= 10))
//    {
//      pMChair->PromptToneTLMs = 300;                             
//    }
  }
}

/*
************************************************************************************************************************
* 函数名称 : SysMode_UserRun_Init                                                                                                         
* 功能描述 : 系统模式 之 用户运行 初始化                                                                                    
* 输入参数 : 无                                                                                 
* 返回参数 : 无                                                                 
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_UserRun_Init(void)
{
  uint8_t i;


  /*检测键值表格排列是否正确------------------------------*/
  for(i=1; i<USERRUN_KEY_TAB_NUM; i++)
  {
    if(UserRun_KeyLogicTab[i].KeyValID <= UserRun_KeyLogicTab[i-1].KeyValID)
    {
      while(1);  /*请将KeyValID 从小到大，无重复排列使用*/
    }   
  }
}

/*
************************************************************************************************************************
* 函数名称 : SysMode_UserRun_Handle                                                                                                         
* 功能描述 : 系统模式 之 用户运行处理                                                                                    
* 输入参数 : 无                                                                            
* 返回参数 : 无                                                             
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_UserRun_Handle(void)
{
  /*发生模式切换操作-----------------------------------------------------*/
  if(pMChair->SysModeHis != pMChair->SysModeCur)
  {
    pMChair->SysModeHis = pMChair->SysModeCur; 
    pMChair->CSFlag.Bit.Pause = FALSE;                          
  }

  /*根据各个模式的不同，对键值处理相关变量赋值---------------------------*/
  pMChair->KeyValHandle.KeyLogicTab    = UserRun_KeyLogicTab;      /*按键逻辑表*/
  pMChair->KeyValHandle.KeyLogicTabNum = USERRUN_KEY_TAB_NUM;      /*按键逻辑表 大小*/
  pMChair->KeyValHandle.pGetMatchID    = UserRun_GetKeyValID;      /*函数指针，指向的函数作用：返回表格条目 中 的要搜索的数据 所在的索引*/
  pMChair->KeyValHandle.pAddOp         = UserRun_KeyValAdditonOp;  /*函数指针，指向的函数作用：键值执行前后的附加操作 */
}

/*
************************************************************************************************************************
* 函数名称 : SysMode_UserRun_Enter                                                                                                         
* 功能描述 : 系统模式 之 用户运行 进入                                                                                    
* 输入参数 : 无                                                                            
* 返回参数 : SUCCESS -- 进入成功     FAIL -- 进入失败                                                               
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t SysMode_UserRun_Enter(void)
{
  if(TRUE == pMChair->CSFlag.Bit.OccurNoStartUpFault)    
  {
    pMChair->ERPPowerSw = ON;                                            /*开启主电源，让类平板可显示故障码*/
    pMChair->ERPPowerOffWaitTimeMs = 0;
    return FAIL;                                                         /*发生不允许启动的故障*/
  }

  if((FALSE == pMChair->StateXMotor.Bit.PositionResetOK) ||
     (FALSE == pMChair->StateYMotor.Bit.PositionResetOK) ||
     (FALSE == pMChair->StateZMotor.Bit.PositionResetOK) )
  {
    return FAIL;                                                         /*机芯位置还未复位*/
  }
  
  if(Core_GetYPosition() != PY_MIN)
  {
    return FAIL;                                                         /*机芯不处于顶端*/
  }

  if((FALSE == pMChair->StateBackSpike.Bit.PositionResetOK)   ||
     //(FALSE == pMChair->StateZeroSpike.Bit.PositionResetOK)    ||
     (FALSE == pMChair->StateFeetSpike.Bit.PositionResetOK)   ||
     (FALSE == pMChair->StateLegFlexSpike.Bit.PositionResetOK)) 
  {
    return FAIL;                                                         /*推杆位置还未复位*/
  }

  if(pMChair->SysModeCur != SYS_MODE_STANDBY)                      
  {
    return FAIL;                                                         /*只能从待机模式进入用户运行模式*/
  }

  pMChair->CSFlag.Bit.MChairReported = TRUE;                             /*开机上报*/  
  /*待机时，可能还会有部分功能可开启，比如推杆功能。因此开机前 清零所有按摩功能*/
  MChair_FuncLogic_ClearAllFunc();  
  
  Spike_SetAngle(PBACK_USER_ANGLE, PFEET_USER_ANGLE, PZERO_USER_ANGLE);  /*开机角度*/

  pMChair->FuncMA_Led.Bit.Logo = FMA_LOGO_LED_Mannual;                   /*开机就打开Logo灯光*/
  pMChair->FuncMA_Led.Bit.Projection = FMA_PROJECTION_LED_Mannual;       /*开机就打开投影灯光*/

  pMChair->SysModeCur    = SYS_MODE_USERRUN;                             /*进入用户运行模式*/
  pMChair->SysModeHis    = SYS_MODE_STANDBY;                             /*只能从待机模式进入*/
  pMChair->SysModeVender = SYS_MODE_NONE;                                /*无厂家模式*/

  pMChair->LcdBackLightTLMs = 60000;                                     /*开背光*/

  return SUCCESS;
}
