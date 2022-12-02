/*
========================================================================================================================
**���ļ�������                                        ���ļ�������                                        ���ļ�������**
========================================================================================================================
**    �ļ�����: BackSpike.c                                                                                                         
**
**    ��������: �����Ƹ�������
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
#include "BackSpike.h"


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
static void BackSpike_SetAction(uint8_t Action);


static BackSpike_t BackSpike;
BackSpike_t *pBackSpike = &BackSpike;


#if (BACKSPIKE_POSITION_DETECT_MODE == BACKSPIKE_POSITION_DETECT_BY_CODE) /*λ�ü��ʹ�����̱��뷽ʽ*/
/*
* �Ƹ�λ�õ㣬���̱����
*
* �����Ƹ�ʹ������ȫ��2λ�����Ʊ��� 
* ʹ��λ�ñ����������ȷ��λ�á�
* ��׺����λ�û�Ӧʹ�ñ��루���00  �10����ȷ����
*
* ���̱����(͸�� 1  �ڵ� 0)��
*  B(00)   //��� 
*  B(01),  //
*  B(11),  //
*  B(10)   //� 
*/
static const PositionCodeMap_t BackSpike_PositionCodeMapTab[] =
{
  {B(00), B(01), BACKSPIKE_POSITION_MAX},  
  {B(01), B(11), 1},
  {B(11), B(10), BACKSPIKE_POSITION_MIN}
};

#define  BACKSPIKE_POSITION_CODE_MAPTAB_NUM   TAB_NUM(BackSpike_PositionCodeMapTab)

#endif /*���� #if(BACKSPIKE_POSITION_DETECT_MODE == BACKSPIKE_POSITION_DETECT_BY_CODE)*/



/*
========================================================================================================================
*���������塿                                          ���������塿                                          ���������塿
========================================================================================================================
*/

#if (BACKSPIKE_POSITION_DETECT_MODE == BACKSPIKE_POSITION_DETECT_BY_CODE) /*λ�ü��ʹ�����̱��뷽ʽ*/
/*
************************************************************************************************************************
* �������� : BackSpike_PositionCodeMap                                                                                                         
* �������� : �Ƹ�λ�� ���� ӳ��                                                                                                     
* ������� : CodeCur -- ��ǰλ�ñ���                                                                                                      
* ���ز��� : ���� BACKSPIKE_POSITION_MAX       -- ��Ч�ı��룬λ�ô������⡣
*            С�ڻ����BACKSPIKE_POSITION_MAX  -- λ�ñ�����Ч                                                                                                        
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
uint8_t BackSpike_PositionCodeMap(uint8_t CodeCur)
{
  uint8_t i;
  uint8_t Position;
  static uint8_t CodeHis = 0xFF;


  Position = pBackSpike->PositionRealVal;             /*�ȼ���λ��û�ı䣬���´��뽫��������ı�Position�ĸ�ֵ*/

  /*��׺����λ�ã� ����ʹ��λ�ñ�����ȷ��*/
  if(B(00) == CodeCur)
  {
    Position = BACKSPIKE_POSITION_MAX;
    pBackSpike->CSFlag.Bit.ReachDownLimt = TRUE;
    pBackSpike->CSFlag.Bit.ReachUpLimt = FALSE; 
  }
  else if(B(10) == CodeCur)
  {
    Position =  BACKSPIKE_POSITION_MIN;
    pBackSpike->CSFlag.Bit.ReachUpLimt = TRUE; 
    pBackSpike->CSFlag.Bit.ReachDownLimt = FALSE;
  }

  /*ʹ�ñ���������ȷ��λ��*/
  else if(CodeHis != CodeCur) 
  {
    for(i=0; i<BACKSPIKE_POSITION_CODE_MAPTAB_NUM; i++)
    {
      if((CodeHis == BackSpike_PositionCodeMapTab[i].HopCode1) && 
         (CodeCur == BackSpike_PositionCodeMapTab[i].HopCode2) )
      {
        Position = BackSpike_PositionCodeMapTab[i].Positon;
        break;
      }
      else if((CodeHis == BackSpike_PositionCodeMapTab[i].HopCode2) && 
              (CodeCur == BackSpike_PositionCodeMapTab[i].HopCode1) )
      {
        Position = BackSpike_PositionCodeMapTab[i].Positon;
        break;
      }
    }

    pBackSpike->CSFlag.Bit.ReachUpLimt   = FALSE;    /*���벻���ڼ���λ�ã�������ޱ�ʶ*/
    pBackSpike->CSFlag.Bit.ReachDownLimt = FALSE;
  }
  else
  {
    //Position = pBackSpike->PositionRealVal; /*û�������䣬�򱣳�ԭλ��*/
    pBackSpike->CSFlag.Bit.ReachUpLimt   = FALSE;    /*���벻���ڼ���λ�ã�������ޱ�ʶ*/
    pBackSpike->CSFlag.Bit.ReachDownLimt = FALSE;
  }

  CodeHis = CodeCur;
  return Position; 
}

/*
************************************************************************************************************************
* �������� : BackSpike_PositionIOCheck                                                                                                         
* �������� : λ�� IO�ڵļ��                                                                                            
* ������� : ExePeriod -- ������ִ������                                                                                                 
* ���ز��� : ��                                                                                             
* ����˵�� : ��                                                                                                         
************************************************************************************************************************
*/
void BackSpike_PositionIOCheck(Ticker_t ExePeriod)
{
  static uint8_t StableIOCode;                                      /*�ȶ��ı���*/
  static uint8_t StableStat;                                        /*״̬�ȶ�ͳ��*/
  static uint8_t IOCode = B(00);                                  /*Ҫ��λ�������ȼ����ʼΪ��׶�*/


  /*��ʱ���и��ţ����������״̬�ȶ����ж�------------------------*/
  if(StableIOCode != (BSP_IO_ReadInput_BackSpikePosition() & B(11)))
  {
    StableStat = 0;                                                 /*�����仯���ʾ���ȶ�*/
    StableIOCode = BSP_IO_ReadInput_BackSpikePosition() & B(11);    /*������*/
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
  if(pBackSpike->PositionMonitor.PositionCode == IOCode)            /*λ��û�ı�*/
  {
    if(ON == pBackSpike->CSFlag.Bit.Run)                            /*���������ʱ���ۼӴ�����ʧ��ʱ��*/
    {
      if(pBackSpike->PositionMonitor.SensorLostTimeMs <= BACKSPIKE_POSITION_SENSOR_LOST_TIME_THRESHOLD) /*δ����ʧ������ʱ��*/
      {
        pBackSpike->PositionMonitor.SensorLostTimeMs += ExePeriod;
      }
      else
      {
        pBackSpike->CSFlag.Bit.PositionSensorFault = FAULT;         /*λ�ô��������ϣ����ֺ󣬳��򲻻����㣬����λ�����ϵ������*/
      }
    }
    else
    {
      pBackSpike->PositionMonitor.SensorLostTimeMs = 0;             /*���㴫����ʧ��ʱ��*/
    }
  }
  else  /*λ�øı�*/
  { 
    pBackSpike->PositionMonitor.SensorLostTimeMs = 0;	              /*���㴫����ʧ��ʱ��*/
  }


  /*λ����ر����ж������--------------------------------------------*/
  pBackSpike->PositionRealVal = BackSpike_PositionCodeMap(IOCode);
  if(BACKSPIKE_POSITION_MIN == pBackSpike->PositionRealVal)       /*�λ��*/
  {
    pBackSpike->CSFlag.Bit.PositionResetOK = TRUE;                /*λ�ø�λ���*/
  }

  if((BACKSPIKE_ACTION_UP == pBackSpike->Action) && (pBackSpike->CSFlag.Bit.ReachUpLimt))
  {
    BackSpike_SetAction(BACKSPIKE_ACTION_STOP);                     /*�ﵽ����λ������ִ�������˶�*/
  }

  if((BACKSPIKE_ACTION_DOWN == pBackSpike->Action) && (pBackSpike->CSFlag.Bit.ReachDownLimt))
  {
    BackSpike_SetAction(BACKSPIKE_ACTION_STOP);                     /*�ﵽ����λ������ִ�������˶�*/
  }

  pBackSpike->PositionMonitor.PositionCode = IOCode;                /*��¼�±���*/
}

#endif /*���� #if(BACKSPIKE_POSITION_DETECT_MODE == BACKSPIKE_POSITION_DETECT_BY_CODE)*/



#if (BACKSPIKE_POSITION_DETECT_MODE == BACKSPIKE_POSITION_DETECT_BY_COUNT) /*λ�ü��ʹ�ü�����ʽ*/
/*
************************************************************************************************************************
* �������� : BackSpike_CountIOCheck_CB                                                                                                         
* �������� : λ�� ����IO�ڼ��  �Ļص�����                                                                                           
* ������� : ��                                                                                    
* ���ز��� : ��                                                                                             
* ����˵�� : �ú���ͨ�� BSP_IO_InputInterrupt_RegCB_BackSpikeCount(BackSpike_CountIOCheck_CB);����ע���BSP��                                                                                                         
************************************************************************************************************************
*/
static void BackSpike_CountIOCheck_CB(void)
{
  /*_COUNT_MIN+3���������������Ƹ�ͣ��ʱ�򣬼���ֵ������0������ӿ쵽0�Ĵ���*/
  MotorCountUpdata(&pBackSpike->PositionMonitor.PositionCountCur, 
                   pBackSpike->PositionMonitor.CountDirection, 
                   BACKSPIKE_COUNT_MAX, BACKSPIKE_COUNT_MIN+3);
}

/*
************************************************************************************************************************
* �������� : BackSpike_PositionIOCheck                                                                                                         
* �������� : λ�� IO�ڵļ��                                                                                   
* ������� : ExePeriod -- ������ִ������                                                                                  
* ���ز��� : ��                                                                                             
* ����˵�� : ��                                                                                                       
************************************************************************************************************************
*/
void BackSpike_PositionIOCheck(Ticker_t ExePeriod)
{
  static  Ticker_t ReachMinCountMs;
  
  /*�������������ϼ��---------------------------------------------*/
  if(pBackSpike->PositionMonitor.PositionCountHis == pBackSpike->PositionMonitor.PositionCountCur)  /*�����ޱ仯*/
  {
    if(ON == pBackSpike->CSFlag.Bit.Run)                                             /*�Ƹ˿���*/
    {
      if(pBackSpike->PositionMonitor.SensorLostTimeMs <= BACKSPIKE_COUNT_SENSOR_LOST_TIME_THRESHOLD)
      {
        pBackSpike->PositionMonitor.SensorLostTimeMs += ExePeriod;                   /*���������ʱ���ۼӼ���������ʧ��ʱ��*/
      }
      else
      {
        BackSpike_SetAction(BACKSPIKE_ACTION_STOP);                                  /*����һ��ֹͣ����ֹͣ����˶�*/

        if(FALSE == pBackSpike->CSFlag.Bit.PositionResetOK)                          /*λ�û�δ��λ��ɣ�����ϵ�Ҫ���ҳ�ʼλ��*/
        {
          pBackSpike->CSFlag.Bit.PositionResetOK = TRUE;                             /*λ�ø�λ���*/
          pBackSpike->PositionMonitor.PositionCountCur = BACKSPIKE_COUNT_MIN;        /*����λ�ö�Ҫ��������ֵ*/
          pBackSpike->PositionRealVal = BACKSPIKE_POSITION_MIN;
        }
        else  //if(TRUE == pBackSpike->CSFlag.Bit.PositionResetOK)                   /*λ���Ѿ���λ��ɵ�*/
        {
          if((pBackSpike->PositionSetVal > BACKSPIKE_POSITION_MIN) &&                /*Ҫ�˶����м��λ�õ�*/
             (pBackSpike->PositionSetVal < BACKSPIKE_POSITION_MAX) )
          {
            pBackSpike->CSFlag.Bit.CountFault = TRUE;                                /*�м�λ�õ���ּ���ֹͣ�����ʾ����������������*/
          }
          else if(BACKSPIKE_POSITION_MIN == pBackSpike->PositionSetVal)              /*Ҫ�˶�����Сλ��*/
          {
            if(pBackSpike->PositionMonitor.PositionCountCur > BACKSPIKE_COUNT_PER_SEGMENT)
            {
              pBackSpike->CSFlag.Bit.CountFault = TRUE;                              /*��Сλ�ü���ֵ����С���ʾ����������������*/
            }
            pBackSpike->PositionMonitor.PositionCountCur = BACKSPIKE_COUNT_MIN;      /*����λ�ö�Ҫ��������ֵ*/
          }
          else //if(BACKSPIKE_POSITION_MAX == pBackSpike->PositionSetVal)            /*Ҫ�˶������λ��*/     
          {
            if(pBackSpike->PositionMonitor.PositionCountCur < (BACKSPIKE_COUNT_MAX - BACKSPIKE_COUNT_PER_SEGMENT))
            {
              pBackSpike->CSFlag.Bit.CountFault = TRUE;                              /*���λ�ü���ֵ���������ʾ����������������*/
            }
            pBackSpike->PositionMonitor.PositionCountCur = BACKSPIKE_COUNT_MAX;      /*����λ�ö�Ҫ��������ֵ*/
          }
        }
      }  
      
      pBackSpike->CSFlag.Bit.CountFault &= pBackSpike->CSFlag.Bit.CountFaultCheckSw; /*��⿪����Ч�Ĳ��澯*/
    }
    else //if(OFF == pBackSpike->CSFlag.Bit.Run)                                     /*�Ƹ�û��*/
    {
      pBackSpike->PositionMonitor.SensorLostTimeMs = 0;                              /*�������������ʧ��ʱ��*/
    }
  }
  else //if(pBackSpike->PositionMonitor.PositionCountHis != pBackSpike->PositionMonitor.PositionCountCur)   /*�����б仯*/
  {
    pBackSpike->PositionMonitor.PositionCountHis = pBackSpike->PositionMonitor.PositionCountCur;
    pBackSpike->PositionMonitor.SensorLostTimeMs = 0;                                /*�������������ʧ��ʱ��*/
  }

    
  /*�ɼ���ֵ�������ǰ��λ�õ�---------------------------------------------------------------*/
  if(BACKSPIKE_COUNT_MIN == pBackSpike->PositionMonitor.PositionCountCur) 
  {
    if(ReachMinCountMs < 400)        /*����ʼλ�ö�����400ms��У��ʱ��*/
    {
      ReachMinCountMs += ExePeriod;
    }
    else
    {
      pBackSpike->PositionRealVal          = BACKSPIKE_POSITION_MIN;
      pBackSpike->CSFlag.Bit.ReachUpLimt   = TRUE;                                     /*���Ｋ��λ��*/
      pBackSpike->CSFlag.Bit.ReachDownLimt = FALSE;                                
    }
  }
  else if(BACKSPIKE_COUNT_MAX == pBackSpike->PositionMonitor.PositionCountCur)
  {
    ReachMinCountMs = 0;
    pBackSpike->PositionRealVal          = BACKSPIKE_POSITION_MAX;
    pBackSpike->CSFlag.Bit.ReachDownLimt = TRUE;                                     /*���Ｋ��λ��*/
    pBackSpike->CSFlag.Bit.ReachUpLimt   = FALSE;                               
  }
  else
  {
    ReachMinCountMs = 0;
    pBackSpike->CSFlag.Bit.ReachUpLimt   = FALSE;                                    /*�����ڼ���λ��*/
    pBackSpike->CSFlag.Bit.ReachDownLimt = FALSE;                                    /*�����ڼ���λ��*/

    if(OFF == pBackSpike->CSFlag.Bit.Run)
    {
      return;                                                                        /*�����תʱ���Ÿ��¼���λ��ֵ*/
    }
    
    if(POSITION_COUNT_INC == pBackSpike->PositionMonitor.CountDirection)             /*��������*/
    {
      pBackSpike->PositionRealVal = pBackSpike->PositionMonitor.PositionCountCur/BACKSPIKE_COUNT_PER_SEGMENT;
    }
    else //if(POSITION_COUNT_DEC == pBackSpike->PositionMonitor.CountDirection)      /*��������*/
    {
      pBackSpike->PositionRealVal = pBackSpike->PositionMonitor.PositionCountCur/BACKSPIKE_COUNT_PER_SEGMENT + 1;
    }
  }
}

#endif  /* ����if(BACKSPIKE_POSITION_DETECT_MODE == BACKSPIKE_POSITION_DETECT_BY_COUNT) */


/*
************************************************************************************************************************
* �������� : BackSpike_OverCurrentIOCheck                                                                                                         
* �������� : �Ƹ˹����� IO�ڵļ��                                                                               
* ������� : ExePeriod -- ������ִ������                                                                                  
* ���ز��� : ��                                                                                             
* ����˵�� : ��                                                                                                       
************************************************************************************************************************
*/
void BackSpike_OverCurrentIOCheck(Ticker_t ExePeriod)
{
  uint8_t IOCode;

  IOCode = BSP_IO_ReadInput_BackSpikeOverCurrent(); 
  if(BACKSPIKE_OVER_CURRENT_LEVEL == IOCode)
  {
    if(pBackSpike->OverCurrentTimeMs <= BACKSPIKE_OVER_CURRENT_TIME_THRESHOLD)
    {
      pBackSpike->OverCurrentTimeMs += ExePeriod;
    }
    else
    {
      pBackSpike->CSFlag.Bit.OverCurrentFault = FAULT; 
    }
  }
  else
  {
    pBackSpike->OverCurrentTimeMs = 0;
  }
}


/*
************************************************************************************************************************
* �������� : BackSpike_PauseOn                                                                                                         
* �������� : ��ͣ�Ƹ�                                                                            
* ������� : ��                                                                                
* ���ز��� : ��                                                                                             
* ����˵�� : ������������ת�����ֹͣ������ת��
*            ֻ�н����ͣ��������������ת��                                                                                                      
************************************************************************************************************************
*/
void BackSpike_PauseOn(void)
{
  if(pBackSpike->CSFlag.Bit.Pause < 0x1F)
  {
    pBackSpike->CSFlag.Bit.Pause++;
  }
}

/*
************************************************************************************************************************
* �������� : BackSpike_PauseOff                                                                                                         
* �������� : �����ͣ�Ƹ�                                                                        
* ������� : ��                                                                                
* ���ز��� : ��                                                                                             
* ����˵�� : ������������ת�����ֹͣ������ת��
*            ֻ�н����ͣ��������������ת��                                                                                                      
************************************************************************************************************************
*/
void BackSpike_PauseOff(void)
{
  if(pBackSpike->CSFlag.Bit.Pause > 0)
  {
    pBackSpike->CSFlag.Bit.Pause--;
  }
}


/*
************************************************************************************************************************
* �������� : BackSpike_SetAction                                                                                                         
* �������� : �����Ƹ�Ҫִ�еĶ���                                                                  
* ������� : Action --> ��������ȡֵ��
*                       BACKSPIKE_ACTION_UP
*                       BACKSPIKE_ACTION_DOWN
*                       BACKSPIKE_ACTION_STOP                                                                                
* ���ز��� : ��                                                                                             
* ����˵�� : ��                                                                                               
************************************************************************************************************************
*/
void BackSpike_SetAction(uint8_t Action)
{
  if((Action != BACKSPIKE_ACTION_UP)   &&
     (Action != BACKSPIKE_ACTION_DOWN) &&
     (Action != BACKSPIKE_ACTION_STOP) )
  {
    Action = BACKSPIKE_ACTION_STOP;       /*����������Ч����ִ��ֹͣ����*/
  }
  
  if((BACKSPIKE_ACTION_UP == Action) && (pBackSpike->CSFlag.Bit.ReachUpLimt))
  {
    return;                               /*�ﵽ����λ������ִ�������˶�*/
  }
  
  if((BACKSPIKE_ACTION_DOWN == Action) && (pBackSpike->CSFlag.Bit.ReachDownLimt))
  {
    return;                               /*�ﵽ����λ������ִ�������˶�*/
  }

  if(TRUE == pBackSpike->CSFlag.Bit.Locked)  
  {
    return;                               /*��ﱻ������ִ���κζ���*/
  }

  if(Action != BACKSPIKE_ACTION_STOP) 
  {
    pBackSpike->CSFlag.Bit.Work = TRUE;   /*������Ч����ʼ����*/
  }
  else
  {
    pBackSpike->CSFlag.Bit.Work = FALSE;  /*������ЧЧ���򲻹���*/
  }

  pBackSpike->Action = Action;
}

/*
************************************************************************************************************************
* �������� : BackSpike_GetPosition                                                                                                         
* �������� : ��ȡ�Ƹ�λ��                                                           
* ������� : ��                                                                               
* ���ز��� : �Ƹ˵�ǰλ��                                                                                            
* ����˵�� : ��                                                                                               
************************************************************************************************************************
*/
uint8_t BackSpike_GetPosition(void)
{
  return pBackSpike->PositionRealVal;
}

/*
************************************************************************************************************************
* �������� : BackSpike_SetPosition                                                                                                         
* �������� : �����Ƹ�λ��                                                         
* ������� : Position --> �Ƹ� ͣ��λ��
*                         ����ֵ��PKEEP          -- ���ֵ�ǰλ�ò�����
*                                 �����������ֵ -- �˶���������ꡣ                                                                                
* ���ز��� : ��                                                                                       
* ����˵�� : ��                                                                                               
************************************************************************************************************************
*/
void BackSpike_SetPosition(uint8_t Position)
{
  if((Position > BACKSPIKE_POSITION_MAX) &&(Position != PKEEP)) 
  {
    Position = BACKSPIKE_POSITION_MAX;
  }

  pBackSpike->PositionSetVal = Position; 
}

/*
************************************************************************************************************************
* �������� : BackSpike_PositionHandle                                                                                                         
* �������� : �Ƹ�ͣ��λ�ô���                                                    
* ������� : ExePeriod -- ������ִ������                                                                     
* ���ز��� : ��                                                                                      
* ����˵�� : λ�õļ��㣬������ȫ���ö�λ��IO�����Ʊ����⣬
*            ����ֻ��ʹ��  �ο���  ���  ��ǰ�������������Ʊ��������㡣
*            ��ˣ����ҵ��ο�����ǰ���޷���ȷ��֪��ǰλ�á�                                                                                               
************************************************************************************************************************
*/
void BackSpike_PositionHandle(Ticker_t ExePeriod)
{
  if(FALSE == pBackSpike->CSFlag.Bit.PositionResetOK)                /*λ�û�û��λ������û�ҵ�λ�ü���ο���*/
  {
    BackSpike_SetAction(BACKSPIKE_ACTION_UP);
  }
  else //if(TRUE == pBackSpike->CSFlag.Bit.PositionResetOK)          /*λ���Ѿ���λ����λ�ü���ο�����ȷ��*/
  {
    if(PKEEP == pBackSpike->PositionSetVal)                          /*λ�ñ���*/
    {
      BackSpike_SetAction(BACKSPIKE_ACTION_STOP);
    }
    else                                                             /*����λ��*/
    {
      if(BACKSPIKE_POSITION_MAX == pBackSpike->PositionSetVal)       /*����λ�� ��������*/
      {
        if(FALSE == pBackSpike->CSFlag.Bit.ReachDownLimt)
        {
          BackSpike_SetAction(BACKSPIKE_ACTION_DOWN);
        }
        else
        {
          BackSpike_SetAction(BACKSPIKE_ACTION_STOP);
        }
      }
      else if(BACKSPIKE_POSITION_MIN == pBackSpike->PositionSetVal)  /*����λ�� ��������*/
      {
        if(FALSE == pBackSpike->CSFlag.Bit.ReachUpLimt)
        {
          BackSpike_SetAction(BACKSPIKE_ACTION_UP);
        }
        else
        {
          BackSpike_SetAction(BACKSPIKE_ACTION_STOP);
        }
      }
      else if(pBackSpike->PositionSetVal == pBackSpike->PositionRealVal)
      {
        BackSpike_SetAction(BACKSPIKE_ACTION_STOP);
      }
      else if(pBackSpike->PositionSetVal > pBackSpike->PositionRealVal)
      {
        BackSpike_SetAction(BACKSPIKE_ACTION_DOWN);
      }
      else //(pBackSpike->PositionSetVal < pBackSpike->PositionRealVal)
      {
        BackSpike_SetAction(BACKSPIKE_ACTION_UP);
      }
    }
  }
}


/*
************************************************************************************************************************
* �������� : BackSpike_ActionHandle                                                                                                         
* �������� : ��ﶯ������                                           
* ������� : ExePeriod -- ������ִ������                                                                     
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/
void BackSpike_ActionHandle(Ticker_t ExePeriod)
{
  static uint8_t   ActionHis = 0xFF;                                      /*��ʷ����״̬*/


  /*����״̬�ĸı��ж�------------------------------------*/
  if(ActionHis != pBackSpike->Action)
  {
    pBackSpike->CSFlag.Bit.Run = OFF;                                     /*�����ı䣬����ֹͣ���*/
    if(ActionHis != BACKSPIKE_ACTION_STOP)
    {
      pBackSpike->StateCtrlTimeMs = 0;                                    /*��<-->�� �� ��/��-->ֹͣ��������ʱ��*/
    }
    ActionHis = pBackSpike->Action;
  }

  do
  {
    /*��ͣ��ֹͣ���-----------------------------------------*/
    if(pBackSpike->CSFlag.Bit.Pause > 0)
    {
      pBackSpike->CSFlag.Bit.Run = OFF;  
      pBackSpike->PWMFinalSetVal = BACKSPIKE_PWM_MIN;    /*��ͣ�����������Ҳ��Ҫ������*/
      break;
    }

    /* �����쳣����ֹͣ���-------------------------------------*/
    if((FAULT == pBackSpike->CSFlag.Bit.PositionCodeFault)   ||           /*λ�ñ������*/
       (FAULT == pBackSpike->CSFlag.Bit.PositionSensorFault) ||           /*λ�ô���������*/
       (FAULT == pBackSpike->CSFlag.Bit.CountFault)          ||           /*��������*/
       (FAULT == pBackSpike->CSFlag.Bit.OverCurrentFault)    )            /*����������*/
    {
      pBackSpike->CSFlag.Bit.Locked = TRUE;                               /*�쳣���������*/
      pBackSpike->CSFlag.Bit.Run    = OFF;                                /*�쳣��ͣ���*/
      pBackSpike->CSFlag.Bit.Work   = FALSE;  
      pBackSpike->StateCtrlTimeMs = 0;
      break;
    }

    /*�������--------------------------------------------------*/
    if(pBackSpike->Action != BACKSPIKE_ACTION_STOP)
    {
      if(pBackSpike->StateCtrlTimeMs < 5000)
      {
        pBackSpike->StateCtrlTimeMs += ExePeriod; 
      }

      if(pBackSpike->StateCtrlTimeMs <= BACKSPIKE_DIRECTION_TIME_MS)      /*�ȹص��------------*/
      {
        pBackSpike->CSFlag.Bit.Run = OFF;
        pBackSpike->PWMFinalSetVal = 0;                   /*������*/
      }
      else if(pBackSpike->StateCtrlTimeMs <= BACKSPIKE_REVERSE_TIME_MS)   /*�л�����------------*/
      {
        if(BACKSPIKE_ACTION_UP == pBackSpike->Action)
        {
          pBackSpike->UpRunTimeMs                    = 0; 
          pBackSpike->CSFlag.Bit.Direction           = BACKSPIKE_DIRECTION_UP;
          pBackSpike->PositionMonitor.CountDirection = POSITION_COUNT_DEC;
        }
        else //if(BACKSPIKE_ACTION_DOWN == pBackSpike->Action)
        {
          pBackSpike->DownRunTimeMs                  = 0; 
          pBackSpike->CSFlag.Bit.Direction           = BACKSPIKE_DIRECTION_DOWN;
          pBackSpike->PositionMonitor.CountDirection = POSITION_COUNT_INC;
        }
        pBackSpike->PWMFinalSetVal = BACKSPIKE_PWM_MIN;     /*������*/
      }
      else /*�����ת---------------------------------------------------------------------------*/
      {
        pBackSpike->CSFlag.Bit.Run = ON;
        if(pBackSpike->PWMFinalSetVal < BACKSPIKE_PWM_MAX)  /*������*/
        {
          pBackSpike->PWMFinalSetVal += BACKSPIKE_PWM_FIXED_STEPING_VAL;
        }
        else
        {
          pBackSpike->PWMFinalSetVal = BACKSPIKE_PWM_MAX;
        }

        if(BACKSPIKE_ACTION_UP == pBackSpike->Action)
        {
          if(pBackSpike->UpRunTimeMs < (0xFFFF-ExePeriod))                /*-ExePeriod :��ֹ�Ӳ������*/
          {
            pBackSpike->UpRunTimeMs += ExePeriod; 
          }
        }
        else //if(BACKSPIKE_ACTION_DOWN == pBackSpike->Action)
        {
          if(pBackSpike->DownRunTimeMs < (0xFFFF-ExePeriod))              /*-ExePeriod :��ֹ�Ӳ������*/
          {
            pBackSpike->DownRunTimeMs += ExePeriod; 
          }
        }
        pBackSpike->RunTimeMs += ExePeriod;                               /*ͳ�������תʱ��*/
      }
    }
    else /*pBackSpike->Action == BACKSPIKE_ACTION_STOP*/
    {
      pBackSpike->CSFlag.Bit.Run = OFF;

      if(pBackSpike->StateCtrlTimeMs < BACKSPIKE_DIRECTION_TIME_MS)       /*ֹͣʱ�����ۼ�ֹͣʱ�䣬Ҫ����ʱ���ɼӿ�����*/
      {
        pBackSpike->StateCtrlTimeMs += ExePeriod; 
      }
    }
  }while(0);

  BSP_IO_SetOutput_BackSpikeCtrl(pBackSpike->CSFlag.Bit.Run, pBackSpike->CSFlag.Bit.Direction, pBackSpike->PWMFinalSetVal);
}


/*
************************************************************************************************************************
* �������� : BackSpike_Init                                                                                                         
* �������� : �Ƹ˳�ʼ��                                   
* ������� : ��                                                             
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/
BackSpike_t* BackSpike_Init(void)
{
  memset(pBackSpike, 0, sizeof(BackSpike_t));                                 /*������������*/
  BackSpike_ResetPosition();
  #if (BACKSPIKE_POSITION_DETECT_MODE == BACKSPIKE_POSITION_DETECT_BY_COUNT)  /*λ�ü��ʹ�ü�����ʽ*/
    BSP_IO_InputInterrupt_RegCB_BackSpikeCount(BackSpike_CountIOCheck_CB);    
  #endif
  
  return pBackSpike;
}


/*
************************************************************************************************************************
* �������� : BackSpike_GetCSFlag                                                                                                          
* �������� : ��� ���� �� ״̬ ��ʶ                                   
* ������� : ��                                                            
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/
BackSpikeCSFlag_t BackSpike_GetCSFlag(void)
{
  return pBackSpike->CSFlag;
}


/*
************************************************************************************************************************
* �������� : BackSpike_ResetPosition                                                                                                          
* �������� : ��λλ��                                    
* ������� : ��                                                             
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/
void BackSpike_ResetPosition(void)
{
  pBackSpike->CSFlag.Bit.PositionResetOK = FALSE;
  pBackSpike->PositionSetVal                   = BACKSPIKE_POSITION_MIN;    /*Ҫʹ�õĲο�λ��*/
  pBackSpike->PositionRealVal                  = BACKSPIKE_POSITION_MAX;    /*����ĵ�ǰλ��*/ 
  pBackSpike->PositionMonitor.PositionCountCur = BACKSPIKE_COUNT_MAX*2;     /*����ĵ�ǰλ�ü���*/ 
}

/*
************************************************************************************************************************
* �������� : BackSpike_SetCountFaultCheckSw                                                                                                          
* �������� : ���ü������ϼ�⿪��                                  
* ������� : Sw -- ON  ��
*                  OFF ��
* ���ز��� : ��                                                                                      
* ����˵�� : ��                                                                                             
************************************************************************************************************************
*/
void BackSpike_SetCountFaultCheckSw(uint8_t Sw)
{
  if((Sw != ON) && (Sw != OFF))
  {
    Sw = OFF;
  }
  pBackSpike->CSFlag.Bit.CountFaultCheckSw = Sw;
}
