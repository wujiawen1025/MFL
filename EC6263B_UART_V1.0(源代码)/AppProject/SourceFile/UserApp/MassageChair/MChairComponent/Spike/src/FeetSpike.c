/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: FeetSpike.c                                                                                                         
**
**    ��������: С���Ƹ�������
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
#include "FeetSpike.h"


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
static void FeetSpike_SetAction(uint8_t Action);


static FeetSpike_t FeetSpike;
FeetSpike_t *pFeetSpike = &FeetSpike;


#if (FEETSPIKE_POSITION_DETECT_MODE == FEETSPIKE_POSITION_DETECT_BY_CODE) /*λ�ü��ʹ�����̱��뷽ʽ*/
/*
* �Ƹ�λ�õ㣬���̱����
*
* С���Ƹ�ʹ������ȫ��2λ�����Ʊ��� 
* ʹ��λ�ñ����������ȷ��λ�á�
* ��׺����λ�û�Ӧʹ�ñ��루���10  �00����ȷ����
*
* ���̱����(͸�� 1  �ڵ� 0)��
* B(10)   //��� 
* B(11)   //
* B(01)   //
* B(00)   //� 
*/
static const PositionCodeMap_t FeetSpike_PositionCodeMapTab[] =
{
  {B(10), B(11), FEETSPIKE_POSITION_MIN},  
  {B(11), B(01), 1},
  {B(01), B(00), FEETSPIKE_POSITION_MAX}
};

#define  FEETSPIKE_POSITION_CODE_MAPTAB_NUM   TAB_NUM(FeetSpike_PositionCodeMapTab)

#endif /*���� #if(FEETSPIKE_POSITION_DETECT_MODE == FEETSPIKE_POSITION_DETECT_BY_CODE)*/




/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/

#if (FEETSPIKE_POSITION_DETECT_MODE == FEETSPIKE_POSITION_DETECT_BY_CODE) /*λ�ü��ʹ�����̱��뷽ʽ*/
/*
************************************************************************************************************************
* �������� : FeetSpike_PositionCodeMap                                                                                                         
* �������� : �Ƹ�λ�� ���� ӳ��                                                                                                     
* ������� : CodeCur -- ��ǰλ�ñ���                                                                                                      
* ���ز��� : ���� FEETSPIKE_POSITION_MAX       -- ��Ч�ı��룬λ�ô������⡣
*            С�ڻ����FEETSPIKE_POSITION_MAX  -- λ�ñ�����Ч                                                                                                        
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t FeetSpike_PositionCodeMap(uint8_t CodeCur)
{
  uint8_t i;
  uint8_t Position;
  static uint8_t CodeHis = 0xFF;


  Position = pFeetSpike->PositionRealVal;            /*�ȼ���λ��û�ı䣬���´��뽫��������ı�Position�ĸ�ֵ*/

  /*��׺����λ�ã� ����ʹ��λ�ñ�����ȷ��*/
  if(B(10) == CodeCur)
  {
    Position = FEETSPIKE_POSITION_MIN;
    pFeetSpike->CSFlag.Bit.ReachDownLimt = TRUE;
    pFeetSpike->CSFlag.Bit.ReachUpLimt = FALSE; 
  }
  else if(B(00) == CodeCur)
  {
    Position =  FEETSPIKE_POSITION_MAX;
    pFeetSpike->CSFlag.Bit.ReachUpLimt = TRUE; 
    pFeetSpike->CSFlag.Bit.ReachDownLimt = FALSE;
  }

  /*ʹ�ñ���������ȷ��λ��*/
  else if(CodeHis != CodeCur) 
  {
    for(i=0; i<FEETSPIKE_POSITION_CODE_MAPTAB_NUM; i++)
    {
      if((CodeHis == FeetSpike_PositionCodeMapTab[i].HopCode1) && 
         (CodeCur == FeetSpike_PositionCodeMapTab[i].HopCode2) )
      {
        Position = FeetSpike_PositionCodeMapTab[i].Positon;
        break;
      }
      else if((CodeHis == FeetSpike_PositionCodeMapTab[i].HopCode2) && 
              (CodeCur == FeetSpike_PositionCodeMapTab[i].HopCode1) )
      {
        Position = FeetSpike_PositionCodeMapTab[i].Positon;
        break;
      }
    }

    pFeetSpike->CSFlag.Bit.ReachUpLimt   = FALSE;    /*���벻���ڼ���λ�ã�������ޱ�ʶ*/
    pFeetSpike->CSFlag.Bit.ReachDownLimt = FALSE;
  }
  else
  {
    //Position = pFeetSpike->PositionRealVal; /*û�������䣬�򱣳�ԭλ��*/
    pFeetSpike->CSFlag.Bit.ReachUpLimt   = FALSE;    /*���벻���ڼ���λ�ã�������ޱ�ʶ*/
    pFeetSpike->CSFlag.Bit.ReachDownLimt = FALSE;
  }

  CodeHis = CodeCur;
  return Position; 
}

/*
************************************************************************************************************************
* �������� : FeetSpike_PositionIOCheck                                                                                                         
* �������� : λ�� IO�ڵļ��                                                                                            
* ������� : ExePeriod -- ������ִ������                                                                                                 
* ���ز��� : ��                                                                                             
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void FeetSpike_PositionIOCheck(Ticker_t ExePeriod)
{
  static uint8_t StableIOCode;                                      /*�ȶ��ı���*/
  static uint8_t StableStat;                                        /*״̬�ȶ�ͳ��*/
  static uint8_t IOCode = B(00);                                  /*Ҫ��λ���ף��ȼ����ʼΪ���*/


  /*��ʱ���и��ţ����������״̬�ȶ����ж�------------------------*/
  if(StableIOCode != (BSP_IO_ReadInput_FeetSpikePosition() & B(11)))
  {
    StableStat = 0;                                                 /*�����仯���ʾ���ȶ�*/
    StableIOCode = BSP_IO_ReadInput_FeetSpikePosition() & B(11);    /*������*/
  }
  else
  {
    if(StableStat < 10)   
    {
      StableStat++;                                                 /*û�����仯�����ȶ�ͳ������*/ 
    }
    else
    {
      IOCode = StableIOCode;                                        /*��ȡ�ȶ���ı���*/
    }
  }


  /* ���ȼ��λ�ñ����Ƿ���ϣ�---------------------------------------------
   * һ��ֻ�����̰�װ���󣬻���û����ʱ��ͣ�����г̣��Ż�������ֹ���
   * ע������ʹ����ȫ�����Ʊ��룬������ λ�ñ������ �ļ�⡣ */


  /*λ�ô��������ϼ�� ------------------------------------------------*/
  if(pFeetSpike->PositionMonitor.PositionCode == IOCode)            /*λ��û�ı�*/
  {
    if(ON == pFeetSpike->CSFlag.Bit.Run)                            /*���������ʱ���ۼӴ�����ʧ��ʱ��*/
    {
      if(pFeetSpike->PositionMonitor.SensorLostTimeMs <= FEETSPIKE_POSITION_SENSOR_LOST_TIME_THRESHOLD) /*δ����ʧ������ʱ��*/
      {
        pFeetSpike->PositionMonitor.SensorLostTimeMs += ExePeriod;
      }
      else
      {
        pFeetSpike->CSFlag.Bit.PositionSensorFault = FAULT;         /*λ�ô��������ϣ����ֺ󣬳��򲻻����㣬����λ�����ϵ������*/
      }
    }
    else
    {
      pFeetSpike->PositionMonitor.SensorLostTimeMs = 0;             /*���㴫����ʧ��ʱ��*/
    }
  }
  else  /*λ�øı�*/
  { 
    pFeetSpike->PositionMonitor.SensorLostTimeMs = 0;	              /*���㴫����ʧ��ʱ��*/
  }


  /*λ����ر����ж������--------------------------------------------*/
  pFeetSpike->PositionRealVal = FeetSpike_PositionCodeMap(IOCode);
  if(FEETSPIKE_POSITION_MIN == pFeetSpike->PositionRealVal)       /*���λ��*/
  {
    pFeetSpike->CSFlag.Bit.PositionResetOK = TRUE;                /*λ�ø�λ���*/
  }

  if((FEETSPIKE_ACTION_UP == pFeetSpike->Action) && (pFeetSpike->CSFlag.Bit.ReachUpLimt))
  {
    FeetSpike_SetAction(FEETSPIKE_ACTION_STOP);                     /*�ﵽ����λ������ִ�������˶�*/
  }

  if((FEETSPIKE_ACTION_DOWN == pFeetSpike->Action) && (pFeetSpike->CSFlag.Bit.ReachDownLimt))
  {
    FeetSpike_SetAction(FEETSPIKE_ACTION_STOP);                     /*�ﵽ����λ������ִ�������˶�*/
  }

  pFeetSpike->PositionMonitor.PositionCode = IOCode;                /*��¼�±���*/
}

#endif /*���� #if(FEETSPIKE_POSITION_DETECT_MODE == FEETSPIKE_POSITION_DETECT_BY_CODE)*/



#if (FEETSPIKE_POSITION_DETECT_MODE == FEETSPIKE_POSITION_DETECT_BY_COUNT) /*λ�ü��ʹ�ü�����ʽ*/
/*
************************************************************************************************************************
* �������� : FeetSpike_CountIOCheck_CB                                                                                                         
* �������� : λ�� ����IO�ڼ��  �Ļص�����                                                                                          
* ������� : ��                                                                                    
* ���ز��� : ��                                                                                             
* ����˵�� : �ú���ͨ�� BSP_IO_InputInterrupt_RegCB_FeetSpikeCount(FeetSpike_CountIOCheck_CB);����ע���BSP��                                                                                                         
************************************************************************************************************************
*/
static void FeetSpike_CountIOCheck_CB(void)
{
  /*_COUNT_MIN+3���������������Ƹ�ͣ��ʱ�򣬼���ֵ������0������ӿ쵽0�Ĵ���*/
  MotorCountUpdata(&pFeetSpike->PositionMonitor.PositionCountCur, 
                   pFeetSpike->PositionMonitor.CountDirection, 
                   FEETSPIKE_COUNT_MAX, FEETSPIKE_COUNT_MIN+3);
}

/*
************************************************************************************************************************
* �������� : FeetSpike_PositionIOCheck                                                                                                         
* �������� : λ�� IO�ڵļ��                                                                                   
* ������� : ExePeriod -- ������ִ������                                                                                  
* ���ز��� : ��                                                                                             
* ����˵�� : ��                                                                                                       
************************************************************************************************************************
*/
void FeetSpike_PositionIOCheck(Ticker_t ExePeriod)
{
  static  Ticker_t ReachMinCountMs;

  /*�������������ϼ��---------------------------------------------*/
  if(pFeetSpike->PositionMonitor.PositionCountHis == pFeetSpike->PositionMonitor.PositionCountCur)  /*�����ޱ仯*/
  {
    if(ON == pFeetSpike->CSFlag.Bit.Run)                                             /*�Ƹ˿���*/
    {
      if(pFeetSpike->PositionMonitor.SensorLostTimeMs <= FEETSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD)
      {
        pFeetSpike->PositionMonitor.SensorLostTimeMs += ExePeriod;                   /*���������ʱ���ۼӼ���������ʧ��ʱ��*/
      }
      else
      {
        FeetSpike_SetAction(FEETSPIKE_ACTION_STOP);                                  /*����һ��ֹͣ����ֹͣ����˶�*/

        if(FALSE == pFeetSpike->CSFlag.Bit.PositionResetOK)                          /*λ�û�δ��λ��ɣ�����ϵ�Ҫ���ҳ�ʼλ��*/
        {
          pFeetSpike->CSFlag.Bit.PositionResetOK = TRUE;                             /*λ�ø�λ���*/
          pFeetSpike->PositionMonitor.PositionCountCur = FEETSPIKE_COUNT_MIN;        /*����λ�ö�Ҫ��������ֵ*/
          pFeetSpike->PositionRealVal = FEETSPIKE_POSITION_MIN;
        }
        else  //if(TRUE == pFeetSpike->CSFlag.Bit.PositionResetOK)                   /*λ���Ѿ���λ��ɵ�*/
        {
          if((pFeetSpike->PositionSetVal > FEETSPIKE_POSITION_MIN) &&                /*Ҫ�˶����м��λ�õ�*/
             (pFeetSpike->PositionSetVal < FEETSPIKE_POSITION_MAX) )
          {
            pFeetSpike->CSFlag.Bit.CountFault = TRUE;                                /*�м�λ�õ���ּ���ֹͣ�����ʾ����������������*/
          }
          else if(FEETSPIKE_POSITION_MIN == pFeetSpike->PositionSetVal)              /*Ҫ�˶�����Сλ��*/
          {
            if(pFeetSpike->PositionMonitor.PositionCountCur > FEETSPIKE_COUNT_PER_SEGMENT)
            {
              pFeetSpike->CSFlag.Bit.CountFault = TRUE;                              /*��Сλ�ü���ֵ����С���ʾ����������������*/
            }
            pFeetSpike->PositionMonitor.PositionCountCur = FEETSPIKE_COUNT_MIN;      /*����λ�ö�Ҫ��������ֵ*/
          }
          else //if(FEETSPIKE_POSITION_MAX == pFeetSpike->PositionSetVal)            /*Ҫ�˶������λ��*/     
          {
            if(pFeetSpike->PositionMonitor.PositionCountCur < (FEETSPIKE_COUNT_MAX - FEETSPIKE_COUNT_PER_SEGMENT))
            {
              pFeetSpike->CSFlag.Bit.CountFault = TRUE;                              /*���λ�ü���ֵ���������ʾ����������������*/
            }
            pFeetSpike->PositionMonitor.PositionCountCur = FEETSPIKE_COUNT_MAX;      /*����λ�ö�Ҫ��������ֵ*/
          }
        }
      }  
      
      pFeetSpike->CSFlag.Bit.CountFault &= pFeetSpike->CSFlag.Bit.CountFaultCheckSw; /*��⿪����Ч�Ĳ��澯*/
    }
    else //if(OFF == pFeetSpike->CSFlag.Bit.Run)                                     /*�Ƹ�û��*/
    {
      pFeetSpike->PositionMonitor.SensorLostTimeMs = 0;                              /*�������������ʧ��ʱ��*/
    }
  }
  else //if(pFeetSpike->PositionMonitor.PositionCountHis != pFeetSpike->PositionMonitor.PositionCountCur)   /*�����б仯*/
  {
    pFeetSpike->PositionMonitor.PositionCountHis = pFeetSpike->PositionMonitor.PositionCountCur;
    pFeetSpike->PositionMonitor.SensorLostTimeMs = 0;                                /*�������������ʧ��ʱ��*/
  }
  
  /*�ɼ���ֵ�������ǰ��λ�õ�---------------------------------------------------------------*/
  if(FEETSPIKE_COUNT_MIN == pFeetSpike->PositionMonitor.PositionCountCur)
  {
    if(ReachMinCountMs < 400)        /*����ʼλ�ö�����400ms��У��ʱ��*/
    {
      ReachMinCountMs += ExePeriod;
    }
    else
    {
      pFeetSpike->PositionRealVal          = FEETSPIKE_POSITION_MIN;
      pFeetSpike->CSFlag.Bit.ReachDownLimt = TRUE;                                     /*���Ｋ��λ��*/
      pFeetSpike->CSFlag.Bit.ReachUpLimt   = FALSE;                                
    }
  }
  else if(FEETSPIKE_COUNT_MAX == pFeetSpike->PositionMonitor.PositionCountCur)
  {
    ReachMinCountMs = 0;
    pFeetSpike->PositionRealVal          = FEETSPIKE_POSITION_MAX;
    pFeetSpike->CSFlag.Bit.ReachUpLimt   = TRUE;                                     /*���Ｋ��λ��*/
    pFeetSpike->CSFlag.Bit.ReachDownLimt = FALSE;                               
  }
  else
  {
    ReachMinCountMs = 0;
    pFeetSpike->CSFlag.Bit.ReachUpLimt   = FALSE;                                    /*�����ڼ���λ��*/
    pFeetSpike->CSFlag.Bit.ReachDownLimt = FALSE;                                    /*�����ڼ���λ��*/

    if(OFF == pFeetSpike->CSFlag.Bit.Run)
    {
      return;                                                                        /*�����תʱ���Ÿ��¼���λ��ֵ*/
    }
    
    if(POSITION_COUNT_INC == pFeetSpike->PositionMonitor.CountDirection)             /*��������*/
    {
      pFeetSpike->PositionRealVal = pFeetSpike->PositionMonitor.PositionCountCur/FEETSPIKE_COUNT_PER_SEGMENT;
    }
    else //if(POSITION_COUNT_DEC == pFeetSpike->PositionMonitor.CountDirection)      /*��������*/
    {
      pFeetSpike->PositionRealVal = (pFeetSpike->PositionMonitor.PositionCountCur/FEETSPIKE_COUNT_PER_SEGMENT) + 1;
    }
  }
}

#endif  /* ����if(FEETSPIKE_POSITION_DETECT_MODE == FEETSPIKE_POSITION_DETECT_BY_COUNT) */


/*
************************************************************************************************************************
* �������� : FeetSpike_OverCurrentIOCheck                                                                                                         
* �������� : �Ƹ˹����� IO�ڵļ��                                                                               
* ������� : ExePeriod -- ������ִ������                                                                                  
* ���ز��� : ��                                                                                             
* ����˵�� : ��                                                                                                       
************************************************************************************************************************
*/
void FeetSpike_OverCurrentIOCheck(Ticker_t ExePeriod)
{
  uint8_t IOCode;

  IOCode = BSP_IO_ReadInput_FeetSpikeOverCurrent(); 
  if(FEETSPIKE_OVER_CURRENT_LEVEL == IOCode)
  {
    if(pFeetSpike->OverCurrentTimeMs <= FEETSPIKE_OVER_CURRENT_TIME_THRESHOLD)
    {
      pFeetSpike->OverCurrentTimeMs += ExePeriod;
    }
    else
    {
      pFeetSpike->CSFlag.Bit.OverCurrentFault = FAULT; 
    }
  }
  else
  {
    pFeetSpike->OverCurrentTimeMs = 0;
  }
}


/*
************************************************************************************************************************
* �������� : FeetSpike_PauseOn                                                                                                         
* �������� : ��ͣ�Ƹ�                                                                            
* ������� : ��                                                                                
* ���ز��� : ��                                                                                             
* ����˵�� : ������������ת�����ֹͣ������ת��
*            ֻ�н����ͣ��������������ת��                                                                                                      
************************************************************************************************************************
*/
void FeetSpike_PauseOn(void)
{
  if(pFeetSpike->CSFlag.Bit.Pause < 0x1F)
  {
    pFeetSpike->CSFlag.Bit.Pause++;
  }
}

/*
************************************************************************************************************************
* �������� : FeetSpike_PauseOff                                                                                                         
* �������� : �����ͣ�Ƹ�                                                                        
* ������� : ��                                                                                
* ���ز��� : ��                                                                                             
* ����˵�� : ������������ת�����ֹͣ������ת��
*            ֻ�н����ͣ��������������ת��                                                                                                      
************************************************************************************************************************
*/
void FeetSpike_PauseOff(void)
{
  if(pFeetSpike->CSFlag.Bit.Pause > 0)
  {
    pFeetSpike->CSFlag.Bit.Pause--;
  }
}


/*
************************************************************************************************************************
* �������� : FeetSpike_SetAction                                                                                                         
* �������� : �����Ƹ�Ҫִ�еĶ���                                                                  
* ������� : Action --> ��������ȡֵ��
*                       FEETSPIKE_ACTION_UP
*                       FEETSPIKE_ACTION_DOWN
*                       FEETSPIKE_ACTION_STOP                                                                                
* ���ز��� : ��                                                                                             
* ����˵�� : ��                                                                                               
************************************************************************************************************************
*/
void FeetSpike_SetAction(uint8_t Action)
{
  if((Action != FEETSPIKE_ACTION_UP)   &&
     (Action != FEETSPIKE_ACTION_DOWN) &&
     (Action != FEETSPIKE_ACTION_STOP) )
  {
    Action = FEETSPIKE_ACTION_STOP;       /*����������Ч����ִ��ֹͣ����*/
  }
  
  if((FEETSPIKE_ACTION_UP == Action) && (pFeetSpike->CSFlag.Bit.ReachUpLimt))
  {
    return;                               /*�ﵽ����λ������ִ�������˶�*/
  }
  
  if((FEETSPIKE_ACTION_DOWN == Action) && (pFeetSpike->CSFlag.Bit.ReachDownLimt))
  {
    return;                               /*�ﵽ����λ������ִ�������˶�*/
  }

  if(TRUE == pFeetSpike->CSFlag.Bit.Locked)  
  {
    return;                               /*��ﱻ������ִ���κζ���*/
  }

  if(Action != FEETSPIKE_ACTION_STOP) 
  {
    pFeetSpike->CSFlag.Bit.Work = TRUE;   /*������Ч����ʼ����*/
  }
  else
  {
    pFeetSpike->CSFlag.Bit.Work = FALSE;  /*������ЧЧ���򲻹���*/
  }

  pFeetSpike->Action = Action;
}

/*
************************************************************************************************************************
* �������� : FeetSpike_GetPosition                                                                                                         
* �������� : ��ȡ�Ƹ�λ��                                                           
* ������� : ��                                                                               
* ���ز��� : �Ƹ˵�ǰλ��                                                                                            
* ����˵�� : ��                                                                                               
************************************************************************************************************************
*/
uint8_t FeetSpike_GetPosition(void)
{
  return pFeetSpike->PositionRealVal;
  //return  pFeetSpike->PositionSetVal; 
}

/*
************************************************************************************************************************
* �������� : FeetSpike_SetPosition                                                                                                         
* �������� : �����Ƹ�λ��                                                         
* ������� : Position --> �Ƹ� ͣ��λ��
*                         ����ֵ��PKEEP          -- ���ֵ�ǰλ�ò�����
*                                 �����������ֵ -- �˶���������ꡣ                                                                                
* ���ز��� : ��                                                                                       
* ����˵�� : ��                                                                                               
************************************************************************************************************************
*/
void FeetSpike_SetPosition(uint8_t Position)
{
  if((Position > FEETSPIKE_POSITION_MAX) &&(Position != PKEEP)) 
  {
    Position = FEETSPIKE_POSITION_MAX;
  }

  pFeetSpike->PositionSetVal = Position; 
}

/*
************************************************************************************************************************
* �������� : FeetSpike_PositionHandle                                                                                                         
* �������� : �Ƹ�ͣ��λ�ô���                                                    
* ������� : ExePeriod -- ������ִ������                                                                     
* ���ز��� : ��                                                                                      
* ����˵�� : λ�õļ��㣬������ȫ���ö�λ��IO�����Ʊ����⣬
*            ����ֻ��ʹ��  �ο���  ���  ��ǰ�������������Ʊ��������㡣
*            ��ˣ����ҵ��ο�����ǰ���޷���ȷ��֪��ǰλ�á�                                                                                               
************************************************************************************************************************
*/
void FeetSpike_PositionHandle(Ticker_t ExePeriod)
{
  if(FALSE == pFeetSpike->CSFlag.Bit.PositionResetOK)                /*λ�û�û��λ������û�ҵ�λ�ü���ο���*/
  {
    FeetSpike_SetAction(FEETSPIKE_ACTION_DOWN);
  }
  else                                                               /*λ���Ѿ���λ����λ�ü���ο�����ȷ��*/
  {
    if(PKEEP == pFeetSpike->PositionSetVal)                          /*λ�ñ���*/
    {
      FeetSpike_SetAction(FEETSPIKE_ACTION_STOP);
    }
    else                                                             /*����λ��*/
    {
      if(FEETSPIKE_POSITION_MIN == pFeetSpike->PositionSetVal)       /*����λ�� ��������*/
      {
        if(FALSE == pFeetSpike->CSFlag.Bit.ReachDownLimt)
        {
          FeetSpike_SetAction(FEETSPIKE_ACTION_DOWN);
        }
        else
        {
          FeetSpike_SetAction(FEETSPIKE_ACTION_STOP);
        }
      }
      else if(FEETSPIKE_POSITION_MAX == pFeetSpike->PositionSetVal)  /*����λ�� ��������*/
      {
        if(FALSE == pFeetSpike->CSFlag.Bit.ReachUpLimt)
        {
          FeetSpike_SetAction(FEETSPIKE_ACTION_UP);
        }
        else
        {
          FeetSpike_SetAction(FEETSPIKE_ACTION_STOP);
        }
      }
      else if(pFeetSpike->PositionSetVal == pFeetSpike->PositionRealVal)
      {
        FeetSpike_SetAction(FEETSPIKE_ACTION_STOP);
      }
      else if(pFeetSpike->PositionSetVal > pFeetSpike->PositionRealVal)
      {
        FeetSpike_SetAction(FEETSPIKE_ACTION_UP);
      }
      else //(pFeetSpike->PositionSetVal < pFeetSpike->PositionRealVal)
      {
        FeetSpike_SetAction(FEETSPIKE_ACTION_DOWN);
      }
    }
  }
}


/*
************************************************************************************************************************
* �������� : FeetSpike_ActionHandle                                                                                                         
* �������� : ��ﶯ������                                           
* ������� : ExePeriod -- ������ִ������                                                                     
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/
void FeetSpike_ActionHandle(Ticker_t ExePeriod)
{
  static uint8_t     ActionHis = 0xFF;                                    /*��ʷ����״̬*/


  /*����״̬�ĸı��ж�------------------------------------*/
  if(ActionHis != pFeetSpike->Action)
  {
    pFeetSpike->CSFlag.Bit.Run = OFF;                                     /*�����ı䣬����ֹͣ���*/
    if(ActionHis != FEETSPIKE_ACTION_STOP)
    {
      pFeetSpike->StateCtrlTimeMs = 0;                                    /*��<-->�� �� ��/��-->ֹͣ��������ʱ��*/
    }
    ActionHis = pFeetSpike->Action;
  }

  do
  {
    /*��ͣ��ֹͣ���-----------------------------------------*/
    if(pFeetSpike->CSFlag.Bit.Pause > 0)
    {
      pFeetSpike->CSFlag.Bit.Run = OFF;
      pFeetSpike->PWMFinalSetVal = FEETSPIKE_PWM_MIN;    /*��ͣ�����������Ҳ��Ҫ������*/
     break;
    }

    /* �����쳣����ֹͣ���-------------------------------------*/
    if((FAULT == pFeetSpike->CSFlag.Bit.PositionCodeFault)   ||           /*λ�ñ������*/
       (FAULT == pFeetSpike->CSFlag.Bit.PositionSensorFault) ||           /*λ�ô���������*/
       (FAULT == pFeetSpike->CSFlag.Bit.CountFault)          ||           /*��������*/
       (FAULT == pFeetSpike->CSFlag.Bit.OverCurrentFault)    )            /*����������*/
    {
      pFeetSpike->CSFlag.Bit.Locked = TRUE;                               /*�쳣���������*/
      pFeetSpike->CSFlag.Bit.Run    = OFF;                                /*�쳣��ͣ���*/
      pFeetSpike->CSFlag.Bit.Work   = FALSE;  
      pFeetSpike->StateCtrlTimeMs = 0;
      break;
    }

    /*�������--------------------------------------------------*/
    if(pFeetSpike->Action != FEETSPIKE_ACTION_STOP)
    {
      if(pFeetSpike->StateCtrlTimeMs < 5000)
      {
        pFeetSpike->StateCtrlTimeMs += ExePeriod; 
      }

      if(pFeetSpike->StateCtrlTimeMs <= FEETSPIKE_DIRECTION_TIME_MS)      /*�ȹص��-----------*/
      {
        pFeetSpike->CSFlag.Bit.Run = OFF;
        pFeetSpike->PWMFinalSetVal = 0;                   /*������*/
      }
      else if(pFeetSpike->StateCtrlTimeMs <= FEETSPIKE_REVERSE_TIME_MS)   /*�л�����------------*/
      {
        if(FEETSPIKE_ACTION_UP == pFeetSpike->Action)
        {
          pFeetSpike->UpRunTimeMs                    = 0; 
          pFeetSpike->CSFlag.Bit.Direction           = FEETSPIKE_DIRECTION_UP;
          pFeetSpike->PositionMonitor.CountDirection = POSITION_COUNT_INC;
        }
        else //if(FEETSPIKE_ACTION_DOWN == pFeetSpike->Action)
        {
          pFeetSpike->DownRunTimeMs                  = 0; 
          pFeetSpike->CSFlag.Bit.Direction           = FEETSPIKE_DIRECTION_DOWN;
          pFeetSpike->PositionMonitor.CountDirection = POSITION_COUNT_DEC;
        }
        pFeetSpike->PWMFinalSetVal = FEETSPIKE_PWM_MIN;     /*������*/
      }
      else /*�����ת---------------------------------------------------------------------------*/
      {
        pFeetSpike->CSFlag.Bit.Run = ON;
        if(pFeetSpike->PWMFinalSetVal < FEETSPIKE_PWM_MAX)  /*������*/
        {
          pFeetSpike->PWMFinalSetVal += FEETSPIKE_PWM_FIXED_STEPING_VAL;
        }
        else
        {
          pFeetSpike->PWMFinalSetVal = FEETSPIKE_PWM_MAX;
        }

        if(FEETSPIKE_ACTION_UP == pFeetSpike->Action)
        {
          if(pFeetSpike->UpRunTimeMs < (0xFFFF-ExePeriod))                /*-ExePeriod :��ֹ�Ӳ������*/
          {
            pFeetSpike->UpRunTimeMs += ExePeriod; 
          }
        }
        else //if(FEETSPIKE_ACTION_DOWN == pFeetSpike->Action)
        {
          if(pFeetSpike->DownRunTimeMs < (0xFFFF-ExePeriod))              /*-ExePeriod :��ֹ�Ӳ������*/
          {
            pFeetSpike->DownRunTimeMs += ExePeriod; 
          }
        }

        pFeetSpike->RunTimeMs += ExePeriod;                               /*ͳ�������תʱ��*/
      }
    }
    else /*pFeetSpike->Action == FEETSPIKE_ACTION_STOP*/
    {
      pFeetSpike->CSFlag.Bit.Run = OFF;
      if(pFeetSpike->StateCtrlTimeMs < FEETSPIKE_DIRECTION_TIME_MS)       /*ֹͣʱ�����ۼ�ֹͣʱ�䣬Ҫ����ʱ���ɼӿ�����*/
      {
        pFeetSpike->StateCtrlTimeMs += ExePeriod; 
      }
    }
  }while(0);

  BSP_IO_SetOutput_FeetSpikeCtrl(pFeetSpike->CSFlag.Bit.Run, pFeetSpike->CSFlag.Bit.Direction, pFeetSpike->PWMFinalSetVal);
}


/*
************************************************************************************************************************
* �������� : FeetSpike_Init                                                                                                         
* �������� : �Ƹ˳�ʼ��                                   
* ������� : ��                                                             
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/
FeetSpike_t* FeetSpike_Init(void)
{
  memset(pFeetSpike, 0, sizeof(FeetSpike_t));                                 /*������������*/
  FeetSpike_ResetPosition();
  #if (FEETSPIKE_POSITION_DETECT_MODE == FEETSPIKE_POSITION_DETECT_BY_COUNT)  /*λ�ü��ʹ�ü�����ʽ*/
    BSP_IO_InputInterrupt_RegCB_FeetSpikeCount(FeetSpike_CountIOCheck_CB);    
  #endif
  
  return pFeetSpike;
}


/*
************************************************************************************************************************
* �������� : FeetSpike_GetCSFlag                                                                                                         
* �������� : ��� ���� �� ״̬ ��ʶ                                   
* ������� : ��                                                             
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/
FeetSpikeCSFlag_t FeetSpike_GetCSFlag(void)
{
  return pFeetSpike->CSFlag;
}


/*
************************************************************************************************************************
* �������� : FeetSpike_ResetPosition                                                                                                         
* �������� : ��λλ��                                   
* ������� : ��                                                             
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/
void FeetSpike_ResetPosition(void)
{
  pFeetSpike->CSFlag.Bit.PositionResetOK = FALSE;
  pFeetSpike->PositionSetVal                   = FEETSPIKE_POSITION_MIN;    /*Ҫʹ�õĲο�λ��*/
  pFeetSpike->PositionRealVal                  = FEETSPIKE_POSITION_MAX;    /*����ĵ�ǰλ��*/   
  pFeetSpike->PositionMonitor.PositionCountCur = FEETSPIKE_COUNT_MAX*2;     /*����ĵ�ǰλ�ü���*/ 
}

/*
************************************************************************************************************************
* �������� : FeetSpike_SetCountFaultCheckSw                                                                                                          
* �������� : ���ü������ϼ�⿪��                                  
* ������� : Sw -- ON  ��
*                  OFF ��
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/
void FeetSpike_SetCountFaultCheckSw(uint8_t Sw)
{
  if((Sw != ON) && (Sw != OFF))
  {
    Sw = OFF;
  }
  pFeetSpike->CSFlag.Bit.CountFaultCheckSw = Sw;
}

