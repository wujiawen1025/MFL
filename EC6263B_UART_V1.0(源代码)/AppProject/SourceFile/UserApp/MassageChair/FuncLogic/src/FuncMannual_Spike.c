/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ����ƣ�FuncMannual_Spike.c 
**
**    ��������:���Ƹˡ��ֶ�
**
**    ��    ˾���ɷ�������
**
**    ��Ŀ���ƣ�
**
**    ƽ̨��Ϣ��
**
**    ��    �ߣ�Hzy
**
**    ����˵��:	
**
**    �޸ļ�¼:  --------------------------------------------------------------
**
========================================================================================================================
========================================================================================================================
*/

/*
========================================================================================================================
* ���ļ�������                                         ���ļ�������                                          ���ļ�������
========================================================================================================================
*/
#include "FuncLogic.h"
#include "MChair.h"


/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/


/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/


/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                         ���������� & ����������    
========================================================================================================================
*/


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : MChair_FuncSwitch_SpikeMannual                                                                                               
* �������� : ��Ħ�� �����л� ֮  ���Ƹˡ��ֶ�                                                                              
* ������� : SwitchMode -- Ҫ�л�ģʽ
*            pFuncLogic -- �����߼�������                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
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
* �������� : MChair_FuncExe_SpikeMannual                                                                                               
* �������� : ��Ħ�� ����ִ�� ֮  ���Ƹˡ��ֶ�                                                                              
* ������� : ExePeriod  -- ִ������
*            pFuncLogic -- ָ���������߼���ָ�롣                                                                                      
* ���ز��� : ��                                                                                              
* ����˵�� : ��                                                           
************************************************************************************************************************
*/
void MChair_FuncExe_SpikeMannual(Ticker_t ExePeriod, FuncLogic_t *pFuncLogic)
{
  SpikeAction_t SpikeActionCur;
  
  SpikeActionCur.All = *pFuncLogic->pFuncCur;

  pMChair->ComponentFuncState.Bit.Spike = FUNC_TYPE_MANNUAL;     /*�Ƹ˹���״̬���ֶ�*/
  Spike_SetAngle(PKEEP, PKEEP, PKEEP);                           /*ֹͣ�Ƹ�*/
  
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)                   /*�Ƹ�Ϊ�̰�*/
  
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
