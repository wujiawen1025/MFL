/*
========================================================================================================================
**【文件描述】                                        【文件描述】                                        【文件描述】**
========================================================================================================================
**    文件名称：FuncMannual_Spike.c 
**
**    功能描述:【推杆】手动
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


/*
========================================================================================================================
*【函数定义】                                          【函数定义】                                          【函数定义】
========================================================================================================================
*/
/*
************************************************************************************************************************
* 函数名称 : MChair_FuncSwitch_SpikeMannual                                                                                               
* 功能描述 : 按摩椅 功能切换 之  【推杆】手动                                                                              
* 输入参数 : SwitchMode -- 要切换模式
*            pFuncLogic -- 功能逻辑的描述                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncSwitch_SpikeMannual(uint8_t SwitchMode, FuncLogic_t *pFuncLogic)
{
  SpikeAction_t SpikeActionCur;
  SpikeAction_t SpikeActionHis;
  
  SpikeActionCur.All = *pFuncLogic->pFuncCur;
  SpikeActionHis.All = *pFuncLogic->pFuncHis;
  
  if(SpikeActionCur.Bit.BackMove != SpikeActionHis.Bit.BackMove)   
  {
    Spike_SetBackMove(SpikeActionCur.Bit.BackMove);
  }
  if(SpikeActionCur.Bit.FeetMove != SpikeActionHis.Bit.FeetMove)   
  {
    Spike_SetFeetMove(SpikeActionCur.Bit.FeetMove);
  }
  if(SpikeActionCur.Bit.LegFlexMove != SpikeActionHis.Bit.LegFlexMove)   
  {
    Spike_SetLegFlexMove(SpikeActionCur.Bit.LegFlexMove);
  }
  if(SpikeActionCur.Bit.ULegFlexMove != SpikeActionHis.Bit.ULegFlexMove)   
  {
    Spike_SetULegFlexMove(SpikeActionCur.Bit.ULegFlexMove);
  }

  if(OPEN == SwitchMode)
  {
    MChair_SetFuncAutoSpike(FA_SPIKE_NONE, FALSE);
    //Spike_SetMoveAction(pMChair->FuncMannual_Spike.All);
  }
//  else// if(CLOSE == SwitchMode)
//  {
//    Spike_SetMoveAction(SPIKE_MOVE_NONE);
//  }
}

/*
************************************************************************************************************************
* 函数名称 : MChair_FuncExe_SpikeMannual                                                                                               
* 功能描述 : 按摩椅 功能执行 之  【推杆】手动                                                                              
* 输入参数 : ExePeriod  -- 执行周期
*            pFuncLogic -- 指向自身功能逻辑的指针。                                                                                      
* 返回参数 : 无                                                                                              
* 补充说明 : 无                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_SpikeMannual(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  SpikeAction_t SpikeActionCur;
  
  SpikeActionCur.All = *pFuncLogic->pFuncCur;

  pMChair->ComponentFuncState.Bit.Spike = FUNC_TYPE_MANNUAL;     /*推杆功能状态：手动*/
  Spike_SetAngle(PKEEP, PKEEP, PKEEP);                           /*停止推杆*/
  
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)                   /*推杆为短按*/
  
  if((TRUE == pMChair->StateBackSpike.Bit.ReachDownLimt)              &&
     (SPIKE_MOVE_BACK_DOWN == pMChair->FuncMannual_Spike.Bit.BackMove))
  {
    pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;    
  }
  else if((TRUE == pMChair->StateBackSpike.Bit.ReachUpLimt)              &&
          (SPIKE_MOVE_BACK_UP == pMChair->FuncMannual_Spike.Bit.BackMove))
  {
    pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;    
  }
  
  if((TRUE == pMChair->StateFeetSpike.Bit.ReachDownLimt)              &&
     (SPIKE_MOVE_FEET_DOWN == pMChair->FuncMannual_Spike.Bit.FeetMove))
  {
    pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;    
  }
  else if((TRUE == pMChair->StateFeetSpike.Bit.ReachUpLimt)              &&
          (SPIKE_MOVE_FEET_UP == pMChair->FuncMannual_Spike.Bit.FeetMove))
  {
    pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;    
  }  
  
  if(SPIKE_MOVE_LEG_EXTEND == pMChair->FuncMannual_Spike.Bit.LegFlexMove)
  {
    if((TRUE == pMChair->StateLegFlexSpike.Bit.ReachExtendLimt) || 
       (TRUE == pMChair->StateLegFlexSpike.Bit.TouchGround)     )   
    {
      pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_NONE;    
    }
  }
  else if(SPIKE_MOVE_LEG_SHORT == pMChair->FuncMannual_Spike.Bit.LegFlexMove)
  {
    if((TRUE == pMChair->StateLegFlexSpike.Bit.ReachShortenLimt) || 
       (TRUE == pMChair->StateLegFlexSpike.Bit.TouchFeet)     )   
    {
      pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_NONE;    
    }
  }   

  if((TRUE == pMChair->StateLegFlexSpike.Bit.ULegReachExtendLimt)          &&
     (SPIKE_MOVE_LEG_EXTEND == pMChair->FuncMannual_Spike.Bit.ULegFlexMove))
  {
    pMChair->FuncMannual_Spike.Bit.ULegFlexMove = SPIKE_MOVE_NONE;    
  }
  else if((TRUE == pMChair->StateLegFlexSpike.Bit.ULegReachShortenLimt)        &&
          (SPIKE_MOVE_LEG_SHORT == pMChair->FuncMannual_Spike.Bit.ULegFlexMove))
  {
    pMChair->FuncMannual_Spike.Bit.ULegFlexMove = SPIKE_MOVE_NONE;    
  }   
  #endif 
  
//  Spike_SetMoveAction(pMChair->FuncMannual_Spike.All);
  if(SpikeActionCur.Bit.BackMove)   
  {
    Spike_SetBackMove(SpikeActionCur.Bit.BackMove);
  }
  if(SpikeActionCur.Bit.FeetMove)   
  {
    Spike_SetFeetMove(SpikeActionCur.Bit.FeetMove);
  }
  if(SpikeActionCur.Bit.LegFlexMove)   
  {
    Spike_SetLegFlexMove(SpikeActionCur.Bit.LegFlexMove);
  }
  if(SpikeActionCur.Bit.ULegFlexMove)   
  {
    Spike_SetULegFlexMove(SpikeActionCur.Bit.ULegFlexMove);
  }
}
