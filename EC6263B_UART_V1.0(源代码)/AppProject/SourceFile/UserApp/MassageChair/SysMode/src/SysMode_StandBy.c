/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: SysMode_StandBy.c 
**
**    ��������: ϵͳģʽ ֮  ����
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
#include "SysMode.h"


/*
========================================================================================================================
*�����غ궨�塿                                       �����غ궨�塿                                       �����غ궨�塿
========================================================================================================================
*/
#pragma  diag_suppress 177            /*����mdk�У�����������û�����õĸ澯*/


/*
========================================================================================================================
*�������������Ͷ��塿                              �������������Ͷ��塿                              �������������Ͷ��塿
========================================================================================================================
*/
static Ticker_t  EngiModeSelcetTL;    /*����ģʽѡ��ʱ�䳤��*/

/*
========================================================================================================================
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : SysMode_StandBy_EngineeringModeSelcetTLHandle                                                                                                         
* �������� : ����ģʽѡ��ʱ�䳤�ȴ���                                                                                   
* ������� : ExePeriod -- ����ִ������                                                                                       
* ���ز��� : ��                                                                
* ����˵�� : ��                                                                                                         
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
* �������� : StandBy_Key_NoKeyPress                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                 
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_NoKeyPress(uint8_t *pData)
{
  /*�����������ͷŴ���------------------------------*/
  Core_SetMoveAdjustRoll(CORE_MOVE_ADJUST_NONE);                    /*��о���µ��� �ĳ����ͷ�*/

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)                       /*�Ƹ�Ϊ����*/
    pMChair->FuncMannual_Spike.Bit.BackMove     = SPIKE_MOVE_NONE;  /*�������Ƹ� �ĳ����ͷ�*/
    pMChair->FuncMannual_Spike.Bit.BackMove     = SPIKE_MOVE_NONE;  /*�����Ƹ� �ĳ����ͷ�*/
    pMChair->FuncMannual_Spike.Bit.FeetMove     = SPIKE_MOVE_NONE;  /*С���Ƹ� �ĳ����ͷ�*/
    pMChair->FuncMannual_Spike.Bit.LegFlexMove  = SPIKE_MOVE_NONE;  /*С�������Ƹ� �ĳ����ͷ�*/
    pMChair->FuncMannual_Spike.Bit.ULegFlexMove = SPIKE_MOVE_NONE;  /*��С�������Ƹ� �ĳ����ͷ�*/
  #endif

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : StandBy_Key_Power                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                 
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_Power(uint8_t *pData)
{
  return SysMode_UserRun_Enter();
}

/*
************************************************************************************************************************
* �������� : StandBy_Key_Pause                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
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
* �������� : StandBy_Key_SpikeBackUp                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                 
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
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

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*�Ƹ�Ϊ����*/
    if(SPIKE_MOVE_BACK_UP == pMChair->FuncMannual_Spike.Bit.BackMove)
    {
      return FAIL; /*�ö����Ѿ���ִ���ˣ�û��Ҫ�ٴθ�ֵ*/
    }
    pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
    pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_BACK_UP;
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*�Ƹ�Ϊ�̰�*/
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
* �������� : StandBy_Key_SpikeBackDown                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                 
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
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

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*�Ƹ�Ϊ����*/
    if(SPIKE_MOVE_BACK_DOWN == pMChair->FuncMannual_Spike.Bit.BackMove)
    {
      return FAIL; /*�ö����Ѿ���ִ���ˣ�û��Ҫ�ٴθ�ֵ*/
    }
    pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
    pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_BACK_DOWN;
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*�Ƹ�Ϊ�̰�*/
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
* �������� : StandBy_Key_SpikeFeetUp                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                 
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
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

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*�Ƹ�Ϊ����*/
    if(SPIKE_MOVE_FEET_UP == pMChair->FuncMannual_Spike.Bit.FeetMove)
    {
      return FAIL; /*�ö����Ѿ���ִ���ˣ�û��Ҫ�ٴθ�ֵ*/
    }
    pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;
    pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_FEET_UP;
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*�Ƹ�Ϊ�̰�*/
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
* �������� : StandBy_Key_SpikeFeetDown                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                 
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
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

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*�Ƹ�Ϊ����*/
    if(SPIKE_MOVE_FEET_DOWN == pMChair->FuncMannual_Spike.Bit.FeetMove)
    {
      return FAIL; /*�ö����Ѿ���ִ���ˣ�û��Ҫ�ٴθ�ֵ*/
    }
    pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;
    pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_FEET_DOWN;
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*�Ƹ�Ϊ�̰�*/
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
* �������� : StandBy_Key_SpikeBackUpFeetDown                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                 
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
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

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*�Ƹ�Ϊ����*/
    if((SPIKE_MOVE_BACK_UP   == pMChair->FuncMannual_Spike.Bit.BackMove) && 
       (SPIKE_MOVE_FEET_DOWN == pMChair->FuncMannual_Spike.Bit.FeetMove) ) 
    {
      return FAIL; /*�ö����Ѿ���ִ���ˣ�û��Ҫ�ٴθ�ֵ*/
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
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*�Ƹ�Ϊ�̰�*/
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
* �������� : StandBy_Key_SpikeBackDownFeetUp                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                 
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
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

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*�Ƹ�Ϊ����*/
    if((SPIKE_MOVE_BACK_DOWN == pMChair->FuncMannual_Spike.Bit.BackMove) && 
       (SPIKE_MOVE_FEET_UP   == pMChair->FuncMannual_Spike.Bit.FeetMove) ) 
    {
      return FAIL; /*�ö����Ѿ���ִ���ˣ�û��Ҫ�ٴθ�ֵ*/
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
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*�Ƹ�Ϊ�̰�*/
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
* �������� : StandBy_Key_SpikeLegExtend                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
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

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*�Ƹ�Ϊ����*/
    if(SPIKE_MOVE_LEG_EXTEND == pMChair->FuncMannual_Spike.Bit.LegFlexMove)
    {
      return FAIL; /*�ö����Ѿ���ִ���ˣ�û��Ҫ�ٴθ�ֵ*/
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_LEG_EXTEND;
    }  
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*�Ƹ�Ϊ�̰�*/
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
* �������� : StandBy_Key_SpikeLegShorten                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
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

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*�Ƹ�Ϊ����*/
    if(SPIKE_MOVE_LEG_SHORT == pMChair->FuncMannual_Spike.Bit.LegFlexMove)
    {
      return FAIL; /*�ö����Ѿ���ִ���ˣ�û��Ҫ�ٴθ�ֵ*/
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_LEG_SHORT;
    }  
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*�Ƹ�Ϊ�̰�*/
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
* �������� : StandBy_Key_SpikeULegExtend                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
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

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*�Ƹ�Ϊ����*/
    if(SPIKE_MOVE_LEG_EXTEND == pMChair->FuncMannual_Spike.Bit.ULegFlexMove)
    {
      return FAIL; /*�ö����Ѿ���ִ���ˣ�û��Ҫ�ٴθ�ֵ*/
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.ULegFlexMove = SPIKE_MOVE_LEG_EXTEND;
    }  
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*�Ƹ�Ϊ�̰�*/
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
* �������� : StandBy_Key_SpikeULegShorten                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
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

  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_LONG)         /*�Ƹ�Ϊ����*/
    if(SPIKE_MOVE_LEG_SHORT == pMChair->FuncMannual_Spike.Bit.ULegFlexMove)
    {
      return FAIL; /*�ö����Ѿ���ִ���ˣ�û��Ҫ�ٴθ�ֵ*/
    }
    else
    {
      pMChair->FuncMannual_Spike.Bit.ULegFlexMove = SPIKE_MOVE_LEG_SHORT;
    }  
  #endif
    
  #if (SPIKE_KEY_MODE == SPIKE_KEY_MODE_SHORT)        /*�Ƹ�Ϊ�̰�*/
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
* �������� : StandBy_Key_SpikeZeroGravity1                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeZeroGravity1(uint8_t *pData)
{
  if(TRUE == pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable)
  {
    return FAIL; 
  }
  
  if((FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Spike) && 
     (FALSE == pMChair->CSFlag.Bit.ZeroGravityAngleRun)        ) /*û�ڵ���������*/
  {
    return FAIL; /*�Ƹ˹������Զ������У����������ڵ��Զ�������⣩����������������Ч*/
  }

  pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;/*ͣ�������Ƹ˵��˶�*/
  pMChair->FuncMannual_Spike.Bit.ZeroMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_NONE;

  /*�߼�˳��������1-->�ޣ� ��ִֵ��ʱ���ж��Ƿ���������1�ĽǶ�ֵ*/
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
* �������� : StandBy_Key_SpikeZeroGravity2                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeZeroGravity2(uint8_t *pData)
{
  if(TRUE == pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable)
  {
    return FAIL; 
  }
  
  if((FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Spike) && 
     (FALSE == pMChair->CSFlag.Bit.ZeroGravityAngleRun)        ) /*û�ڵ���������*/
  {
    return FAIL; /*�Ƹ˹������Զ������У����������ڵ��Զ�������⣩����������������Ч*/
  }

  pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;/*ͣ�������Ƹ˵��˶�*/
  pMChair->FuncMannual_Spike.Bit.ZeroMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_NONE;

  /*�߼�˳��������2-->�ޣ� ��ִֵ��ʱ���ж��Ƿ���������2�ĽǶ�ֵ*/
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
* �������� : StandBy_Key_SpikeZeroGravity                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeZeroGravity(uint8_t *pData)
{
  if(TRUE == pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable)
  {
    return FAIL; 
  }

  if((FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Spike) && 
     (FALSE == pMChair->CSFlag.Bit.ZeroGravityAngleRun)        ) /*û�ڵ���������*/
  {
    return FAIL; /*�Ƹ˹������Զ������У����������ڵ��Զ�������⣩����������������Ч*/
  }

  pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;/*ͣ�������Ƹ˵��˶�*/
  pMChair->FuncMannual_Spike.Bit.ZeroMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_NONE;

  /*�߼�˳��������2-->������1�� ��ִֵ��ʱ���ж��Ƿ���������2�ĽǶ�ֵ*/
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
* �������� : StandBy_Key_SpikeHomeReset                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t StandBy_Key_SpikeHomeReset(uint8_t *pData)
{
  if(TRUE == pMChair->CSFlag.Bit.ZeroSpikeMannualMoveDisable)
  {
    return FAIL; 
  }
  
  if((FUNC_TYPE_AUTO == pMChair->ComponentFuncState.Bit.Spike) && 
     (FALSE == pMChair->CSFlag.Bit.ZeroGravityAngleRun)        ) /*û�ڵ���������*/
  {
    return FAIL; /*�Ƹ˹������Զ������У����������ڵ��Զ�������⣩����������������Ч*/
  }

  pMChair->FuncMannual_Spike.Bit.BackMove = SPIKE_MOVE_NONE;/*ͣ�������Ƹ˵��˶�*/
  pMChair->FuncMannual_Spike.Bit.ZeroMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.FeetMove = SPIKE_MOVE_NONE;
  pMChair->FuncMannual_Spike.Bit.LegFlexMove = SPIKE_MOVE_NONE;

  /*�߼�˳�򣺸�λ�Ƕ�-->�ޣ� ��ִֵ��ʱ���ж��Ƿ��ڸ�λ�Ƕ�*/
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
* �������� : StandBy_EnterSysModeVender                                                                                                         
* �������� : ���볧��ģ                                                                                    
* ������� : pData         -- ��ֵ���������������� 
*            SysModeVender -- Ҫ����ĳ���ģʽ
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_EnterSysModeVender(uint8_t *pData, uint8_t SysModeVender)
{
  if((0 == EngiModeSelcetTL)   ||                /*ѡ�����ʱ����Ч*/
     (EngiModeSelcetTL > 24000))                 /*��ֹ��ϼ��ͷ�ʱ�Ķ���*/
  {
    return FAIL;
  }

  pMChair->SysModeCur    = SysModeVender;    /*������Ӧ�ĳ���ģʽ*/
  pMChair->SysModeHis    = SYS_MODE_STANDBY;  
  pMChair->SysModeVender = SYS_MODE_NONE;       
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : StandBy_Key_InspectAuto                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_InspectAuto(uint8_t *pData)
{
  return StandBy_EnterSysModeVender(pData, SYS_MODE_INSPECTAUTO);
}

/*
************************************************************************************************************************
* �������� : StandBy_Key_InspectManual                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_InspectManual(uint8_t *pData)
{
  return StandBy_EnterSysModeVender(pData, SYS_MODE_INSPECTMANUAL);
}

/*
************************************************************************************************************************
* �������� : StandBy_Key_PackingAngle                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_PackingAngle(uint8_t *pData)
{
  return StandBy_EnterSysModeVender(pData, SYS_MODE_PACKING);
}

/*
************************************************************************************************************************
* �������� : StandBy_Key_TestNoTimer                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_TestNoTimer(uint8_t *pData)
{
  return StandBy_EnterSysModeVender(pData, SYS_MODE_TESTNOTIMER);
}

/*
************************************************************************************************************************
* �������� : StandBy_Key_TestAge                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_TestAge(uint8_t *pData)
{
  return StandBy_EnterSysModeVender(pData, SYS_MODE_TESTAGE);
}

/*
************************************************************************************************************************
* �������� : StandBy_Key_TestSpike                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_TestSpike(uint8_t *pData)
{
  return StandBy_EnterSysModeVender(pData, SYS_MODE_TESTSPIKE);
}

/*
************************************************************************************************************************
* �������� : StandBy_Key_TestOther1                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_TestOther1(uint8_t *pData)
{
  return StandBy_EnterSysModeVender(pData, SYS_MODE_TESTOTHER1);
}

/*
************************************************************************************************************************
* �������� : StandBy_Key_EngiModeSelect                                                                                                         
* �������� :                                                                                     
* ������� : pData -- ��ֵ����������������                                                                                  
* ���ز��� : SUCCESS -- ��ִֵ�гɹ�     FAIL -- ��ִֵ��ʧ��                                                                  
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
static uint8_t StandBy_Key_EngiModeSelect(uint8_t *pData)
{
  EngiModeSelcetTL = 25000;    /*����ģʽѡ�� ����ʱ��*/
  return SUCCESS;
}

/*����������������������������������������������������������������������������������������������������������������������*/

static const SysMode_KeyLogicTabItem_t StandBy_KeyLogicTab[] = /*��ֵ��*/
{
  /*���Ӳ�����

    ��ִֵ��ǰ��bit7 -- 1��ERP����Դ�رգ����ִֵ��ǰ��Ҫ���¿�����    
                        0��ERP����Դ�رգ����ִֵ��ǰ������Ҫ���¿�����    
    ��ִֵ��ǰ��bit6 -- 1����ͣ�������Կ�ִ�м�ֵ��  
                        0����ͣ���������ֵ��ִ�С�
    ��ִֵ�к�                                                   */

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

  /*����ģʽ���л�------------------------------------------------------------------*/
  {KEYVAL_InspectAuto,              B(00000000),    StandBy_Key_InspectAuto},           /*ϵͳģʽ�������Լ�*/
  {KEYVAL_InspectManual,            B(00000000),    StandBy_Key_InspectManual},         /*ϵͳģʽ�������ּ�*/
  {KEYVAL_PackingAngle,             B(00000000),    StandBy_Key_PackingAngle},          /*ϵͳģʽ�����Ұ�װ*/
  {KEYVAL_TestNoTimer,              B(00000000),    StandBy_Key_TestNoTimer},           /*ϵͳģʽ�����ҿ��� ֮ �޶�ʱ����ģʽ*/
  {KEYVAL_TestSpike,                B(00000000),    StandBy_Key_TestSpike},             /*ϵͳģʽ�����ҿ��� ֮ �Ƹ�*/
  {KEYVAL_TestAge,                  B(00000000),    StandBy_Key_TestAge},               /*ϵͳģʽ�����ҿ��� ֮ ���� ��һСʱ��ͣ15����*/
  {KEYVAL_TestOther1,               B(00000000),    StandBy_Key_TestOther1},            /*ϵͳģʽ���������ҿ���1*/
  {KEYVAL_EngiModeSelect,           B(00000000),    StandBy_Key_EngiModeSelect},        /*����ģʽѡ��*/
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
* �������� : UserRun_KeyValAdditonOp                                                                                                         
* �������� : ��ִֵ��ǰ��ĸ��Ӳ���                                                                                    
* ������� : Index       -- ��ֵ�ڱ���������
*            BeforeAfter -- BEFORE����ִֵ��ǰִ�и��Ӳ���
*                           AFTER����ִֵ�к�ִ�и��Ӳ���   
*            CurExeState -- ��ǰִ��״̬�� SUCCESS �ɹ�   FAIL ʧ�� 
* ���ز��� : SUCCESS -- ��ִ�к�����ֵ������
*            FAIL    -- ����ִ�к�����ֵ������                                                            
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t Standby_KeyValAdditonOp(uint8_t Index, uint8_t BeforeAfter, uint8_t CurExeState)
{
  uint8_t ret;

  
  ret = SUCCESS;                                                /*�ȼ���ɹ�*/

  /*��ִֵ��ǰ�ĸ��Ӳ���---------------------------------------------------*/
  if(BEFORE == BeforeAfter)                    
  {
    /*��ִֵ��ǰ��bit7 -- 1��ERP����Դ�رգ����ִֵ��ǰ��Ҫ���¿�����    
                          0��ERP����Դ�رգ����ִֵ��ǰ������Ҫ���¿����� */   
    if(StandBy_KeyLogicTab[Index].AdditonOp & B(10000000))
    {
      if(OFF == pMChair->ERPPowerSw)                            /*����Դ���رգ������¿���*/
      {
        pMChair->ERPPowerSw = ON;                               /*��������Դ*/
        pMChair->ERPPowerOnTimeMs = 0;
      }
      pMChair->ERPPowerOffWaitTimeMs = 0;
    }
    
    /*��ִֵ��ǰ��bit6 -- 1����ͣ�������Կ�ִ�м�ֵ��  
                          0����ͣ���������ֵ��ִ�С�*/
    if(0 == (StandBy_KeyLogicTab[Index].AdditonOp & B(01000000))) 
    {
      if(TRUE == pMChair->CSFlag.Bit.Pause)
      {
        ret = FAIL;                                             /*��ͣ��������ִ�м�ֵ����*/
      }
    }
  }
  
  /*��ִֵ�к�ĸ��Ӳ���---------------------------------------------------*/
  else 
  {
    if((SUCCESS == CurExeState) &&                               /*��ֵ�ɹ�ִ��*/
       (StandBy_KeyLogicTab[Index].KeyValID != KEYVAL_NoPress))  /*�а�������*/
    {
      pMChair->PromptToneTLMs = 300;                             /*��ֵ�ɹ�ִ�У�����ʾ��*/
    }
  }

  return ret;
}


/*����������������������������������������������������������������������������������������������������������������������*/
/*
************************************************************************************************************************
* �������� : SysMode_Standby_Init                                                                                                         
* �������� : ϵͳģʽ ֮ ���� ��ʼ��                                                                                    
* ������� : ��                                                                               
* ���ز��� : ��                                                          
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_Standby_Init(void)
{
  uint8_t i;

  /*����ֵ��������Ƿ���ȷ------------------------------*/
  for(i=1; i<STANDBY_KEY_TAB_NUM; i++)
  {
    if(StandBy_KeyLogicTab[i].KeyValID <= StandBy_KeyLogicTab[i-1].KeyValID)
    {
      while(1);  /*�뽫KeyValID ��С�������ظ�����ʹ��*/
    }   
  }
}

/*
************************************************************************************************************************
* �������� : SysMode_Standby_Handle                                                                                                         
* �������� : ϵͳģʽ ֮ ��������                                                                                    
* ������� : ��                                                                               
* ���ز��� : ��                                                          
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void SysMode_Standby_Handle(void)
{
  /*����ģʽ�л�����-----------------------------------------------------*/
  if(pMChair->SysModeHis != pMChair->SysModeCur)      
  {
    BackSpike_SetCountFaultCheckSw(OFF);                                 /*�ػ��󣬹ر��Ƹ˵ļ������ϼ�⿪��*/
    FeetSpike_SetCountFaultCheckSw(OFF);
    ZeroSpike_SetCountFaultCheckSw(OFF);
    
    Core_ShoulderAdjustRe();                                             /*�ػ�������粿�����ɱ�־λ*/
    Core_SetZMBackProtectDisableSw(OFF);                                 /*�ػ��󣬿�����о��3D�˵���������*/

    memset(&pMChair->VenderInspect, 0, sizeof(pMChair->VenderInspect));  /*���� ���Ҽ���������*/
 
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
    //pMChair->CSFlag.Bit.OccurNoStartUpFault       = 0;                 /*�﷢�������������Ĺ��ϣ��ñ�ʶ�������ֵ���֡�*/
    pMChair->CSFlag.Bit.UserSpikeAngleSetd          = FALSE;
    pMChair->CSFlag.Bit.VenderOpFinish              = FALSE;
    pMChair->CSFlag.Bit.LegFlexTestSw               = FALSE;


    pMChair->PromptToneAddr = SYS_PROMPT_TONE_ADDR_DEFAULT;              /*ϵͳĬ����ʾ����ַ*/

    pMChair->CSFlag.Bit.UserMassageTimeOut = FALSE;                      /*�û���Ħ��ʱ�� ʱ�䵽 ����*/
    pMChair->CSFlag.Bit.UserMassageTimeRun = OFF;                        /*�û���Ħ��ʱ�� ���� ��*/
    pMChair->UserMassageTimeMin            = MASSAGETIME_MIN_DEFAULT;    /*�û���Ħʱ�� ��*/
    pMChair->UserMassageTimeSec            = 0;                          /*�û���Ħʱ�� ��*/
    pMChair->UserMassageTimeDelayOnSec     = 0;                          /*�û���Ħ��ʱ�� ��ʱ����������*/
    pMChair->UserMassageIdleTimeSec        = 0;                          /*�û���Ħ����ʱ�� ����*/

    pMChair->ERPPowerSw = ON;                                            /*������ģʽ���ȿ���ERP��Դ*/

    pMChair->CommonStep     = 0;                                         /*����ģʽ������Ҫ����ʹ�õĲ���*/
    pMChair->CommonTimeSec  = 0;                                         /*����ϵͳģʽ������Ҫ����ʹ�õ�ʱ�䣬��λ��*/
    pMChair->CommonTimeSec1 = 0;                                         /*����ϵͳģʽ������Ҫ����ʹ�õ�ʱ�䣬��λ��*/

    BodyScan_Init();                                                     /*ÿ�δ�������Ӧ���³�ʼ�� ����ɨ��*/              
    MChair_FuncLogic_ClearAllFunc();                                     /*���� ���а�Ħ����*/
                   
    pMChair->AutoCoreFlexLevelAdjust   = CORE_AUTO_PZLEVEL_REF;          /*�Զ�������  ��о������ ����ֵ*/
    pMChair->GasIntensity              = 3;                              /*����ǿ��*/
    pMChair->MannualCoreXYZActionSpeed = 3;                              /*�ֶ�������  XYZ�����ַ��ٶ�*/
    pMChair->MannualCoreTCSActionSpeed = 3;                              /*�ֶ�������  TCS�����ַ��ٶ�*/
    pMChair->MannualCoreWidth          = 2;                              /*�ֶ�������  ��о���*/
    pMChair->MannualCoreFlexLevel      = 2;                              /*�ֶ�������  ��о������*/

    /*ϵͳģʽ��ر�������*/
    pMChair->SysModeHis = pMChair->SysModeCur; 
    pMChair->CSFlag.Bit.Pause = FALSE;                                   /*�� ��ͣ*/

    if(pMChair->SysModeVender != SYS_MODE_NONE)                          /*�û��ڿ���״̬�£������˳���ģʽ*/
    {
      pMChair->SysModeCur    = pMChair->SysModeVender;                   /*�Ӵ���ģʽת�뵽����ģʽ*/
      pMChair->SysModeHis    = SYS_MODE_STANDBY;   
      pMChair->SysModeVender = SYS_MODE_NONE;  
    }
  }

  /*���ݸ���ģʽ�Ĳ�ͬ���Լ�ֵ������ر�����ֵ---------------------------*/
  pMChair->KeyValHandle.KeyLogicTab    = StandBy_KeyLogicTab;            /*�����߼���*/
  pMChair->KeyValHandle.KeyLogicTabNum = STANDBY_KEY_TAB_NUM;            /*�����߼��� ��С*/
  pMChair->KeyValHandle.pGetMatchID    = StandBy_GetKeyValID;            /*����ָ�룬ָ��ĺ������ã����ر����Ŀ �� ��Ҫ���������� ���ڵ�����*/
  pMChair->KeyValHandle.pAddOp         = Standby_KeyValAdditonOp;        /*����ָ�룬ָ��ĺ������ã���ִֵ��ǰ��ĸ��Ӳ��� */
}

/*
************************************************************************************************************************
* �������� : SysMode_Standby_Enter                                                                                                         
* �������� : ϵͳģʽ ֮ ���� ����                                                                                    
* ������� : CurSysMode       -- ��ǰ������ϵͳģʽ   
*            ResetSpikeAngle  -- ȡֵ��TRUE  -- ��λ�Ƹ˽Ƕ�
*                                      FALSE -- ����λ�Ƹ˽Ƕȣ����ֵ�ǰ�ĽǶȲ��䡣                                          
* ���ز��� : SUCCESS -- ����ɹ�     FAIL -- ����ʧ��                                                    
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t SysMode_Standby_Enter(uint8_t CurSysMode, uint8_t ResetSpikeAngle)
{
  if(SYS_MODE_STANDBY == pMChair->SysModeCur)
  {
    return SUCCESS;
  }
  
  pMChair->CSFlag.Bit.MChairReported = TRUE;            /*�ػ��ϱ�*/

  pMChair->SysModeHis    = CurSysMode;
  pMChair->SysModeCur    = SYS_MODE_STANDBY;            /*�������ģʽ*/
  pMChair->SysModeVender = SYS_MODE_NONE;               /*�޳���ģʽ*/

  if(TRUE == ResetSpikeAngle)
  {
    Spike_SetLegFlexAngle(PLEGFLEX_MIN);                /*�����Ƹ��������*/
    Spike_SetULegFlexAngle(PULEGFLEX_MAX);              /*��С���쵽�*/
    Spike_SetAngle(PBACK_MIN, PFEET_MIN, PZERO_MIN);    /*�����Ƕ�*/
  }

  return SUCCESS;
}
