/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: SysMode_StandBy.c 
**
**    功能描述: 系统模式 之  待机
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
static Ticker_t  EngiModeSelcetTL;    /*工程模式选择时间长度*/

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
* 函数名称 : SysMode_StandBy_EngineeringModeSelcetTLHandle                                                                                                         
* 功能描述 : 工程模式选择时间长度处理                                                                                   
* 输入参数 : ExePeriod -- 函数执行周期                                                                                       
* 返回参数 : 无                                                                
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_StandBy_EngiModeSelcetTLHandle(Ticker_t ExePeriod)
{
  if(pMChair->SysModeCur != SYS_MODE_STANDBY)
  {
    EngiModeSelcetTL = 0;
    return;
  }
  
  if(EngiModeSelcetTL > ExePeriod)
  {
    EngiModeSelcetTL -= ExePeriod;
  }
  else
  {
    EngiModeSelcetTL = 0;
  }
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_NoKeyPress                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                 
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_NoKeyPress(uint8_t *pData)
{
  /*长按按键的释放处理------------------------------*/
  Core_SetMoveAdjustRoll(CORE_MOVE_ADJUST_NONE);                    /*机芯上下调节 的长按释放*/

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)                       /*推杆为长按*/
    pMChair->FuncMannual_Spike.Bit.BackMove     = SPIKE_MOVE_NONE;  /*零重力推杆 的长按释放*/
    pMChair->FuncMannual_Spike.Bit.BackMove     = SPIKE_MOVE_NONE;  /*靠背推杆 的长按释放*/
    pMChair->FuncMannual_Spike.Bit.FeetMove     = SPIKE_MOVE_NONE;  /*小腿推杆 的长按释放*/
    pMChair->FuncMannual_Spike.Bit.LegFlexMove  = SPIKE_MOVE_NONE;  /*小腿伸缩推杆 的长按释放*/
    pMChair->FuncMannual_Spike.Bit.ULegFlexMove = SPIKE_MOVE_NONE;  /*上小腿伸缩推杆 的长按释放*/
  #endif

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_Power                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                 
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_Power(uint8_t *pData)
{
  return SysMode_UserRun_Enter();
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_Pause                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_Pause(uint8_t *pData)
{
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
* 函数名称 : StandBy_Key_SpikeBackUp                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                 
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeBackUp(uint8_t *pData)
{
  if((TRUE  == pMChair->StateBackSpike.Bit.ReachUpLimt)         ||
     (FALSE == pMChair->StateBackSpike.Bit.PositionResetOK)     ||
     (TRUE  == pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable) )
  {
    return FAIL;
  }

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*推杆为长按*/
    if(SPIKE_MOVE_BACK_UP == pMChair->FuncMannual_Spike.Bit.BackMove)
    {
      return FAIL; /*该动作已经在执行了，没必要再次赋值*/
    }
    pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
    pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_BACK_UP;
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*推杆为短按*/
    if((pMChair->FuncMannual_Spike.Bit.BackMove != SPIKE_MOVE_NONE) ||
       (pMChair->FuncMannual_Spike.Bit.FeetMove != SPIKE_MOVE_NONE) )
    {
      pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;
      pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_BACK_UP;
    }
  #endif

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_SpikeBackDown                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                 
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeBackDown(uint8_t *pData)
{
  if((TRUE  == pMChair->StateBackSpike.Bit.ReachDownLimt)       ||
     (FALSE == pMChair->StateBackSpike.Bit.PositionResetOK)     ||
     (TRUE  == pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable) )
  {
    return FAIL;
  }

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*推杆为长按*/
    if(SPIKE_MOVE_BACK_DOWN == pMChair->FuncMannual_Spike.Bit.BackMove)
    {
      return FAIL; /*该动作已经在执行了，没必要再次赋值*/
    }
    pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
    pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_BACK_DOWN;
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*推杆为短按*/
    if((pMChair->FuncMannual_Spike.Bit.BackMove != SPIKE_MOVE_NONE) ||
       (pMChair->FuncMannual_Spike.Bit.FeetMove != SPIKE_MOVE_NONE) )
    {
      pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;
      pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_BACK_DOWN;
    }
  #endif  
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_SpikeFeetUp                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                 
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeFeetUp(uint8_t *pData)
{
  if((TRUE  == pMChair->StateFeetSpike.Bit.ReachUpLimt)         ||
     (FALSE == pMChair->StateFeetSpike.Bit.PositionResetOK)     ||
     (TRUE  == pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable) )
  {
    return FAIL;
  }

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*推杆为长按*/
    if(SPIKE_MOVE_FEET_UP == pMChair->FuncMannual_Spike.Bit.FeetMove)
    {
      return FAIL; /*该动作已经在执行了，没必要再次赋值*/
    }
    pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;
    pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_FEET_UP;
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*推杆为短按*/
    if((pMChair->FuncMannual_Spike.Bit.BackMove != SPIKE_MOVE_NONE) ||
       (pMChair->FuncMannual_Spike.Bit.FeetMove != SPIKE_MOVE_NONE) )
    {
      pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;
      pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_FEET_UP;
    }
  #endif  
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_SpikeFeetDown                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                 
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeFeetDown(uint8_t *pData)
{
  if((TRUE  == pMChair->StateFeetSpike.Bit.ReachDownLimt)       ||
     (FALSE == pMChair->StateFeetSpike.Bit.PositionResetOK)     ||
     (TRUE  == pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable) )
  {
    return FAIL;
  }

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*推杆为长按*/
    if(SPIKE_MOVE_FEET_DOWN == pMChair->FuncMannual_Spike.Bit.FeetMove)
    {
      return FAIL; /*该动作已经在执行了，没必要再次赋值*/
    }
    pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;
    pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_FEET_DOWN;
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*推杆为短按*/
    if((pMChair->FuncMannual_Spike.Bit.BackMove != SPIKE_MOVE_NONE) ||
       (pMChair->FuncMannual_Spike.Bit.FeetMove != SPIKE_MOVE_NONE) )
    {
      pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;
      pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_FEET_DOWN;
    }
  #endif  

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_SpikeBackUpFeetDown                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                 
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeBackUpFeetDown(uint8_t *pData)
{
  if((FALSE == pMChair->StateBackSpike.Bit.PositionResetOK) ||
     (FALSE == pMChair->StateFeetSpike.Bit.PositionResetOK) )
  {
    return FAIL;
  }

  if((TRUE == pMChair->StateBackSpike.Bit.ReachUpLimt)   &&
     (TRUE == pMChair->StateFeetSpike.Bit.ReachDownLimt) )
  {
    return FAIL;
  }
  
  if((TRUE == pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable) &&
     (TRUE == pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable) )
  {
    return FAIL; 
  }

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*推杆为长按*/
    if((SPIKE_MOVE_BACK_UP   == pMChair->FuncMannual_Spike.Bit.BackMove) && 
       (SPIKE_MOVE_FEET_DOWN == pMChair->FuncMannual_Spike.Bit.FeetMove) ) 
    {
      return FAIL; /*该动作已经在执行了，没必要再次赋值*/
    }
    if(FALSE == pMChair->StateBackSpike.Bit.ReachUpLimt) 
    {
      pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_BACK_UP;
    }
    if(FALSE == pMChair->StateFeetSpike.Bit.ReachDownLimt) 
    {
      pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_FEET_DOWN;
    }
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*推杆为短按*/
    if((pMChair->FuncMannual_Spike.Bit.BackMove != SPIKE_MOVE_NONE) ||
       (pMChair->FuncMannual_Spike.Bit.FeetMove != SPIKE_MOVE_NONE) )
    {
      pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;
      pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_BACK_UP;
      pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_FEET_DOWN;
    }
  #endif  
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_SpikeBackDownFeetUp                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                 
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeBackDownFeetUp(uint8_t *pData)
{
  if((FALSE == pMChair->StateBackSpike.Bit.PositionResetOK) ||
     (FALSE == pMChair->StateFeetSpike.Bit.PositionResetOK) )
  {
    return FAIL;
  }

  if((TRUE == pMChair->StateBackSpike.Bit.ReachDownLimt) &&
     (TRUE == pMChair->StateFeetSpike.Bit.ReachUpLimt)   )
  {
    return FAIL;
  }

  if((TRUE == pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable) &&
     (TRUE == pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable) )
  {
    return FAIL; 
  }

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*推杆为长按*/
    if((SPIKE_MOVE_BACK_DOWN == pMChair->FuncMannual_Spike.Bit.BackMove) && 
       (SPIKE_MOVE_FEET_UP   == pMChair->FuncMannual_Spike.Bit.FeetMove) ) 
    {
      return FAIL; /*该动作已经在执行了，没必要再次赋值*/
    }
    if(FALSE == pMChair->StateBackSpike.Bit.ReachDownLimt)   
    {
      pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_BACK_DOWN;
    }
    if(FALSE == pMChair->StateFeetSpike.Bit.ReachUpLimt)       
    {
      pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_FEET_UP;
    }
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*推杆为短按*/
    if((pMChair->FuncMannual_Spike.Bit.BackMove != SPIKE_MOVE_NONE) ||
       (pMChair->FuncMannual_Spike.Bit.FeetMove != SPIKE_MOVE_NONE) )
    {
      pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;
      pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_BACK_DOWN;
      pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_FEET_UP;
    }
  #endif  
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_SpikeLegExtend                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeLegExtend(uint8_t *pData)
{
  if((FALSE == pMChair->StateLegFlexSpike.Bit.PositionResetOK)  ||
     (TRUE  == pMChair->CSFlag.Bit.LegFlexMannualMoveDisable)   ||
     (TRUE  == pMChair->StateLegFlexSpike.Bit.ReachExtendLimt)  ||
     (TRUE  == pMChair->StateLegFlexSpike.Bit.TouchGround)      )
  {
    return FAIL;
  }

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*推杆为长按*/
    if(SPIKE_MOVE_LEG_EXTEND == pMChair->FuncMannual_Spike.Bit.LegFlexMove)
    {
      return FAIL; /*该动作已经在执行了，没必要再次赋值*/
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_LEG_EXTEND;
    }  
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*推杆为短按*/
    if(pMChair->FuncMannual_Spike.Bit.LegFlexMove != SPIKE_MOVE_NONE)
    {
      pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_NONE;
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_LEG_EXTEND;
    }  
  #endif  
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_SpikeLegShorten                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeLegShorten(uint8_t *pData)
{
  if((FALSE == pMChair->StateLegFlexSpike.Bit.PositionResetOK) ||
     (TRUE  == pMChair->CSFlag.Bit.LegFlexMannualMoveDisable)   ||
     (TRUE  == pMChair->StateLegFlexSpike.Bit.ReachShortenLimt) ||
     (TRUE  == pMChair->StateLegFlexSpike.Bit.TouchFeet)        )
  {
    return FAIL;
  }

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*推杆为长按*/
    if(SPIKE_MOVE_LEG_SHORT == pMChair->FuncMannual_Spike.Bit.LegFlexMove)
    {
      return FAIL; /*该动作已经在执行了，没必要再次赋值*/
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_LEG_SHORT;
    }  
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*推杆为短按*/
    if(pMChair->FuncMannual_Spike.Bit.LegFlexMove != SPIKE_MOVE_NONE)
    {
      pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_NONE;
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_LEG_SHORT;
    }
  #endif  
  
  return SUCCESS;
}


/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_SpikeULegExtend                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeULegExtend(uint8_t *pData)
{
  if((FALSE == pMChair->StateLegFlexSpike.Bit.ULegPositionResetOK) ||
     (TRUE  == pMChair->CSFlag.Bit.ULegFlexMannualMoveDisable)     ||
     (TRUE  == pMChair->StateLegFlexSpike.Bit.ULegReachExtendLimt) )
  {
    return FAIL;
  }

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*推杆为长按*/
    if(SPIKE_MOVE_LEG_EXTEND == pMChair->FuncMannual_Spike.Bit.ULegFlexMove)
    {
      return FAIL; /*该动作已经在执行了，没必要再次赋值*/
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.ULegFlexMove = SPIKE_MOVE_LEG_EXTEND;
    }  
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*推杆为短按*/
    if(pMChair->FuncMannual_Spike.Bit.ULegFlexMove != SPIKE_MOVE_NONE)
    {
      pMChair->FuncMannual_Spike.Bit.ULegFlexMove = SPIKE_MOVE_NONE;
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.ULegFlexMove = SPIKE_MOVE_LEG_EXTEND;
    }  
  #endif  
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_SpikeULegShorten                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeULegShorten(uint8_t *pData)
{
  if((FALSE == pMChair->StateLegFlexSpike.Bit.ULegPositionResetOK) ||
     (TRUE  == pMChair->CSFlag.Bit.ULegFlexMannualMoveDisable)     ||
     (TRUE  == pMChair->StateLegFlexSpike.Bit.ULegReachShortenLimt))
  {
    return FAIL;
  }

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*推杆为长按*/
    if(SPIKE_MOVE_LEG_SHORT == pMChair->FuncMannual_Spike.Bit.ULegFlexMove)
    {
      return FAIL; /*该动作已经在执行了，没必要再次赋值*/
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.ULegFlexMove = SPIKE_MOVE_LEG_SHORT;
    }  
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*推杆为短按*/
    if(pMChair->FuncMannual_Spike.Bit.ULegFlexMove != SPIKE_MOVE_NONE)
    {
      pMChair->FuncMannual_Spike.Bit.ULegFlexMove = SPIKE_MOVE_NONE;
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.ULegFlexMove = SPIKE_MOVE_LEG_SHORT;
    }
  #endif  
  
  return SUCCESS;
}
/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_SpikeZeroGravity1                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeZeroGravity1(uint8_t *pData)
{
  if(TRUE == pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable)
  {
    return FAIL; 
  }
  
  if((FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Spike) && 
     (FALSE == pMChair->CSFlag.Bit.ZeroGravityAngleRun)        ) /*没在调节零重力*/
  {
    return FAIL; /*推杆工作在自动程序中（零重力调节的自动程序除外），则零重力调节无效*/
  }

  pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;/*停掉所有推杆的运动*/
  pMChair->FuncMannual_Spike.Bit.ZeroMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_NONE;

  /*逻辑顺序：零重力1-->无， 键值执行时先判段是否处于零重力1的角度值*/
//  if((PBACK_ZERO1_ANGLE == Spike_GetBackAngle()) && (PFEET_ZERO1_ANGLE == Spike_GetFeetAngle()))
//  {
//    pMChair->FuncAuto_Spike = FA_SPIKE_ZeroGravity1;
//  }
  if((PBACK_ZERO1_ANGLE == Spike_GetBackAngle()) && (FALSE == pMChair->StateBackSpike.Bit.Work) &&
     (PFEET_ZERO1_ANGLE == Spike_GetFeetAngle()) && (FALSE == pMChair->StateFeetSpike.Bit.Work) )
  {
    MChair_SetFuncAutoSpike(FA_SPIKE_NONE, TRUE);
    return SUCCESS;
  }

  if(pMChair->FuncAuto_Spike != FA_SPIKE_NONE)
  {
    MChair_SetFuncAutoSpike(FA_SPIKE_NONE, TRUE);
  }
  else
  {
    MChair_SetFuncAutoSpike(FA_SPIKE_ZeroGravity1, FALSE);
  }
  
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_SpikeZeroGravity2                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeZeroGravity2(uint8_t *pData)
{
  if(TRUE == pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable)
  {
    return FAIL; 
  }
  
  if((FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Spike) && 
     (FALSE == pMChair->CSFlag.Bit.ZeroGravityAngleRun)        ) /*没在调节零重力*/
  {
    return FAIL; /*推杆工作在自动程序中（零重力调节的自动程序除外），则零重力调节无效*/
  }

  pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;/*停掉所有推杆的运动*/
  pMChair->FuncMannual_Spike.Bit.ZeroMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_NONE;

  /*逻辑顺序：零重力2-->无， 键值执行时先判段是否处于零重力2的角度值*/
//  if((PBACK_ZERO2_ANGLE == Spike_GetBackAngle()) && (PFEET_ZERO2_ANGLE == Spike_GetFeetAngle()))
//  {
//    pMChair->FuncAuto_Spike = FA_SPIKE_ZeroGravity2;
//  }
  if((PBACK_ZERO2_ANGLE == Spike_GetBackAngle()) && (FALSE == pMChair->StateBackSpike.Bit.Work) &&
     (PFEET_ZERO2_ANGLE == Spike_GetFeetAngle()) && (FALSE == pMChair->StateFeetSpike.Bit.Work) )
  {
    MChair_SetFuncAutoSpike(FA_SPIKE_NONE, TRUE);
    return SUCCESS;
  }
  
  if(pMChair->FuncAuto_Spike != FA_SPIKE_NONE)
  {
    MChair_SetFuncAutoSpike(FA_SPIKE_NONE, TRUE);
  }
  else
  {
    MChair_SetFuncAutoSpike(FA_SPIKE_ZeroGravity2, FALSE);
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_SpikeZeroGravity                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeZeroGravity(uint8_t *pData)
{
  if(TRUE == pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable)
  {
    return FAIL; 
  }

  if((FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Spike) && 
     (FALSE == pMChair->CSFlag.Bit.ZeroGravityAngleRun)        ) /*没在调节零重力*/
  {
    return FAIL; /*推杆工作在自动程序中（零重力调节的自动程序除外），则零重力调节无效*/
  }

  pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;/*停掉所有推杆的运动*/
  pMChair->FuncMannual_Spike.Bit.ZeroMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_NONE;

  /*逻辑顺序：零重力2-->零重力1， 键值执行时先判段是否处于零重力2的角度值*/
  if((PBACK_ZERO2_ANGLE == Spike_GetBackAngle()) && (FALSE == pMChair->StateBackSpike.Bit.Work) &&
     (PFEET_ZERO2_ANGLE == Spike_GetFeetAngle()) && (FALSE == pMChair->StateFeetSpike.Bit.Work) )
  {
    pMChair->FuncAuto_Spike = FA_SPIKE_ZeroGravity2;
  }


  if(FA_SPIKE_ZeroGravity2 == pMChair->FuncAuto_Spike)
  {
    MChair_SetFuncAutoSpike(FA_SPIKE_ZeroGravity1, FALSE);
  }
  else if(FA_SPIKE_ZeroGravity1 == pMChair->FuncAuto_Spike)
  {
    MChair_SetFuncAutoSpike(FA_SPIKE_ZeroGravity2, FALSE);
  } 
  else
  {
    MChair_SetFuncAutoSpike(FA_SPIKE_ZeroGravity2, FALSE);
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_SpikeHomeReset                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeHomeReset(uint8_t *pData)
{
  if(TRUE == pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable)
  {
    return FAIL; 
  }
  
  if((FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Spike) && 
     (FALSE == pMChair->CSFlag.Bit.ZeroGravityAngleRun)        ) /*没在调节零重力*/
  {
    return FAIL; /*推杆工作在自动程序中（零重力调节的自动程序除外），则零重力调节无效*/
  }

  pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;/*停掉所有推杆的运动*/
  pMChair->FuncMannual_Spike.Bit.ZeroMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_NONE;

  /*逻辑顺序：复位角度-->无， 键值执行时先判段是否处于复位角度*/
  if((PBACK_HOME_ANGLE == Spike_GetBackAngle()) && (FALSE == pMChair->StateBackSpike.Bit.Work) &&
     (PFEET_HOME_ANGLE == Spike_GetFeetAngle()) && (FALSE == pMChair->StateFeetSpike.Bit.Work) )
  {
    MChair_SetFuncAutoSpike(FA_SPIKE_NONE, TRUE);
    return SUCCESS;
  }
  
  if(pMChair->FuncAuto_Spike == FA_SPIKE_Home)
  {
    MChair_SetFuncAutoSpike(FA_SPIKE_NONE, TRUE);
  }
  else
  {
    MChair_SetFuncAutoSpike(FA_SPIKE_Home, FALSE);
  }

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_EnterSysModeVender                                                                                                         
* 功能描述 : 进入厂家模                                                                                    
* 输入参数 : pData         -- 键值所附带的命令数据 
*            SysModeVender -- 要进入的厂家模式
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_EnterSysModeVender(uint8_t *pData, uint8_t SysModeVender)
{
  if((0 == EngiModeSelcetTL)   ||                /*选择可用时间无效*/
     (EngiModeSelcetTL > 24000))                 /*防止组合键释放时的抖动*/
  {
    return FAIL;
  }

  pMChair->SysModeCur    = SysModeVender;    /*进入相应的厂家模式*/
  pMChair->SysModeHis    = SYS_MODE_STANDBY;  
  pMChair->SysModeVender = SYS_MODE_NONE;       
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_InspectAuto                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_InspectAuto(uint8_t *pData)
{
  return StandBy_EnterSysModeVender(pData, SYS_MODE_INSPECTAUTO);
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_InspectManual                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_InspectManual(uint8_t *pData)
{
  return StandBy_EnterSysModeVender(pData, SYS_MODE_INSPECTMANUAL);
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_PackingAngle                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_PackingAngle(uint8_t *pData)
{
  return StandBy_EnterSysModeVender(pData, SYS_MODE_PACKING);
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_TestNoTimer                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_TestNoTimer(uint8_t *pData)
{
  return StandBy_EnterSysModeVender(pData, SYS_MODE_TESTNOTIMER);
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_TestAge                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_TestAge(uint8_t *pData)
{
  return StandBy_EnterSysModeVender(pData, SYS_MODE_TESTAGE);
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_TestSpike                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_TestSpike(uint8_t *pData)
{
  return StandBy_EnterSysModeVender(pData, SYS_MODE_TESTSPIKE);
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_TestOther1                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_TestOther1(uint8_t *pData)
{
  return StandBy_EnterSysModeVender(pData, SYS_MODE_TESTOTHER1);
}

/*
************************************************************************************************************************
* 函数名称 : StandBy_Key_EngiModeSelect                                                                                                         
* 功能描述 :                                                                                     
* 输入参数 : pData -- 键值所附带的命令数据                                                                                  
* 返回参数 : SUCCESS -- 键值执行成功     FAIL -- 键值执行失败                                                                  
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_EngiModeSelect(uint8_t *pData)
{
  EngiModeSelcetTL = 25000;    /*工程模式选择 可用时间*/
  return SUCCESS;
}

/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/

static const SysMode_KeyLogicTabItem_t StandBy_KeyLogicTab[] = /*键值表*/
{
  /*附加操作：

    键值执行前：bit7 -- 1：ERP主电源关闭，则键值执行前，要重新开启。    
                        0：ERP主电源关闭，则键值执行前，不需要重新开启。    
    键值执行前：bit6 -- 1：暂停开启，仍可执行键值。  
                        0：暂停开启，则键值不执行。
    键值执行后：                                                   */

  {KEYVAL_NoPress,                  B(01000000),    StandBy_Key_NoKeyPress},
  {KEYVAL_Power,                    B(01000000),    StandBy_Key_Power},
  {KEYVAL_Pause,                    B(01000000),    StandBy_Key_Pause},
//  {KEYVAL_SpikeBackUp,              B(10000000),    StandBy_Key_SpikeBackUp},
//  {KEYVAL_SpikeBackDown,            B(10000000),    StandBy_Key_SpikeBackDown},
  {KEYVAL_SpikeFeetUp,              B(10000000),    StandBy_Key_SpikeFeetUp},
  {KEYVAL_SpikeFeetDown,            B(10000000),    StandBy_Key_SpikeFeetDown},
  {KEYVAL_SpikeBackUpFeetDown,      B(10000000),    StandBy_Key_SpikeBackUpFeetDown},
  {KEYVAL_SpikeBackDownFeetUp,      B(10000000),    StandBy_Key_SpikeBackDownFeetUp},
//  {KEYVAL_SpikeLegExtend,           B(10000000),    StandBy_Key_SpikeLegExtend},
//  {KEYVAL_SpikeLegShorten,          B(10000000),    StandBy_Key_SpikeLegShorten},
  {KEYVAL_SpikeZeroGravity1,        B(10000000),    StandBy_Key_SpikeZeroGravity1},
  {KEYVAL_SpikeZeroGravity,         B(10000000),    StandBy_Key_SpikeZeroGravity2},
  {KEYVAL_SpikeHomeReset,           B(10000000),    StandBy_Key_SpikeBackUpFeetDown},

  /*厂家模式的切换------------------------------------------------------------------*/
  {KEYVAL_InspectAuto,              B(00000000),    StandBy_Key_InspectAuto},           /*系统模式：厂家自检*/
  {KEYVAL_InspectManual,            B(00000000),    StandBy_Key_InspectManual},         /*系统模式：厂家手检*/
  {KEYVAL_PackingAngle,             B(00000000),    StandBy_Key_PackingAngle},          /*系统模式：厂家包装*/
  {KEYVAL_TestNoTimer,              B(00000000),    StandBy_Key_TestNoTimer},           /*系统模式：厂家考机 之 无定时测试模式*/
  {KEYVAL_TestSpike,                B(00000000),    StandBy_Key_TestSpike},             /*系统模式：厂家考机 之 推杆*/
  {KEYVAL_TestAge,                  B(00000000),    StandBy_Key_TestAge},               /*系统模式：厂家考机 之 寿命 动一小时，停15分钟*/
  {KEYVAL_TestOther1,               B(00000000),    StandBy_Key_TestOther1},            /*系统模式：其他厂家考机1*/
  {KEYVAL_EngiModeSelect,           B(00000000),    StandBy_Key_EngiModeSelect},        /*工程模式选择*/
  /*---------------------------------------------------*/
  {KEYVAL_MAX,                      B(00000000),    NULL}
};

#define STANDBY_KEY_TAB_NUM  TAB_NUM(StandBy_KeyLogicTab)

static uint16_t StandBy_GetKeyValID(uint16_t index)
{
  if(index > (STANDBY_KEY_TAB_NUM-1))
  {
    return INDEX_NO_MATCH;
  }
  return StandBy_KeyLogicTab[index].KeyValID;
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
uint8_t Standby_KeyValAdditonOp(uint8_t Index, uint8_t BeforeAfter, uint8_t CurExeState)
{
  uint8_t ret;

  
  ret = SUCCESS;                                                /*先假设成功*/

  /*键值执行前的附加操作---------------------------------------------------*/
  if(BEFORE == BeforeAfter)                    
  {
    /*键值执行前：bit7 -- 1：ERP主电源关闭，则键值执行前，要重新开启。    
                          0：ERP主电源关闭，则键值执行前，不需要重新开启。 */   
    if(StandBy_KeyLogicTab[Index].AdditonOp & B(10000000))
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
    if(0 == (StandBy_KeyLogicTab[Index].AdditonOp & B(01000000))) 
    {
      if(TRUE == pMChair->CSFlag.Bit.Pause)
      {
        ret = FAIL;                                             /*暂停开启，则不执行键值处理*/
      }
    }
  }
  
  /*键值执行后的附加操作---------------------------------------------------*/
  else 
  {
    if((SUCCESS == CurExeState) &&                               /*键值成功执行*/
       (StandBy_KeyLogicTab[Index].KeyValID != KEYVAL_NoPress))  /*有按键按下*/
    {
      pMChair->PromptToneTLMs = 300;                             /*键值成功执行，则开提示音*/
    }
  }

  return ret;
}


/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
/*
************************************************************************************************************************
* 函数名称 : SysMode_Standby_Init                                                                                                         
* 功能描述 : 系统模式 之 待机 初始化                                                                                    
* 输入参数 : 无                                                                               
* 返回参数 : 无                                                          
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_Standby_Init(void)
{
  uint8_t i;

  /*检测键值表格排列是否正确------------------------------*/
  for(i=1; i<STANDBY_KEY_TAB_NUM; i++)
  {
    if(StandBy_KeyLogicTab[i].KeyValID <= StandBy_KeyLogicTab[i-1].KeyValID)
    {
      while(1);  /*请将KeyValID 从小到大，无重复排列使用*/
    }   
  }
}

/*
************************************************************************************************************************
* 函数名称 : SysMode_Standby_Handle                                                                                                         
* 功能描述 : 系统模式 之 待机处理                                                                                    
* 输入参数 : 无                                                                               
* 返回参数 : 无                                                          
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void SysMode_Standby_Handle(void)
{
  /*发生模式切换操作-----------------------------------------------------*/
  if(pMChair->SysModeHis != pMChair->SysModeCur)      
  {
    BackSpike_SetCountFaultCheckSw(OFF);                                 /*关机后，关闭推杆的计数故障检测开关*/
    FeetSpike_SetCountFaultCheckSw(OFF);
    ZeroSpike_SetCountFaultCheckSw(OFF);
    
    Core_ShoulderAdjustRe();                                             /*关机后清除肩部检测完成标志位*/
    Core_SetZMBackProtectDisableSw(OFF);                                 /*关机后，开启机芯的3D退档保护功能*/

    memset(&pMChair->VenderInspect, 0, sizeof(pMChair->VenderInspect));  /*清零 厂家检测相关数据*/
 
    pMChair->CSFlag.Bit.SysRun                      = FALSE;
    pMChair->CSFlag.Bit.Pause                       = FALSE;
    pMChair->CSFlag.Bit.ZeroGravityAngleRun         = FALSE;
    pMChair->CSFlag.Bit.BackSpikeMannualMoveDisable = FALSE;
    pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable = FALSE;
    pMChair->CSFlag.Bit.FeetSpikeMannualMoveDisable = FALSE;
    pMChair->CSFlag.Bit.LegFlexMannualMoveDisable   = FALSE;
    pMChair->CSFlag.Bit.ULegFlexMannualMoveDisable  = FALSE;
    pMChair->CSFlag.Bit.GasCooperateSpikeRun        = FALSE;
    //pMChair->CSFlag.Bit.PromptToneRun               = OFF;
    //pMChair->CSFlag.Bit.KeyValExeResult             = FAIL;
    pMChair->CSFlag.Bit.IDCodeOpRun                 = OFF;
    //pMChair->CSFlag.Bit.OccurNoStartUpFault       = 0;                 /*★发生不允许启动的故障，该标识不清除，值保持★*/
    pMChair->CSFlag.Bit.UserSpikeAngleSetd          = FALSE;
    pMChair->CSFlag.Bit.VenderOpFinish              = FALSE;
    pMChair->CSFlag.Bit.LegFlexTestSw               = FALSE;


    pMChair->PromptToneAddr = SYS_PROMPT_TONE_ADDR_DEFAULT;              /*系统默认提示音地址*/

    pMChair->CSFlag.Bit.UserMassageTimeOut = FALSE;                      /*用户按摩定时器 时间到 清零*/
    pMChair->CSFlag.Bit.UserMassageTimeRun = OFF;                        /*用户按摩定时器 运行 关*/
    pMChair->UserMassageTimeMin            = MASSAGETIME_MIN_DEFAULT;    /*用户按摩时间 分*/
    pMChair->UserMassageTimeSec            = 0;                          /*用户按摩时间 秒*/
    pMChair->UserMassageTimeDelayOnSec     = 0;                          /*用户按摩定时器 延时启动的秒数*/
    pMChair->UserMassageIdleTimeSec        = 0;                          /*用户按摩空闲时间 清零*/

    pMChair->ERPPowerSw = ON;                                            /*进入新模式，先开启ERP电源*/

    pMChair->CommonStep     = 0;                                         /*各个模式根据需要都可使用的步骤*/
    pMChair->CommonTimeSec  = 0;                                         /*各个系统模式根据需要都可使用的时间，单位秒*/
    pMChair->CommonTimeSec1 = 0;                                         /*各个系统模式根据需要都可使用的时间，单位秒*/

    BodyScan_Init();                                                     /*每次待机，都应重新初始化 人体扫描*/              
    MChair_FuncLogic_ClearAllFunc();                                     /*清零 所有按摩功能*/
                   
    pMChair->AutoCoreFlexLevelAdjust   = CORE_AUTO_PZLEVEL_REF;          /*自动程序下  机芯伸缩度 调节值*/
    pMChair->GasIntensity              = 3;                              /*充气强度*/
    pMChair->MannualCoreXYZActionSpeed = 3;                              /*手动程序下  XYZ动作手法速度*/
    pMChair->MannualCoreTCSActionSpeed = 3;                              /*手动程序下  TCS动作手法速度*/
    pMChair->MannualCoreWidth          = 2;                              /*手动程序下  机芯宽度*/
    pMChair->MannualCoreFlexLevel      = 2;                              /*手动程序下  机芯伸缩度*/

    /*系统模式相关变量设置*/
    pMChair->SysModeHis = pMChair->SysModeCur; 
    pMChair->CSFlag.Bit.Pause = FALSE;                                   /*非 暂停*/

    if(pMChair->SysModeVender != SYS_MODE_NONE)                          /*用户在开机状态下，触发了厂家模式*/
    {
      pMChair->SysModeCur    = pMChair->SysModeVender;                   /*从待机模式转入到厂家模式*/
      pMChair->SysModeHis    = SYS_MODE_STANDBY;   
      pMChair->SysModeVender = SYS_MODE_NONE;  
    }
  }

  /*根据各个模式的不同，对键值处理相关变量赋值---------------------------*/
  pMChair->KeyValHandle.KeyLogicTab    = StandBy_KeyLogicTab;            /*按键逻辑表*/
  pMChair->KeyValHandle.KeyLogicTabNum = STANDBY_KEY_TAB_NUM;            /*按键逻辑表 大小*/
  pMChair->KeyValHandle.pGetMatchID    = StandBy_GetKeyValID;            /*函数指针，指向的函数作用：返回表格条目 中 的要搜索的数据 所在的索引*/
  pMChair->KeyValHandle.pAddOp         = Standby_KeyValAdditonOp;        /*函数指针，指向的函数作用：键值执行前后的附加操作 */
}

/*
************************************************************************************************************************
* 函数名称 : SysMode_Standby_Enter                                                                                                         
* 功能描述 : 系统模式 之 待机 进入                                                                                    
* 输入参数 : CurSysMode       -- 当前所处的系统模式   
*            ResetSpikeAngle  -- 取值：TRUE  -- 复位推杆角度
*                                      FALSE -- 不复位推杆角度，保持当前的角度不变。                                          
* 返回参数 : SUCCESS -- 进入成功     FAIL -- 进入失败                                                    
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t SysMode_Standby_Enter(uint8_t CurSysMode, uint8_t ResetSpikeAngle)
{
  if(SYS_MODE_STANDBY == pMChair->SysModeCur)
  {
    return SUCCESS;
  }
  
  pMChair->CSFlag.Bit.MChairReported = TRUE;            /*关机上报*/

  pMChair->SysModeHis    = CurSysMode;
  pMChair->SysModeCur    = SYS_MODE_STANDBY;            /*进入待机模式*/
  pMChair->SysModeVender = SYS_MODE_NONE;               /*无厂家模式*/

  if(TRUE == ResetSpikeAngle)
  {
    Spike_SetLegFlexAngle(PLEGFLEX_MIN);                /*伸缩推杆缩到最短*/
    Spike_SetULegFlexAngle(PULEGFLEX_MAX);              /*上小腿伸到最长*/
    Spike_SetAngle(PBACK_MIN, PFEET_MIN, PZERO_MIN);    /*开机角度*/
  }

  return SUCCESS;
}
