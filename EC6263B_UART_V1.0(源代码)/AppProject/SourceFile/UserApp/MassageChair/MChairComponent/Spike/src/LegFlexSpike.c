/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: LegFlexSpike.c                                                                                                         
**
**    ��������: С�����Ƹ�������
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
#include "LegFlexSpike.h"

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
static LegFlexSpike_t LegFlexSpike;
LegFlexSpike_t *pLegFlexSpike = &LegFlexSpike;



/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/
/*
************************************************************************************************************************
* �������� : LegFlexSpike_CountIOCheck_CB                                                                                                         
* �������� : λ�� ����IO�ڼ��  �Ļص�����                                                                                           
* ������� : ��                                                                                    
* ���ز��� : ��                                                                                             
* ����˵�� : �ú���ͨ�� BSP_IO_InputInterrupt_RegCB_LegFlexSpikeCount(LegFlexSpike_CountIOCheck_CB);����ע���BSP��                                                                                                         
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
* �������� : LegFlexSpike_IOCheck                                                                                                         
* �������� : IO�ڵļ��                                                                                          
* ������� : ExePeriod -- ������ִ������                                                                                   
* ���ز��� : ��                                                                                            
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void LegFlexSpike_IOCheck(Ticker_t ExePeriod)
{
  //static uint8_t StableIOCode;                                                                     /*�ȶ��ı���*/
  //static uint8_t StableStat;                                                                       /*״̬�ȶ�ͳ��*/
  static uint8_t IOCode;                       

  //static uint8_t UStableIOCode;                                                                    /*�ȶ��ı���*/
  //static uint8_t UStableStat;                                                                      /*״̬�ȶ�ͳ��*/
  static uint8_t UIOCode;                       
  
  
  /*��ʱ���и��ţ����������״̬�ȶ����ж�------------------------*/
  //if(PositionIOStableStat((BSP_IO_ReadInput_LegFlexSpikePosition() & B(11)), &DStableIOCode, &DStableStat) >= 3)
  //{
  //  IOCode = StableIOCode;                                                                      /*��ȡ�ȶ���ı���*/
  //}
  IOCode = pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegReachExtendLimt;
  IOCode <<= 1;
  IOCode |= pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegReachShortenLimt;
  
  /*���ȼ��λ�ñ����Ƿ���ϣ�--------------------------------------------------
    ǰ�󴫸����Ƿ�ͬʱ��Ч���Ż�������ֹ���*/
  if(BIN(11) == IOCode) 
  {
    if(pLegFlexSpike->PositionMonitor.PositionCodeErrTimeMs <= LEGFLEXSPIKE_POSITION_CODE_ERR_TIME_THRESHOLD) /*δ��������ʱ��*/
    {
      pLegFlexSpike->PositionMonitor.PositionCodeErrTimeMs += ExePeriod;
    }
    else
    {
      pLegFlexSpike->CSFlag.Bit.PositionCodeFault = FAULT;            /*λ�ñ������, ���ֺ󣬳��򲻻����㣬����λ�����ϵ������*/
      return;                                                          /*���ٽ����κκ���������ֱ�ӷ���*/
    }
  }
  else
  {
    pLegFlexSpike->PositionMonitor.PositionCodeErrTimeMs = 0;
  }
  
  /*λ�ü������������ϼ��----------------------------------------------------------------------------*/
  pLegFlexSpike->PositionMonitor.PositionCountCur = pLegFlexSpike->SetQry0x4B.LegPositionCount;
  if(pLegFlexSpike->PositionMonitor.PositionCountHis == pLegFlexSpike->PositionMonitor.PositionCountCur)  /*λ�ü����ޱ仯*/
  {
    if(ON == pLegFlexSpike->CSFlag.Bit.Run)                                                             /*���������ʱ���ۼӴ�����ʧ��ʱ��*/
    {
      if(pLegFlexSpike->PositionMonitor.SensorLostTimeMs <= LEGFLEXSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD)
      {
        pLegFlexSpike->PositionMonitor.SensorLostTimeMs += ExePeriod;                                   /*���������ʱ���ۼӼ���������ʧ��ʱ��*/
      }
      else
      {
        if((LEGFLEXSPIKE_ACTION_SHORTEN == pLegFlexSpike->Action) &&
           (0 == pLegFlexSpike->PositionMonitor.PositionCountCur)  )
        {
          pLegFlexSpike->CSFlag.Bit.ShortPositionSensorFault = FAULT;                                   /*�����λ����������*/
        }
        else if((LEGFLEXSPIKE_ACTION_EXTEND == pLegFlexSpike->Action)                       && 
                (LEGFLEXSPIKE_COUNT_MAX <= pLegFlexSpike->PositionMonitor.PositionCountCur) )
        {
          pLegFlexSpike->CSFlag.Bit.ExtendPositionSensorFault = FAULT;                                  /*���λ����������*/
        }
        else 
        {
          pLegFlexSpike->CSFlag.Bit.CountFault = FAULT;                                                 /*��������*/
        }
      }    
    }
    else //if(OFF == pLegFlexSpike->CSFlag.Bit.Run)                                                         /*���û��*/
    {
      pLegFlexSpike->PositionMonitor.SensorLostTimeMs = 0;                                              /*�������������ʧ��ʱ��*/
    }
  }
  else //if(pLegFlexSpike->PositionMonitor.PositionCountHis != pLegFlexSpike->PositionMonitor.PositionCountCur)/*�����б仯*/
  {
    pLegFlexSpike->PositionMonitor.PositionCountHis = pLegFlexSpike->PositionMonitor.PositionCountCur;
    pLegFlexSpike->PositionMonitor.SensorLostTimeMs = 0;                                                /*�������������ʧ��ʱ��*/
  }
  
  
  /*λ�ú��ź�IO��ȡ---------------------------------------------------*/
  pLegFlexSpike->CSFlag.Bit.ReachExtendLimt  = BIT_GET(IOCode, 1);
  pLegFlexSpike->CSFlag.Bit.ReachShortenLimt = BIT_GET(IOCode, 0);
//  pLegFlexSpike->CSFlag.Bit.TouchGround      = pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegTouchGround; //BSP_IO_ReadInput_LegFlexSpikeTouchGround();
//  pLegFlexSpike->CSFlag.Bit.TouchFeet        = pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegTouchFeet;   //!BSP_IO_ReadInput_LegFlexSpikeTouchFeet();
  
  /*�쵽��򴥵أ�ֹͣ�쳤�˶�*/
  if((TRUE == pLegFlexSpike->CSFlag.Bit.TouchGround)    ||
     (TRUE == pLegFlexSpike->CSFlag.Bit.ReachExtendLimt)) 
  {
    if(LEGFLEXSPIKE_ACTION_EXTEND == pLegFlexSpike->Action)
    {
      LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_STOP);
    }
  }

  /*������̻򴥽ţ�ֹͣ�����˶�*/                         
  //if((TRUE == pLegFlexSpike->CSFlag.Bit.ReachShortenLimt)                                                ||
  //   ((TRUE == pLegFlexSpike->CSFlag.Bit.TouchFeet) && (FALSE == pLegFlexSpike->CSFlag.Bit.TouchGround)) ) /*���ŵ�������*/   
  if(TRUE == pLegFlexSpike->CSFlag.Bit.ReachShortenLimt)  
  {
    if(LEGFLEXSPIKE_ACTION_SHORTEN == pLegFlexSpike->Action)
    {
      LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_STOP);
    }
    pLegFlexSpike->CSFlag.Bit.PositionResetOK = TRUE;        /*λ�ø�λ���*/
  }
  
  /*λ��ֵ����*/
  if(TRUE == pLegFlexSpike->CSFlag.Bit.ReachExtendLimt) 
  {
    pLegFlexSpike->PositionRealVal = LEGFLEXSPIKE_POSITION_MAX;
    pLegFlexSpike->PositionMonitor.PositionCountCur = LEGFLEXSPIKE_COUNT_MAX;         /*����λ�ö�Ҫ��������ֵ*/
  }
  else if(TRUE == pLegFlexSpike->CSFlag.Bit.ReachShortenLimt) 
  {
    pLegFlexSpike->PositionRealVal = LEGFLEXSPIKE_POSITION_MIN;
    pLegFlexSpike->PositionMonitor.PositionCountCur = LEGFLEXSPIKE_COUNT_MIN;         /*����λ�ö�Ҫ��������ֵ*/
  }
  else
  {
    if(POSITION_COUNT_INC == pLegFlexSpike->PositionMonitor.CountDirection)             /*��������*/
    {
      pLegFlexSpike->PositionRealVal = pLegFlexSpike->PositionMonitor.PositionCountCur/LEGFLEXSPIKE_COUNT_PER_SEGMENT;
    }
    else //if(POSITION_COUNT_DEC == pLegFlexSpike->PositionMonitor.CountDirection)      /*��������*/
    {
      pLegFlexSpike->PositionRealVal = pLegFlexSpike->PositionMonitor.PositionCountCur/LEGFLEXSPIKE_COUNT_PER_SEGMENT + 1;
    }
  }
 

  
#if(1==LEGFLEX_UP_EN)
  //=============================================================================================================================
  //=============================================================================================================================
  //=============================================================================================================================
  /*��ʱ���и��ţ����������״̬�ȶ����ж�------------------------*/
  //if(PositionIOStableStat((BSP_IO_ReadInput_LegFlexSpikePosition() & B(11)), &UStableIOCode, &UStableStat) >= 3)
  //{
  //  UIOCode = UStableIOCode;                                                                      /*��ȡ�ȶ���ı���*/
  //}
 
  UIOCode = pLegFlexSpike->SetQry0x4B.Byte2.Bit.ULegReachExtendLimt;
  UIOCode <<= 1;
  UIOCode |= pLegFlexSpike->SetQry0x4B.Byte2.Bit.ULegReachShortenLimt;
  
  /*���ȼ��λ�ñ����Ƿ���ϣ�--------------------------------------------------
    ǰ�󴫸����Ƿ�ͬʱ��Ч���Ż�������ֹ���*/
  if(BIN(11) == UIOCode) 
  {
    if(pLegFlexSpike->ULegPositionMonitor.PositionCodeErrTimeMs <= LEGFLEXSPIKE_POSITION_CODE_ERR_TIME_THRESHOLD) /*δ��������ʱ��*/
    {
      pLegFlexSpike->ULegPositionMonitor.PositionCodeErrTimeMs += ExePeriod;
    }
    else
    {
      pLegFlexSpike->CSFlag.Bit.ULegPositionCodeFault = FAULT;         /*λ�ñ������, ���ֺ󣬳��򲻻����㣬����λ�����ϵ������*/
      return;                                                          /*���ٽ����κκ���������ֱ�ӷ���*/
    }
  }
  else
  {
    pLegFlexSpike->ULegPositionMonitor.PositionCodeErrTimeMs = 0;
  }

  /*λ�ü������������ϼ��----------------------------------------------------------------------------*/
  pLegFlexSpike->ULegPositionMonitor.PositionCountCur = pLegFlexSpike->SetQry0x4B.ULegPositionCount;
  if(pLegFlexSpike->ULegPositionMonitor.PositionCountHis == pLegFlexSpike->ULegPositionMonitor.PositionCountCur)  /*λ�ü����ޱ仯*/
  {
    if(ON == pLegFlexSpike->CSFlag.Bit.ULegRun)                                                             /*���������ʱ���ۼӴ�����ʧ��ʱ��*/
    {
      if(pLegFlexSpike->ULegPositionMonitor.SensorLostTimeMs <= LEGFLEXSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD)
      {
        pLegFlexSpike->ULegPositionMonitor.SensorLostTimeMs += ExePeriod;                                   /*���������ʱ���ۼӼ���������ʧ��ʱ��*/
      }
      else
      {
        if((LEGFLEXSPIKE_ACTION_SHORTEN == pLegFlexSpike->ULegAction) &&
           (0 == pLegFlexSpike->ULegPositionMonitor.PositionCountCur)  )
        {
          pLegFlexSpike->CSFlag.Bit.ULegShortPositionSensorFault = FAULT;                                   /*�����λ����������*/
        }
        else if((LEGFLEXSPIKE_ACTION_EXTEND == pLegFlexSpike->ULegAction)                       && 
                (ULEGFLEXSPIKE_COUNT_MAX <= pLegFlexSpike->ULegPositionMonitor.PositionCountCur) )
        {
          pLegFlexSpike->CSFlag.Bit.ULegExtendPositionSensorFault = FAULT;                                  /*���λ����������*/
        }
        else 
        {
          pLegFlexSpike->CSFlag.Bit.ULegCountFault = FAULT;                                                 /*��������*/
        }
      }    
    }
    else //if(OFF == pLegFlexSpike->CSFlag.Bit.Run)                                                         /*���û��*/
    {
      pLegFlexSpike->ULegPositionMonitor.SensorLostTimeMs = 0;                                              /*�������������ʧ��ʱ��*/
    }
  }
  else //if(pLegFlexSpike->PositionMonitor.PositionCountHis != pLegFlexSpike->PositionMonitor.PositionCountCur)/*�����б仯*/
  {
    pLegFlexSpike->ULegPositionMonitor.PositionCountHis = pLegFlexSpike->ULegPositionMonitor.PositionCountCur;
    pLegFlexSpike->ULegPositionMonitor.SensorLostTimeMs = 0;                                                /*�������������ʧ��ʱ��*/
  }
  
  
  /*λ�ú��ź�IO��ȡ---------------------------------------------------*/
  pLegFlexSpike->CSFlag.Bit.ULegReachExtendLimt  = BIT_GET(UIOCode, 1);
  pLegFlexSpike->CSFlag.Bit.ULegReachShortenLimt = BIT_GET(UIOCode, 0);

  /*�쵽���ֹͣ�쳤�˶�*/
  if(TRUE == pLegFlexSpike->CSFlag.Bit.ULegReachExtendLimt) 
  {
    if(LEGFLEXSPIKE_ACTION_EXTEND == pLegFlexSpike->ULegAction)
    {
      LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_STOP);
    }
    pLegFlexSpike->CSFlag.Bit.ULegPositionResetOK = TRUE;        /*λ�ø�λ���*/
  }

  /*������̣�ֹͣ�����˶�*/
  if(TRUE == pLegFlexSpike->CSFlag.Bit.ULegReachShortenLimt) 
  {
    if(LEGFLEXSPIKE_ACTION_SHORTEN == pLegFlexSpike->ULegAction)
    {
      LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_STOP);
    }
  }
  
  /*λ��ֵ����*/
  if(TRUE == pLegFlexSpike->CSFlag.Bit.ULegReachExtendLimt) 
  {
    pLegFlexSpike->ULegPositionRealVal = ULEGFLEXSPIKE_POSITION_MAX;
    pLegFlexSpike->ULegPositionMonitor.PositionCountCur = ULEGFLEXSPIKE_COUNT_MAX;         /*����λ�ö�Ҫ��������ֵ*/
  }
  else if(TRUE == pLegFlexSpike->CSFlag.Bit.ULegReachShortenLimt) 
  {
    pLegFlexSpike->ULegPositionRealVal = ULEGFLEXSPIKE_POSITION_MIN;
    pLegFlexSpike->ULegPositionMonitor.PositionCountCur = ULEGFLEXSPIKE_COUNT_MIN;         /*����λ�ö�Ҫ��������ֵ*/
  }
  else
  {
    if(POSITION_COUNT_INC == pLegFlexSpike->ULegPositionMonitor.CountDirection)             /*��������*/
    {
      pLegFlexSpike->ULegPositionRealVal = pLegFlexSpike->ULegPositionMonitor.PositionCountCur/ULEGFLEXSPIKE_COUNT_PER_SEGMENT;
    }
    else //if(POSITION_COUNT_DEC == pLegFlexSpike->PositionMonitor.CountDirection)          /*��������*/
    {
      pLegFlexSpike->ULegPositionRealVal = pLegFlexSpike->ULegPositionMonitor.PositionCountCur/ULEGFLEXSPIKE_COUNT_PER_SEGMENT + 1;
    }
  }
#endif
}


/*
************************************************************************************************************************
* �������� : LegFlexSpike_PauseOn                                                                                                         
* �������� : ��ͣ���                                                                                       
* ������� : ��                                                                                   
* ���ز��� : ��                                                                                            
* ����˵�� : ������������ת�����ֹͣ������ת��
*            ֻ�н����ͣ��������������ת��                                                                                                         
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
* �������� : LegFlexSpike_PauseOff                                                                                                         
* �������� : �����ͣ���                                                                                  
* ������� : ��                                                                                   
* ���ز��� : ��                                                                                            
* ����˵�� : ������������ת�����ֹͣ������ת��
*            ֻ�н����ͣ��������������ת��                                                                                                         
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
* �������� : LegFlexSpike_SetAction                                                                                                         
* �������� : �������Ҫִ�еĶ���                                                                          
* ������� : Action --> ��������ȡֵ��
*                       LEGFLEXSPIKE_ACTION_UP
*                       LEGFLEXSPIKE_ACTION_DOWN
*                       LEGFLEXSPIKE_ACTION_STOP                                                                                   
* ���ز��� : ��                                                                                            
* ����˵�� : ��                                                                                              
************************************************************************************************************************
*/
void LegFlexSpike_SetAction(uint8_t Action)
{
  if((Action != LEGFLEXSPIKE_ACTION_STOP)   &&
     (Action != LEGFLEXSPIKE_ACTION_SHORTEN) &&
     (Action != LEGFLEXSPIKE_ACTION_EXTEND) )
  {
    Action = LEGFLEXSPIKE_ACTION_STOP;       /*����������Ч����ִ��ֹͣ����*/
  }
  
  if((LEGFLEXSPIKE_ACTION_SHORTEN == Action) && 
      (pLegFlexSpike->CSFlag.Bit.ReachShortenLimt))
  {
    return;                                   /*������̣�������ִ�������˶�*/
  }
  
  if((LEGFLEXSPIKE_ACTION_EXTEND == Action) && 
     ((pLegFlexSpike->CSFlag.Bit.ReachExtendLimt) || (pLegFlexSpike->CSFlag.Bit.TouchGround)))
  {
    return;                                   /*�쵽��򴥵أ�������ִ���쳤�˶�*/
  }

  if(Action != LEGFLEXSPIKE_ACTION_STOP) 
  {
    pLegFlexSpike->CSFlag.Bit.Work = TRUE;   /*������Ч����ʼ����*/
  }
  else
  {
    pLegFlexSpike->CSFlag.Bit.Work = FALSE;  /*������ЧЧ���򲻹���*/
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
    Action = LEGFLEXSPIKE_ACTION_STOP;       /*����������Ч����ִ��ֹͣ����*/
  }
  
  if((LEGFLEXSPIKE_ACTION_SHORTEN == Action) && 
      (pLegFlexSpike->CSFlag.Bit.ULegReachShortenLimt))
  {
    return;                                   /*������̣�������ִ�������˶�*/
  }
  
  if((LEGFLEXSPIKE_ACTION_EXTEND == Action) && 
     (pLegFlexSpike->CSFlag.Bit.ULegReachExtendLimt))
  {
    return;                                   /*�쵽��򴥵أ�������ִ���쳤�˶�*/
  }

  if(Action != LEGFLEXSPIKE_ACTION_STOP) 
  {
    pLegFlexSpike->CSFlag.Bit.ULegWork = TRUE;   /*������Ч����ʼ����*/
  }
  else
  {
    pLegFlexSpike->CSFlag.Bit.ULegWork = FALSE;  /*������ЧЧ���򲻹���*/
  }

  pLegFlexSpike->ULegAction = Action;
#endif
}


/*
************************************************************************************************************************
* �������� : LegFlexSpike_GetPosition                                                                                                         
* �������� : ��ȡ�Ƹ�λ��                                                           
* ������� : ��                                                                               
* ���ز��� : �Ƹ˵�ǰλ��                                                                                            
* ����˵�� : ��                                                                                               
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
* �������� : LegFlexSpike_SetPosition                                                                                                         
* �������� : �����Ƹ�λ��                                                         
* ������� : Position --> �Ƹ� ͣ��λ��
*                         ����ֵ��PKEEP          -- ���ֵ�ǰλ�ò�����
*                                 �����������ֵ -- �˶���������ꡣ                                                                                
* ���ز��� : ��                                                                                       
* ����˵�� : ��                                                                                               
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
* �������� : LegFlexSpike_PositionHandle                                                                                                         
* �������� : �Ƹ�ͣ��λ�ô���                                                    
* ������� : ExePeriod -- ������ִ������                                                                     
* ���ز��� : ��                                                                                      
* ����˵�� : λ�õļ��㣬������ȫ���ö�λ��IO�����Ʊ����⣬
*            ����ֻ��ʹ��  �ο���  ���  ��ǰ�������������Ʊ��������㡣
*            ��ˣ����ҵ��ο�����ǰ���޷���ȷ��֪��ǰλ�á�                                                                                               
************************************************************************************************************************
*/
void LegFlexSpike_PositionHandle(Ticker_t ExePeriod)
{
  if(FALSE == pLegFlexSpike->CSFlag.Bit.PositionResetOK)                /*λ�û�û��λ������û�ҵ�λ�ü���ο���*/
  {
    LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_SHORTEN);      
  }
  else //if(TRUE == pLegFlexSpike->CSFlag.Bit.PositionResetOK)          /*λ���Ѿ���λ����λ�ü���ο�����ȷ��*/
  {
    if(PKEEP == pLegFlexSpike->PositionSetVal)                          /*λ�ñ���*/
    {
      LegFlexSpike_SetAction(LEGFLEXSPIKE_ACTION_STOP);
    }
    else                                                                /*����λ��*/
    {
      if(LEGFLEXSPIKE_POSITION_MAX == pLegFlexSpike->PositionSetVal)    /*����λ�� ��������*/
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
      else if(LEGFLEXSPIKE_POSITION_MIN == pLegFlexSpike->PositionSetVal)  /*����λ�� ��������*/
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
  if(FALSE == pLegFlexSpike->CSFlag.Bit.ULegPositionResetOK)                /*λ�û�û��λ������û�ҵ�λ�ü���ο���*/
  {
    LegFlexSpike_SetULegAction(LEGFLEXSPIKE_ACTION_EXTEND);      
  }
  else //if(TRUE == pLegFlexSpike->CSFlag.Bit.ULegPositionResetOK)          /*λ���Ѿ���λ����λ�ü���ο�����ȷ��*/
  {
    if(PKEEP == pLegFlexSpike->ULegPositionSetVal)                          /*λ�ñ���*/
    {
      LegFlexSpike_SetULegAction(LEGFLEXSPIKE_ACTION_STOP);
    }
    else                                                                    /*����λ��*/
    {
      if(ULEGFLEXSPIKE_POSITION_MAX == pLegFlexSpike->ULegPositionSetVal)    /*����λ�� ��������*/
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
      else if(ULEGFLEXSPIKE_POSITION_MIN == pLegFlexSpike->ULegPositionSetVal)  /*����λ�� ��������*/
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
* �������� : LegFlexSpike_ActionHandle                                                                                                         
* �������� : ��ﶯ������                                                                   
* ������� : ExePeriod -- ������ִ������                                                                        
* ���ز��� : ��                                                                                            
* ����˵�� : ��                                                                                              
************************************************************************************************************************
*/
void LegFlexSpike_ActionHandle(Ticker_t ExePeriod)
{
  static uint8_t     ActionHis = 0xFF;                   /*��ʷ����״̬*/
  static uint8_t     ULegActionHis = 0xFF;                   /*��ʷ����״̬*/


  /*����״̬�ĸı��ж�------------------------------------*/
  if(ActionHis != pLegFlexSpike->Action)
  {
    pLegFlexSpike->CSFlag.Bit.Run = OFF;                 /*�����ı䣬����ֹͣ���*/
    ActionHis = pLegFlexSpike->Action;
    pLegFlexSpike->StateCtrlTimeMs = 0;
  }

  pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegFlexAction = pLegFlexSpike->Action;
  
  do
  {
    /*��ͣ��ֹͣ���-----------------------------------------*/
    if(pLegFlexSpike->CSFlag.Bit.Pause > 0)
    {
      pLegFlexSpike->CSFlag.Bit.Run = OFF; 
      pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegFlexAction = LEGFLEXSPIKE_ACTION_STOP;
      break;
    }

    /* �����쳣����ֹͣ���-------------------------------------*/
    if((FAULT == pLegFlexSpike->CSFlag.Bit.PositionCodeFault)        ||        /*λ�ñ������*/
       (FAULT == pLegFlexSpike->CSFlag.Bit.CountFault)               ||        /*��������*/
       (FAULT == pLegFlexSpike->CSFlag.Bit.ShortPositionSensorFault) ||        /*λ�ô���������*/
       (FAULT == pLegFlexSpike->CSFlag.Bit.ExtendPositionSensorFault))         /*λ�ô���������*/
    {
      pLegFlexSpike->CSFlag.Bit.Locked = TRUE;                                 /*�쳣���������*/
      pLegFlexSpike->CSFlag.Bit.Run    = OFF;                                  /*�쳣��ͣ���*/
      pLegFlexSpike->CSFlag.Bit.Work   = FALSE;  
      pLegFlexSpike->StateCtrlTimeMs = 0;
      pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegFlexAction = LEGFLEXSPIKE_ACTION_STOP;
      break;
    }
    
    /*�������--------------------------------------------------*/
    if(pLegFlexSpike->Action != LEGFLEXSPIKE_ACTION_STOP)
    {
      if(pLegFlexSpike->StateCtrlTimeMs < 30000)
      {
        pLegFlexSpike->StateCtrlTimeMs += ExePeriod; 
      }

      if(pLegFlexSpike->StateCtrlTimeMs <= LEGFLEXSPIKE_DIRECTION_TIME_MS)     /*�ȹص��-----------*/
      {
        pLegFlexSpike->CSFlag.Bit.Run = OFF;
      }
      else if(pLegFlexSpike->StateCtrlTimeMs <= LEGFLEXSPIKE_REVERSE_TIME_MS)  /*�л�����------------*/
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
      else if(pLegFlexSpike->StateCtrlTimeMs <= 26000)                         /*�����ת-----------------------------------------*/
      {
        pLegFlexSpike->CSFlag.Bit.Run = ON;
      }
      else                                                                     /*��ʱ�����У���δ��⵽��λ�źţ�����йض�*/
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

  /*����״̬�ĸı��ж�------------------------------------*/
  if(ULegActionHis != pLegFlexSpike->ULegAction)
  {
    pLegFlexSpike->CSFlag.Bit.ULegRun = OFF;                 /*�����ı䣬����ֹͣ���*/
    ULegActionHis = pLegFlexSpike->ULegAction;
    pLegFlexSpike->ULegStateCtrlTimeMs = 0;
  }
  
  pLegFlexSpike->SetQry0x4B.Byte2.Bit.ULegFlexAction = pLegFlexSpike->ULegAction;

  do
  {
    /*��ͣ��ֹͣ���-----------------------------------------*/
    if(pLegFlexSpike->CSFlag.Bit.ULegPause > 0)
    {
      pLegFlexSpike->CSFlag.Bit.ULegRun = OFF; 
      pLegFlexSpike->SetQry0x4B.Byte2.Bit.ULegFlexAction = LEGFLEXSPIKE_ACTION_STOP;
      break;
    }

    /* �����쳣����ֹͣ���-------------------------------------*/
    if((FAULT == pLegFlexSpike->CSFlag.Bit.ULegPositionCodeFault)        ||        /*λ�ñ������*/
       (FAULT == pLegFlexSpike->CSFlag.Bit.ULegCountFault)               ||        /*��������*/
       (FAULT == pLegFlexSpike->CSFlag.Bit.ULegShortPositionSensorFault) ||        /*λ�ô���������*/
       (FAULT == pLegFlexSpike->CSFlag.Bit.ULegExtendPositionSensorFault))         /*λ�ô���������*/
    {
      pLegFlexSpike->CSFlag.Bit.ULegLocked = TRUE;                                 /*�쳣���������*/
      pLegFlexSpike->CSFlag.Bit.ULegRun    = OFF;                                  /*�쳣��ͣ���*/
      pLegFlexSpike->CSFlag.Bit.ULegWork   = FALSE;  
      pLegFlexSpike->ULegStateCtrlTimeMs = 0;
      pLegFlexSpike->SetQry0x4B.Byte2.Bit.ULegFlexAction = LEGFLEXSPIKE_ACTION_STOP;
      break;
    }
    
    /*�������--------------------------------------------------*/
    if(pLegFlexSpike->ULegAction != LEGFLEXSPIKE_ACTION_STOP)
    {
      if(pLegFlexSpike->ULegStateCtrlTimeMs < 30000)
      {
        pLegFlexSpike->ULegStateCtrlTimeMs += ExePeriod; 
      }

      if(pLegFlexSpike->ULegStateCtrlTimeMs <= LEGFLEXSPIKE_DIRECTION_TIME_MS)     /*�ȹص��-----------*/
      {
        pLegFlexSpike->CSFlag.Bit.ULegRun = OFF;
      }
      else if(pLegFlexSpike->ULegStateCtrlTimeMs <= LEGFLEXSPIKE_REVERSE_TIME_MS)  /*�л�����------------*/
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
      else if(pLegFlexSpike->ULegStateCtrlTimeMs <= 26000)                         /*�����ת-----------------------------------------*/
      {
        pLegFlexSpike->CSFlag.Bit.ULegRun = ON;
      }
      else                                                                     /*��ʱ�����У���δ��⵽��λ�źţ�����йض�*/
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
* �������� : LegFlexSpike_Init                                                                                                         
* �������� : �Ƹ˳�ʼ��                                                             
* ������� : ��                                                                    
* ���ز��� : ��                                                                                            
* ����˵�� : ��                                                                                              
************************************************************************************************************************
*/
LegFlexSpike_t* LegFlexSpike_Init(void)
{
  memset(pLegFlexSpike, 0, sizeof(LegFlexSpike_t));        /*������������*/
  
  pLegFlexSpike->CSFlag.Bit.PositionResetOK = FALSE;
  pLegFlexSpike->PositionSetVal                   = LEGFLEXSPIKE_POSITION_MIN;    /*Ҫʹ�õĲο�λ��*/
  pLegFlexSpike->PositionRealVal                  = LEGFLEXSPIKE_POSITION_MAX;    /*����ĵ�ǰλ��*/ 
  pLegFlexSpike->PositionMonitor.PositionCountCur = LEGFLEXSPIKE_COUNT_MAX*2;     /*����ĵ�ǰλ�ü���*/ 

  
#if(1==LEGFLEX_UP_EN)
  pLegFlexSpike->CSFlag.Bit.ULegPositionResetOK = FALSE;
  pLegFlexSpike->ULegPositionSetVal                   = ULEGFLEXSPIKE_POSITION_MAX;   /*Ҫʹ�õĲο�λ��*/
  pLegFlexSpike->ULegPositionRealVal                  = ULEGFLEXSPIKE_POSITION_MIN;   /*����ĵ�ǰλ��*/ 
  pLegFlexSpike->ULegPositionMonitor.PositionCountCur = 0;                            /*����ĵ�ǰλ�ü���*/ 
#endif  
  //BSP_IO_InputInterrupt_RegCB_LegFlexSpikeCount(LegFlexSpike_CountIOCheck_CB);   
  
  return pLegFlexSpike;
}

/*
************************************************************************************************************************
* �������� : LegFlexSpike_GetCSFlag                                                                                                         
* �������� : ��� ���� �� ״̬ ��ʶ                                                           
* ������� : ��                                                                    
* ���ز��� : ������״̬��ʶ �Ľṹ��                                                                                           
* ����˵�� : ��                                                                                              
************************************************************************************************************************
*/
LegFlexSpikeCSFlag_t LegFlexSpike_GetCSFlag(void)
{
  if(0 == BSP_IO_GetVenderTestPin())      /*��װ����£���С�ȸ��أ����������ع��ϸ澯*/
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
* �������� : LegFlexSpike_CDPDataObjRx_0x4B                                                                                      
* �������� : 0x4B �Ƚ���������(���İ�<-->�Ƚſ��ư壩
* ������� : pRxDU   -- ָ����յ����ݶ���Ԫ
*            pAckDU  -- ָ��Ӧ������ݶ���Ԫ
*            SrcAddr -- ���ݵ���Դ
*            Cmd     -- ����
* ���ز��� : ����ɹ��������ݶ��������ݵĳ���    
             �������CDP_DU_HANDLE_ERR ���ݴ������
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t LegFlexSpike_CDPDataObjRx_0x4B(uint8_t *pRxDU, uint8_t *pAckDU, uint8_t SrcAddr, uint8_t Cmd)
{
  /*�������ݵ����İ�-------------------------------------------------------------*/
  memcpy((uint8_t *)&pLegFlexSpike->SetQry0x4B, &pRxDU[CDP_DU_OFFSET_LEN], pRxDU[CDP_DU_OFFSET_LEN]);

  pLegFlexSpike->CSFlag.Bit.TouchGround      = pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegTouchGround;         /*�����ź�*/
  pLegFlexSpike->CSFlag.Bit.TouchFeet        = pLegFlexSpike->SetQry0x4B.Byte0.Bit.LegTouchFeet;           /*�����ź�*/
  
  return pRxDU[CDP_DU_OFFSET_LEN];
}

/*
************************************************************************************************************************
* �������� : LegFlexSpike_CDPDataObjTx_0x4B                                                                                      
* �������� : 0x4B �Ƚ���������(���İ�<-->�Ƚſ��ư壩
* ������� : ��
* ���ز��� : �ɹ��򷵻�Ҫ���͵����ݵ��ڴ��׵�ַ��ʧ�ܷ���NULL��ָ��
* ����˵�� : ��
************************************************************************************************************************
*/
uint8_t* LegFlexSpike_CDPDataObjTx_0x4B(void)
{
  pLegFlexSpike->SetQry0x4B.DataLen = sizeof(pLegFlexSpike->SetQry0x4B);  
  pLegFlexSpike->SetQry0x4B.DataID = 0x4B;  

  return (uint8_t *)&pLegFlexSpike->SetQry0x4B;
}
