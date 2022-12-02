/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: LegFlexSpike.c                                                                                                         
**
**    功能描述: 小腿缩推杆驱动。
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
#include "LegFlexSpike.h"

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
static LegFlexSpike_t LegFlexSpike;
LegFlexSpike_t *pLegFlexSpike = &LegFlexSpike;



/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : LegFlexSpike_CountIOCheck_CB                                                                                                         
* 功能描述 : 位置 计数IO口检测  的回调函数                                                                                           
* 输入参数 : 无                                                                                    
* 返回参数 : 无                                                                                             
* 补充说明 : 该函数通过 BSP_IO_InputInterrupt_RegCB_LegFlexSpikeCount(LegFlexSpike_CountIOCheck_CB);向下注册给BSP层                                                                                                         
************************************************************************************************************************
*/
void LegFlexSpike_CountIOCheck_CB(void)
{
  #if(1==LEGFLEX_DOWN_EN)
  MotorCountUpdata(&pLegFlexSpike->PositionMonitor.PositionCountCur, 
                   pLegFlexSpike->PositionMonitor.CountDirection, 
                   LEGFLEXSPIKE_COUNT_MAX, LEGFLEXSPIKE_COUNT_MIN);
  #endif
 
  #if(1==LEGFLEX_UP_EN)
  MotorCountUpdata(&pLegFlexSpike->ULegPositionMonitor.PositionCountCur, 
                   pLegFlexSpike->ULegPositionMonitor.CountDirection, 
                   ULEGFLEXSPIKE_COUNT_MAX, ULEGFLEXSPIKE_COUNT_MIN);
  #endif
}

/*
************************************************************************************************************************
* 函数名称 : LegFlexSpike_IOCheck                                                                                                         
* 功能描述 : IO口的检测                                                                                          
* 输入参数 : ExePeriod -- 函数的执行周期                                                                                   
* 返回参数 : 无                                                                                            
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void LegFlexSpike_IOCheck(Ticker_t ExePeriod)
{
  //static uint8_t StableIOCode;                                                                     /*稳定的编码*/
  //static uint8_t StableStat;                                                                       /*状态稳定统计*/
  static uint8_t IOCode;                       

  //static uint8_t UStableIOCode;                                                                    /*稳定的编码*/
  //static uint8_t UStableStat;                                                                      /*状态稳定统计*/
  static uint8_t UIOCode;                       
  
  
  /*有时会有干扰，因此这里做状态稳定的判断------------------------*/
  //if(PositionIOStableStat((BSP_IO_ReadInput_LegFlexSpikePosition() & B(11)), &DStableIOCode, &DStableStat) >= 3)
  //{
  //  IOCode = StableIOCode;                                                                      /*获取稳定后的编码*/
  //}
  IOCode = pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegReachExtendLimt;
  IOCode <<= 1;
  IOCode |= pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegReachShortenLimt;
  
  /*优先检测位置编码是否故障，--------------------------------------------------
    前后传感器是否同时有效，才会出现这种故障*/
  if(BIN(11) == IOCode) 
  {
    if(pLegFlexSpike->PositionMonitor.PositionCodeErrTimeMs <= LEGFLEXSPIKE_POSITION_CODE_ERR_TIME_THRESHOLD) /*未超过门限时间*/
    {
      pLegFlexSpike->PositionMonitor.PositionCodeErrTimeMs += ExePeriod;
    }
    else
    {
      pLegFlexSpike->CSFlag.Bit.PositionCodeFault = FAULT;            /*位置编码故障, 出现后，程序不会清零，靠复位或重上电才清零*/
      return;                                                          /*不再进行任何后续操作，直接返回*/
    }
  }
  else
  {
    pLegFlexSpike->PositionMonitor.PositionCodeErrTimeMs = 0;
  }
  
  /*位置计数传感器故障检测----------------------------------------------------------------------------*/
  pLegFlexSpike->PositionMonitor.PositionCountCur = pLegFlexSpike->SetQry0x4B.LegPositionCount;
  if(pLegFlexSpike->PositionMonitor.PositionCountHis == pLegFlexSpike->PositionMonitor.PositionCountCur)  /*位置计数无变化*/
  {
    if(ON == pLegFlexSpike->CSFlag.Bit.Run)                                                             /*马达在运行时，累加传感器失联时间*/
    {
      if(pLegFlexSpike->PositionMonitor.SensorLostTimeMs <= LEGFLEXSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD)
      {
        pLegFlexSpike->PositionMonitor.SensorLostTimeMs += ExePeriod;                                   /*马达在运行时，累加计数传感器失联时间*/
      }
      else
      {
        if((LEGFLEXSPIKE_ACTION_SHORTEN == pLegFlexSpike->Action) &&
           (0 == pLegFlexSpike->PositionMonitor.PositionCountCur)  )
        {
          pLegFlexSpike->CSFlag.Bit.ShortPositionSensorFault = FAULT;                                   /*最短限位传感器故障*/
        }
        else if((LEGFLEXSPIKE_ACTION_EXTEND == pLegFlexSpike->Action)                       && 
                (LEGFLEXSPIKE_COUNT_MAX <= pLegFlexSpike->PositionMonitor.PositionCountCur) )
        {
          pLegFlexSpike->CSFlag.Bit.ExtendPositionSensorFault = FAULT;                                  /*最长限位传感器故障*/
        }
        else 
        {
          pLegFlexSpike->CSFlag.Bit.CountFault = FAULT;                                                 /*计数故障*/
        }
      }    
    }
    else //if(OFF == pLegFlexSpike->CSFlag.Bit.Run)                                                         /*马达没开*/
    {
      pLegFlexSpike->PositionMonitor.SensorLostTimeMs = 0;                                              /*清零计数传感器失联时间*/
    }
  }
  else //if(pLegFlexSpike->PositionMonitor.PositionCountHis != pLegFlexSpike->PositionMonitor.PositionCountCur)/*计数有变化*/
  {
    pLegFlexSpike->PositionMonitor.PositionCountHis = pLegFlexSpike->PositionMonitor.PositionCountCur;
    pLegFlexSpike->PositionMonitor.SensorLostTimeMs = 0;                                                /*清零计数传感器失联时间*/
  }
  
  
  /*位置和信号IO读取---------------------------------------------------*/
  pLegFlexSpike->CSFlag.Bit.ReachExtendLimt  = BIT_GET(IOCode, 1);
  pLegFlexSpike->CSFlag.Bit.ReachShortenLimt = BIT_GET(IOCode, 0);
//  pLegFlexSpike->CSFlag.Bit.TouchGround      = pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegTouchGround; //BSP_IO_ReadInput_LegFlexSpikeTouchGround();
//  pLegFlexSpike->CSFlag.Bit.TouchFeet        = pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegTouchFeet;   //!BSP_IO_ReadInput_LegFlexSpikeTouchFeet();
  
  /*伸到最长或触地，停止伸长运动*/
  if((TRUE == pLegFlexSpike->CSFlag.Bit.TouchGround)    ||
     (TRUE == pLegFlexSpike->CSFlag.Bit.ReachExtendLimt)) 
  {
    if(LEGFLEXSPIKE_ACTION_EXTEND == pLegFlexSpike->Action)
    {
      LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_STOP);
    }
  }

  /*缩到最短或触脚，停止缩短运动*/                         
  //if((TRUE == pLegFlexSpike->CSFlag.Bit.ReachShortenLimt)                                                ||
  //   ((TRUE == pLegFlexSpike->CSFlag.Bit.TouchFeet) && (FALSE == pLegFlexSpike->CSFlag.Bit.TouchGround)) ) /*触脚但不触地*/   
  if(TRUE == pLegFlexSpike->CSFlag.Bit.ReachShortenLimt)  
  {
    if(LEGFLEXSPIKE_ACTION_SHORTEN == pLegFlexSpike->Action)
    {
      LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_STOP);
    }
    pLegFlexSpike->CSFlag.Bit.PositionResetOK = TRUE;        /*位置复位完成*/
  }
  
  /*位置值更新*/
  if(TRUE == pLegFlexSpike->CSFlag.Bit.ReachExtendLimt) 
  {
    pLegFlexSpike->PositionRealVal = LEGFLEXSPIKE_POSITION_MAX;
    pLegFlexSpike->PositionMonitor.PositionCountCur = LEGFLEXSPIKE_COUNT_MAX;         /*极限位置都要修正计数值*/
  }
  else if(TRUE == pLegFlexSpike->CSFlag.Bit.ReachShortenLimt) 
  {
    pLegFlexSpike->PositionRealVal = LEGFLEXSPIKE_POSITION_MIN;
    pLegFlexSpike->PositionMonitor.PositionCountCur = LEGFLEXSPIKE_COUNT_MIN;         /*极限位置都要修正计数值*/
  }
  else
  {
    if(POSITION_COUNT_INC == pLegFlexSpike->PositionMonitor.CountDirection)             /*计数增加*/
    {
      pLegFlexSpike->PositionRealVal = pLegFlexSpike->PositionMonitor.PositionCountCur/LEGFLEXSPIKE_COUNT_PER_SEGMENT;
    }
    else //if(POSITION_COUNT_DEC == pLegFlexSpike->PositionMonitor.CountDirection)      /*计数减少*/
    {
      pLegFlexSpike->PositionRealVal = pLegFlexSpike->PositionMonitor.PositionCountCur/LEGFLEXSPIKE_COUNT_PER_SEGMENT + 1;
    }
  }
 

  
#if(1==LEGFLEX_UP_EN)
  //=============================================================================================================================
  //=============================================================================================================================
  //=============================================================================================================================
  /*有时会有干扰，因此这里做状态稳定的判断------------------------*/
  //if(PositionIOStableStat((BSP_IO_ReadInput_LegFlexSpikePosition() & B(11)), &UStableIOCode, &UStableStat) >= 3)
  //{
  //  UIOCode = UStableIOCode;                                                                      /*获取稳定后的编码*/
  //}
 
  UIOCode = pLegFlexSpike->SetQry0x4B.Byte2.Bit.ULegReachExtendLimt;
  UIOCode <<= 1;
  UIOCode |= pLegFlexSpike->SetQry0x4B.Byte2.Bit.ULegReachShortenLimt;
  
  /*优先检测位置编码是否故障，--------------------------------------------------
    前后传感器是否同时有效，才会出现这种故障*/
  if(BIN(11) == UIOCode) 
  {
    if(pLegFlexSpike->ULegPositionMonitor.PositionCodeErrTimeMs <= LEGFLEXSPIKE_POSITION_CODE_ERR_TIME_THRESHOLD) /*未超过门限时间*/
    {
      pLegFlexSpike->ULegPositionMonitor.PositionCodeErrTimeMs += ExePeriod;
    }
    else
    {
      pLegFlexSpike->CSFlag.Bit.ULegPositionCodeFault = FAULT;         /*位置编码故障, 出现后，程序不会清零，靠复位或重上电才清零*/
      return;                                                          /*不再进行任何后续操作，直接返回*/
    }
  }
  else
  {
    pLegFlexSpike->ULegPositionMonitor.PositionCodeErrTimeMs = 0;
  }

  /*位置计数传感器故障检测----------------------------------------------------------------------------*/
  pLegFlexSpike->ULegPositionMonitor.PositionCountCur = pLegFlexSpike->SetQry0x4B.ULegPositionCount;
  if(pLegFlexSpike->ULegPositionMonitor.PositionCountHis == pLegFlexSpike->ULegPositionMonitor.PositionCountCur)  /*位置计数无变化*/
  {
    if(ON == pLegFlexSpike->CSFlag.Bit.ULegRun)                                                             /*马达在运行时，累加传感器失联时间*/
    {
      if(pLegFlexSpike->ULegPositionMonitor.SensorLostTimeMs <= LEGFLEXSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD)
      {
        pLegFlexSpike->ULegPositionMonitor.SensorLostTimeMs += ExePeriod;                                   /*马达在运行时，累加计数传感器失联时间*/
      }
      else
      {
        if((LEGFLEXSPIKE_ACTION_SHORTEN == pLegFlexSpike->ULegAction) &&
           (0 == pLegFlexSpike->ULegPositionMonitor.PositionCountCur)  )
        {
          pLegFlexSpike->CSFlag.Bit.ULegShortPositionSensorFault = FAULT;                                   /*最短限位传感器故障*/
        }
        else if((LEGFLEXSPIKE_ACTION_EXTEND == pLegFlexSpike->ULegAction)                       && 
                (ULEGFLEXSPIKE_COUNT_MAX <= pLegFlexSpike->ULegPositionMonitor.PositionCountCur) )
        {
          pLegFlexSpike->CSFlag.Bit.ULegExtendPositionSensorFault = FAULT;                                  /*最长限位传感器故障*/
        }
        else 
        {
          pLegFlexSpike->CSFlag.Bit.ULegCountFault = FAULT;                                                 /*计数故障*/
        }
      }    
    }
    else //if(OFF == pLegFlexSpike->CSFlag.Bit.Run)                                                         /*马达没开*/
    {
      pLegFlexSpike->ULegPositionMonitor.SensorLostTimeMs = 0;                                              /*清零计数传感器失联时间*/
    }
  }
  else //if(pLegFlexSpike->PositionMonitor.PositionCountHis != pLegFlexSpike->PositionMonitor.PositionCountCur)/*计数有变化*/
  {
    pLegFlexSpike->ULegPositionMonitor.PositionCountHis = pLegFlexSpike->ULegPositionMonitor.PositionCountCur;
    pLegFlexSpike->ULegPositionMonitor.SensorLostTimeMs = 0;                                                /*清零计数传感器失联时间*/
  }
  
  
  /*位置和信号IO读取---------------------------------------------------*/
  pLegFlexSpike->CSFlag.Bit.ULegReachExtendLimt  = BIT_GET(UIOCode, 1);
  pLegFlexSpike->CSFlag.Bit.ULegReachShortenLimt = BIT_GET(UIOCode, 0);

  /*伸到最长，停止伸长运动*/
  if(TRUE == pLegFlexSpike->CSFlag.Bit.ULegReachExtendLimt) 
  {
    if(LEGFLEXSPIKE_ACTION_EXTEND == pLegFlexSpike->ULegAction)
    {
      LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_STOP);
    }
    pLegFlexSpike->CSFlag.Bit.ULegPositionResetOK = TRUE;        /*位置复位完成*/
  }

  /*缩到最短，停止缩短运动*/
  if(TRUE == pLegFlexSpike->CSFlag.Bit.ULegReachShortenLimt) 
  {
    if(LEGFLEXSPIKE_ACTION_SHORTEN == pLegFlexSpike->ULegAction)
    {
      LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_STOP);
    }
  }
  
  /*位置值更新*/
  if(TRUE == pLegFlexSpike->CSFlag.Bit.ULegReachExtendLimt) 
  {
    pLegFlexSpike->ULegPositionRealVal = ULEGFLEXSPIKE_POSITION_MAX;
    pLegFlexSpike->ULegPositionMonitor.PositionCountCur = ULEGFLEXSPIKE_COUNT_MAX;         /*极限位置都要修正计数值*/
  }
  else if(TRUE == pLegFlexSpike->CSFlag.Bit.ULegReachShortenLimt) 
  {
    pLegFlexSpike->ULegPositionRealVal = ULEGFLEXSPIKE_POSITION_MIN;
    pLegFlexSpike->ULegPositionMonitor.PositionCountCur = ULEGFLEXSPIKE_COUNT_MIN;         /*极限位置都要修正计数值*/
  }
  else
  {
    if(POSITION_COUNT_INC == pLegFlexSpike->ULegPositionMonitor.CountDirection)             /*计数增加*/
    {
      pLegFlexSpike->ULegPositionRealVal = pLegFlexSpike->ULegPositionMonitor.PositionCountCur/ULEGFLEXSPIKE_COUNT_PER_SEGMENT;
    }
    else //if(POSITION_COUNT_DEC == pLegFlexSpike->PositionMonitor.CountDirection)          /*计数减少*/
    {
      pLegFlexSpike->ULegPositionRealVal = pLegFlexSpike->ULegPositionMonitor.PositionCountCur/ULEGFLEXSPIKE_COUNT_PER_SEGMENT + 1;
    }
  }
#endif
}


/*
************************************************************************************************************************
* 函数名称 : LegFlexSpike_PauseOn                                                                                                         
* 功能描述 : 暂停马达                                                                                       
* 输入参数 : 无                                                                                   
* 返回参数 : 无                                                                                            
* 补充说明 : 如果马达正在运转，则会停止马达的运转。
*            只有解除暂停，马达才能重新运转。                                                                                                         
************************************************************************************************************************
*/
void LegFlexSpike_PauseOn(void)
{
  if(pLegFlexSpike->CSFlag.Bit.Pause < 0x0F)
  {
    pLegFlexSpike->CSFlag.Bit.Pause++;
  }
  
#if(1==LEGFLEX_UP_EN)
  if(pLegFlexSpike->CSFlag.Bit.ULegPause < 0x0F)
  {
    pLegFlexSpike->CSFlag.Bit.ULegPause++;
  }
#endif
}


/*
************************************************************************************************************************
* 函数名称 : LegFlexSpike_PauseOff                                                                                                         
* 功能描述 : 解除暂停马达                                                                                  
* 输入参数 : 无                                                                                   
* 返回参数 : 无                                                                                            
* 补充说明 : 如果马达正在运转，则会停止马达的运转。
*            只有解除暂停，马达才能重新运转。                                                                                                         
************************************************************************************************************************
*/
void LegFlexSpike_PauseOff(void)
{
  if(pLegFlexSpike->CSFlag.Bit.Pause > 0)
  {
    pLegFlexSpike->CSFlag.Bit.Pause--;
  }
  
#if(1==LEGFLEX_UP_EN)
  if(pLegFlexSpike->CSFlag.Bit.ULegPause > 0)
  {
    pLegFlexSpike->CSFlag.Bit.ULegPause--;
  }
#endif
}


/*
************************************************************************************************************************
* 函数名称 : LegFlexSpike_SetAction                                                                                                         
* 功能描述 : 设置马达要执行的动作                                                                          
* 输入参数 : Action --> 动作需求，取值：
*                       LEGFLEXSPIKE_ACTION_UP
*                       LEGFLEXSPIKE_ACTION_DOWN
*                       LEGFLEXSPIKE_ACTION_STOP                                                                                   
* 返回参数 : 无                                                                                            
* 补充说明 : 无                                                                                              
************************************************************************************************************************
*/
void LegFlexSpike_SetAction(uint8_t Action)
{
  if((Action != LEGFLEXSPIKE_ACTION_STOP)   &&
     (Action != LEGFLEXSPIKE_ACTION_SHORTEN) &&
     (Action != LEGFLEXSPIKE_ACTION_EXTEND) )
  {
    Action = LEGFLEXSPIKE_ACTION_STOP;       /*动作参数无效，则执行停止动作*/
  }
  
  if((LEGFLEXSPIKE_ACTION_SHORTEN == Action) && 
      (pLegFlexSpike->CSFlag.Bit.ReachShortenLimt))
  {
    return;                                   /*缩到最短，不能再执行缩短运动*/
  }
  
  if((LEGFLEXSPIKE_ACTION_EXTEND == Action) && 
     ((pLegFlexSpike->CSFlag.Bit.ReachExtendLimt) || (pLegFlexSpike->CSFlag.Bit.TouchGround)))
  {
    return;                                   /*伸到最长或触地，不能再执行伸长运动*/
  }

  if(Action != LEGFLEXSPIKE_ACTION_STOP) 
  {
    pLegFlexSpike->CSFlag.Bit.Work = TRUE;   /*动作有效，则开始工作*/
  }
  else
  {
    pLegFlexSpike->CSFlag.Bit.Work = FALSE;  /*动作无效效，则不工作*/
  }

  pLegFlexSpike->Action = Action;
}

void LegFlexSpike_SetULegAction(uint8_t Action)
{
#if(1==LEGFLEX_UP_EN)
  if((Action != LEGFLEXSPIKE_ACTION_STOP)   &&
     (Action != LEGFLEXSPIKE_ACTION_SHORTEN) &&
     (Action != LEGFLEXSPIKE_ACTION_EXTEND) )
  {
    Action = LEGFLEXSPIKE_ACTION_STOP;       /*动作参数无效，则执行停止动作*/
  }
  
  if((LEGFLEXSPIKE_ACTION_SHORTEN == Action) && 
      (pLegFlexSpike->CSFlag.Bit.ULegReachShortenLimt))
  {
    return;                                   /*缩到最短，不能再执行缩短运动*/
  }
  
  if((LEGFLEXSPIKE_ACTION_EXTEND == Action) && 
     (pLegFlexSpike->CSFlag.Bit.ULegReachExtendLimt))
  {
    return;                                   /*伸到最长或触地，不能再执行伸长运动*/
  }

  if(Action != LEGFLEXSPIKE_ACTION_STOP) 
  {
    pLegFlexSpike->CSFlag.Bit.ULegWork = TRUE;   /*动作有效，则开始工作*/
  }
  else
  {
    pLegFlexSpike->CSFlag.Bit.ULegWork = FALSE;  /*动作无效效，则不工作*/
  }

  pLegFlexSpike->ULegAction = Action;
#endif
}


/*
************************************************************************************************************************
* 函数名称 : LegFlexSpike_GetPosition                                                                                                         
* 功能描述 : 获取推杆位置                                                           
* 输入参数 : 无                                                                               
* 返回参数 : 推杆当前位置                                                                                            
* 补充说明 : 无                                                                                               
************************************************************************************************************************
*/
uint8_t LegFlexSpike_GetPosition(void)
{
  return pLegFlexSpike->PositionRealVal;
}

uint8_t LegFlexSpike_GetULegPosition(void)
{
  return pLegFlexSpike->ULegPositionRealVal;
}
/*
************************************************************************************************************************
* 函数名称 : LegFlexSpike_SetPosition                                                                                                         
* 功能描述 : 设置推杆位置                                                         
* 输入参数 : Position --> 推杆 停靠位置
*                         特殊值：PKEEP          -- 保持当前位置不动。
*                                 大于最大坐标值 -- 运动到最大坐标。                                                                                
* 返回参数 : 无                                                                                       
* 补充说明 : 无                                                                                               
************************************************************************************************************************
*/
void LegFlexSpike_SetPosition(uint8_t Position)
{
  if((Position > LEGFLEXSPIKE_POSITION_MAX) && (Position != PKEEP)) 
  {
    Position = LEGFLEXSPIKE_POSITION_MAX;
  }

  pLegFlexSpike->PositionSetVal = Position; 
}

void LegFlexSpike_SetULegPosition(uint8_t Position)
{
  if((Position > ULEGFLEXSPIKE_POSITION_MAX) && (Position != PKEEP)) 
  {
    Position = ULEGFLEXSPIKE_POSITION_MAX;
  }

  pLegFlexSpike->ULegPositionSetVal = Position; 
}
/*
************************************************************************************************************************
* 函数名称 : LegFlexSpike_PositionHandle                                                                                                         
* 功能描述 : 推杆停靠位置处理                                                    
* 输入参数 : ExePeriod -- 函数的执行周期                                                                     
* 返回参数 : 无                                                                                      
* 补充说明 : 位置的计算，除非完全采用多位的IO二进制编码检测，
*            否则，只能使用  参考点  结合  当前脉冲计数或二进制编码来计算。
*            因此，在找到参考点以前，无法正确得知当前位置。                                                                                               
************************************************************************************************************************
*/
void LegFlexSpike_PositionHandle(Ticker_t ExePeriod)
{
  if(FALSE == pLegFlexSpike->CSFlag.Bit.PositionResetOK)                /*位置还没复位，即还没找到位置计算参考点*/
  {
    LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_SHORTEN);      
  }
  else //if(TRUE == pLegFlexSpike->CSFlag.Bit.PositionResetOK)          /*位置已经复位，即位置计算参考点已确认*/
  {
    if(PKEEP == pLegFlexSpike->PositionSetVal)                          /*位置保持*/
    {
      LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_STOP);
    }
    else                                                                /*调节位置*/
    {
      if(LEGFLEXSPIKE_POSITION_MAX == pLegFlexSpike->PositionSetVal)    /*极限位置 单独处理*/
      {
        if(FALSE == pLegFlexSpike->CSFlag.Bit.ReachExtendLimt)
        {
          LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_EXTEND);
        }
        else
        {
          LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_STOP);
        }
      }
      else if(LEGFLEXSPIKE_POSITION_MIN == pLegFlexSpike->PositionSetVal)  /*极限位置 单独处理*/
      {
        if(FALSE == pLegFlexSpike->CSFlag.Bit.ReachShortenLimt)
        {
          LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_SHORTEN);
        }
        else
        {
          LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_STOP);
        }
      }
      else if(pLegFlexSpike->PositionSetVal == pLegFlexSpike->PositionRealVal)
      {
        LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_STOP);
      }
      else if(pLegFlexSpike->PositionSetVal > pLegFlexSpike->PositionRealVal)
      {
        LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_EXTEND);
      }
      else //(pLegFlexSpike->PositionSetVal < pLegFlexSpike->PositionRealVal)
      {
        LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_SHORTEN);
      }
    }
  }

#if(1==LEGFLEX_UP_EN)
  //=========================================================================
  if(FALSE == pLegFlexSpike->CSFlag.Bit.ULegPositionResetOK)                /*位置还没复位，即还没找到位置计算参考点*/
  {
    LegFlexSpike_SetULegAction(LEGFLEXSPIKE_ACTION_EXTEND);      
  }
  else //if(TRUE == pLegFlexSpike->CSFlag.Bit.ULegPositionResetOK)          /*位置已经复位，即位置计算参考点已确认*/
  {
    if(PKEEP == pLegFlexSpike->ULegPositionSetVal)                          /*位置保持*/
    {
      LegFlexSpike_SetULegAction(LEGFLEXSPIKE_ACTION_STOP);
    }
    else                                                                    /*调节位置*/
    {
      if(ULEGFLEXSPIKE_POSITION_MAX == pLegFlexSpike->ULegPositionSetVal)    /*极限位置 单独处理*/
      {
        if(FALSE == pLegFlexSpike->CSFlag.Bit.ULegReachExtendLimt)
        {
          LegFlexSpike_SetULegAction(LEGFLEXSPIKE_ACTION_EXTEND);
        }
        else
        {
          LegFlexSpike_SetULegAction(LEGFLEXSPIKE_ACTION_STOP);
        }
      }
      else if(ULEGFLEXSPIKE_POSITION_MIN == pLegFlexSpike->ULegPositionSetVal)  /*极限位置 单独处理*/
      {
        if(FALSE == pLegFlexSpike->CSFlag.Bit.ULegReachShortenLimt)
        {
          LegFlexSpike_SetULegAction(LEGFLEXSPIKE_ACTION_SHORTEN);
        }
        else
        {
          LegFlexSpike_SetULegAction(LEGFLEXSPIKE_ACTION_STOP);
        }
      }
      else if(pLegFlexSpike->ULegPositionSetVal == pLegFlexSpike->ULegPositionRealVal)
      {
        LegFlexSpike_SetULegAction(LEGFLEXSPIKE_ACTION_STOP);
      }
      else if(pLegFlexSpike->ULegPositionSetVal > pLegFlexSpike->ULegPositionRealVal)
      {
        LegFlexSpike_SetULegAction(LEGFLEXSPIKE_ACTION_EXTEND);
      }
      else //(pLegFlexSpike->ULegPositionSetVal < pLegFlexSpike->ULegPositionRealVal)
      {
        LegFlexSpike_SetULegAction(LEGFLEXSPIKE_ACTION_SHORTEN);
      }
    }
  }
#endif
}

/*
************************************************************************************************************************
* 函数名称 : LegFlexSpike_ActionHandle                                                                                                         
* 功能描述 : 马达动作处理                                                                   
* 输入参数 : ExePeriod -- 函数的执行周期                                                                        
* 返回参数 : 无                                                                                            
* 补充说明 : 无                                                                                              
************************************************************************************************************************
*/
void LegFlexSpike_ActionHandle(Ticker_t ExePeriod)
{
  static uint8_t     ActionHis = 0xFF;                   /*历史动作状态*/
  static uint8_t     ULegActionHis = 0xFF;                   /*历史动作状态*/


  /*动作状态的改变判断------------------------------------*/
  if(ActionHis != pLegFlexSpike->Action)
  {
    pLegFlexSpike->CSFlag.Bit.Run = OFF;                 /*动作改变，都先停止电机*/
    ActionHis = pLegFlexSpike->Action;
    pLegFlexSpike->StateCtrlTimeMs = 0;
  }

  pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegFlexAction = pLegFlexSpike->Action;
  
  do
  {
    /*暂停则停止电机-----------------------------------------*/
    if(pLegFlexSpike->CSFlag.Bit.Pause > 0)
    {
      pLegFlexSpike->CSFlag.Bit.Run = OFF; 
      pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegFlexAction = LEGFLEXSPIKE_ACTION_STOP;
      break;
    }

    /* 发生异常，则停止马达-------------------------------------*/
    if((FAULT == pLegFlexSpike->CSFlag.Bit.PositionCodeFault)        ||        /*位置编码故障*/
       (FAULT == pLegFlexSpike->CSFlag.Bit.CountFault)               ||        /*计数故障*/
       (FAULT == pLegFlexSpike->CSFlag.Bit.ShortPositionSensorFault) ||        /*位置传感器故障*/
       (FAULT == pLegFlexSpike->CSFlag.Bit.ExtendPositionSensorFault))         /*位置传感器故障*/
    {
      pLegFlexSpike->CSFlag.Bit.Locked = TRUE;                                 /*异常则上锁马达*/
      pLegFlexSpike->CSFlag.Bit.Run    = OFF;                                  /*异常则停马达*/
      pLegFlexSpike->CSFlag.Bit.Work   = FALSE;  
      pLegFlexSpike->StateCtrlTimeMs = 0;
      pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegFlexAction = LEGFLEXSPIKE_ACTION_STOP;
      break;
    }
    
    /*马达驱动--------------------------------------------------*/
    if(pLegFlexSpike->Action != LEGFLEXSPIKE_ACTION_STOP)
    {
      if(pLegFlexSpike->StateCtrlTimeMs < 30000)
      {
        pLegFlexSpike->StateCtrlTimeMs += ExePeriod; 
      }

      if(pLegFlexSpike->StateCtrlTimeMs <= LEGFLEXSPIKE_DIRECTION_TIME_MS)     /*先关电机-----------*/
      {
        pLegFlexSpike->CSFlag.Bit.Run = OFF;
      }
      else if(pLegFlexSpike->StateCtrlTimeMs <= LEGFLEXSPIKE_REVERSE_TIME_MS)  /*切换方向------------*/
      {
        if(LEGFLEXSPIKE_ACTION_SHORTEN == pLegFlexSpike->Action)
        {
          pLegFlexSpike->CSFlag.Bit.Direction = LEGFLEXSPIKE_DIRECTION_SHORTEN;
          pLegFlexSpike->PositionMonitor.CountDirection = POSITION_COUNT_DEC;
        }
        else if(LEGFLEXSPIKE_ACTION_EXTEND == pLegFlexSpike->Action)
        {
          pLegFlexSpike->CSFlag.Bit.Direction = LEGFLEXSPIKE_DIRECTION_EXTEND;
          pLegFlexSpike->PositionMonitor.CountDirection = POSITION_COUNT_INC;
        }
      }
      else if(pLegFlexSpike->StateCtrlTimeMs <= 26000)                         /*马达运转-----------------------------------------*/
      {
        pLegFlexSpike->CSFlag.Bit.Run = ON;
      }
      else                                                                     /*长时间运行，还未检测到限位信号，则进行关断*/
      {
        pLegFlexSpike->CSFlag.Bit.Run = OFF;
      }
    }
    else /*pLegFlexSpike->Action == LEGFLEXSPIKE_ACTION_STOP*/
    {
      pLegFlexSpike->CSFlag.Bit.Run = OFF;
      pLegFlexSpike->StateCtrlTimeMs = 0;
    }
  }while(0);

  //BSP_IO_SetOutput_LegFlexSpikeCtrl(pLegFlexSpike->CSFlag.Bit.Run, pLegFlexSpike->CSFlag.Bit.Direction, 0);

  
#if(1==LEGFLEX_UP_EN)
  //=========================================================================================================
  //=========================================================================================================

  /*动作状态的改变判断------------------------------------*/
  if(ULegActionHis != pLegFlexSpike->ULegAction)
  {
    pLegFlexSpike->CSFlag.Bit.ULegRun = OFF;                 /*动作改变，都先停止电机*/
    ULegActionHis = pLegFlexSpike->ULegAction;
    pLegFlexSpike->ULegStateCtrlTimeMs = 0;
  }
  
  pLegFlexSpike->SetQry0x4B.Byte2.Bit.ULegFlexAction = pLegFlexSpike->ULegAction;

  do
  {
    /*暂停则停止电机-----------------------------------------*/
    if(pLegFlexSpike->CSFlag.Bit.ULegPause > 0)
    {
      pLegFlexSpike->CSFlag.Bit.ULegRun = OFF; 
      pLegFlexSpike->SetQry0x4B.Byte2.Bit.ULegFlexAction = LEGFLEXSPIKE_ACTION_STOP;
      break;
    }

    /* 发生异常，则停止马达-------------------------------------*/
    if((FAULT == pLegFlexSpike->CSFlag.Bit.ULegPositionCodeFault)        ||        /*位置编码故障*/
       (FAULT == pLegFlexSpike->CSFlag.Bit.ULegCountFault)               ||        /*计数故障*/
       (FAULT == pLegFlexSpike->CSFlag.Bit.ULegShortPositionSensorFault) ||        /*位置传感器故障*/
       (FAULT == pLegFlexSpike->CSFlag.Bit.ULegExtendPositionSensorFault))         /*位置传感器故障*/
    {
      pLegFlexSpike->CSFlag.Bit.ULegLocked = TRUE;                                 /*异常则上锁马达*/
      pLegFlexSpike->CSFlag.Bit.ULegRun    = OFF;                                  /*异常则停马达*/
      pLegFlexSpike->CSFlag.Bit.ULegWork   = FALSE;  
      pLegFlexSpike->ULegStateCtrlTimeMs = 0;
      pLegFlexSpike->SetQry0x4B.Byte2.Bit.ULegFlexAction = LEGFLEXSPIKE_ACTION_STOP;
      break;
    }
    
    /*马达驱动--------------------------------------------------*/
    if(pLegFlexSpike->ULegAction != LEGFLEXSPIKE_ACTION_STOP)
    {
      if(pLegFlexSpike->ULegStateCtrlTimeMs < 30000)
      {
        pLegFlexSpike->ULegStateCtrlTimeMs += ExePeriod; 
      }

      if(pLegFlexSpike->ULegStateCtrlTimeMs <= LEGFLEXSPIKE_DIRECTION_TIME_MS)     /*先关电机-----------*/
      {
        pLegFlexSpike->CSFlag.Bit.ULegRun = OFF;
      }
      else if(pLegFlexSpike->ULegStateCtrlTimeMs <= LEGFLEXSPIKE_REVERSE_TIME_MS)  /*切换方向------------*/
      {
        if(LEGFLEXSPIKE_ACTION_SHORTEN == pLegFlexSpike->ULegAction)
        {
          pLegFlexSpike->CSFlag.Bit.ULegDirection = LEGFLEXSPIKE_DIRECTION_SHORTEN;
          pLegFlexSpike->ULegPositionMonitor.CountDirection = POSITION_COUNT_DEC;
        }
        else if(LEGFLEXSPIKE_ACTION_EXTEND == pLegFlexSpike->ULegAction)
        {
          pLegFlexSpike->CSFlag.Bit.ULegDirection = LEGFLEXSPIKE_DIRECTION_EXTEND;
          pLegFlexSpike->ULegPositionMonitor.CountDirection = POSITION_COUNT_INC;
        }
      }
      else if(pLegFlexSpike->ULegStateCtrlTimeMs <= 26000)                         /*马达运转-----------------------------------------*/
      {
        pLegFlexSpike->CSFlag.Bit.ULegRun = ON;
      }
      else                                                                     /*长时间运行，还未检测到限位信号，则进行关断*/
      {
        pLegFlexSpike->CSFlag.Bit.ULegRun = OFF;
      }
    }
    else /*pLegFlexSpike->ULegAction == LEGFLEXSPIKE_ACTION_STOP*/
    {
      pLegFlexSpike->CSFlag.Bit.ULegRun = OFF;
      pLegFlexSpike->ULegStateCtrlTimeMs = 0;
    }
  }while(0);

//  BSP_IO_SetOutput_LegFlexSpikeCtrl(pLegFlexSpike->CSFlag.Bit.Run, pLegFlexSpike->CSFlag.Bit.Direction, 0);
#endif
}


/*
************************************************************************************************************************
* 函数名称 : LegFlexSpike_Init                                                                                                         
* 功能描述 : 推杆初始化                                                             
* 输入参数 : 无                                                                    
* 返回参数 : 无                                                                                            
* 补充说明 : 无                                                                                              
************************************************************************************************************************
*/
LegFlexSpike_t* LegFlexSpike_Init(void)
{
  memset(pLegFlexSpike, 0, sizeof(LegFlexSpike_t));        /*清零所有数据*/
  
  pLegFlexSpike->CSFlag.Bit.PositionResetOK = FALSE;
  pLegFlexSpike->PositionSetVal                   = LEGFLEXSPIKE_POSITION_MIN;    /*要使用的参考位置*/
  pLegFlexSpike->PositionRealVal                  = LEGFLEXSPIKE_POSITION_MAX;    /*假设的当前位置*/ 
  pLegFlexSpike->PositionMonitor.PositionCountCur = LEGFLEXSPIKE_COUNT_MAX*2;     /*假设的当前位置计数*/ 

  
#if(1==LEGFLEX_UP_EN)
  pLegFlexSpike->CSFlag.Bit.ULegPositionResetOK = FALSE;
  pLegFlexSpike->ULegPositionSetVal                   = ULEGFLEXSPIKE_POSITION_MAX;   /*要使用的参考位置*/
  pLegFlexSpike->ULegPositionRealVal                  = ULEGFLEXSPIKE_POSITION_MIN;   /*假设的当前位置*/ 
  pLegFlexSpike->ULegPositionMonitor.PositionCountCur = 0;                            /*假设的当前位置计数*/ 
#endif  
  //BSP_IO_InputInterrupt_RegCB_LegFlexSpikeCount(LegFlexSpike_CountIOCheck_CB);   
  
  return pLegFlexSpike;
}

/*
************************************************************************************************************************
* 函数名称 : LegFlexSpike_GetCSFlag                                                                                                         
* 功能描述 : 获得 控制 与 状态 标识                                                           
* 输入参数 : 无                                                                    
* 返回参数 : 控制与状态标识 的结构体                                                                                           
* 补充说明 : 无                                                                                              
************************************************************************************************************************
*/
LegFlexSpikeCSFlag_t LegFlexSpike_GetCSFlag(void)
{
  if(0 == BSP_IO_GetVenderTestPin())      /*工装检测下，无小腿负载，因此屏蔽相关故障告警*/
  {
    pLegFlexSpike->CSFlag.Bit.PositionCodeFault = NORMAL;
    pLegFlexSpike->CSFlag.Bit.CountFault = NORMAL;
    pLegFlexSpike->CSFlag.Bit.ShortPositionSensorFault = NORMAL;
    pLegFlexSpike->CSFlag.Bit.ExtendPositionSensorFault = NORMAL;
    pLegFlexSpike->CSFlag.Bit.PositionResetOK = TRUE;
  }

  return pLegFlexSpike->CSFlag;
}

/*
************************************************************************************************************************
* 函数名称 : LegFlexSpike_CDPDataObjRx_0x4B                                                                                      
* 功能描述 : 0x4B 腿脚伸缩控制(中心板<-->腿脚控制板）
* 输入参数 : pRxDU   -- 指向接收的数据对象单元
*            pAckDU  -- 指向应答的数据对象单元
*            SrcAddr -- 数据的来源
*            Cmd     -- 命令
* 返回参数 : 处理成功：该数据对象中数据的长度    
             处理出错：CDP_DU_HANDLE_ERR 数据处理出错
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t LegFlexSpike_CDPDataObjRx_0x4B(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  /*更新数据到中心板-------------------------------------------------------------*/
  memcpy((uint8_t *)&pLegFlexSpike->SetQry0x4B, &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);

  pLegFlexSpike->CSFlag.Bit.TouchGround      = pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegTouchGround;         /*触地信号*/
  pLegFlexSpike->CSFlag.Bit.TouchFeet        = pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegTouchFeet;           /*触脚信号*/
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* 函数名称 : LegFlexSpike_CDPDataObjTx_0x4B                                                                                      
* 功能描述 : 0x4B 腿脚伸缩控制(中心板<-->腿脚控制板）
* 输入参数 : 无
* 返回参数 : 成功则返回要发送的数据的内存首地址，失败返回NULL空指针
* 补充说明 : 无
************************************************************************************************************************
*/
uint8_t* LegFlexSpike_CDPDataObjTx_0x4B(void)
{
  pLegFlexSpike->SetQry0x4B.DataLen = sizeof(pLegFlexSpike->SetQry0x4B);  
  pLegFlexSpike->SetQry0x4B.DataID = 0x4B;  

  return (uint8_t *)&pLegFlexSpike->SetQry0x4B;
}
