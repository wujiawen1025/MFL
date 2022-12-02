/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: Spike.c                                                                                                         
**
**    ��������: �Ƹ����������� ������С�ȡ�С�������������� ���Ƹ�
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
#include "Spike.h"
#include "ESF.h"


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
*���������� & ����������                          ���������� & ����������                          ���������� & ����������    
========================================================================================================================
*/
Spike_t Spike;
Spike_t  *pSpike = &Spike;


/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : Spike_SetBackAngle                                                                                                         
* �������� : �Ƹ� ���� �����Ƕ�                                                                                                
* ������� : BackAngle -- �Ƕȣ�ȡֵ PBACK_MIN ~ PBACK_MAX ��PKEEP                                                                                               
* ���ز��� : ʧ��--FAIL    �ɹ�--SUCCESS                                                                                                  
* ����˵�� : �����Ƹ˽Ƕ�ʱ�����Զ�������ص�Move�˶�����������ֶ����Ƹ˵��ڣ��򽫱��������                                                                                                        
************************************************************************************************************************
*/
uint8_t Spike_SetBackAngle(uint8_t BackAngle)
{
  if((BackAngle > PBACK_MAX) && (BackAngle!= PKEEP))
  {
    return FAIL;
  }
  pSpike->BackAngleSetVal = BackAngle;
  pSpike->ActionCur.Bit.BackMove = SPIKE_MOVE_NONE;  /*����Ƹ˵����˶�*/
  pSpike->ActionHis.Bit.BackMove = SPIKE_MOVE_NONE;  /*����Ƹ˵����˶�*/

  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : Spike_SetZeroAngle                                                                                                         
* �������� : �Ƹ� ���� �������Ƕ�                                                                                            
* ������� : ZeroAngle -- �Ƕȣ�ȡֵ PZERO_MIN ~ PZERO_MAX ��PKEEP                                                                                               
* ���ز��� : ʧ��--FAIL    �ɹ�--SUCCESS                                                                                                  
* ����˵�� : �����Ƹ˽Ƕ�ʱ�����Զ�������ص�Move�˶�����������ֶ����Ƹ˵��ڣ��򽫱��������                                                                                                        
************************************************************************************************************************
*/
uint8_t Spike_SetZeroAngle(uint8_t ZeroAngle)
{
  if((ZeroAngle > PZERO_MAX) && (ZeroAngle!= PKEEP))
  {
    return FAIL;
  }
  pSpike->ZeroAngleSetVal = ZeroAngle;
  pSpike->ActionCur.Bit.ZeroMove = SPIKE_MOVE_NONE;  /*����Ƹ˵����˶�*/
  pSpike->ActionHis.Bit.ZeroMove = SPIKE_MOVE_NONE;  /*����Ƹ˵����˶�*/
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : Spike_SetFeetAngle                                                                                                         
* �������� : �Ƹ� ���� �ȽŽǶ�                                                                                         
* ������� : FeetAngle -- �Ƕȣ�ȡֵ PFEET_MIN ~ PFEET_MAX ��PKEEP                                                                                               
* ���ز��� : ʧ��--FAIL    �ɹ�--SUCCESS                                                                                                  
* ����˵�� : �����Ƹ˽Ƕ�ʱ�����Զ�������ص�Move�˶�����������ֶ����Ƹ˵��ڣ��򽫱��������                                                                                                        
************************************************************************************************************************
*/
uint8_t Spike_SetFeetAngle(uint8_t FeetAngle)
{
  if((FeetAngle > PFEET_MAX) && (FeetAngle!= PKEEP))
  {
    return FAIL;
  }
  pSpike->FeetAngleSetVal = FeetAngle;
  pSpike->ActionCur.Bit.FeetMove = SPIKE_MOVE_NONE;  /*����Ƹ˵����˶�*/
  pSpike->ActionHis.Bit.FeetMove = SPIKE_MOVE_NONE;  /*����Ƹ˵����˶�*/
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : Spike_SetAngle                                                                                                         
* �������� : �Ƹ� ���� ���������������Ƚ� �Ƕ�                                                                                
* ������� : BackAngle -- �����Ƕȣ�  ȡֵ PBACK_MIN ~ PBACK_MAX ��PKEEP                                                                                               
*            FeetAngle -- С�ȽǶȣ�  ȡֵ PFEET_MIN ~ PFEET_MAX ��PKEEP                                                                                               
*            ZeroAngle -- �������Ƕȣ�ȡֵ PZERO_MIN ~ PZERO_MAX ��PKEEP                                                                                               
* ���ز��� : ��                                                                                               
* ����˵�� : �����Ƹ˽Ƕ�ʱ�����Զ�������ص�Move�˶�����������ֶ����Ƹ˵��ڣ��򽫱��������                                                                                                        
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
* �������� : Spike_SetLegFlexAngle                                                                                                         
* �������� : �Ƹ� ���� �Ƚ������Ƕ�                                                                                         
* ������� : LegFlexAngle -- �Ƕȣ�ȡֵ PLEGFLEX_MIN ~ PLEGFLEX_MAX ��PKEEP                                                                                               
* ���ز��� : ʧ��--FAIL    �ɹ�--SUCCESS                                                                                                  
* ����˵�� : �����Ƹ˽Ƕ�ʱ�����Զ�������ص�Move�˶�����������ֶ����Ƹ˵��ڣ��򽫱��������                                                                                                        
************************************************************************************************************************
*/
uint8_t Spike_SetLegFlexAngle(uint8_t LegFlexAngle)
{
  if((LegFlexAngle > PLEGFLEX_MAX) && (LegFlexAngle!= PKEEP))
  {
    return FAIL;
  }
  pSpike->LegFlexAngleSetVal = LegFlexAngle;
  pSpike->ActionCur.Bit.LegFlexMove = SPIKE_MOVE_NONE;  /*����Ƹ˵����˶�*/
  pSpike->ActionHis.Bit.LegFlexMove = SPIKE_MOVE_NONE;  /*����Ƹ˵����˶�*/
  if(TRUE == pSpike->CSFlag.Bit.LegLenDetectRun)        
  {
    pSpike->CSFlag.Bit.LegLenDetectRun = FALSE;
    pSpike->LegLenDetectStep = 255;                     /*�ϲ���õ��������Ƹˣ�������ȳ��Զ����*/
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
  pSpike->ActionCur.Bit.ULegFlexMove = SPIKE_MOVE_NONE;  /*����Ƹ˵����˶�*/
  pSpike->ActionHis.Bit.ULegFlexMove = SPIKE_MOVE_NONE;  /*����Ƹ˵����˶�*/
  return SUCCESS;
}

/*
************************************************************************************************************************
* �������� : Spike_SetBackMove                                                                                                         
* �������� : �Ƹ� ���� ���� ���� ����                                                                                
* ������� : Move ȡֵ�� SPIKE_MOVE_NONE
*                        SPIKE_MOVE_BACK_UP
*                        SPIKE_MOVE_BACK_DOWN                                                                                         
* ���ز��� : ��                                                                                               
* ����˵�� : �������Spike_MoveActionHandle()�����н��Զ�����صĽǶ�����ΪPKEEP(λ�ñ���)                                                                                                      
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

  /*��������ȫ�Ƕ��޶�ʱ�������ٵ�����*/
  if((TRUE == pSpike->CSFlag.Bit.ReachZeroSafetyAngleLimit) &&
     (SPIKE_MOVE_BACK_DOWN == Move)) 
  {
    return;
  }

  pSpike->ActionCur.Bit.BackMove = Move;
}


/*
************************************************************************************************************************
* �������� : Spike_GetBackMove                                                                                                         
* �������� : �Ƹ� ��ѯ ���� ���� ����                                                                          
* ������� : ��                                                                                  
* ���ز��� : SPIKE_MOVE_NONE
*            SPIKE_MOVE_BACK_UP
*            SPIKE_MOVE_BACK_DOWN                                                                                               
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t Spike_GetBackMove(void)
{
  return pSpike->ActionCur.Bit.BackMove;
}

/*
************************************************************************************************************************
* �������� : Spike_SetZeroMove                                                                                                         
* �������� : �Ƹ� ���� ������ ���� ����                                                                          
* ������� : Move ȡֵ�� SPIKE_MOVE_NONE
*                        SPIKE_MOVE_ZERO_UP
*                        SPIKE_MOVE_ZERO_DOWN                                                                              
* ���ز��� : ��                                                                                               
* ����˵�� : �������Spike_MoveActionHandle()�����н��Զ�����صĽǶ�����ΪPKEEP(λ�ñ���)                                                                                                      
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
* �������� : Spike_GetZeroMove                                                                                                         
* �������� : �Ƹ� ��ѯ ������ ���� ����                                                                   
* ������� : ��                                                                          
* ���ز��� : SPIKE_MOVE_NONE
*            SPIKE_MOVE_ZERO_UP
*            SPIKE_MOVE_ZERO_DOWN                                                                                               
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t Spike_GetZeroMove(void)
{
  return pSpike->ActionCur.Bit.ZeroMove;
}

/*
************************************************************************************************************************
* �������� : Spike_SetFeetMove                                                                                                         
* �������� : �Ƹ� ���� �Ƚ� ���� ����                                                        
* ������� : Move ȡֵ�� SPIKE_MOVE_NONE
*                        SPIKE_MOVE_FEET_UP
*                        SPIKE_MOVE_FEET_DOWN                                                                          
* ���ز��� : ��                                                                                         
* ����˵�� : �������Spike_MoveActionHandle()�����н��Զ�����صĽǶ�����ΪPKEEP(λ�ñ���)                                                                                                      
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
* �������� : Spike_GetFeetMove                                                                                                         
* �������� : �Ƹ� ��ѯ �Ƚ� ���� ����                                                       
* ������� : ��                                                                       
* ���ز��� : SPIKE_MOVE_NONE
*            SPIKE_MOVE_FEET_UP
*            SPIKE_MOVE_FEET_DOWN                                                                                         
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t Spike_GetFeetMove(void)
{
  return pSpike->ActionCur.Bit.FeetMove;
}


/*
************************************************************************************************************************
* �������� : Spike_SetLegFlexMove                                                                                                         
* �������� : �Ƹ� ���� �Ƚ� ���� ����                                                
* ������� : Move ȡֵ�� SPIKE_MOVE_NONE
*                        SPIKE_MOVE_LEG_SHORT
*                        SPIKE_MOVE_LEG_EXTEND                                                                      
* ���ز��� : ��                                                                                        
* ����˵�� : ��                                                                                                         
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
    pSpike->LegLenDetectStep = 255;                     /*�ϲ���õ��������Ƹˣ�������ȳ��Զ����*/
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
* �������� : Spike_GetLegFlexMove                                                                                                         
* �������� : �Ƹ� ��ѯ �Ƚ� ���� ����                                                
* ������� : ��                                                                 
* ���ز��� : SPIKE_MOVE_NONE
*            SPIKE_MOVE_FEET_SHORT
*            SPIKE_MOVE_FEET_EXTEND                                                                                               
* ����˵�� : ��                                                                                                         
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
* �������� : Spike_SetMoveAction                                                                                                         
* �������� : �Ƹ� ����  ����                                     
* ������� : SpikeMoveAction -- ����                                                                
* ���ز��� : ��                                                                                           
* ����˵�� : ��                                                                                                         
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
* �������� : Spike_SetZeroSafetyAngleLimitRef                                                                                                         
* �������� : �Ƹ� ����  ��������ȫ�Ƕ� �޶� �ж� �ο�ֵ                                
* ������� : RefBack -- �ο��ı����Ƕ�
*            RefZero -- �ο����������Ƕ�                                                            
* ���ز��� : ��                                                                                           
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Spike_SetZeroSafetyAngleLimitRef(uint8_t RefBack, uint8_t RefZero)
{
  pSpike->ZeroSafetyAngleLimitBackAngele = RefBack;
  pSpike->ZeroSafetyAngleLimitZeroAngele = RefZero;
}


/*
************************************************************************************************************************
* �������� : Spike_SetLegLenDetectSw                                                                                                         
* �������� : �Ƹ� ����  �ȳ���⿪��                       
* ������� : Sw -- ����                                                          
* ���ز��� : ��                                                                                           
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Spike_SetLegLenDetectSw(uint8_t Sw)
{
  pSpike->CSFlag.Bit.LegLenDetectSw = (Sw == ON) ? ON : OFF;
}

/*
************************************************************************************************************************
* �������� : Spike_LegLenDetectRedo                                                                                                        
* �������� : �Ƹ�  �ȳ���� ����                   
* ������� : ��                                                      
* ���ز��� : ��                                                                                           
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Spike_LegLenDetectRedo(void)
{
  pSpike->LegLenDetectStep = 0;                               
  pSpike->CSFlag.Bit.LegLenDetectFinish = FALSE;  
}

/*
************************************************************************************************************************
* �������� : Spike_SetLegLenDetectExtendMax                                                                                                         
* �������� : �Ƹ� ����  �ȳ���� �쳤���ֵ                      
* ������� : MaxLen -- �쳤���ֵ                                                          
* ���ز��� : ��                                                                                           
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Spike_SetLegLenDetectExtendMax(uint8_t MaxLen)
{
  pSpike->LegLenDetectExtendMax = MaxLen;
}

/*
************************************************************************************************************************
* �������� : Spike_LegLenDetectPauseOn                                                                                                         
* �������� : ��ͣ�ȳ����                                                                       
* ������� : ��                                                                                
* ���ز��� : ��                                                                                             
* ����˵�� : ������������ת�����ֹͣ������ת��
*            ֻ�н����ͣ��������������ת��                                                                                                      
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
* �������� : Spike_LegLenDetectPauseOff                                                                                                         
* �������� : �����ͣ�ȳ����                                                                      
* ������� : ��                                                                                
* ���ز��� : ��                                                                                             
* ����˵�� : ������������ת�����ֹͣ������ת��
*            ֻ�н����ͣ��������������ת��                                                                                                      
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
* �������� : Spike_MoveActionHandle                                                                                                         
* �������� : �Ƹ�  ����  �߼�����                             
* ������� : ExePeriod -- ִ������                                                    
* ���ز��� : ��                                                                                           
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Spike_MoveActionHandle(Ticker_t ExePeroid)
{
  /*�����Ƹ�----------------------------------------------------------*/
  if(pSpike->ActionHis.Bit.BackMove != pSpike->ActionCur.Bit.BackMove)
  {
    pSpike->ActionHis.Bit.BackMove = pSpike->ActionCur.Bit.BackMove;

    if(SPIKE_MOVE_NONE == pSpike->ActionCur.Bit.BackMove)
    {
      pSpike->BackAngleSetVal = PKEEP; /*������ɺ� λ�ñ���*/
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
      /*�ж�������ʱ��������ȫ�޶��Ƕ�*/
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


  /*�������Ƹ�--------------------------------------------------------*/
  if(pSpike->ActionHis.Bit.ZeroMove != pSpike->ActionCur.Bit.ZeroMove)
  {
    pSpike->ActionHis.Bit.ZeroMove = pSpike->ActionCur.Bit.ZeroMove;

    if(SPIKE_MOVE_NONE == pSpike->ActionCur.Bit.ZeroMove)
    {
      pSpike->ZeroAngleSetVal = PKEEP; /*������ɺ� λ�ñ���*/
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


  /*���Ƹ�------------------------------------------------------------*/
  if(pSpike->ActionHis.Bit.FeetMove != pSpike->ActionCur.Bit.FeetMove)
  {
    pSpike->ActionHis.Bit.FeetMove = pSpike->ActionCur.Bit.FeetMove;

    if(SPIKE_MOVE_NONE == pSpike->ActionCur.Bit.FeetMove)
    {
      pSpike->FeetAngleSetVal = PKEEP; /*������ɺ� λ�ñ���*/
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


  /*С�������Ƹ�------------------------------------------------------*/
  if(pSpike->ActionHis.Bit.LegFlexMove != pSpike->ActionCur.Bit.LegFlexMove)
  {
    pSpike->ActionHis.Bit.LegFlexMove = pSpike->ActionCur.Bit.LegFlexMove;

    if(SPIKE_MOVE_NONE == pSpike->ActionCur.Bit.LegFlexMove)
    {
      pSpike->LegFlexAngleSetVal = PKEEP; /*������ɺ� λ�ñ���*/
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
      pSpike->LegFlexAngleSetVal = PKEEP; /*������ɺ� λ�ñ���*/
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
      pSpike->LegFlexAngleSetVal = PKEEP; /*������ɺ� λ�ñ���*/
    }
  }
  else //(SPIKE_MOVE_BACK_DOWN == pSpike->ActionCur.Bit.LegFlexMove)
  {
    LegFlexSpike_SetPosition(pSpike->LegFlexAngleSetVal);
  }
  
  
  /*�ȳ��Զ����-------------------------*/
  if(TRUE == FeetSpike_GetCSFlag().Bit.Run)
  {
    pSpike->LegLenDetectStep = 0;                                 /*С���������˶�������Ҫ���¼���ȳ�����λ�䲽��*/
    pSpike->CSFlag.Bit.LegLenDetectFinish = FALSE;  
    if(TRUE == pSpike->CSFlag.Bit.LegLenDetectRun)
    {
      Spike_LegFlexMoveStop();
      pSpike->CSFlag.Bit.LegLenDetectRun = FALSE; 
    }
  }
  else
  {
    if(ON == pSpike->CSFlag.Bit.LegLenDetectSw)                     /*��⿪����Ч*/
    {
      if((Spike_GetBackAngle() > PBACK_LEG_LEN_DETECT_ANGLE) ||     /*���Ƕ�����*/
         (Spike_GetFeetAngle() > PFEET_LEG_LEN_DETECT_ANGLE) ||     /*���Ƕ�����*/
         (Spike_GetZeroAngle() > PZERO_LEG_LEN_DETECT_ANGLE) )      /*���Ƕ�����*/
      {
        if((FALSE == BackSpike_GetCSFlag().Bit.Run) &&              /*�Ƹ˵��˶�ֹͣ*/
           (FALSE == FeetSpike_GetCSFlag().Bit.Run) &&
           (FALSE == ZeroSpike_GetCSFlag().Bit.Run) )
        {
          if(0 == pSpike->CSFlag.Bit.LegLenDetectPause)
          {
            if(0 == pSpike->LegLenDetectStep)                         /*����*/
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
            else if(1 == pSpike->LegLenDetectStep)                    /*����*/
            {
              pSpike->CSFlag.Bit.LegLenDetectRun = TRUE;                
              Spike_LegFlexMoveShorten();
              if((LegFlexSpike_GetCSFlag().Bit.TouchFeet)       || 
                 (LegFlexSpike_GetCSFlag().Bit.ReachShortenLimt))
              {
                pSpike->LegLenDetectStep = 2;
              }
            }
            else if(2 == pSpike->LegLenDetectStep)                    /*������*/
            {
              pSpike->CSFlag.Bit.LegLenDetectRun = FALSE;                
              Spike_LegFlexMoveStop();
              pSpike->LegFlexAngleSetVal = PKEEP;                     /*������ɺ� λ�ñ���*/
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
  
  /*���ȡ���������������ʱ�� ��С�ȴ��أ���ʱ�轫С������*/
  if(((FEETSPIKE_DIRECTION_DOWN == FeetSpike_GetCSFlag().Bit.Direction) && (ON == FeetSpike_GetCSFlag().Bit.Run)) || 
     ((BACKSPIKE_DIRECTION_UP   == BackSpike_GetCSFlag().Bit.Direction) && (ON == BackSpike_GetCSFlag().Bit.Run)) || 
     ((ZEROSPIKE_DIRECTION_DOWN == ZeroSpike_GetCSFlag().Bit.Direction) && (ON == ZeroSpike_GetCSFlag().Bit.Run)) ) 
  {
    if(TRUE == LegFlexSpike_GetCSFlag().Bit.TouchGround)          /*���غ󣬽��ȡ������������������з��գ���������*/
    {
      pSpike->CSFlag.Bit.LegTouchGroundProtectRun = ON;
    }
  }
  if((FALSE == LegFlexSpike_GetCSFlag().Bit.TouchGround)     ||   /*û�д���*/
     (TRUE  == LegFlexSpike_GetCSFlag().Bit.ReachShortenLimt))    /*�Ѿ���ȫ����*/
  {
    pSpike->CSFlag.Bit.LegTouchGroundProtectRun = OFF;            /*�رձ���*/
  }
  if(ON == pSpike->CSFlag.Bit.LegTouchGroundProtectRun)
  {
    Spike_LegFlexMoveShorten();
  }
  

  /*��С�������Ƹ�------------------------------------------------------*/
  if(pSpike->ActionHis.Bit.ULegFlexMove != pSpike->ActionCur.Bit.ULegFlexMove)
  {
    pSpike->ActionHis.Bit.ULegFlexMove = pSpike->ActionCur.Bit.ULegFlexMove;

    if(SPIKE_MOVE_NONE == pSpike->ActionCur.Bit.ULegFlexMove)
    {
      pSpike->ULegFlexAngleSetVal = PKEEP; /*������ɺ� λ�ñ���*/
    }
  }
  
  if(SPIKE_MOVE_LEG_SHORT == pSpike->ActionCur.Bit.ULegFlexMove)
  {
    Spike_ULegFlexMoveShorten();
    if( LegFlexSpike_GetCSFlag().Bit.ULegReachShortenLimt )
    {
      pSpike->ActionCur.Bit.ULegFlexMove = SPIKE_MOVE_NONE;
      pSpike->ULegFlexAngleSetVal = PKEEP; /*������ɺ� λ�ñ���*/
    }
  }
  else if(SPIKE_MOVE_LEG_EXTEND == pSpike->ActionCur.Bit.ULegFlexMove)
  {
    Spike_ULegFlexMoveExtend();
    if( LegFlexSpike_GetCSFlag().Bit.ULegReachExtendLimt )
    {
      pSpike->ActionCur.Bit.ULegFlexMove = SPIKE_MOVE_NONE;
      pSpike->ULegFlexAngleSetVal = PKEEP; /*������ɺ� λ�ñ���*/
    }
  }
  else //(SPIKE_MOVE_BACK_DOWN == pSpike->ActionCur.Bit.ULegFlexMove)
  {
    LegFlexSpike_SetULegPosition(pSpike->ULegFlexAngleSetVal);
  }  
}

/*
************************************************************************************************************************
* �������� : Spike_ResetHandle                                                                                                         
* �������� : �Ƹ�оƬ ��λ �߼�����                             
* ������� : ExePeriod -- ִ������                                                    
* ���ز��� : ��                                                                                           
* ����˵�� : ��⵽4959�������ŵ�ƽ��Ч�͸�оƬreset��һ���͵�ƽ������и�λ                                                                                                        
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
/*������������������������������������������������������������������������������������������������������������*/
/*������������������������������������������������������������������������������������������������������������*/
/*
========================================================================================================================
*         �Ƹ˹��ܺ�����                           �Ƹ˹��ܺ�����                           �Ƹ˹��ܺ�����
========================================================================================================================
*/
#define  SPIKE_TICK_COUNT_BUF_NUM   17

static Ticker_t Spike_TickCount[SPIKE_TICK_COUNT_BUF_NUM];
static const ESF_TmrExeFunc_t  Spike_TmrExeFuncTab[] = 
{
  /*   ִ�к���                   ִ������      ʱ���������*/
  {Spike_MoveActionHandle,           47,       &Spike_TickCount[0]},

  //{BackSpike_OverCurrentIOCheck,     91,       &Spike_TickCount[1]},  /*������*/
  {BackSpike_PositionHandle,         31,       &Spike_TickCount[2]},  /*λ�ô���*/
  {BackSpike_PositionIOCheck,        7,        &Spike_TickCount[3]},  /*λ��IO*/
  {BackSpike_ActionHandle,           25,       &Spike_TickCount[4]},  /*����*/ 
  
  //{FeetSpike_OverCurrentIOCheck,     92,       &Spike_TickCount[5]},  /*������*/
  {FeetSpike_PositionHandle,         32,       &Spike_TickCount[6]},  /*λ�ô���*/
  {FeetSpike_PositionIOCheck,        7,        &Spike_TickCount[7]},  /*λ��IO*/
  {FeetSpike_ActionHandle,           26,       &Spike_TickCount[8]},   /*����*/ 
 
//  {ZeroSpike_OverCurrentIOCheck,     93,       &Spike_TickCount[9]},  /*������*/
//  {ZeroSpike_PositionHandle,         33,       &Spike_TickCount[10]}, /*λ�ô���*/
//  {ZeroSpike_PositionIOCheck,        7,        &Spike_TickCount[11]}, /*λ��IO*/
//  {ZeroSpike_ActionHandle,           27,       &Spike_TickCount[12]}, /*����*/ 
//  
  {LegFlexSpike_PositionHandle,      34,       &Spike_TickCount[13]}, /*λ�ô���*/ 
  {LegFlexSpike_IOCheck,             7,        &Spike_TickCount[14]}, /*IO*/
  {LegFlexSpike_ActionHandle,        28,       &Spike_TickCount[15]},  /*����*/ 
  
  {Spike_ResetHandle,                 9,       &Spike_TickCount[16]}  /*4959��λ���� */
};

#define  SPIKE_TMR_EXE_FUNC_TAB_NUM     TAB_NUM(Spike_TmrExeFuncTab)

/*
************************************************************************************************************************
* �������� : Spike_Handle                                                                                                         
* �������� : �Ƹ� ����                
* ������� : ��                                            
* ���ز��� : ��                                                                        
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void Spike_Handle(void)
{
  /*Ҫ�Ƚ�ʵʱ�ؿ���ת�ټ��IO�ڵ��жϡ��������������������ʱ��Ƭ��ִ�С�*/
  BSP_IO_EnableInputInterrupt_BackSpikeCount();
  BSP_IO_EnableInputInterrupt_FeetSpikeCount();
  BSP_IO_EnableInputInterrupt_ZeroSpikeCount();

  /*���ȹ��ܺ�����------------------------------------------------*/
  ESF_TmrExeFuncScheduling(Spike_TmrExeFuncTab, SPIKE_TMR_EXE_FUNC_TAB_NUM);
}


/*
************************************************************************************************************************
* �������� : Spike_Init                                                                                                         
* �������� : �Ƹ� ��ʼ��                 
* ������� : ��                                            
* ���ز��� : ���� �ɲ����Ƹ˹��� �Ľṹ�� ��ָ��                                                                               
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
Spike_t* Spike_Init(void)
{
  /*��ʼ���������------------------------------------------*/
  memset(pSpike, 0, sizeof(Spike_t)); /*������������*/

  pSpike->ZeroSafetyAngleLimitBackAngele = PBACK12;
  pSpike->ZeroSafetyAngleLimitZeroAngele = PZERO10;

  /*�Ƹ˲���------------------------------------------------*/
  pSpike->pBackSpike    = BackSpike_Init();
  pSpike->pFeetSpike    = FeetSpike_Init();
  pSpike->pZeroSpike    = ZeroSpike_Init();
  pSpike->pLegFlexSpike = LegFlexSpike_Init();

  /*Ϊ��ֹ������޸ģ��ڴ˼�⹦�ܺ������Ƿ���ȷ------------------------------*/
  ESF_TmrExeFuncTabCheck(Spike_TmrExeFuncTab, SPIKE_TMR_EXE_FUNC_TAB_NUM, SPIKE_TICK_COUNT_BUF_NUM);

  return pSpike;
}

/*
************************************************************************************************************************
* �������� : Spike_GetCSFlag                                                                                                         
* �������� : ��� ���� �� ״̬ ��ʶ                        
* ������� : ��                                            
* ���ز��� : ������״̬��ʶ �Ľṹ��                                                                                           
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
SpikeCSFlag_t Spike_GetCSFlag(void)
{
  return pSpike->CSFlag;
}
