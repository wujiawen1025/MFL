/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称: Spike.c                                                                                                         
**
**    功能描述: 推杆驱动。管理 靠背、小腿、小腿伸缩、零重力 等推杆
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
#include "Spike.h"
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
Spike_t Spike;
Spike_t  *pSpike = &Spike;


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : Spike_SetBackAngle                                                                                                         
* 功能描述 : 推杆 设置 靠背角度                                                                                                
* 输入参数 : BackAngle -- 角度，取值 PBACK_MIN ~ PBACK_MAX 、PKEEP                                                                                               
* 返回参数 : 失败--FAIL    成功--SUCCESS                                                                                                  
* 补充说明 : 设置推杆角度时，将自动清零相关的Move运动（即如果有手动的推杆调节，则将被清除）。                                                                                                        
************************************************************************************************************************
*/
uint8_t Spike_SetBackAngle(uint8_t BackAngle)
{
  if((BackAngle > PBACK_MAX) && (BackAngle!= PKEEP))
  {
    return FAIL;
  }
  pSpike->BackAngleSetVal = BackAngle;
  pSpike->ActionCur.Bit.BackMove = SPIKE_MOVE_NONE;  /*清除推杆调节运动*/
  pSpike->ActionHis.Bit.BackMove = SPIKE_MOVE_NONE;  /*清除推杆调节运动*/

  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : Spike_SetZeroAngle                                                                                                         
* 功能描述 : 推杆 设置 零重力角度                                                                                            
* 输入参数 : ZeroAngle -- 角度，取值 PZERO_MIN ~ PZERO_MAX 、PKEEP                                                                                               
* 返回参数 : 失败--FAIL    成功--SUCCESS                                                                                                  
* 补充说明 : 设置推杆角度时，将自动清零相关的Move运动（即如果有手动的推杆调节，则将被清除）。                                                                                                        
************************************************************************************************************************
*/
uint8_t Spike_SetZeroAngle(uint8_t ZeroAngle)
{
  if((ZeroAngle > PZERO_MAX) && (ZeroAngle!= PKEEP))
  {
    return FAIL;
  }
  pSpike->ZeroAngleSetVal = ZeroAngle;
  pSpike->ActionCur.Bit.ZeroMove = SPIKE_MOVE_NONE;  /*清除推杆调节运动*/
  pSpike->ActionHis.Bit.ZeroMove = SPIKE_MOVE_NONE;  /*清除推杆调节运动*/
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : Spike_SetFeetAngle                                                                                                         
* 功能描述 : 推杆 设置 腿脚角度                                                                                         
* 输入参数 : FeetAngle -- 角度，取值 PFEET_MIN ~ PFEET_MAX 、PKEEP                                                                                               
* 返回参数 : 失败--FAIL    成功--SUCCESS                                                                                                  
* 补充说明 : 设置推杆角度时，将自动清零相关的Move运动（即如果有手动的推杆调节，则将被清除）。                                                                                                        
************************************************************************************************************************
*/
uint8_t Spike_SetFeetAngle(uint8_t FeetAngle)
{
  if((FeetAngle > PFEET_MAX) && (FeetAngle!= PKEEP))
  {
    return FAIL;
  }
  pSpike->FeetAngleSetVal = FeetAngle;
  pSpike->ActionCur.Bit.FeetMove = SPIKE_MOVE_NONE;  /*清除推杆调节运动*/
  pSpike->ActionHis.Bit.FeetMove = SPIKE_MOVE_NONE;  /*清除推杆调节运动*/
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : Spike_SetAngle                                                                                                         
* 功能描述 : 推杆 设置 靠背、零重力、腿脚 角度                                                                                
* 输入参数 : BackAngle -- 靠背角度，  取值 PBACK_MIN ~ PBACK_MAX 、PKEEP                                                                                               
*            FeetAngle -- 小腿角度，  取值 PFEET_MIN ~ PFEET_MAX 、PKEEP                                                                                               
*            ZeroAngle -- 零重力角度，取值 PZERO_MIN ~ PZERO_MAX 、PKEEP                                                                                               
* 返回参数 : 无                                                                                               
* 补充说明 : 设置推杆角度时，将自动清零相关的Move运动（即如果有手动的推杆调节，则将被清除）。                                                                                                        
************************************************************************************************************************
*/
void Spike_SetAngle(uint8_t BackAngle, uint8_t FeetAngle, uint8_t ZeroAngle)
{
  Spike_SetBackAngle(BackAngle);
  Spike_SetFeetAngle(FeetAngle);
  Spike_SetZeroAngle(ZeroAngle);
}

/*
************************************************************************************************************************
* 函数名称 : Spike_SetLegFlexAngle                                                                                                         
* 功能描述 : 推杆 设置 腿脚伸缩角度                                                                                         
* 输入参数 : LegFlexAngle -- 角度，取值 PLEGFLEX_MIN ~ PLEGFLEX_MAX 、PKEEP                                                                                               
* 返回参数 : 失败--FAIL    成功--SUCCESS                                                                                                  
* 补充说明 : 设置推杆角度时，将自动清零相关的Move运动（即如果有手动的推杆调节，则将被清除）。                                                                                                        
************************************************************************************************************************
*/
uint8_t Spike_SetLegFlexAngle(uint8_t LegFlexAngle)
{
  if((LegFlexAngle > PLEGFLEX_MAX) && (LegFlexAngle!= PKEEP))
  {
    return FAIL;
  }
  pSpike->LegFlexAngleSetVal = LegFlexAngle;
  pSpike->ActionCur.Bit.LegFlexMove = SPIKE_MOVE_NONE;  /*清除推杆调节运动*/
  pSpike->ActionHis.Bit.LegFlexMove = SPIKE_MOVE_NONE;  /*清除推杆调节运动*/
  if(TRUE == pSpike->CSFlag.Bit.LegLenDetectRun)        
  {
    pSpike->CSFlag.Bit.LegLenDetectRun = FALSE;
    pSpike->LegLenDetectStep = 255;                     /*上层调用调节伸缩推杆，则结束腿长自动检测*/
  }
  return SUCCESS;
}


uint8_t Spike_SetULegFlexAngle(uint8_t LegFlexAngle)
{
  if((LegFlexAngle > PLEGFLEX_MAX) && (LegFlexAngle!= PKEEP))
  {
    return FAIL;
  }
  pSpike->ULegFlexAngleSetVal = LegFlexAngle;
  pSpike->ActionCur.Bit.ULegFlexMove = SPIKE_MOVE_NONE;  /*清除推杆调节运动*/
  pSpike->ActionHis.Bit.ULegFlexMove = SPIKE_MOVE_NONE;  /*清除推杆调节运动*/
  return SUCCESS;
}

/*
************************************************************************************************************************
* 函数名称 : Spike_SetBackMove                                                                                                         
* 功能描述 : 推杆 设置 靠背 升降 动作                                                                                
* 输入参数 : Move 取值： SPIKE_MOVE_NONE
*                        SPIKE_MOVE_BACK_UP
*                        SPIKE_MOVE_BACK_DOWN                                                                                         
* 返回参数 : 无                                                                                               
* 补充说明 : 调节完后，Spike_MoveActionHandle()函数中将自动把相关的角度设置为PKEEP(位置保持)                                                                                                      
************************************************************************************************************************
*/
void Spike_SetBackMove(uint8_t Move)
{
  if((Move != SPIKE_MOVE_NONE)      &&
     (Move != SPIKE_MOVE_BACK_UP)   &&
     (Move != SPIKE_MOVE_BACK_DOWN) )
  {
    Move = SPIKE_MOVE_NONE;
  }

  /*零重力安全角度限定时，不能再倒靠背*/
  if((TRUE == pSpike->CSFlag.Bit.ReachZeroSafetyAngleLimit) &&
     (SPIKE_MOVE_BACK_DOWN == Move)) 
  {
    return;
  }

  pSpike->ActionCur.Bit.BackMove = Move;
}


/*
************************************************************************************************************************
* 函数名称 : Spike_GetBackMove                                                                                                         
* 功能描述 : 推杆 查询 靠背 升降 动作                                                                          
* 输入参数 : 无                                                                                  
* 返回参数 : SPIKE_MOVE_NONE
*            SPIKE_MOVE_BACK_UP
*            SPIKE_MOVE_BACK_DOWN                                                                                               
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t Spike_GetBackMove(void)
{
  return pSpike->ActionCur.Bit.BackMove;
}

/*
************************************************************************************************************************
* 函数名称 : Spike_SetZeroMove                                                                                                         
* 功能描述 : 推杆 设置 零重力 升降 动作                                                                          
* 输入参数 : Move 取值： SPIKE_MOVE_NONE
*                        SPIKE_MOVE_ZERO_UP
*                        SPIKE_MOVE_ZERO_DOWN                                                                              
* 返回参数 : 无                                                                                               
* 补充说明 : 调节完后，Spike_MoveActionHandle()函数中将自动把相关的角度设置为PKEEP(位置保持)                                                                                                      
************************************************************************************************************************
*/
void Spike_SetZeroMove(uint8_t Move)
{
  if((Move != SPIKE_MOVE_NONE)      &&
     (Move != SPIKE_MOVE_ZERO_UP)   &&
     (Move != SPIKE_MOVE_ZERO_DOWN) )
  {
    Move = SPIKE_MOVE_NONE;
  }

  pSpike->ActionCur.Bit.ZeroMove = Move;
}

/*
************************************************************************************************************************
* 函数名称 : Spike_GetZeroMove                                                                                                         
* 功能描述 : 推杆 查询 零重力 升降 动作                                                                   
* 输入参数 : 无                                                                          
* 返回参数 : SPIKE_MOVE_NONE
*            SPIKE_MOVE_ZERO_UP
*            SPIKE_MOVE_ZERO_DOWN                                                                                               
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t Spike_GetZeroMove(void)
{
  return pSpike->ActionCur.Bit.ZeroMove;
}

/*
************************************************************************************************************************
* 函数名称 : Spike_SetFeetMove                                                                                                         
* 功能描述 : 推杆 设置 腿脚 升降 动作                                                        
* 输入参数 : Move 取值： SPIKE_MOVE_NONE
*                        SPIKE_MOVE_FEET_UP
*                        SPIKE_MOVE_FEET_DOWN                                                                          
* 返回参数 : 无                                                                                         
* 补充说明 : 调节完后，Spike_MoveActionHandle()函数中将自动把相关的角度设置为PKEEP(位置保持)                                                                                                      
************************************************************************************************************************
*/
void Spike_SetFeetMove(uint8_t Move)
{
  if((Move != SPIKE_MOVE_NONE)      &&
     (Move != SPIKE_MOVE_FEET_UP)   &&
     (Move != SPIKE_MOVE_FEET_DOWN) )
  {
    Move = SPIKE_MOVE_NONE;
  }

  pSpike->ActionCur.Bit.FeetMove = Move;
}

/*
************************************************************************************************************************
* 函数名称 : Spike_GetFeetMove                                                                                                         
* 功能描述 : 推杆 查询 腿脚 升降 动作                                                       
* 输入参数 : 无                                                                       
* 返回参数 : SPIKE_MOVE_NONE
*            SPIKE_MOVE_FEET_UP
*            SPIKE_MOVE_FEET_DOWN                                                                                         
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t Spike_GetFeetMove(void)
{
  return pSpike->ActionCur.Bit.FeetMove;
}


/*
************************************************************************************************************************
* 函数名称 : Spike_SetLegFlexMove                                                                                                         
* 功能描述 : 推杆 设置 腿脚 伸缩 动作                                                
* 输入参数 : Move 取值： SPIKE_MOVE_NONE
*                        SPIKE_MOVE_LEG_SHORT
*                        SPIKE_MOVE_LEG_EXTEND                                                                      
* 返回参数 : 无                                                                                        
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Spike_SetLegFlexMove(uint8_t Move)
{
  if((Move != SPIKE_MOVE_NONE)      &&
     (Move != SPIKE_MOVE_LEG_SHORT)   &&
     (Move != SPIKE_MOVE_LEG_EXTEND) )
  {
    Move = SPIKE_MOVE_NONE;
  }

  pSpike->ActionCur.Bit.LegFlexMove = Move;
  if(TRUE == pSpike->CSFlag.Bit.LegLenDetectRun)        
  {
    pSpike->CSFlag.Bit.LegLenDetectRun = FALSE;
    pSpike->LegLenDetectStep = 255;                     /*上层调用调节伸缩推杆，则结束腿长自动检测*/
  }
}

void Spike_SetULegFlexMove(uint8_t Move)
{
  if((Move != SPIKE_MOVE_NONE)      &&
     (Move != SPIKE_MOVE_LEG_SHORT)   &&
     (Move != SPIKE_MOVE_LEG_EXTEND) )
  {
    Move = SPIKE_MOVE_NONE;
  }

  pSpike->ActionCur.Bit.ULegFlexMove = Move;
}


/*
************************************************************************************************************************
* 函数名称 : Spike_GetLegFlexMove                                                                                                         
* 功能描述 : 推杆 查询 腿脚 伸缩 动作                                                
* 输入参数 : 无                                                                 
* 返回参数 : SPIKE_MOVE_NONE
*            SPIKE_MOVE_FEET_SHORT
*            SPIKE_MOVE_FEET_EXTEND                                                                                               
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
uint8_t Spike_GetLegFlexMove(void)
{
  return pSpike->ActionCur.Bit.LegFlexMove;
}

uint8_t Spike_GetULegFlexMove(void)
{
  return pSpike->ActionCur.Bit.ULegFlexMove;
}

/*
************************************************************************************************************************
* 函数名称 : Spike_SetMoveAction                                                                                                         
* 功能描述 : 推杆 设置  动作                                     
* 输入参数 : SpikeMoveAction -- 动作                                                                
* 返回参数 : 无                                                                                           
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Spike_SetMoveAction(uint16_t SpikeMoveAction)
{
  SpikeAction_t MoveAction;

  MoveAction.All = SpikeMoveAction;
  Spike_SetBackMove(MoveAction.Bit.BackMove);
  Spike_SetZeroMove(MoveAction.Bit.ZeroMove);
  Spike_SetFeetMove(MoveAction.Bit.FeetMove);
  Spike_SetLegFlexMove(MoveAction.Bit.LegFlexMove);
  Spike_SetULegFlexMove(MoveAction.Bit.ULegFlexMove);
}


/*
************************************************************************************************************************
* 函数名称 : Spike_SetZeroSafetyAngleLimitRef                                                                                                         
* 功能描述 : 推杆 设置  零重力安全角度 限定 判断 参考值                                
* 输入参数 : RefBack -- 参考的背部角度
*            RefZero -- 参考的零重力角度                                                            
* 返回参数 : 无                                                                                           
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Spike_SetZeroSafetyAngleLimitRef(uint8_t RefBack, uint8_t RefZero)
{
  pSpike->ZeroSafetyAngleLimitBackAngele = RefBack;
  pSpike->ZeroSafetyAngleLimitZeroAngele = RefZero;
}


/*
************************************************************************************************************************
* 函数名称 : Spike_SetLegLenDetectSw                                                                                                         
* 功能描述 : 推杆 设置  腿长检测开关                       
* 输入参数 : Sw -- 开关                                                          
* 返回参数 : 无                                                                                           
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Spike_SetLegLenDetectSw(uint8_t Sw)
{
  pSpike->CSFlag.Bit.LegLenDetectSw = (Sw == ON) ? ON : OFF;
}

/*
************************************************************************************************************************
* 函数名称 : Spike_LegLenDetectRedo                                                                                                        
* 功能描述 : 推杆  腿长检测 重做                   
* 输入参数 : 无                                                      
* 返回参数 : 无                                                                                           
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Spike_LegLenDetectRedo(void)
{
  pSpike->LegLenDetectStep = 0;                               
  pSpike->CSFlag.Bit.LegLenDetectFinish = FALSE;  
}

/*
************************************************************************************************************************
* 函数名称 : Spike_SetLegLenDetectExtendMax                                                                                                         
* 功能描述 : 推杆 设置  腿长检测 伸长最大值                      
* 输入参数 : MaxLen -- 伸长最大值                                                          
* 返回参数 : 无                                                                                           
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Spike_SetLegLenDetectExtendMax(uint8_t MaxLen)
{
  pSpike->LegLenDetectExtendMax = MaxLen;
}

/*
************************************************************************************************************************
* 函数名称 : Spike_LegLenDetectPauseOn                                                                                                         
* 功能描述 : 暂停腿长检测                                                                       
* 输入参数 : 无                                                                                
* 返回参数 : 无                                                                                             
* 补充说明 : 如果马达正在运转，则会停止马达的运转。
*            只有解除暂停，马达才能重新运转。                                                                                                      
************************************************************************************************************************
*/
void Spike_LegLenDetectPauseOn(void)
{
  if(pSpike->CSFlag.Bit.LegLenDetectPause < 0x1F)
  {
    pSpike->CSFlag.Bit.LegLenDetectPause++;
  }
}

/*
************************************************************************************************************************
* 函数名称 : Spike_LegLenDetectPauseOff                                                                                                         
* 功能描述 : 解除暂停腿长检测                                                                      
* 输入参数 : 无                                                                                
* 返回参数 : 无                                                                                             
* 补充说明 : 如果马达正在运转，则会停止马达的运转。
*            只有解除暂停，马达才能重新运转。                                                                                                      
************************************************************************************************************************
*/
void Spike_LegLenDetectPauseOff(void)
{
  if(pSpike->CSFlag.Bit.LegLenDetectPause > 0)
  {
    pSpike->CSFlag.Bit.LegLenDetectPause--;
  }
}

/*
************************************************************************************************************************
* 函数名称 : Spike_MoveActionHandle                                                                                                         
* 功能描述 : 推杆  动作  逻辑处理                             
* 输入参数 : ExePeriod -- 执行周期                                                    
* 返回参数 : 无                                                                                           
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Spike_MoveActionHandle(Ticker_t ExePeroid)
{
  /*靠背推杆----------------------------------------------------------*/
  if(pSpike->ActionHis.Bit.BackMove != pSpike->ActionCur.Bit.BackMove)
  {
    pSpike->ActionHis.Bit.BackMove = pSpike->ActionCur.Bit.BackMove;

    if(SPIKE_MOVE_NONE == pSpike->ActionCur.Bit.BackMove)
    {
      pSpike->BackAngleSetVal = PKEEP; /*调节完成后 位置保持*/
    }
  }

  if(SPIKE_MOVE_BACK_UP == pSpike->ActionCur.Bit.BackMove)
  {
    Spike_BackMoveUp();
  }
  else if(SPIKE_MOVE_BACK_DOWN == pSpike->ActionCur.Bit.BackMove)
  {
    Spike_BackMoveDown();
  }
  else //(SPIKE_MOVE_NONE == pSpike->ActionCur.Bit.BackMove)
  {
    if((pSpike->BackAngleSetVal != PKEEP) && (pSpike->ZeroAngleSetVal != PKEEP))
    {
      /*判断零重力时，靠背安全限定角度*/
      if((pSpike->BackAngleSetVal >= pSpike->ZeroSafetyAngleLimitBackAngele) &&
         (pSpike->ZeroAngleSetVal >  pSpike->ZeroSafetyAngleLimitZeroAngele) )
      {
        pSpike->CSFlag.Bit.ReachZeroSafetyAngleLimit = TRUE;
        pSpike->BackAngleSetVal = pSpike->ZeroSafetyAngleLimitBackAngele;
      }
      else
      {
        pSpike->CSFlag.Bit.ReachZeroSafetyAngleLimit = FALSE;
      }     
    }

    BackSpike_SetPosition(pSpike->BackAngleSetVal);
  }


  /*零重力推杆--------------------------------------------------------*/
  if(pSpike->ActionHis.Bit.ZeroMove != pSpike->ActionCur.Bit.ZeroMove)
  {
    pSpike->ActionHis.Bit.ZeroMove = pSpike->ActionCur.Bit.ZeroMove;

    if(SPIKE_MOVE_NONE == pSpike->ActionCur.Bit.ZeroMove)
    {
      pSpike->ZeroAngleSetVal = PKEEP; /*调节完成后 位置保持*/
    }
  }

  if(SPIKE_MOVE_ZERO_UP == pSpike->ActionCur.Bit.ZeroMove)
  {
    Spike_ZeroMoveUp();
  }
  else if(SPIKE_MOVE_ZERO_DOWN == pSpike->ActionCur.Bit.ZeroMove)
  {
    Spike_ZeroMoveDown();
  }
  else //(SPIKE_MOVE_NONE == pSpike->ActionCur.Bit.ZeroMove)
  {
    ZeroSpike_SetPosition(pSpike->BackAngleSetVal);
  }


  /*腿推杆------------------------------------------------------------*/
  if(pSpike->ActionHis.Bit.FeetMove != pSpike->ActionCur.Bit.FeetMove)
  {
    pSpike->ActionHis.Bit.FeetMove = pSpike->ActionCur.Bit.FeetMove;

    if(SPIKE_MOVE_NONE == pSpike->ActionCur.Bit.FeetMove)
    {
      pSpike->FeetAngleSetVal = PKEEP; /*调节完成后 位置保持*/
    }
  }

  if(SPIKE_MOVE_FEET_UP == pSpike->ActionCur.Bit.FeetMove)
  {
    Spike_FeetMoveUp();
  }
  else if(SPIKE_MOVE_FEET_DOWN == pSpike->ActionCur.Bit.FeetMove)
  {
    Spike_FeetMoveDown();
  }
  else //(SPIKE_MOVE_NONE == pSpike->ActionCur.Bit.BackMove)
  {
    FeetSpike_SetPosition(pSpike->FeetAngleSetVal);
  }


  /*小腿伸缩推杆------------------------------------------------------*/
  if(pSpike->ActionHis.Bit.LegFlexMove != pSpike->ActionCur.Bit.LegFlexMove)
  {
    pSpike->ActionHis.Bit.LegFlexMove = pSpike->ActionCur.Bit.LegFlexMove;

    if(SPIKE_MOVE_NONE == pSpike->ActionCur.Bit.LegFlexMove)
    {
      pSpike->LegFlexAngleSetVal = PKEEP; /*调节完成后 位置保持*/
    }
  }
  
  if((SPIKE_MOVE_LEG_SHORT == pSpike->ActionCur.Bit.LegFlexMove) ||
     (PLEGFLEX_MIN == pSpike->LegFlexAngleSetVal))
  {
    Spike_LegFlexMoveShorten();
    if((LegFlexSpike_GetCSFlag().Bit.TouchFeet)       || 
       (LegFlexSpike_GetCSFlag().Bit.ReachShortenLimt))
    {
      pSpike->ActionCur.Bit.LegFlexMove = SPIKE_MOVE_NONE;
      pSpike->LegFlexAngleSetVal = PKEEP; /*调节完成后 位置保持*/
    }
  }
  else if((SPIKE_MOVE_LEG_EXTEND == pSpike->ActionCur.Bit.LegFlexMove) ||
          (PLEGFLEX_MAX == pSpike->LegFlexAngleSetVal))
  {
    Spike_LegFlexMoveExtend();
    if((LegFlexSpike_GetCSFlag().Bit.TouchGround)    || 
       (LegFlexSpike_GetCSFlag().Bit.ReachExtendLimt))
    {
      pSpike->ActionCur.Bit.LegFlexMove = SPIKE_MOVE_NONE;
      pSpike->LegFlexAngleSetVal = PKEEP; /*调节完成后 位置保持*/
    }
  }
  else //(SPIKE_MOVE_BACK_DOWN == pSpike->ActionCur.Bit.LegFlexMove)
  {
    LegFlexSpike_SetPosition(pSpike->LegFlexAngleSetVal);
  }
  
  
  /*腿长自动检测-------------------------*/
  if(TRUE == FeetSpike_GetCSFlag().Bit.Run)
  {
    pSpike->LegLenDetectStep = 0;                                 /*小腿升降有运动，则需要重新检测腿长，复位其步骤*/
    pSpike->CSFlag.Bit.LegLenDetectFinish = FALSE;  
    if(TRUE == pSpike->CSFlag.Bit.LegLenDetectRun)
    {
      Spike_LegFlexMoveStop();
      pSpike->CSFlag.Bit.LegLenDetectRun = FALSE; 
    }
  }
  else
  {
    if(ON == pSpike->CSFlag.Bit.LegLenDetectSw)                     /*检测开关有效*/
    {
      if((Spike_GetBackAngle() > PBACK_LEG_LEN_DETECT_ANGLE) ||     /*检测角度满足*/
         (Spike_GetFeetAngle() > PFEET_LEG_LEN_DETECT_ANGLE) ||     /*检测角度满足*/
         (Spike_GetZeroAngle() > PZERO_LEG_LEN_DETECT_ANGLE) )      /*检测角度满足*/
      {
        if((FALSE == BackSpike_GetCSFlag().Bit.Run) &&              /*推杆的运动停止*/
           (FALSE == FeetSpike_GetCSFlag().Bit.Run) &&
           (FALSE == ZeroSpike_GetCSFlag().Bit.Run) )
        {
          if(0 == pSpike->CSFlag.Bit.LegLenDetectPause)
          {
            if(0 == pSpike->LegLenDetectStep)                         /*先伸*/
            {
              pSpike->CSFlag.Bit.LegLenDetectRun = TRUE;                
              //Spike_LegFlexMoveExtend();
              LegFlexSpike_SetPosition(pSpike->LegLenDetectExtendMax);
              if((LegFlexSpike_GetCSFlag().Bit.TouchGround)    || 
                 (LegFlexSpike_GetCSFlag().Bit.ReachExtendLimt)||
                 (LegFlexSpike_GetPosition() == pSpike->LegLenDetectExtendMax))
              {
                pSpike->LegLenDetectStep = 1;
              }
            }
            else if(1 == pSpike->LegLenDetectStep)                    /*后缩*/
            {
              pSpike->CSFlag.Bit.LegLenDetectRun = TRUE;                
              Spike_LegFlexMoveShorten();
              if((LegFlexSpike_GetCSFlag().Bit.TouchFeet)       || 
                 (LegFlexSpike_GetCSFlag().Bit.ReachShortenLimt))
              {
                pSpike->LegLenDetectStep = 2;
              }
            }
            else if(2 == pSpike->LegLenDetectStep)                    /*检测完成*/
            {
              pSpike->CSFlag.Bit.LegLenDetectRun = FALSE;                
              Spike_LegFlexMoveStop();
              pSpike->LegFlexAngleSetVal = PKEEP;                     /*调节完成后 位置保持*/
              pSpike->LegLenDetectStep = 3;
              pSpike->CSFlag.Bit.LegLenDetectFinish = TRUE;  
            }
          }
        }
      }
    }
    else
    {
      pSpike->LegLenDetectStep = 3;
    }
  }
  
  /*降腿、升背、降零重力时， 若小腿触地，此时需将小腿缩回*/
  if(((FEETSPIKE_DIRECTION_DOWN == FeetSpike_GetCSFlag().Bit.Direction) && (ON == FeetSpike_GetCSFlag().Bit.Run)) || 
     ((BACKSPIKE_DIRECTION_UP   == BackSpike_GetCSFlag().Bit.Direction) && (ON == BackSpike_GetCSFlag().Bit.Run)) || 
     ((ZEROSPIKE_DIRECTION_DOWN == ZeroSpike_GetCSFlag().Bit.Direction) && (ON == ZeroSpike_GetCSFlag().Bit.Run)) ) 
  {
    if(TRUE == LegFlexSpike_GetCSFlag().Bit.TouchGround)          /*触地后，降腿、升背、降零重力会有风险，开启保护*/
    {
      pSpike->CSFlag.Bit.LegTouchGroundProtectRun = ON;
    }
  }
  if((FALSE == LegFlexSpike_GetCSFlag().Bit.TouchGround)     ||   /*没有触地*/
     (TRUE  == LegFlexSpike_GetCSFlag().Bit.ReachShortenLimt))    /*已经完全缩回*/
  {
    pSpike->CSFlag.Bit.LegTouchGroundProtectRun = OFF;            /*关闭保护*/
  }
  if(ON == pSpike->CSFlag.Bit.LegTouchGroundProtectRun)
  {
    Spike_LegFlexMoveShorten();
  }
  

  /*上小腿伸缩推杆------------------------------------------------------*/
  if(pSpike->ActionHis.Bit.ULegFlexMove != pSpike->ActionCur.Bit.ULegFlexMove)
  {
    pSpike->ActionHis.Bit.ULegFlexMove = pSpike->ActionCur.Bit.ULegFlexMove;

    if(SPIKE_MOVE_NONE == pSpike->ActionCur.Bit.ULegFlexMove)
    {
      pSpike->ULegFlexAngleSetVal = PKEEP; /*调节完成后 位置保持*/
    }
  }
  
  if(SPIKE_MOVE_LEG_SHORT == pSpike->ActionCur.Bit.ULegFlexMove)
  {
    Spike_ULegFlexMoveShorten();
    if( LegFlexSpike_GetCSFlag().Bit.ULegReachShortenLimt )
    {
      pSpike->ActionCur.Bit.ULegFlexMove = SPIKE_MOVE_NONE;
      pSpike->ULegFlexAngleSetVal = PKEEP; /*调节完成后 位置保持*/
    }
  }
  else if(SPIKE_MOVE_LEG_EXTEND == pSpike->ActionCur.Bit.ULegFlexMove)
  {
    Spike_ULegFlexMoveExtend();
    if( LegFlexSpike_GetCSFlag().Bit.ULegReachExtendLimt )
    {
      pSpike->ActionCur.Bit.ULegFlexMove = SPIKE_MOVE_NONE;
      pSpike->ULegFlexAngleSetVal = PKEEP; /*调节完成后 位置保持*/
    }
  }
  else //(SPIKE_MOVE_BACK_DOWN == pSpike->ActionCur.Bit.ULegFlexMove)
  {
    LegFlexSpike_SetULegPosition(pSpike->ULegFlexAngleSetVal);
  }  
}

/*
************************************************************************************************************************
* 函数名称 : Spike_ResetHandle                                                                                                         
* 功能描述 : 推杆芯片 复位 逻辑处理                             
* 输入参数 : ExePeriod -- 执行周期                                                    
* 返回参数 : 无                                                                                           
* 补充说明 : 检测到4959报错引脚电平有效就给芯片reset脚一个低电平脉冲进行复位                                                                                                        
************************************************************************************************************************
*/
void Spike_ResetHandle(Ticker_t ExePeroid)
{
  static uint8_t BackFaultState,BackResetSucess,FeetFaultState,FeetResetSucess;
  uint8_t BackMotoFault,FeetMotoFault;

  BackMotoFault = BSP_IO_ReadInput_BackMotoFault();
  
  if( (0 == BackMotoFault) && (FALSE == BackFaultState) )
  {
    BackFaultState = TRUE;
  }

  if(TRUE == BackFaultState)
  {
    if(0 == BackResetSucess)
    {
      BSP_IO_4959_BackReset(TRUE);
      BackResetSucess = 1;
    }
    else//if(1 == BackResetSucess)
    {
      BSP_IO_4959_BackReset(FALSE);
      BackResetSucess = 0;
      BackFaultState = FALSE;
    }
  }
  
  FeetMotoFault = BSP_IO_ReadInput_FeetMotoFault();
  
  if( (0 == FeetMotoFault) && (FALSE == FeetFaultState) )
  {
    FeetFaultState = TRUE;
  }

  if(TRUE == FeetFaultState)
  {
    if(0 == FeetResetSucess)
    {
      BSP_IO_4959_FeetReset(TRUE);
      FeetResetSucess = 1;
    }
    else//if(1 == FeetResetSucess)
    {
      BSP_IO_4959_FeetReset(FALSE);
      FeetResetSucess = 0;
      FeetFaultState = FALSE;
    }
  }
  
}
/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
/*〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓*/
/*
========================================================================================================================
*         推杆功能函数表                           推杆功能函数表                           推杆功能函数表
========================================================================================================================
*/
#define  SPIKE_TICK_COUNT_BUF_NUM   17

static Ticker_t Spike_TickCount[SPIKE_TICK_COUNT_BUF_NUM];
static const ESF_TmrExeFunc_t  Spike_TmrExeFuncTab[] = 
{
  /*   执行函数                   执行周期      时间计数变量*/
  {Spike_MoveActionHandle,           47,       &Spike_TickCount[0]},

  //{BackSpike_OverCurrentIOCheck,     91,       &Spike_TickCount[1]},  /*过电流*/
  {BackSpike_PositionHandle,         31,       &Spike_TickCount[2]},  /*位置处理*/
  {BackSpike_PositionIOCheck,        7,        &Spike_TickCount[3]},  /*位置IO*/
  {BackSpike_ActionHandle,           25,       &Spike_TickCount[4]},  /*动作*/ 
  
  //{FeetSpike_OverCurrentIOCheck,     92,       &Spike_TickCount[5]},  /*过电流*/
  {FeetSpike_PositionHandle,         32,       &Spike_TickCount[6]},  /*位置处理*/
  {FeetSpike_PositionIOCheck,        7,        &Spike_TickCount[7]},  /*位置IO*/
  {FeetSpike_ActionHandle,           26,       &Spike_TickCount[8]},   /*动作*/ 
 
//  {ZeroSpike_OverCurrentIOCheck,     93,       &Spike_TickCount[9]},  /*过电流*/
//  {ZeroSpike_PositionHandle,         33,       &Spike_TickCount[10]}, /*位置处理*/
//  {ZeroSpike_PositionIOCheck,        7,        &Spike_TickCount[11]}, /*位置IO*/
//  {ZeroSpike_ActionHandle,           27,       &Spike_TickCount[12]}, /*动作*/ 
//  
  {LegFlexSpike_PositionHandle,      34,       &Spike_TickCount[13]}, /*位置处理*/ 
  {LegFlexSpike_IOCheck,             7,        &Spike_TickCount[14]}, /*IO*/
  {LegFlexSpike_ActionHandle,        28,       &Spike_TickCount[15]},  /*动作*/ 
  
  {Spike_ResetHandle,                 9,       &Spike_TickCount[16]}  /*4959复位处理 */
};

#define  SPIKE_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(Spike_TmrExeFuncTab)

/*
************************************************************************************************************************
* 函数名称 : Spike_Handle                                                                                                         
* 功能描述 : 推杆 处理                
* 输入参数 : 无                                            
* 返回参数 : 无                                                                        
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
void Spike_Handle(void)
{
  /*要比较实时地开启转速检测IO口的中断。因此这三个函数不放在时间片里执行。*/
  BSP_IO_EnableInputInterrupt_BackSpikeCount();
  BSP_IO_EnableInputInterrupt_FeetSpikeCount();
  BSP_IO_EnableInputInterrupt_ZeroSpikeCount();

  /*调度功能函数表------------------------------------------------*/
  ESF_TmrExeFuncScheduling(Spike_TmrExeFuncTab, SPIKE_TMR_EXE_FUNC_TAB_NUM);
}


/*
************************************************************************************************************************
* 函数名称 : Spike_Init                                                                                                         
* 功能描述 : 推杆 初始化                 
* 输入参数 : 无                                            
* 返回参数 : 返回 可操作推杆功能 的结构体 的指针                                                                               
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
Spike_t* Spike_Init(void)
{
  /*初始化相关数据------------------------------------------*/
  memset(pSpike, 0, sizeof(Spike_t)); /*清零所有数据*/

  pSpike->ZeroSafetyAngleLimitBackAngele = PBACK12;
  pSpike->ZeroSafetyAngleLimitZeroAngele = PZERO10;

  /*推杆部件------------------------------------------------*/
  pSpike->pBackSpike    = BackSpike_Init();
  pSpike->pFeetSpike    = FeetSpike_Init();
  pSpike->pZeroSpike    = ZeroSpike_Init();
  pSpike->pLegFlexSpike = LegFlexSpike_Init();

  /*为防止错误的修改，在此检测功能函数表是否正确------------------------------*/
  ESF_TmrExeFuncTabCheck(Spike_TmrExeFuncTab, SPIKE_TMR_EXE_FUNC_TAB_NUM, SPIKE_TICK_COUNT_BUF_NUM);

  return pSpike;
}

/*
************************************************************************************************************************
* 函数名称 : Spike_GetCSFlag                                                                                                         
* 功能描述 : 获得 控制 与 状态 标识                        
* 输入参数 : 无                                            
* 返回参数 : 控制与状态标识 的结构体                                                                                           
* 补充说明 : 无                                                                                                         
************************************************************************************************************************
*/
SpikeCSFlag_t Spike_GetCSFlag(void)
{
  return pSpike->CSFlag;
}
